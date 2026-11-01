tcost = [0] * 103
mget = [0] * 103
ans = 0


def dfs(pos, tleft, tans):
    global ans
    if tleft < 0:
        return
    if pos == n + 1:
        ans = max(ans, tans)
        return
    dfs(pos + 1, tleft, tans)
    dfs(pos + 1, tleft - tcost[pos], tans + mget[pos])


t, n = map(lambda x: int(x), input().split())
for i in range(1, n + 1):
    tcost[i], mget[i] = map(lambda x: int(x), input().split())
dfs(1, t, 0)
print(ans)
