#include <Eigen/Dense>
#include <cmath>

struct Keplerian{
    double a;
    double i;
    double Omega;
    double w;
    double nu;
    double e;
};

struct Cartesian{
    Eigen::Vector3d v;
    Eigen::Vector3d r;
};

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
    Eigen::Vector3d v_M(-elements.e * sinNu, elements.e + cosNu, 0.0);
    v_M *= std::sqrt(mu / p);
    const Eigen::Matrix3d R3w {cosW, -sinW, 0.0, sinW, cosW, 0.0, 0.0, 0.0, 1.0};
    const Eigen::Matrix3d R1i {1.0, 0.0, 0.0, 0.0, cosi, -sini, 0.0, sini, cosi};
    const Eigen::Matrix3d R3Om {cosOm, -sinOm, 0.0, sinOm, cosOm, 0.0, 0.0, 0.0, 1.0};
    const Eigen::Matrix3d R = R3Om * R1i * R3w;
    const Eigen::Vector3d r_O = R * r_M;
    const Eigen::Vector3d v_O = R * v_M;
    return {.r = r_O, .v = v_O};
}

Keplerian cartesianToKeplerian(const Cartesian& state, const double mu){
    const double r_mod = (state.r).norm();
    const double v_mod = (state.v).norm();
    const double eps = v_mod * v_mod / 2 - mu / r_mod;
    Keplerian kepler;
    kepler.a = - mu / (2* eps);
    const Eigen::Vector3d h = (state.r).cross(state.v);
    const Eigen::Vector3d z(0.0, 0.0, 1.0);
    kepler.i = std::acos(h.dot(z)/h.norm());
    const Eigen::Vector3d e = ((state.v).cross(h)/mu - state.r/r_mod);
    kepler.e = e.norm();
    const Eigen::Vector3d n = z.cross(h);
    kepler.Omega = std::atan2(n[1], n[0]);
    const double cosW = (n.dot(e))/(n.norm()*e.norm());
    const double sinW = (h.dot(n.cross(e)))/(n.norm()*e.norm()*h.norm());
    kepler.w = std::atan2(sinW, cosW);
    const double cosNu = (e.dot(state.r))/(e.norm()*r_mod);
    const double sinNu = (h.dot(e.cross(state.r)))/(e.norm()*h.norm()*r_mod);
    kepler.nu = std::atan2(sinNu, cosNu);
    return kepler;
}

int main(){
    // to be continued
}