#ifndef TANGENT_HPP
#define TANGENT_HPP

#include "../process.hpp"

template<typename DType>
class TangentProcess: public Process<DType> {

	protected:
		shared_ptr<Process<DType>> parent;

	public:

		virtual ~TangentProcess() = default;

		TangentProcess(shared_ptr<Process<DType>> parent, State<DType> initialState, string name) :
				Process<DType>(initialState, name), parent(parent) {}

		virtual DType mun(DType h) {
			return this->parent->price() + this->parent->drift() * h;
		}

		virtual DType sigman(DType h) {
			return this->parent->diffusion() * sqrt(h);
		}

		virtual DType dmun(DType h) {
			return this->price() + this->drift() * h;
		}

		virtual DType dsigman(DType h) {
			return this->diffusion() * sqrt(h);
		}
};
#endif
