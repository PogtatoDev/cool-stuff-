from typing import Callable

def derivative(f: Callable[[float], float], eps: float = 1e-6) -> Callable[[float], float]:
    def Df(x: float) -> float:
        return (f(x + eps) - f(x - eps)) / (2 * eps)
    return Df
