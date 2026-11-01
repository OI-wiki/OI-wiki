# --8<-- [start:core]
class Edge:
    def __init__(self, u=0, v=0):
        self.u = u
        self.v = v


n, m = map(int, input().split())

e = [Edge() for _ in range(m)]
vis = [False] * (n + 1)

for i in range(m):
    e[i].u, e[i].v = map(int, input().split())


def find_edge(u, v):
    for i in range(m):
        if e[i].u == u and e[i].v == v:
            return True
    return False


def dfs(u):
    if vis[u]:
        return
    vis[u] = True
    for i in range(m):
        if e[i].u == u:
            dfs(e[i].v)


# --8<-- [end:core]

start, target = map(int, input().split())
print(int(find_edge(start, target)))
dfs(start)
print(*(i for i in range(1, n + 1) if vis[i]))
