
#include <iostream>
#include "../processes/gbm.hpp"
#include "../processes/cir.hpp"
#include "../processes/heston.hpp"

using namespace std;

int main()
{

    // Parameters definition
    double price = 100;
    double rate = -.05;
    double vol = .3;

    double kappa = 0.01;
    double rho = -.85;
    double theta = 5;

    State<double> S0 = {0, price};
    State<double> v0 = {0, .5};

    // Create processes
    auto bsmProcess = make_shared<BlackScholesProcess<double>>(S0, rate, vol);
    auto cirProcess = make_shared<CIRProcess<double>>(v0, kappa, theta, vol);
    auto hesProcess = make_shared<HestonProcess<double>>(S0, cirProcess, rate, rho);

    cout << *bsmProcess << endl;
    cout << *cirProcess << endl;
    cout << *hesProcess << endl;

    cout << bsmProcess->drift() << endl;
    cout << bsmProcess->diffusion() << endl;

    cout << cirProcess->drift() << endl;
    cout << cirProcess->diffusion() << endl;

    cout << hesProcess->drift() << endl;
    cout << hesProcess->diffusion() << endl;
};
