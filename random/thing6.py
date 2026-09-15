import numpy as np
import matplotlib.pyplot as plt
import math

BERNOULLI = [1,-0.5,1.0 / 6.0,0,-1.0 / 30.0,0,1.0 / 42.0,0,-1.0 / 30.0,0,5.0 / 66.0,0,-691.0 / 2730.0,0,7.0 / 6.0,0,-3617.0 / 510.0,0,43867.0 / 798.0,0,-174611.0 / 330.0];

def lgamma(x):
    if x > 0:
        c = 0.5 * (np.log(2) + np.log(np.pi))
        sum = 0

        for k in range(1, 10):
            sum += BERNOULLI[2*k]/(2*k*(2*k-1)) * 1/x**(2*k-1)
        
        return (x-0.5) * np.log(x) -x + c + sum
    else:
        if abs(x - np.floor(x)) < 0.001:
            return np.nan
        return np.log(np.pi) - np.log(np.sin(np.pi*x)) - lgamma(1-x)
    
def np_gamma(x):
    vec = np.vectorize(lgamma)
    return vec(x)


x = np.linspace(-10, 10, 1000)
fact = []
x2 = []
for i in range (0, 10):
    fact.append(math.factorial(i))
    x2.append(i)

plt.ylim(-7, 7)
plt.xlim(-10, 10)
plt.plot(x, np_gamma(x+1), label="log(Γ(x+1))")
plt.scatter(x2, np.log(fact), label="log(n!)")
plt.legend()
plt.grid()
plt.show()
