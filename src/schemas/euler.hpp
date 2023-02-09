#ifndef EULER_HPP
#define EULER_HPP

#include "discretization.hpp"
#include "../helper.hpp"

template <typename DType>
class EulerSchema : public Discretization<DType>
{

public:
    virtual ~EulerSchema() = default;
    EulerSchema(std::shared_ptr<Process<DType>> process) : Discretization<DType>(process, "Euler discretization") {}

protected:
    virtual DType getNewPrice(DType h, DType Z) const override
    {
        return this->process->price() +
               this->process->drift() * h +
               this->process->diffusion() * sqrt(h) * Z;
    }
};

#endif
