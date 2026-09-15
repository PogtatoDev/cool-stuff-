import numpy as np
import matplotlib.pyplot as plt
from newton import manual_newton

def thing(x):
    m, k = np.frexp(x)
    m *= 1 + (k&1)
    k -= k&1


    y = 0.4 + 0.5*m

    y = 0.5*(y + m/y)
    y = 0.5*(y + m/y)
    y = 0.5*(y + m/y)

    return y * np.exp2(k/2)

sqrt_approx = np.vectorize(thing)

def thing2(x):
    m, k = np.frexp(x)
    if (m < np.sqrt(1/2)):
        m *= 2
        k -= 1
    p = m*(m*(m*(m*(0.169433679555718*m - 1.11850247941147) + 3.11760487965055) - 4.8355956920628) + 4.94513272268062) - 2.27807467004003

    return p + k*0.6931471805599453

ln_approx = np.vectorize(thing2)

def thing3(x):
    k = np.floor(x/0.6931471805599453)
    r = x - k*0.6931471805599453
    p = r*(r*(r*(r*(0.0118376428910604*r + 0.0387409545819054) + 0.167774860537651) + 0.499808246072626) + 1.00001219051698) + 0.999999947297752

    return p * np.exp2(k)

exp_approx = np.vectorize(thing3)

def thing4(x):
    f = lambda t : t*exp_approx(t) - x
    df = lambda t : exp_approx(t) * (t + 1)

    guess = ln_approx(x) - ln_approx(ln_approx(x))

    return manual_newton(f, df, guess)

lamb_w_approx = np.vectorize(thing4)


h = "heres to rockafella"

x = np.linspace(1, 30, 1000)

plt.plot(x, lamb_w_approx(x * exp_approx(x)))

plt.legend()
plt.grid()
plt.show()
