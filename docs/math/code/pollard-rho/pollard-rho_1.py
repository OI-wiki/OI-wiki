import sys
from math import isqrt


# --8<-- [start:core]
def breakdown(N):
    result = []
    for i in range(2, isqrt(N) + 1):
        if N % i == 0:  # 如果 i 能够整除 N，说明 i 为 N 的一个质因子．
            while N % i == 0:
                N //= i
            result.append(i)
    if N != 1:  # 说明再经过操作之后 N 留下了一个素数
        result.append(N)
    return result


# --8<-- [end:core]
data = list(map(int, sys.stdin.buffer.read().split()))
for n in data[1 : 1 + data[0]]:
    a = breakdown(n)
    print("Prime" if a[-1] == n else a[-1])
