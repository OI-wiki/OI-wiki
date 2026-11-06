# Sample provenance: Original article input; independently derived DFS/low-link values.
# --8<-- [start:core]
def Tarjan(u):
    global dfc
    dfc = dfc + 1
    low[u] = dfn[u] = dfc  # low 初始化为当前节点 dfn
    for v in G[u]:  # 遍历 u 的相邻节点
        if dfn[v] == False:  # 如果未访问过
            Tarjan(v)  # 递归
            low[u] = min(low[u], low[v])  # 未访问的和 low 取 min
        else:
            low[u] = min(low[u], dfn[v])  # 已访问的和 dfn 取 min


# --8<-- [end:core]

import sys

sys.setrecursionlimit(1000000)
n, m = map(int, input().split())
G = [[] for _ in range(n + 1)]
dfn = [0] * (n + 1)
low = [0] * (n + 1)
dfc = 0
for _ in range(m):
    u, v = map(int, input().split())
    G[u].append(v)
    G[v].append(u)
for u in range(1, n + 1):
    if not dfn[u]:
        Tarjan(u)
print(*dfn[1:])
print(*low[1:])
