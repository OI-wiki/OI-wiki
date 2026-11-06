import sys


# --8<-- [start:core]
def Exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x, y = Exgcd(b, a % b)
    return d, y, x - (a // b) * y


# --8<-- [end:core]

a, b = map(int, sys.stdin.buffer.read().split())
d, x, y = Exgcd(a, b)
assert a * x + b * y == d
print(d)
