#include <cmath>
#include "solveKeplerEquation.hpp"

double solveKeplerEquation(const double M, const double e){
    const double EPS = 1e-10;
    const int MAX_ITERATIONS = 100;
    double E = M;

    for (int i = 0; i < MAX_ITERATIONS; ++i){
        const double f = E - e * std::sin(E) - M;
        const double df = 1.0 - e * std::cos(E);
        const double nextE = E - f / df;

        if (std::abs(nextE - E) < EPS){
            return nextE;
        }
        E = nextE;
    }
    return E;
}
