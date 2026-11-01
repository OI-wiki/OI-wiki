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
from random import randint
from math import gcd


def Pollard_Rho(x):
    if x == 4:
        return 2
    c = randint(1, x - 1)
    s = t = f(0, c, x)
    goal = val = 1
    while True:
        for step in range(1, goal + 1):
            t = f(t, c, x)
            val = val * abs(t - s) % x
            if val == 0:
                return x  # 如果 val 为 0，退出重新分解
            if step % 127 == 0:
                d = gcd(val, x)
                if d > 1:
                    return d
        d = gcd(val, x)
        if d > 1:
            return d
        s = t
        goal <<= 1
        val = 1


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
