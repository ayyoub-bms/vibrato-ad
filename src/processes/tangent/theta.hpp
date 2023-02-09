#ifndef THETA_HPP
#define THETA_HPP

#include "tangent.hpp"

template<typename T>
class ThetaTangent : public TangentProcess<T> {

public:
    ThetaTangent(std::shared_ptr<Process<T>> parent, State<T> initialState) :
            TangentProcess<T>(parent, initialState, "Theta Tangent process") {}

    virtual~ThetaTangent() = default;

    virtual T drift() const override {
        return this->parent->dDrift_dt() + this->parent->dDrift_dx() * this->price();
    }

    virtual T diffusion() const override {
        return this->parent->dDiffusion_dt() + this->parent->dDiffusion_dx() * this->price();
    }

};

#endif  // THETA_HPP
