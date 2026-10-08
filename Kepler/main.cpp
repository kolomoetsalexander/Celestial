#include <Eigen/Dense>
#include <iostream>
#include <cmath>
struct KeplerElem{
    double a;
    double i;
    double Omega;
    double w;
    double nu;
    double e;
};
struct State{
    Eigen::Vector3d v;
    Eigen::Vector3d r;
};
State keplerToState(const KeplerElem& elements, double mu){
    double cosNu = std::cos(elements.nu);
    double sinNu = std::sin(elements.nu);
    double sinW = std::sin(elements.w);
    double cosW = std::cos(elements.w);
    double sinOm = std::sin(elements.Omega);
    double cosOm = std::cos(elements.Omega);
    double sini = std::sin(elements.i);
    double cosi = std::cos(elements.i);
    double p = elements.a * (1 - elements.e * elements.e);
    double r = p / (1 + elements.e * cosNu);
    Eigen::Vector3d r_M(r * cosNu, r * sinNu, 0.0);
    Eigen::Vector3d v_M(-elements.e * sinNu, 1 + elements.e * cosNu, 0.0);
    v_M *= std::sqrt(mu / p);
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
    Eigen::Matrix3d R = R3Om * R1i * R3w;
    Eigen::Vector3d r_O = R * r_M;
    Eigen::Vector3d v_O = R * v_M;
    State res;
    res.v = v_O;
    res.r = r_O;
    return res;
}
KeplerElem stateToKepler(const State& state, double mu){
    double r_mod = (state.r).norm();
    double v_mod = (state.v).norm();
    double eps = v_mod * v_mod / 2 - mu / r_mod;
    KeplerElem kepler;
    kepler.a = - mu / (2* eps);
    Eigen::Vector3d h = (state.r).cross(state.v);
    Eigen::Vector3d z(0.0, 0.0, 1.0);
    kepler.i = std::acos(h.dot(z)/h.norm());
    // place for e

    Eigen::Vector3d e = ((state.v).cross(h)/mu - state.r/r_mod);
    kepler.e = e.norm();
    Eigen::Vector3d n = z.cross(h);
    kepler.Omega = std::atan2(n[1], n[0]);
    double cosW = (n.dot(e))/(n.norm()*e.norm());
    double sinW = (h.dot(n.cross(e)))/(n.norm()*e.norm()*h.norm());
    kepler.w = std::atan2(sinW, cosW);
    double cosNu = (e.dot(state.r))/(e.norm()*r_mod);
    double sinNu = (h.dot(e.cross(state.r)))/(e.norm()*h.norm()*r_mod);
    kepler.nu = std::atan2(sinNu, cosNu);

}



int main(){
    std::cout << "hello" << std::endl;
    // тут пока пусто
}