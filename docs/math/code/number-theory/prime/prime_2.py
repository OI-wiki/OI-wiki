import sys
from math import isqrt


# --8<-- [start:core]
def isPrime(a):
    if a < 2:
        return False
    for i in range(2, isqrt(a) + 1):
        if a % i == 0:
            return False
    return True


# --8<-- [end:core]

data = list(map(int, sys.stdin.buffer.read().split()))
print(sum(isPrime(x) for x in data[1 : 1 + data[0]]))
