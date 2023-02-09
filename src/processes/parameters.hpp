#ifndef SRC_PROCESSES_PARAMETERS_HPP_
#define SRC_PROCESSES_PARAMETERS_HPP_

#include "../helper.hpp"

template <typename T>
struct Params
{
	virtual string headers() const = 0;
};

template <typename T>
struct CIRParams : public Params<T>
{
	CIRParams(T kappa, T theta, T sigma) : kappa(kappa), theta(theta), sigma(sigma){};
	T kappa;
	T theta;
	T sigma;

	virtual string headers() const override
	{
		return "CIR_kappa;CIR_theta;CIR_sigma";
	}

	friend ostream &operator<<(ostream &o, CIRParams<T> const &x)
	{
		return o << x.kappa << ";" << x.theta << ";" << x.sigma;
	}
};

template <typename T>
struct BlackScholesParams : Params<T>
{
	BlackScholesParams(T rate, T sigma) : rate(rate), sigma(sigma){};
	T rate;
	T sigma;

	virtual string headers() const override
	{
		return "BS_rate;BS_sigma";
	}
	friend ostream &operator<<(ostream &o, BlackScholesParams<T> const &x)
	{
		return o << x.rate << ";" << x.sigma;
	}
};

template <typename T>
struct HestonParams : Params<T>
{
	HestonParams(T rate, T correlation) : rate(rate), correlation(correlation) {}
	T rate;
	T correlation;
	virtual string headers() const override
	{
		return "HESTON_rate;HESTON_correlation";
	}

	friend ostream &operator<<(ostream &o, HestonParams<T> const &x)
	{
		return o << x.rate << ";" << x.correlation;
	}
};

#endif
