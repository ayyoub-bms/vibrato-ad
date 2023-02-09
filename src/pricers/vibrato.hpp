#ifndef VIBRATO_HPP
#define VIBRATO_HPP

#include <cmath>
#include <memory>
#include <list>

#include "pricer.hpp"
#include "../helper.hpp"
#include "../random/normal.hpp"
#include "../processes/gbm.hpp"
#include "../schemas/euler.hpp"
#include "../processes/tangent/all.hpp"

using namespace std;

template <typename DType>
class Vibrato : public Pricer<DType>
{

public:
    DType r;
    int n;
    int M;
    int Mz;
    DType h;

    Vibrato(shared_ptr<Option<DType>> option, shared_ptr<Process<DType>> process, DType rate, int n, int M, int Mz) : Pricer<DType>(option, process), r(rate), n(n), M(M), Mz(Mz)
    {
        T = option->maturity;
        levelSchema = make_shared<EulerSchema<DType>>(process);
        deltaSchema = make_shared<EulerSchema<DType>>(deltaTProc);
        vegaSchema = make_shared<EulerSchema<DType>>(vegaTProc);
        rhoSchema = make_shared<EulerSchema<DType>>(rhoTProc);
        thetaSchema = make_shared<EulerSchema<DType>>(thetaTProc);
        vannaSchema = make_shared<EulerSchema<DType>>(vannaTProc);
        volgaSchema = make_shared<EulerSchema<DType>>(volgaTProc);
        h = T / n;
    }

    virtual ~Vibrato() = default;

    virtual void compute() override
    {
        DType premium = 0.;
        DType delta = 0.;
        DType theta = 0.;
        DType gamma = 0.;
        DType rho = 0.;
        DType vega = 0.;
        DType vanna = 0.;
        DType volga = 0.;

        DType discount = exp(-r * T);

        for (int i = 0; i < M; ++i)
        {
            this->process->resetState();
            vegaTProc->resetState();
            rhoTProc->resetState();
            deltaTProc->resetState();
            thetaTProc->resetState();
            vannaTProc->resetState();
            volgaTProc->resetState();

            for (int i = 0; i < n - 1; ++i)
            {
                DType Z = normal();

                vannaSchema->genNextPrice(h, Z);
                volgaSchema->genNextPrice(h, Z);

                deltaSchema->genNextPrice(h, Z);
                vegaSchema->genNextPrice(h, Z);
                rhoSchema->genNextPrice(h, Z);
                thetaSchema->genNextPrice(h, Z);
                levelSchema->genNextPrice(h, Z);
            }
            // Replication step
            DType price = this->process->price();
            DType vol = this->process->volatility();
            DType mu = price * (1 + r * h);
            DType sigma = price * vol * sqrt(h);

            DType subpremium = 0.;
            for (int j = 1; j <= Mz; j++)
            {
                subpremium += this->option->payoff(mu + sigma * normal());
            }
            // End of Replication step
            premium += subpremium / Mz;

            delta += _firstOrderVibrato(this->deltaTProc->mun(h),
                                        this->deltaTProc->dmun(h),
                                        this->deltaTProc->sigman(h),
                                        this->deltaTProc->dsigman(h));

            vega += _firstOrderVibrato(this->vegaTProc->mun(h),
                                       this->vegaTProc->dmun(h),
                                       this->vegaTProc->sigman(h),
                                       this->vegaTProc->dsigman(h));

            rho += _firstOrderVibrato(this->rhoTProc->mun(h),
                                      this->rhoTProc->dmun(h),
                                      this->rhoTProc->sigman(h),
                                      this->rhoTProc->dsigman(h));

            theta += _firstOrderVibrato(this->thetaTProc->mun(h),
                                        this->process->drift(),
                                        this->thetaTProc->sigman(h),
                                        this->process->diffusion() / 2 / sqrt(h));

            gamma += _secondOrderVibrato(this->deltaTProc->mun(h),
                                         this->deltaTProc->sigman(h),
                                         this->deltaTProc->dmun(h),
                                         this->deltaTProc->dsigman(h),
                                         this->deltaTProc->dmun(h),
                                         this->deltaTProc->dsigman(h));

            vanna += _secondOrderVibrato(this->vegaTProc->mun(h),
                                         this->vegaTProc->sigman(h),
                                         this->vegaTProc->dmun(h),
                                         this->vegaTProc->dsigman(h),
                                         this->deltaTProc->dmun(h),
                                         this->deltaTProc->dsigman(h),
                                         this->vannaTProc->dmun(h),
                                         this->vannaTProc->dsigman(h));

            volga += _secondOrderVibrato(this->vegaTProc->mun(h),
                                         this->vegaTProc->sigman(h),
                                         this->vegaTProc->dmun(h),
                                         this->vegaTProc->dsigman(h),
                                         this->vegaTProc->dmun(h),
                                         this->vegaTProc->dsigman(h));
        }
        this->results->premium = discount * premium / M;
        this->results->delta = discount * delta / M;
        this->results->vega = discount * vega / M;
        this->results->rho = discount * (rho - T * premium) / M;
        this->results->theta = discount * (theta - r * premium) / M;
        this->results->gamma = discount * gamma / M;
        this->results->vanna = discount * vanna / M;
        this->results->volga = discount * volga / M;
    }

private:
    DType T;
    shared_ptr<EulerSchema<DType>> levelSchema;
    shared_ptr<EulerSchema<DType>> deltaSchema;
    shared_ptr<EulerSchema<DType>> vegaSchema;
    shared_ptr<EulerSchema<DType>> rhoSchema;
    shared_ptr<EulerSchema<DType>> thetaSchema;
    shared_ptr<EulerSchema<DType>> vannaSchema;
    shared_ptr<EulerSchema<DType>> volgaSchema;

