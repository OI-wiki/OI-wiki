n = int(input())
a = list(map(int, input().split()))
a = [0] + a + a
sum = [0] * (2 * n + 1)
for i in range(1, 2 * n + 1):
    sum[i] = sum[i - 1] + a[i]
f = [[0] * (2 * n + 1) for _ in range(2 * n + 1)]
g = [[0] * (2 * n + 1) for _ in range(2 * n + 1)]
# --8<-- [start:core]
for len in range(2, n + 1):
    for i in range(1, 2 * n - len + 1):
        j = len + i - 1
        for k in range(i, j):
            f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + sum[j] - sum[i - 1])
# --8<-- [end:core]
for length in range(2, n + 1):
    for i in range(1, 2 * n - length + 1):
        j = i + length - 1
        g[i][j] = min(g[i][k] + g[k + 1][j] + sum[j] - sum[i - 1] for k in range(i, j))
print(min(g[i][i + n - 1] for i in range(1, n + 1)))
print(max(f[i][i + n - 1] for i in range(1, n + 1)))
