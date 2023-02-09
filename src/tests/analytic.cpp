#ifndef BS_ANALYTIC_CPP
#define BS_ANALYTIC_CPP

#include <memory>

#include "helper.hpp"

#include "../processes/gbm.hpp"
#include "../instruments/vanilla.hpp"
#include "../instruments/digital.hpp"
#include "../pricers/digital.hpp"
#include "../pricers/vanilla.hpp"
using namespace std;

int main(void)
{

    // Computation of the premium and greeks analytical BS

    double maturity = .5;
    double strike = 100;
    double price = 100;
    double rate = .05;
    double vol = .32;

    State<double> initialState = {0.0, price};

    auto bs = std::make_shared<BlackScholesProcess<double>>(initialState, rate, vol);

    auto vopt = std::make_shared<VanillaOption<double>>(maturity, strike, OptionType::Put);
    auto dopt = std::make_shared<DigitalOption<double>>(maturity, strike, OptionType::Put);

    // Pricing engines definition
    auto be = std::make_shared<VanillaBS<double>>(vopt, bs);
    auto de = std::make_shared<DigitalBS<double>>(dopt, bs);

    cout << "********* Pricing results *******" << endl;

    cout << "*********************************" << endl;
    cout << "Pricing Vanilla option Analytic " << endl;
    cout << "*********************************" << endl;
    Helper<double>::generateGrid(vopt, bs, be, 50.0, 100, 1, "vanilla");
    cout << "*******************************" << endl;
    cout << "Pricing Digital option Analytic" << endl;
    cout << "*******************************" << endl;
    Helper<double>::generateGrid(dopt, bs, de, 50.0, 100, 1, "digital");
    cout << "*************~END~*************" << endl;

    return 0;
}

#endif // MAIN_CPP
