import sys


def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x, y = exgcd(b, a % b)
    return d, y, x - a // b * y


# --8<-- [start:core]
def CRT(k, a, r):
    n = 1
    ans = 0
    for i in range(1, k + 1):
        n = n * r[i]
    for i in range(1, k + 1):
        m = n // r[i]
        _, b, _ = exgcd(m, r[i])  # b * m mod r[i] = 1
        ans = (ans + a[i] * m * b % n) % n
    return (ans % n + n) % n


# --8<-- [end:core]
data = list(map(int, sys.stdin.buffer.read().split()))
k = data[0]
r = [0] + data[1::2]
a = [0] + data[2::2]
print(CRT(k, a, r))
