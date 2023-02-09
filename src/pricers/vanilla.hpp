#ifndef ANALYTIC_BS_HPP
#define ANALYTIC_BS_HPP

#include <cmath>

#include "pricer.hpp"

#include "../random/normal.hpp"
#include "../processes/gbm.hpp"

template<typename DType>
class VanillaBS : public Pricer<DType> {

public:
    VanillaBS(std::shared_ptr<Option<DType>> option, std::shared_ptr<BlackScholesProcess<DType>> process) :
        Pricer<DType>(option, process) {};

    virtual~VanillaBS() = default;

    virtual void compute() override {
        auto process = static_pointer_cast<BlackScholesProcess<DType>>(this->process);

        DType S = process->price();
        DType r = process->rate;
        DType vol = process->vol;
        DType K = this->option->strike;
        DType T = this->option->maturity;
        DType discount = exp(-r * T);
        DType d1 = (log(S / K) + (r + 0.5 * vol * vol) * T) / (vol * sqrt(T));
        DType d2 = d1 - vol * sqrt(T);
        DType nd1 = normal.cdf(d1);
        DType nd2 = normal.cdf(d2);
        DType pd1 = normal.pdf(d1);

        if (this->option->type == OptionType::Call) {
            this->results->premium = S * nd1 - K * discount * nd2;
            this->results->delta = nd1;
            this->results->rho = K * T * discount * nd2;
            this->results->theta = S * pd1 * vol / (2 * sqrt(T)) + r * K * discount * nd2;
        } else {
            this->results->premium = S * (nd1 - 1) + discount * K * (1 - nd2);
            this->results->delta = nd1 - 1;
            this->results->rho = K * T * discount * (nd2 - 1);
            this->results->theta = S * pd1 * vol / (2 * sqrt(T)) - r * K * discount * (1 - nd2);
        }
        this->results->gamma = pd1 / (S * vol * sqrt(T));
        this->results->vega = S * pd1 * sqrt(T);
        this->results->vanna = -pd1 * d2 / vol;
        this->results->volga = S * sqrt(T) * pd1 * d1 * d2 / (vol);
    }
private:
    NormalDistribution<DType> normal = NormalDistribution<DType>(0, 1);
};


#endif  // ANALYTIC_BS_HPP
