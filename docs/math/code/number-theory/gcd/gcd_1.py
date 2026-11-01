import sys


# --8<-- [start:core]
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


# --8<-- [end:core]

a, b = map(int, sys.stdin.buffer.read().split())
print(gcd(a, b))
