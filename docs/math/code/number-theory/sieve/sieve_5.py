import sys
from math import isqrt

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
N = max(2, n + 1)

# --8<-- [start:core]
pri = []
not_prime = [False] * N
phi = [0] * N


def pre(n):
    phi[1] = 1
    for i in range(2, n + 1):
        if not not_prime[i]:
            pri.append(i)
            phi[i] = i - 1
        for pri_j in pri:
            if i * pri_j > n:
                break
            not_prime[i * pri_j] = True
            if i % pri_j == 0:
                phi[i * pri_j] = phi[i] * pri_j
                break
            phi[i * pri_j] = phi[i] * phi[pri_j]


# --8<-- [end:core]

pre(n)
print(phi[n])
