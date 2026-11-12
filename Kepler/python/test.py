import HarmoniaMundi
import math

mu = 3.986004418e14

elements = HarmoniaMundi.Keplerian()

elements.a = 7.0e6
elements.i = 0.5
elements.Omega = 0.3
elements.w = 0.7
elements.nu = 1.0
elements.e = 0.1

state = HarmoniaMundi.keplerian_to_cartesian(elements, mu)

print("Position:", state.r)
print("Velocity:", state.v)

result = HarmoniaMundi.cartesian_to_keplerian(state, mu)

print("a =", result.a)
print("e =", result.e)
print("i =", result.i)

E = HarmoniaMundi.true_to_eccentric(elements.nu, elements.e)
M = E - elements.e * math.sin(E)

solved_E = HarmoniaMundi.solve_kepler_equation(M, elements.e)

print("E =", E)
print("Solved E =", solved_E)

assert math.isclose(E, solved_E, abs_tol=1e-10)
