import sys


# --8<-- [start:core]
def sqrt_newton(n):
    if n == 0:
        return 0.0
    eps = 1e-15
    x = 1
    while True:
        nx = (x + n / x) / 2
        if abs(x - nx) < eps * max(1.0, abs(nx)):
            break
        x = nx
    return x


# --8<-- [end:core]
print(f"{sqrt_newton(float(sys.stdin.buffer.read())):.6f}")
