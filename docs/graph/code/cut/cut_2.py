# Sample provenance: Same simple-graph bridge demonstration as the C++ version.
import sys

sys.setrecursionlimit(1000000)
n, m = map(int, input().split())
MAXN = n + 1

# --8<-- [start:core]
low = [0] * MAXN
dfn = [0] * MAXN
idx = 0
isbridge = [False] * MAXN
G = [[] for _ in range(MAXN)]
cnt_bridge = 0
father = [0] * MAXN


def tarjan(u, fa):
    global idx, cnt_bridge
    father[u] = fa
    idx = idx + 1
    low[u] = dfn[u] = idx
    for i in range(0, len(G[u])):
        v = G[u][i]
        if dfn[v] == False:
            tarjan(v, u)
            low[u] = min(low[u], low[v])
            if low[v] > dfn[u]:
                isbridge[v] = True
                cnt_bridge = cnt_bridge + 1
        elif v != fa:
            low[u] = min(low[u], dfn[v])


# --8<-- [end:core]

for _ in range(m):
    u, v = map(int, input().split())
    G[u].append(v)
    G[v].append(u)
for u in range(1, n + 1):
    if not dfn[u]:
        tarjan(u, 0)
bridges = sorted(
    (min(u, father[u]), max(u, father[u])) for u in range(1, n + 1) if isbridge[u]
)
print(cnt_bridge)
for u, v in bridges:
    print(u, v)
