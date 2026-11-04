#include <cmath>
#include "trueToEccentric.hpp"

double trueToEccentric(const double nu, const double e){
    return std::atan2(std::sqrt(1.0 - e * e) * std::sin(nu), e + std::cos(nu));
}
