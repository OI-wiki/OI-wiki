import sys


# --8<-- [start:core]
def isPrime(a):
    if a < 2:
        return False
    for i in range(2, a):
        if a % i == 0:
            return False
    return True


# --8<-- [end:core]

data = list(map(int, sys.stdin.buffer.read().split()))
print(sum(isPrime(x) for x in data[1 : 1 + data[0]]))
