#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include "../instruments/option.hpp"
#include "../processes/process.hpp"
#include "../helper.hpp"

template <typename T>
class Pricer
{

public:
    std::shared_ptr<Option<T>> option;
    std::shared_ptr<Process<T>> process;
    std::unique_ptr<PricingResults<T>> results;
    Pricer(std::shared_ptr<Option<T>> option, std::shared_ptr<Process<T>> process)
        : option(option), process(process), results(std::make_unique<PricingResults<T>>()){};

    virtual ~Pricer() = default;
    virtual void compute() = 0;

    friend std::ostream &operator<<(std::ostream &o, Pricer<T> &pricer)
    {
        return pricer.displayResults(o);
    }

    virtual std::ostream &displayResults(std::ostream &o)
    {
        return o << *option << std::endl
                 << *process << std::endl
                 << "Premium : " << results->premium << std::endl
                 << "Delta   : " << results->delta << std::endl
                 << "Gamma   : " << results->gamma << std::endl
                 << "Vega    : " << results->vega << std::endl
                 << "Vanna   : " << results->vanna << std::endl
                 << "Volga   : " << results->volga << std::endl
                 << "Rho     : " << results->rho << std::endl
                 << "Theta   : " << results->theta << std::endl;
    };
};

#endif // ENGINE_HPP
