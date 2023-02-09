#include <iostream>
#include "../all.hpp"
#include "helper.hpp"

using namespace std;

int main() {

    std::cout << "***** Staring vibrato for vanilla options !" << std::endl;

    double maturity = .5;
    double strike = 100;
    double price = 70;
    double rate = .05;
    double vol = .2;
    int n = 100;  // number of time steps
    int M = 50000; // number of MC paths
    int Mz = 50;  // number of replications of the last time step

    // Product definition
    auto o = std::make_shared<VanillaOption<double>>(maturity, strike, OptionType::Call);

    // Black Scholes process definition
    State<double> initialState = {0.0, price};
    auto bs = std::make_shared<BlackScholesProcess<double>>(initialState, rate, vol);

    // Pricing engines definition
    auto be = std::make_shared<VanillaBS<double>>(o, bs);
    auto ve = std::make_shared<Vibrato<double>>(o, bs, rate, n, M, Mz);

    size_t vecSize = 60;
    int step = 1;
    
    // Black Scholes
    Helper<double>::generateGrid(o, bs, be, price , vecSize, step, "vanilla");

    Helper<double>::generateGrid(o, bs, ve, price , vecSize, step, "vibrato_anti");

    std::cout << "***** Vibrato for vanilla options terminated!" << std::endl;

    return 0;
}
