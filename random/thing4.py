from newton import manual_newton
import numpy as np
import matplotlib.pyplot as plt

def is_even(x):
    return x%2 == 0

def c_nthroot(x, n):
    if is_even(n) and x < 0:
        return np.nan
    guess = x/n
    f = lambda t : (t**n)-x
    df = lambda t: n*t**(n-1)

    return manual_newton(f, df, guess)

def c_np_nthroot(x, n):
    vec = np.vectorize(c_nthroot)
    return vec(x, n)

x = np.linspace(1, 1000, 10000)

plt.xlim(0, 200)
plt.ylim(-10, 10)
plt.plot(x, c_np_nthroot(x, 2), label="newton approx.")
plt.plot(x, np.sqrt(x), label="sqrt(x)")
plt.plot(x, abs(np.sqrt(x) - c_np_nthroot(x, 2)), label="|approx - true val|")
plt.legend(loc='best')
plt.grid(True)
plt.show()