from newton import manual_newton
import numpy as np
import matplotlib.pyplot as plt

def asin(x):
    if abs(x) > 1:
        return np.nan

    f = lambda t : np.sin(t)-x
    df = lambda t : np.cos(t)

    guess = x / (2*np.pi)

    return manual_newton(f, df, guess)

def plt_asin(x):
    vec = np.vectorize(asin)
    return vec(x)

x = np.linspace(-1, 1, 100)


plt.plot(x, abs(plt_asin(x)-np.asin(x)), label="|approx - true| asin")
plt.plot(x, plt_asin(x), label="|approx - true| asin")
plt.plot(x, np.asin(x), label="|approx - true| asin")
plt.ylim(-1e-5, 1e-5)
plt.legend(loc="best")
plt.show()
