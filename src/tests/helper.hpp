#ifndef VIBRATO_MC_HELPER_H
#define VIBRATO_MC_HELPER_H

# include <vector>
#include "../utils.hpp"
#include "../pricers/pricer.hpp"

using namespace std;

template<typename DType>
class Helper {

public:

	static void generateGrid(shared_ptr<Option<DType>> option,
			shared_ptr<Process<DType>> process, shared_ptr<Pricer<DType>> pricer,
			DType price, size_t size, double step, string filename) {

		string type = option->type == OptionType::Call ? "call_" : "put_";
		string destination = "src/python/datasets/" + type + filename;
		auto grid = make_shared<PricingGrid<DType>>(size);
		auto pvec = make_shared<Path<DType>>(size);
		process->resetState();
		DType original_price = price;
		for (auto &it : *pvec) {
			it = { 0, price };
			price += step;
		}
		price = original_price;
		for (auto &it : *grid) {
            cout << "Computing for price: $" << price << endl;
			process->initialState.value = price;
			process->resetState();
			pricer->compute();
			it = *pricer->results;
			price += step;
		}
		data2csv(destination + "_price", pvec);
		data2csv(destination + "_pricing", grid);
	}
};

#endif //VIBRATO_MC_HELPER_H
