import sys


def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x, y = exgcd(b, a % b)
    return d, y, x - a // b * y


data = list(map(int, sys.stdin.buffer.read().split()))
k = data[0]
p = data[1::2]
a = data[2::2]
x = [0] * k
r = [[0] * k for _ in range(k)]
for i in range(k):
    for j in range(i + 1, k):
        r[i][j] = exgcd(p[i], p[j])[1] % p[j]
# --8<-- [start:core]
for i in range(0, k):
    x[i] = a[i]
    for j in range(0, i):
        x[i] = r[j][i] * (x[i] - x[j])
        x[i] = x[i] % p[i]
        if x[i] < 0:
            x[i] = x[i] + p[i]
# --8<-- [end:core]
ans = 0
product = 1
for i in range(k):
    ans += product * x[i]
    product *= p[i]
print(ans)
