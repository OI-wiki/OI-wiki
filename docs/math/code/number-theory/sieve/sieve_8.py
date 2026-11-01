import sys
from math import isqrt

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
N = max(2, n + 1)

# --8<-- [start:core]
pri = []
not_prime = [False] * N
f = [0] * N
g = [0] * N


def pre(n):
    g[1] = f[1] = 1
    for i in range(2, n + 1):
        if not not_prime[i]:
            pri.append(i)
            g[i] = i + 1
            f[i] = i + 1
        for pri_j in pri:
            if i * pri_j > n:
                break
            not_prime[i * pri_j] = True
            if i % pri_j == 0:
                g[i * pri_j] = g[i] * pri_j + 1
                f[i * pri_j] = f[i] // g[i] * g[i * pri_j]
                break
            f[i * pri_j] = f[i] * f[pri_j]
            g[i * pri_j] = 1 + pri_j


# --8<-- [end:core]

pre(n)
print(f[n])
