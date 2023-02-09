#ifndef VANNA_HPP
#define VANNA_HPP

#include <typeinfo>

#include "tangent.hpp"
#include "delta.hpp"
#include "vega.hpp"
#include "../../schemas/euler.hpp"

// TODO: Check the gamma tangent and correct the generation process
//

using namespace std;

template <typename T>
class VannaTangent : public TangentProcess<T>
{

private:
    shared_ptr<VegaTangent<T>> vegaPRocess;

    shared_ptr<EulerSchema<T>> discretization1;

public:
    VannaTangent(shared_ptr<Process<T>> parent, shared_ptr<VegaTangent<T>> vegaPRocess, State<T> initialState) : TangentProcess<T>(parent, initialState, "Vanna Tangent process"), vegaPRocess(vegaPRocess) {}
    virtual ~VannaTangent() = default;

    virtual T drift() const override
    {
        return (
            this->parent->d2Drift_dx2() * vegaPRocess->price());
    }

    virtual T diffusion() const override
    {
        return (
            this->parent->d2Diffusion_dx_dsigma() +
            this->parent->d2Diffusion_dx2() * vegaPRocess->price());
    }
};

#endif // VANNA_HPP
