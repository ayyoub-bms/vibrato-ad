#ifndef RHO_HPP
#define RHO_HPP

#include "tangent.hpp"

template<typename T>
class RhoTangent : public TangentProcess<T> {

public:
    RhoTangent(std::shared_ptr<Process<T>> parent, State<T> initialState) :
            TangentProcess<T>(parent, initialState, "Rho Tangent process") {}

    virtual~RhoTangent() = default;

    virtual T drift() const override {
        return this->parent->dDrift_dr() +
        	   this->parent->dDrift_dx() * this->price();
    }

    virtual T diffusion() const override {
        return this->parent->dDiffusion_dr() +
               this->parent->dDiffusion_dx() * this->price();
    }

};

#endif  // RHO_HPP
