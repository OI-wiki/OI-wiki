# --8<-- [start:core]
# adj : List[List[int]] 邻接表
# vis : List[bool] 记录节点是否已经遍历


def dfs(u: int) -> None:
    vis[u] = True
    for v in adj[u]:
        if not vis[v]:
            dfs(v)


# --8<-- [end:core]

n, m = map(int, input().split())
adj = [[] for _ in range(n + 1)]
vis = [False] * (n + 1)
for _ in range(m):
    u, v = map(int, input().split())
    adj[u].append(v)
start, target = map(int, input().split())
dfs(start)
print(*(i for i in range(1, n + 1) if vis[i]))
