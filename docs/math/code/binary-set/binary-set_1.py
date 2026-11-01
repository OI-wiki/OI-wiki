import sys


# --8<-- [start:mod]
def modPowerOfTwo(x, mod):
    return x & (mod - 1)


# --8<-- [end:mod]
# --8<-- [start:power]
def isPowerOfTwo(n):
    return n > 0 and (n & (n - 1)) == 0


# --8<-- [end:power]
x, m = map(int, sys.stdin.buffer.read().split())
print(modPowerOfTwo(x, m), int(isPowerOfTwo(m)))
