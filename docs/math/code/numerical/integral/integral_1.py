import sys

a, b, c, d, L, R = map(float, sys.stdin.buffer.read().split())


def f(x):
    return (c * x + d) / (a * x + b)


# --8<-- [start:core]
N = 1000 * 1000


def simpson_integration(a, b):
    h = (b - a) / N
    s = f(a) + f(b)
    for i in range(1, N):
        x = a + h * i
        if i & 1:
            s = s + f(x) * 4
        else:
            s = s + f(x) * 2
    s = s * (h / 3)
    return s


# --8<-- [end:core]
print(f"{simpson_integration(L,R):.6f}")
