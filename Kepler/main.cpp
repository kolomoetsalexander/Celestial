#include <Eigen/Dense>
#include <cmath>
#include <variant>
#include <algorithm>

struct Keplerian{
    double a;
    double i;
    double Omega;
    double w;
    double nu;
    double e;
};
struct CircularOrbit{
    double radius;
    double i;
    double Omega;
    double u;
};
struct ParabolicOrbit{
    double p;
    double i;
    double Omega;
    double w;
    double nu;
};
using OrbitElements = std::variant<Keplerian, CircularOrbit, ParabolicOrbit>;

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
    const Eigen::Vector3d v_M(-elements.e * sinNu * std::sqrt(mu / p), (elements.e + cosNu) * std::sqrt(mu / p), 0.0);
    const Eigen::Matrix3d R3w{
        cosW, -sinW, 0.0,
        sinW, cosW, 0.0,
        0.0, 0.0, 1.0
    };
    const Eigen::Matrix3d R1i{
        1.0, 0.0, 0.0,
        0.0, cosi, -sini,
        0.0, sini, cosi
    };
    const Eigen::Matrix3d R3Om{
        cosOm, -sinOm, 0.0,
        sinOm, cosOm, 0.0,
        0.0, 0.0, 1.0
    };
    const Eigen::Matrix3d R = R3Om * R1i * R3w;
    const Eigen::Vector3d r_O = R * r_M;
    const Eigen::Vector3d v_O = R * v_M;
    return {.v = v_O, .r = r_O};
}

OrbitElements cartesianToKeplerian(const Cartesian& state, const double mu){
    const double r_mod = state.r.norm();
    const double v_mod = state.v.norm();
    const double eps = v_mod * v_mod / 2.0 - mu / r_mod;
    const Eigen::Vector3d h = state.r.cross(state.v);
    const double h_mod = h.norm();
    const Eigen::Vector3d z(0.0, 0.0, 1.0);
    const double i = std::acos(h.dot(z) / h_mod);
    const Eigen::Vector3d e = state.v.cross(h) / mu - state.r / r_mod;
    const double e_mod = e.norm();
    const Eigen::Vector3d n = z.cross(h);
    const double n_mod = n.norm();
    const double Omega = std::atan2(n[1], n[0]);
    //Допуск на погрешность расчетов
    const double delta = 1e-9;
    //Круговая орбита
    if (e_mod < delta){
        const double cosU = n.dot(state.r) / (n_mod * r_mod);
        const double sinU = h.dot(n.cross(state.r))/(h_mod * n_mod * r_mod);
        const double u = std::atan2(sinU, cosU);
        return CircularOrbit{.radius = r_mod, .i = i, .Omega = Omega, .u = u};
    }
    //Элипс или парабола
    const double energyScale = std::max(v_mod * v_mod / 2.0, mu / r_mod);
    const bool parabolic = std::abs(eps) <= delta * energyScale;
    const double cosW = n.dot(e) / (n_mod * e_mod);
    const double sinW = h.dot(n.cross(e)) / (n_mod * e_mod * h_mod);
    const double w = std::atan2(sinW, cosW);
    const double cosNu = e.dot(state.r) / (e_mod * r_mod);
    const double sinNu = h.dot(e.cross(state.r)) / (e_mod * h_mod * r_mod);
    const double nu = std::atan2(sinNu, cosNu);

    if (parabolic){
        //р вместо а
        const double p = h_mod * h_mod / mu;
        return ParabolicOrbit{.p = p, .i = i, .Omega = Omega, .w = w, .nu = nu};
    }
    //Эллипс
    const double a = -mu / (2.0 * eps);
    return Keplerian{.a = a, .i = i, .Omega = Omega, .w = w, .nu = nu, .e = e_mod};
}
