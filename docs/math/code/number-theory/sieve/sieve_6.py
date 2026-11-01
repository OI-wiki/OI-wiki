import sys
from math import isqrt

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
N = max(2, n + 1)

# --8<-- [start:core]
pri = []
not_prime = [False] * N
mu = [0] * N


def pre(n):
    mu[1] = 1
    for i in range(2, n + 1):
        if not not_prime[i]:
            pri.append(i)
            mu[i] = -1
        for pri_j in pri:
            if i * pri_j > n:
                break
            not_prime[i * pri_j] = True
            if i % pri_j == 0:
                mu[i * pri_j] = 0
                break
            mu[i * pri_j] = -mu[i]


# --8<-- [end:core]

pre(n)
print(mu[n])
