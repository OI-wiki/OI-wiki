from types import SimpleNamespace

# --8<-- [start:core]
from queue import Queue


def bfs(u):
    Q = Queue()
    Q.put(u)
    vis[u] = True
    d[u] = 0
    p[u] = -1
    while Q.qsize() != 0:
        u = Q.get()
        i = head[u]
        while i:
            if vis[e[i].to] == False:
                Q.put(e[i].to)
                vis[e[i].to] = True
                d[e[i].to] = d[u] + 1
                p[e[i].to] = u
            i = e[i].nxt


def restore(x):
    res = []
    v = x
    while v != -1:
        res.append(v)
        v = p[v]
    res.reverse()
    print(*res)


# --8<-- [end:core]

n, m = map(int, input().split())
head = [0] * (n + 1)
e = [None]
vis = [False] * (n + 1)
d = [-1] * (n + 1)
p = [-1] * (n + 1)
for _ in range(m):
    u, v = map(int, input().split())
    e.append(SimpleNamespace(to=v, nxt=head[u]))
    head[u] = len(e) - 1
start, target = map(int, input().split())
bfs(start)
print(d[target])
if vis[target]:
    restore(target)
