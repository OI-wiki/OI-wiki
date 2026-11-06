import sys

n = int(sys.stdin.buffer.read())

# --8<-- [start:core]
MAXN = 2000 + 5
bell = [[0 for i in range(MAXN + 1)] for j in range(MAXN + 1)]


def f(n):
    bell[0][0] = 1
    for i in range(1, n + 1):
        bell[i][0] = bell[i - 1][i - 1]
        for j in range(1, i + 1):
            bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1]


# --8<-- [end:core]
f(n)
print(bell[n][0])
