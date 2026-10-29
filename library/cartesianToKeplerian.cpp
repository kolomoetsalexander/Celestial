#include <cmath>
#include <Eigen/Dense>
#include "library/cartesianToKeplerian.hpp"

Keplerian cartesianToKeplerian(const Cartesian& state, const double mu){
    const double r_mod = (state.r).norm();
    const double v_mod = (state.v).norm();
    const double eps = v_mod * v_mod / 2 - mu / r_mod;
    const double a = - mu / (2 * eps);
    const Eigen::Vector3d h = (state.r).cross(state.v);
    const Eigen::Vector3d z(0.0, 0.0, 1.0);
    const double i = std::acos(h.dot(z)/h.norm());
    const Eigen::Vector3d e = ((state.v).cross(h)/mu - state.r/r_mod);
    const double e_mod = e.norm();
    const Eigen::Vector3d n = z.cross(h);
    const double Omega = std::atan2(n[1], n[0]);
    const double cosW = (n.dot(e))/(n.norm()*e.norm());
    const double sinW = (h.dot(n.cross(e)))/(n.norm()*e.norm()*h.norm());
    const double w = std::atan2(sinW, cosW);
    const double cosNu = (e.dot(state.r))/(e.norm()*r_mod);
    const double sinNu = (h.dot(e.cross(state.r)))/(e.norm()*h.norm()*r_mod);
    const double nu = std::atan2(sinNu, cosNu);
    return {.a = a, .i = i, .Omega = Omega, .w = w, .nu = nu, .e = e_mod};
}