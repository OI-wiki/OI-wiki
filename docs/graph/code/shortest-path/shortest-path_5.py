# Sample provenance: https://www.luogu.com.cn/problem/P3371 and the same regression fixtures as the C++ version.
n, m, source = map(int, input().split())
# --8<-- [start:core]
from collections import deque


class Edge:
    def __init__(self, v=0, w=0):
        self.v = v
        self.w = w


e = [[] for _ in range(n + 1)]
INF = float("inf")


def spfa(n, s):
    global dis
    dis = [INF] * (n + 1)
    cnt = [0] * (n + 1)
    vis = [False] * (n + 1)
    q = deque()

    dis[s] = 0
    vis[s] = True
    q.append(s)
    while q:
        u = q.popleft()
        vis[u] = False
        for ed in e[u]:
            v, w = ed.v, ed.w
            if dis[v] > dis[u] + w:
                dis[v] = dis[u] + w
                cnt[v] = cnt[u] + 1  # 记录最短路经过的边数
                if cnt[v] >= n:
                    return False
                # 在不经过负环的情况下，最短路至多经过 n - 1 条边
                # 因此如果经过了多于 n 条边，一定说明经过了负环
                if not vis[v]:
                    q.append(v)
                    vis[v] = True
    return True


# --8<-- [end:core]

for _ in range(m):
    u, v, w = map(int, input().split())
    e[u].append(Edge(v, w))
negative = not spfa(n, source)
if negative:
    print("NEGATIVE CYCLE")
else:
    print(*(dis[u] if dis[u] != float("inf") else 2147483647 for u in range(1, n + 1)))
