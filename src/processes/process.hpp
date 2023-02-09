#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <memory>


#include "../helper.hpp"
#include "parameters.hpp"


using namespace std;


template<typename T>
class Process {

    template <typename T_> friend class Discretization;

    public:
        State<T> initialState;

        virtual ~Process() = default;
        Process(State<T>& initialState, string name) :
            initialState(initialState), priceState(initialState), name(name) {}

        virtual T drift() const = 0;
        virtual T diffusion() const = 0;
        virtual T volatility() const { return 1;};

        virtual State<T> currentState() const {
            return priceState;
        }
        virtual void resetState() {
            priceState = initialState;
        }

        virtual T price() const {
            return priceState.value;
        }

        friend ostream& operator<<(ostream &o, const Process<T> &opt) {
            return opt.describe(o);
        }

        virtual ostream& describe(ostream &o) const {
            return o << "Process name: " << name << endl << "Initial State: "
                    << initialState << endl << "Price State: " << priceState
                    << endl;
        }

        virtual T dDrift_dx() const {return 0;}
        virtual T dDrift_dt() const {return 0;}
        virtual T dDrift_dr() const {return 0;}
        virtual T d2Drift_dx2() const {return 0;}
        virtual T dDrift_dsigma() const {return 0;}

        virtual T dDiffusion_dr() const {return 0;}
        virtual T dDiffusion_dt() const {return 0;}
        virtual T dDiffusion_dx() const {return 0;}
        virtual T d2Diffusion_dx2() const {return 0;}
        virtual T dDiffusion_dsigma() const {return 0;}
        virtual T d2Diffusion_dx_dsigma() const {return 0;}
        virtual T d2Diffusion_dsigma2() const {return 0;}

    protected:
        State<T> priceState;
        string name;
    };


#endif  // PROCESS_HPP
