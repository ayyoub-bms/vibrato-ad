#ifndef CIR_HPP
#define CIR_HPP

#include "process.hpp"
#include "../random/normal.hpp"
#include "parameters.hpp"

template<typename T>
class CIRProcess: public Process<T> {

public:
    T speed;
    T mean;
    T vol;
	virtual ~CIRProcess() = default;
	CIRProcess(State<T>& initialState, T kappa, T theta, T sigma):
			Process<T>(initialState, "Cox-Ingeresoll-Ross"), speed(kappa), mean(theta), vol(sigma){
            if (2 * kappa * theta < sigma * sigma ) {
                std::cout << "WARNING: Feller condition unsatisfied. Some discretization schemas might not work properly"
                          << std::endl;
            }
        }

	virtual T drift() const override {
		return speed * (mean - this->price());
	}

	virtual T diffusion() const override {
		return vol  * sqrt(this->price());
	}

    virtual T volatility() const override {return vol;}
	virtual std::ostream& describe(std::ostream &o) const {
		return Process<T>::describe(o) <<
            "Kappa :" << speed << std::endl <<
			"Theta :" << mean << std::endl <<
		    "Sigma :" << vol << std::endl;
	}
};

#endif // CIR_HPP