    NormalDistribution<DType> normal = NormalDistribution<DType>(0, 1);

    DType time = this->process->initialState.time;
    State<DType> deltaState = {time, 1};
    State<DType> vegaState = {time, 0};
    State<DType> thetaState = {time, 0};
    State<DType> rhoState = {time, 0};
    shared_ptr<DeltaTangent<DType>> deltaTProc = make_shared<DeltaTangent<DType>>(this->process, deltaState);
    shared_ptr<VegaTangent<DType>> vegaTProc = make_shared<VegaTangent<DType>>(this->process, vegaState);
    shared_ptr<RhoTangent<DType>> rhoTProc = make_shared<RhoTangent<DType>>(this->process, rhoState);
    shared_ptr<ThetaTangent<DType>> thetaTProc = make_shared<ThetaTangent<DType>>(this->process, thetaState);
    shared_ptr<VannaTangent<DType>> vannaTProc = make_shared<VannaTangent<DType>>(this->process, vegaTProc, vegaState);
    shared_ptr<VolgaTangent<DType>> volgaTProc = make_shared<VolgaTangent<DType>>(this->process, vegaTProc, vegaState);

    DType _firstOrderVibrato(DType mun, DType dmun, DType sigman, DType dsigman)
    {
        DType Z;
        DType espMu = 0;
        DType espSigma = 0;
        DType pplus;
        DType pminus;
        DType pmu;
        for (int j = 0; j < Mz; j++)
        {
            Z = normal();
            pplus = this->option->payoff(mun + sigman * Z);
            pminus = this->option->payoff(mun - sigman * Z);
            pmu = this->option->payoff(mun);
            espMu += Z * (pplus - pminus) / (2 * sigman);
            espSigma += (Z * Z - 1) * (pplus - 2 * pmu + pminus) / (2 * sigman);
        }
        return (dmun * espMu + dsigman * espSigma) / Mz;
    }

    DType _secondOrderVibrato(DType mun, DType sigman, DType mun1, DType sigman1, DType mun2, DType sigman2, DType mun12 = 0, DType sigman12 = 0)
    {
        DType s2 = pow(sigman, 2);
        DType espMuMu = 0;
        DType espMu2 = 0;

        DType espSigmaSigma = 0;
        DType espSigma2 = 0;
        DType espMuSigma = 0;

        DType Z;
        DType Z2;
        DType Z4;
        DType pplus;
        DType pminus;
        DType pmu;

        for (int j = 0; j < Mz; j++)
        {
            Z = normal();
            Z2 = pow(Z, 2);
            Z4 = pow(Z, 4);
            pplus = this->option->payoff(mun + sigman * Z);
            pminus = this->option->payoff(mun - sigman * Z);
            pmu = this->option->payoff(mun);
            espMu2 += Z * (pplus - pminus) / (2 * sigman);
            espMuMu += (Z2 - 1) * (pplus - 2 * pmu + pminus) / (2 * s2);
            espSigmaSigma += (Z4 - 5 * Z2 + 2) * (pplus - 2 * pmu + pminus) / (2 * s2);
            espSigma2 += (Z2 - 1) * (pplus - 2 * pmu + pminus) / (2 * sigman);
            espMuSigma += Z * (Z2 - 3) * (pplus - pminus) / (s2);
        }
        return (
                   mun1 * mun2 * espMuMu +
                   sigman1 * sigman2 * espSigmaSigma +
                   mun12 * espMu2 + sigman12 * espSigma2 +
                   (sigman1 * mun2 + sigman2 * mun1) * espMuSigma) /
               Mz;
    }
};

#endif // VIBRATO_HPP
