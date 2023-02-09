
#include <iostream>

# include "../processes/gbm.hpp"
# include "../processes/cir.hpp"
# include "../processes/heston.hpp"
#include "../schemas/bsexact.hpp"
#include "../schemas/cirexplicit1.hpp"
#include "../schemas/cirexplicit2.hpp"

#include "../utils.hpp"

using namespace std;

int main() {
	// ***************** Testing the CIR simulations ************************ //
	// Parameters definition
	double maturity = 10;
	double vol = .001;
	double kappa = 5;
	double theta = .01;

	State<double> v0 = {0, .02};

	// Create processes
	auto cirProcess = std::make_shared<CIRProcess<double>>(v0, kappa, theta, vol);


	auto CIRExp1 = std::make_shared<CIR1Schema<double>>(cirProcess);
	auto CIRExp2 = std::make_shared<CIR2Schema<double>>(cirProcess);

	int nbSamples = 500;
	auto CIRExp1Path = CIRExp1->generatePath(nbSamples, maturity);
	auto CIRExp2Path = CIRExp2->generatePath(nbSamples, maturity);


	data2csv("src/python/datasets/CIR1", CIRExp1Path);

}
