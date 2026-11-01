import sys
from math import isqrt

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
N = max(2, n + 1)

# --8<-- [start:core]
pri = []
not_prime = [False] * N


def pre(n):
    for i in range(2, n + 1):
        if not not_prime[i]:
            pri.append(i)
        for pri_j in pri:
            if i * pri_j > n:
                break
            not_prime[i * pri_j] = True
            if i % pri_j == 0:
                """
                i % pri_j == 0
                换言之，i 之前被 pri_j 筛过了
                由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被
                pri_j 的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break
                掉就好了
                """
                break


# --8<-- [end:core]

pre(n)
for k in data[2 : 2 + data[1]]:
    print(pri[k - 1])
