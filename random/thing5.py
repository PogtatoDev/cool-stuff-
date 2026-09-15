from remez import remez
import numpy as np
import sympy as sp


m, n = sp.symbols('m, n')
s = sp.summation(((1-m)**n) / n, (n, 1, 20))
raw_poly = s.expand()

print(s)