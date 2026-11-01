import sys
import random
from math import gcd, isqrt

random.seed(1)


def prime(n):
    if n < 2:
        return False
    d = n - 1
    s = 0
    while d % 2 == 0:
        d //= 2
        s += 1
    for a in (2, 325, 9375, 28178, 450775, 9780504, 1795265022):
        if a % n == 0:
            continue
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(s - 1):
            x = x * x % n
            if x == n - 1:
                break
        else:
            return False
    return True


def f(a, c, mod):
    return (a * a + c) % mod


# --8<-- [start:core]
import random


def Pollard_Rho(N):
    if N == 4:
        return 2  # 因为一开始跳了两步，所以需要特判一下 4
    c = random.randint(1, N - 1)
    t = f(0, c, N)
    r = f(f(0, c, N), c, N)
    while t != r:
        d = gcd(abs(t - r), N)
        if d > 1:
            return d
        t = f(t, c, N)
        r = f(f(r, c, N), c, N)
    return N


# --8<-- [end:core]
def largest(n):
    if n == 1:
        return 1
    if prime(n):
        return n
    d = n
    while d == n:
        d = Pollard_Rho(n)
    return max(largest(d), largest(n // d))


data = list(map(int, sys.stdin.buffer.read().split()))
for n in data[1 : 1 + data[0]]:
    a = largest(n)
    print("Prime" if a == n else a)
