#include "library/keplerianToCartesian.hpp"
#include "library/cartesianToKeplerian.hpp"
#include <iostream>

int main(){
    const double mu = 3.986004418e14;
    const Keplerian elements{
        7.0e6,  // a
        0.5,    // i
        0.3,    // Omega
        0.7,    // w
        1.0,    // nu
        0.1     // e
    };
    const Cartesian state = keplerianToCartesian(elements, mu);
    const Keplerian result = cartesianToKeplerian(state, mu);
    std::cout << "a = " << result.a << '\n';
    std::cout << "e = " << result.e << '\n';
    std::cout << "i = " << result.i << '\n';
    return 0;
}