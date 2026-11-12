import celestial
import math

mu = 3.986004418e14

elements = celestial.Keplerian()

elements.a = 7.0e6
elements.i = 0.5
elements.Omega = 0.3
elements.w = 0.7
elements.nu = 1.0
elements.e = 0.1

state = celestial.keplerian_to_cartesian(elements, mu)

print("Position:", state.r)
print("Velocity:", state.v)

result = celestial.cartesian_to_keplerian(state, mu)

print("a =", result.a)
print("e =", result.e)
print("i =", result.i)

E = celestial.true_to_eccentric(elements.nu, elements.e)
M = E - elements.e * math.sin(E)

solved_E = celestial.solve_kepler_equation(M, elements.e)

print("E =", E)
print("Solved E =", solved_E)

assert math.isclose(E, solved_E, abs_tol=1e-10)
