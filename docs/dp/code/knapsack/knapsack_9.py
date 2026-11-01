n, m, t = map(int, input().split())
costs = [tuple(map(int, input().split())) for _ in range(n)]
dp = [[0] * (t + 1) for _ in range(m + 1)]
# --8<-- [start:core]
for k in range(1, n + 1):
    mi, ti = costs[k - 1]
    for i in range(m, mi - 1, -1):  # 对经费进行一层枚举
        for j in range(t, ti - 1, -1):  # 对时间进行一层枚举
            dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1)
# --8<-- [end:core]
print(dp[m][t])
