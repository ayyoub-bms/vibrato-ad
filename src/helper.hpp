#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

template <typename T>
struct State
{
    T time;
    T value;
    friend ostream &operator<<(ostream &o, State<T> const &s)
    {
        return o << s.time << ";" << s.value;
    }
};

template <typename T>
struct Path : protected vector<State<T>>
{
    using vec = vector<State<T>>;
    using vec::vec;
    using vec::operator[];
    using vec::begin;
    using vec::end;
    using vec::size;

    string headers() const
    {
        return "time;price";
    }

    friend ostream &operator<<(ostream &o, Path<T> const &p)
    {
        for (auto const &st : p)
            o << st << endl;
        return o << endl;
    }
};

template <typename T>
struct PricingResults
{
    T premium = nan("");
    T delta = nan("");
    T gamma = nan("");
    T vega = nan("");
    T theta = nan("");
    T rho = nan("");
    T vanna = nan("");
    T volga = nan("");

    friend ostream &operator<<(ostream &o, PricingResults<T> const &pr)
    {
        return o << pr.premium << ";" << pr.delta << ";" << pr.gamma << ";" << pr.vega << ";" << pr.theta << ";" << pr.rho << ";" << pr.vanna << ";" << pr.volga;
    }
};

template <typename T>
struct PricingGrid : protected vector<PricingResults<T>>
{
    using vec = vector<PricingResults<T>>;
    using vec::vec;
    using vec::operator[];
    using vec::begin;
    using vec::end;
    using vec::size;

    string headers() const
    {
        return "premium;delta;gamma;vega;theta;rho;vanna;volga";
    }

    friend ostream &operator<<(ostream &o, PricingGrid<T> const &grid)
    {
        for (auto const &pr : grid)
        {
            o << pr << endl;
        }
        return o << endl;
    }
};

#endif // HELPER_HPP
