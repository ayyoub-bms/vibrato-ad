#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>
enum OptionType {
    Call = 1, Put = -1
};

template<typename T>
class Option {

public:
	T maturity;
	T strike;
	const OptionType type;
    virtual~Option() = default;

    Option(T &maturity, T &strike, const OptionType type, std::string name)
            : maturity(maturity), strike(strike), type(type), name_(name) {}

    virtual T payoff(T price) const = 0;

    std::string name() const { return name_; };

    double dtype() const { return (double) type; }

    friend std::ostream &operator<<(std::ostream &o, const Option<T> &opt) {
        return opt.describe(o);
    }

    virtual std::ostream &describe(std::ostream &o) const {
        return o << "Name: " << name_ << std::endl <<
                 "Option Type: " << (type == OptionType::Call ? "Call" : "Put") <<
                 std::endl <<
                 "Maturity: " << maturity << std::endl <<
                 "Strike: " << strike << std::endl;
    };

protected:
    const std::string name_;
};


#endif  // OPTION_HPP
