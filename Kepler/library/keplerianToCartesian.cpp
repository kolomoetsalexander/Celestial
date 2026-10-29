#include <cmath>
#include <Eigen/Dense>
#include "keplerianToCartesian.hpp"

Cartesian keplerianToCartesian(const Keplerian& elements, const double mu){
    const double cosNu = std::cos(elements.nu);
    const double sinNu = std::sin(elements.nu);
    const double sinW = std::sin(elements.w);
    const double cosW = std::cos(elements.w);
    const double sinOm = std::sin(elements.Omega);
    const double cosOm = std::cos(elements.Omega);
    const double sini = std::sin(elements.i);
    const double cosi = std::cos(elements.i);
    const double p = elements.a * (1 - elements.e * elements.e);
    const double r = p / (1 + elements.e * cosNu);
    const Eigen::Vector3d r_M(r * cosNu, r * sinNu, 0.0);
    const Eigen::Vector3d v_M(-elements.e * sinNu * std::sqrt(mu / p), (elements.e + cosNu) * std::sqrt(mu / p), 0.0);
    Eigen::Matrix3d R3w;
        R3w << cosW, -sinW, 0.0, 
        sinW, cosW, 0.0, 
        0.0, 0.0, 1.0;
    
    Eigen::Matrix3d R1i;
        R1i << 1.0, 0.0, 0.0, 
        0.0, cosi, -sini, 
        0.0, sini, cosi;
    
    Eigen::Matrix3d R3Om;
        R3Om << cosOm, -sinOm, 0.0, 
        sinOm, cosOm, 0.0, 
        0.0, 0.0, 1.0;
        
    const Eigen::Matrix3d R = R3Om * R1i * R3w;
    const Eigen::Vector3d r_O = R * r_M;
    const Eigen::Vector3d v_O = R * v_M;
    return {.v = v_O, .r = r_O};
}