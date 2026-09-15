import newton
import numpy as np

def sqrt1(x):
    f=lambda t:(t*t)-x
    df=lambda t:2*t
    guess=np.floor(2**(np.floor(np.log2(x))/2))
    return newton.manual_newton(f, df, guess)

def sqrt2(x):
    f=lambda t:(t*t)-x
    guess=np.floor(2**(np.floor(np.log2(x))/2))
    return newton.newton(f, guess)

sink = 0
for i in range(1, 100000000):
    sink += sqrt2(i)

print(sink)