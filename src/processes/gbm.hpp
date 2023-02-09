#ifndef BLACKSCHOLES_HPP
#define BLACKSCHOLES_HPP

#include <cmath>
#include <iostream>

#include "../random/normal.hpp"
#include "../helper.hpp"
#include "process.hpp"

template<typename T>
class BlackScholesProcess : public Process<T> {

public:
    T rate;
    T vol;
	BlackScholesProcess(State<T>& initialState, T rate, T vol):
		Process<T>(initialState, "Black-Scholes"), rate(rate), vol(vol){}

	virtual~BlackScholesProcess() = default;

	virtual T drift() const override {
		return rate * this->price();
	}

	virtual T diffusion() const override {
		return vol * this->price();
	}

    virtual T volatility() const override { return vol;}

	virtual std::ostream &describe(std::ostream &o) const override {
		return Process<T>::describe(o) <<
            "Rate       : " << rate << std::endl <<
		    "Volatility : " << vol << std::endl;
	}

protected:
	virtual T dDiffusion_dsigma() const override {
		return this->price();
	}

	virtual T dDiffusion_dx() const override {
		return vol;
	}

	virtual T dDrift_dr() const override {
		return this->price();
	}


	virtual T dDrift_dx() const override {
		return rate;
	}

	virtual T d2Diffusion_dx_dsigma() const override {
		return 1;
	}
};

#endif  // BLACKSCHOLES_HPP
