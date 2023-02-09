#ifndef ANALYTIC_DIGITAL_BS_HPP
#define ANALYTIC_DIGITAL_BS_HPP

#include <cmath>

#include "../random/normal.hpp"
#include "../processes/gbm.hpp"
#include "pricer.hpp"

template<typename DType>
class DigitalBS : public Pricer<DType> {

public:
    DigitalBS(std::shared_ptr<Option<DType>> option, std::shared_ptr<BlackScholesProcess<DType>> process)
        :Pricer<DType>(option, process) {};

    virtual~DigitalBS() = default;

    virtual void compute() override {
        auto process = static_pointer_cast<BlackScholesProcess<DType>>(this->process);
        DType r = process->rate;
        DType S = process->initialState.value;
        DType vol = process->vol;
        DType K = this->option->strike;
        DType T = this->option->maturity;
        DType discount = exp(-r * T);
        DType d1 = (log(S / K) + (r + 0.5 * vol * vol) * T) / (vol * sqrt(T));
        DType d2 = d1 - vol * sqrt(T);
        DType nd2 = normal.cdf(d2);
        DType pd2 = normal.pdf(d2);
        DType crho = discount * pd2 * sqrt(T) / vol - T * discount * nd2;
        DType ctheta = discount * nd2 * r;
        DType otype = this->option->dtype();
        ctheta += discount * pd2 * (d1 / (2 * T) - r / (vol * sqrt(T)));

        if (this->option->type == OptionType::Call) {
            this->results->premium = discount * nd2;
            this->results->rho = crho;
            this->results->theta = -ctheta;
        } else {
            this->results->premium =  discount * (1 - nd2);
            this->results->rho = -T * discount - crho;
            this->results->theta = ctheta - r * discount;
        }

        DType disc_pd2 = otype * discount * pd2;
        this->results->delta = disc_pd2 / (vol * sqrt(T) * S);
        this->results->vega = -d1 * disc_pd2 / vol;
        this->results->gamma = -disc_pd2 * d1 / (vol * vol * S * S * T);
        this->results->vanna = disc_pd2 * (d1 * d2 - 1) / (S * vol * vol * sqrt(T));
        this->results->volga = -disc_pd2 * (d1 * d1 * d2 - d1 - d2) / (vol * vol);
    }

private:
    NormalDistribution<DType> normal = NormalDistribution<DType>(0, 1);
};


#endif  // ANALYTIC_iDIGITAL_BS_HPP
