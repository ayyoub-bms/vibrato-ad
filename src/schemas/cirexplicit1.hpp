#ifndef EXPLICITCIR1DISCRETIZATION_HPP
#define EXPLICITCIR1DISCRETIZATION_HPP


# include "discretization.hpp"
# include "../processes/cir.hpp"
# include "../helper.hpp"

template <typename T>
class CIR1Schema: public Discretization<T>{

    public:
        virtual ~CIR1Schema() = default;
        CIR1Schema(std::shared_ptr<CIRProcess<T>>& process): Discretization<T>(process, "Explicit CIR discretization (version 1)"){}
    protected:

        virtual T getNewPrice(T h, T Z) const override {

            auto process = std::static_pointer_cast<CIRProcess<T>>(this->process);
            T Xt = process->price();
            T dWt = Z * sqrt(h);
        	T sigma = process->vol;
		    T kappa = process->speed;
			T theta = process->mean;

            T result = sigma * dWt;
            T v0 = 1 + kappa * h;
            T v1 = pow(sigma * dWt, 2);
            T v2 = 	kappa * h * (theta - pow(sigma, 2) / (2* kappa)) + Xt;
            result = 0.5 * (result + sqrt(v1 + 4 * v0 * v2)) / v0;
            return pow(result, 2);
        }
};

#endif
