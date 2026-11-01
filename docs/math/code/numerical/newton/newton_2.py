import sys


# --8<-- [start:core]
def isqrt_newton(n):
    if n == 0:
        return 0
    x = 1
    decreased = False
    while True:
        nx = (x + n // x) // 2
        if x == nx or (nx > x and decreased):
            break
        decreased = nx < x
        x = nx
    return x


# --8<-- [end:core]
print(isqrt_newton(int(sys.stdin.buffer.read())))
