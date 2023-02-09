#ifndef EXPLICITCIR2DISCRETIZATION_HPP
#define EXPLICITCIR2DISCRETIZATION_HPP


# include "discretization.hpp"
# include "../helper.hpp"
# include "../processes/cir.hpp"

template <typename T>
class CIR2Schema: public Discretization<T>{

    public:
        virtual ~CIR2Schema() = default;
        CIR2Schema(std::shared_ptr<CIRProcess<T>>& process):
        	Discretization<T>(process, "Explicit CIR discretization (version 2)"){}

    protected:
        virtual T getNewPrice(T h, T Z) const override {
            auto process = std::static_pointer_cast<CIRProcess<T>>(this->process);
            T Yt = sqrt(process->price());
            T dWt = Z * sqrt(h);
            T c = 1 - pow(process->vol, 2) / (4 * process->speed * process->mean);

            T v0 = 1 + 0.5*process->speed * h;
            T v1 = pow(Yt + 0.5*process->vol* dWt, 2);
            T v2 = 2 * process->mean * process->speed * c * h * v0;
            T v3 = Yt + 0.5 * process->vol* dWt;

            return pow((v3 + sqrt(v1 + v2)) / (2 * v0), 2);
        }
};

#endif
