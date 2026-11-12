#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>

#include <array>

#include "OrbitTypes.hpp"
#include "keplerianToCartesian.hpp"
#include "cartesianToKeplerian.hpp"
#include "trueToEccentric.hpp"
#include "eccentricToTrue.hpp"
#include "solveKeplerEquation.hpp"

namespace nb = nanobind;
using namespace nb::literals;

NB_MODULE(celestial, m){
    m.doc() = "Celestial mechanics library";
    nb::class_<Keplerian>(m, "Keplerian")
        .def(nb::init<>())
        .def_rw("a", &Keplerian::a)
        .def_rw("i", &Keplerian::i)
        .def_rw("Omega", &Keplerian::Omega)
        .def_rw("w", &Keplerian::w)
        .def_rw("nu", &Keplerian::nu)
        .def_rw("e", &Keplerian::e);

    nb::class_<Cartesian>(m, "Cartesian")
        .def(nb::init<>())
        .def_prop_rw("r",
            [](const Cartesian& state){
                return std::array<double, 3>{state.r.x(), state.r.y(), state.r.z()};
            },
            [](Cartesian& state,
               const std::array<double, 3>& r) {
                state.r = Eigen::Vector3d(
                    r[0], r[1], r[2]
                );
            })

        .def_prop_rw("v",
            [](const Cartesian& state) {
                return std::array<double, 3>{
                    state.v.x(),
                    state.v.y(),
                    state.v.z()
                };
            },
            [](Cartesian& state,
               const std::array<double, 3>& v) {
                state.v = Eigen::Vector3d(
                    v[0], v[1], v[2]
                );
            });

    m.def("keplerian_to_cartesian", &keplerianToCartesian, "elements"_a, "mu"_a);
    m.def("cartesian_to_keplerian", &cartesianToKeplerian, "state"_a, "mu"_a);
    m.def("true_to_eccentric", &trueToEccentric, "nu"_a, "e"_a);
    m.def("eccentric_to_true", &eccentricToTrue, "E"_a, "e"_a);
    m.def("solve_kepler_equation", &solveKeplerEquation, "M"_a, "e"_a);
}
