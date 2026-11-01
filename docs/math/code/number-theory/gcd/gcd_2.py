import sys


# --8<-- [start:core]
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


# --8<-- [end:core]

a, b = map(int, sys.stdin.buffer.read().split())
print(gcd(a, b))
