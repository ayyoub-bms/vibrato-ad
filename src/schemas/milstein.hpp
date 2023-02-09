#ifndef MILSTEIN_HPP
#define MILSTEIN_HPP

#include "discretization.hpp"
#include "../helper.hpp"

template <typename T>
class MilsteinSchema : public Discretization<T>
{

public:
    virtual ~MilsteinSchema() = default;
    MilsteinSchema(shared_ptr<Process<T>> process) : Discretization<T>(process, "Milstein discretization") {}

protected:
    virtual T getNewPrice(T h, T Z) const override
    {
        return this->process->price() +
               this->process->drift() * h +
               this->process->diffusion() * sqrt(h) * Z +
               this->process->diffusion() * this->process->dDiffusion_dx() * h * (Z * Z - 1) / 2;
    }
};

#endif
