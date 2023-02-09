#ifndef VEGA_HPP
#define VEGA_HPP

#include "tangent.hpp"

template<typename T>
class VegaTangent : public TangentProcess<T> {

public:
    VegaTangent(std::shared_ptr<Process<T>>& parent, State<T> initialState) :
            TangentProcess<T>(parent, initialState, "Vega Tangent process") {}

    virtual~VegaTangent() = default;

    virtual T drift() const override {
        return this->parent->dDrift_dsigma() +
               this->parent->dDrift_dx() * this->price();
    }

    virtual T diffusion() const override {
        return this->parent->dDiffusion_dsigma() +
               this->parent->dDiffusion_dx() * this->price();
    }

};

#endif  // VEGA_HPP
