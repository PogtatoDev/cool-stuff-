import matplotlib.pyplot as plt
import numpy as np
from remez import remez
import sympy as sp
import sys

sys.setrecursionlimit(1000000000)


coeffs, _ = remez(np.atan, 200, -1, 1)
x = sp.symbols('x')
raw_poly = sp.Poly(coeffs[::-1], x)
horner_poly = sp.horner(raw_poly)
print(horner_poly)

def fast_atan(x):
    x = np.asarray(x)

    A = 0.0776509570923569
    B = -0.287434475393028
    C = (np.pi/4 - A - B)

    st1 = x < -1 
    bt1 = x > 1

    x = np.where(bt1 | st1, 1.0 / x, x)

    x2 = x**2

    p = ((A*x2 + B)*x2 + C)*x

    return np.where(bt1, np.pi/2 - p, np.where(st1, -np.pi/2 - p, p))

x = np.linspace(-20, 20, 1000)

plt.xlim(-8, 8)
plt.ylim(-3, 3)
plt.grid(True)


plt.plot(x, abs(fast_atan(x)), label="|custom_atan(x)|")

plt.legend(loc='best')
plt.show()