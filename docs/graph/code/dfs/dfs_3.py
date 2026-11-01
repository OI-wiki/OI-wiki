from types import SimpleNamespace


# --8<-- [start:core]
def dfs(u):
    vis[u] = True
    i = head[u]
    while i:
        if vis[e[i].t] == False:
            dfs(e[i].t)
        i = e[i].x


# --8<-- [end:core]

n, m = map(int, input().split())
head = [0] * (n + 1)
e = [None]
vis = [False] * (n + 1)
for _ in range(m):
    u, v = map(int, input().split())
    e.append(SimpleNamespace(t=v, x=head[u]))
    head[u] = len(e) - 1
start, target = map(int, input().split())
dfs(start)
print(*(i for i in range(1, n + 1) if vis[i]))
