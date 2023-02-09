#ifndef VOLGA_HPP
#define VOLGA_HPP

#include <memory>

#include "tangent.hpp"
#include "vega.hpp"
#include "../../schemas/euler.hpp"
using namespace std;


template<typename T>
class VolgaTangent : public TangentProcess<T> {

private:
    shared_ptr<VegaTangent<T>> vegaProcess;

public:
    VolgaTangent(shared_ptr<Process<T>> parent, shared_ptr<VegaTangent<T>> vegaTangent, State<T> initialState) :
            TangentProcess<T>(parent, initialState, "Volga Tangent process"), vegaProcess(vegaTangent){}

    virtual~VolgaTangent() = default;

    virtual T drift() const override {
        return (
                this->parent->dDrift_dx() * this->price() +
                this->parent->d2Drift_dx2() * vegaProcess->price() * vegaProcess->price()
        );
    }

    virtual T diffusion() const override {
        return (
                this->parent->d2Diffusion_dsigma2() + 
                2 * this->parent->d2Diffusion_dx_dsigma() * vegaProcess->price() +
                this->parent->d2Diffusion_dx2() * vegaProcess->price() * vegaProcess->price() +
                this->parent->dDiffusion_dx() * this->price()
        );
    }

};


#endif  // VOLGA_HPP
