import sys


# --8<-- [start:core]
def eulerianNumber(n, m):
    if m >= n or n == 0:
        return 0
    if m == 0:
        return 1
    return ((n - m) * eulerianNumber(n - 1, m - 1)) + (
        (m + 1) * eulerianNumber(n - 1, m)
    )


# --8<-- [end:core]
n, m = map(int, sys.stdin.buffer.read().split())
print(eulerianNumber(n, m))
