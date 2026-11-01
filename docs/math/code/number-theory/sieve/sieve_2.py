import sys
from math import isqrt

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
N = max(2, n + 1)

# --8<-- [start:core]
prime = []
is_prime = [False] * N


def Eratosthenes(n):
    is_prime[0] = is_prime[1] = False
    for i in range(2, n + 1):
        is_prime[i] = True
    # 让 i 循环到 <= sqrt(n)
    for i in range(2, isqrt(n) + 1):  # `isqrt` 是 Python 3.8 新增的函数
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    for i in range(2, n + 1):
        if is_prime[i]:
            prime.append(i)


# --8<-- [end:core]

Eratosthenes(n)
for k in data[2 : 2 + data[1]]:
    print(prime[k - 1])
