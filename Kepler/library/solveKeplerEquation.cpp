#include <cmath>
#include "solveKeplerEquation.hpp"

double solveKeplerEquation(const double M, const double e){
    const double EPS = 1e-10;
    const int MAX_ITERATIONS = 101;
    double E = M;
    const double sinE = std::sin(E);
    const double cosE = std::cos(E);

    for (int i = 0; i < MAX_ITERATIONS; ++i){
        const double f = E - e * sinE - M;
        const double df = 1.0 - e * cosE;
        const double nextE = E - f / df;

        if (std::abs(nextE - E) < EPS){
            return nextE;
        }
        E = nextE;
    }
    return E;
}
