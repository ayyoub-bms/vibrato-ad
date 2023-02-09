#ifndef EXACT_BSDISCRETIZATION_HPP
#define EXACT_BSDISCRETIZATION_HPP

#include "discretization.hpp"
#include "../helper.hpp"
#include "../processes/gbm.hpp"

template <typename T>
class ExactBSSchema : Discretization<T>
{

public:
    virtual ~ExactBSSchema() = default;
    ExactBSSchema(std::shared_ptr<BlackScholesProcess<T>> process) : Discretization<T>(process, "Exact Black-Scholes discretization") {}

protected:
    virtual T getNewPrice(T h, T Z) const override
    {
        auto process = static_pointer_cast<BlackScholesProcess<T>>(this->process);
        T v = process->vol;
        T r = process->rate;
        T S = process->price();
        return S * exp((r - 0.5 * v * v) * h + v * sqrt(h) * Z);
    }
};

#endif
