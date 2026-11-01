m, n = map(int, input().split())
w, c = [0] * (n + 1), [0] * (n + 1)
t = [[] for _ in range(1010)]
cnt = [0] * 1010
ts = 0
for i in range(1, n + 1):
    w[i], c[i], group = map(int, input().split())
    if not t[group]:
        t[group].append(0)
    t[group].append(i)
    cnt[group] += 1
    ts = max(ts, group)
dp = [0] * (m + 1)
# --8<-- [start:core]
for k in range(1, ts + 1):  # 循环每一组
    for i in range(m, -1, -1):  # 循环背包容量
        for j in range(1, cnt[k] + 1):  # 循环该组的每一个物品
            if i >= w[t[k][j]]:  # 背包容量充足
                dp[i] = max(
                    dp[i], dp[i - w[t[k][j]]] + c[t[k][j]]
                )  # 像0-1背包一样状态转移
# --8<-- [end:core]
print(dp[m])
