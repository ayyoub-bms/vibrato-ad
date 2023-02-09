#ifndef DELTA_HPP
#define DELTA_HPP

#include "tangent.hpp"

template<typename T>
class DeltaTangent : public TangentProcess<T> {

public:
    DeltaTangent(std::shared_ptr<Process<T>> parent, State<T> initialState) :
            TangentProcess<T>(parent, initialState, "Delta Tangent process") {}

    virtual~DeltaTangent() = default;

    virtual T drift() const override {
        return this->parent->dDrift_dx() * this->price();
    }

    virtual T diffusion() const override {
        return this->parent->dDiffusion_dx() * this->price();
    }
};

#endif  // DELTA_HPP
