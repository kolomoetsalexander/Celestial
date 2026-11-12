
#include "library/keplerianToCartesian.hpp"
#include "library/cartesianToKeplerian.hpp"
#include "library/trueToEccentric.hpp"
#include "library/eccentricToTrue.hpp"
#include "library/solveKeplerEquation.hpp"
#include <iostream>
#include <cmath>

int main() {
    const double mu = 3.986004418e14;
    const Keplerian elements{
        7.0e6,  // a
        0.5,    // i
        0.3,    // Omega
        0.7,    // w
        1.0,    // nu
        0.1     // e
    };

    //keplerian -> cartesian -> keplerian
    const Cartesian state = keplerianToCartesian(elements, mu);
    const Keplerian result = cartesianToKeplerian(state, mu);
    std::cout << "a = " << result.a << '\n';
    std::cout << "e = " << result.e << '\n';
    std::cout << "i = " << result.i << '\n';
    std::cout << "Omega = " << result.Omega << '\n';
    std::cout << "w = " << result.w << '\n';
    std::cout << "nu = " << result.nu << "\n\n";

    //true -> eccentric 
    const double E = trueToEccentric(elements.nu, elements.e);
    std::cout << "nu = " << elements.nu << '\n';
    std::cout << "E = " << E << "\n\n";

    //eccentric -> true
    const double nu = eccentricToTrue(E, elements.e);
    std::cout << "E = " << E << '\n';
    std::cout << "nu = " << nu << "\n\n";

    //численное решение ур-ния Кеплера
    const double M = E - elements.e * std::sin(E);
    const double solvedE = solveKeplerEquation(M, elements.e);
    std::cout << "M = " << M << '\n';
    std::cout << "E (original) = " << E << '\n';
    std::cout << "E (solved) = " << solvedE << '\n';
    std::cout << "Difference = " << std::abs(E - solvedE) << '\n';
    return 0;
}
