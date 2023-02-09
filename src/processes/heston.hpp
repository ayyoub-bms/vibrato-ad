#ifndef HESTON_HPP
#define HESTON_HPP

#include "process.hpp"
#include "cir.hpp"
#include "../random/normal.hpp"

template <typename T>
class HestonProcess : public Process<T>
{

protected:
	virtual T dDiffusion_dsigma() const override
	{
		return this->price() / (2 * sqrt(volProcess->price()));
	}

	virtual T dDrift_dr() const override
	{
		return this->price();
	}

	virtual T dDiffusion_dx() const override
	{
		return sqrt(volProcess->price());
	}

	virtual T dDrift_dx() const override
	{
		return rate;
	}

	virtual T d2Diffusion_dsigma_dx() const override
	{
		return 1 / (2 * sqrt(volProcess->price()));
	}

	virtual T d2Diffusion_dsigma2() const override
	{
		return -this->price() / (4 * pow(volProcess->price(), 3 / 2));
	}

public:
	std::shared_ptr<CIRProcess<T>> volProcess;
	T rate;
	T correlation;
	HestonProcess(State<T> &initialState, std::shared_ptr<CIRProcess<T>> &volProcess, T rate, T correlation) : Process<T>(initialState, "Heston"), volProcess(volProcess), rate(rate), correlation(correlation) {}

	virtual ~HestonProcess() = default;

	virtual T drift() const override
	{
		return rate * this->price();
	}

	virtual T volatility() const override
	{
		return 1;
	}
	virtual T diffusion() const override
	{
		return sqrt(volProcess->price()) * this->price();
	}

	virtual void resetState() override
	{
		this->volProcess->resetState();
		Process<T>::resetState();
	}

	virtual std::ostream &describe(std::ostream &o) const override
	{
		return Process<T>::describe(o) << "Rate        : " << rate << std::endl
									   << "Correlation : " << correlation << std::endl
									   << "Volatility process : " << std::endl
									   << *volProcess << std::endl;
	}
};
#endif // HESTON_HPP
