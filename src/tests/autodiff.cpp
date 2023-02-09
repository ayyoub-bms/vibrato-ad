#include <iostream>
// #include <autodiff/forward/dual.hpp>
#include <autodiff/reverse/var.hpp>
using namespace autodiff;

// dual f1(dual& x, dual& y) {
//     dual val = x - y;
//     return val > 0 ? val : 0;
// }

var f2(var x, var y) {
    var val = x - y;
    if (val <= 0)
        val = 0;
        
    return val;
}

int main() {
    // forward mode
    // dual y = 0;
    // dual x = 5;
    // for (int i = 0; i < 10; i++) {
    //     y += 1;
    //     std::cout << i << 
    //         ": f(x, y) = " << f(x, y) << 
    //         ": df/dy = " << derivative(f1, wrt(y), at(x, y)) <<
    //         ": df/dx = " << derivative(f1, wrt(x), at(x, y)) << 
    //         std::endl;
    // }
    var x = 5;
    for (int i = 0; i < 10; i++) {
        var y = i + 1;
        var u = f2(x, y);
        auto [ux, uy] = derivatives(u, wrt(x, y));

        std::cout << i << ": f(x, y) = " << u << ": df/dy = " << uy << ": df/dx = " << ux << std::endl;
    }
    // reverse mode
    //
    //
    return 0;
}
