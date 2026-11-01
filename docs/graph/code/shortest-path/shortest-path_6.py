# Sample provenance: https://www.luogu.com.cn/problem/P3371 and the same regression fixtures as the C++ version.
n, m, source = map(int, input().split())


# --8<-- [start:core]
class Edge:
    def __init__(self, v=0, w=0):
        self.v = v
        self.w = w


e = [[] for _ in range(n + 1)]
INF = float("inf")


def dijkstra(n, s):
    global dis
    dis = [INF] * (n + 1)
    vis = [0] * (n + 1)

    dis[s] = 0
    for i in range(1, n + 1):
        u = 0
        mind = INF
        for j in range(1, n + 1):
            if not vis[j] and dis[j] < mind:
                u = j
                mind = dis[j]
        if not u:
            break
        vis[u] = True
        for ed in e[u]:
            v, w = ed.v, ed.w
            if dis[v] > dis[u] + w:
                dis[v] = dis[u] + w


# --8<-- [end:core]

for _ in range(m):
    u, v, w = map(int, input().split())
    e[u].append(Edge(v, w))
dijkstra(n, source)
negative = False
if negative:
    print("NEGATIVE CYCLE")
else:
    print(*(dis[u] if dis[u] != float("inf") else 2147483647 for u in range(1, n + 1)))
