#ifndef DISCRETIZATION_HPP
#define DISCRETIZATION_HPP

#include <memory>
#include "../helper.hpp"
#include "../processes/process.hpp"
#include "../random/normal.hpp"

using namespace std;

// To use the template parameter as a parameter of the template class P
template <typename T>
class Discretization
{

public:
    virtual ~Discretization() = default;

    Discretization(shared_ptr<Process<T>> process, string name) : process(process), name(name){};

    virtual std::shared_ptr<Path<T>> generatePath(int nsamples, T horizon)
    {
        process->resetState();
        auto path = std::make_shared<Path<T>>(nsamples + 1);
        (*path)[0] = process->initialState;
        T h = horizon / nsamples;
        for (int i = 1; i <= nsamples; ++i)
        {
            genNextPrice(h);
            (*path)[i] = process->priceState;
        }
        return path;
    }

    virtual void genNextPrice(T h, T Z = NormalDistribution<T>()())
    {
        process->priceState = {
            process->priceState.time + h,
            this->getNewPrice(h, Z)};
    }

    friend ostream &operator<<(ostream &o, const Discretization<T> &opt)
    {
        return opt.describe(o);
    }

    virtual ostream &describe(ostream &o) const
    {
        return o << "Discretization name: " << name << endl
                 << "Process: " << endl
                 << *process << endl;
    }

protected:
    shared_ptr<Process<T>> process;
    virtual T getNewPrice(T h, T Z) const = 0;

private:
    string name;
};

#endif
