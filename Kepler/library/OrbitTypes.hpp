#pragma once
#include <Eigen/Dense>

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