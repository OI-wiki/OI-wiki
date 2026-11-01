# Sample provenance: https://www.luogu.com.cn/problem/P3371 and the same regression fixtures as the C++ version.
import heapq
from collections import defaultdict

n, m, source = map(int, input().split())


# --8<-- [start:core]
def dijkstra(e, s):
    """
    输入：
    e:邻接表
    s:起点
    返回：
    dis:从s到每个顶点的最短路长度
    """
    dis = defaultdict(lambda: float("inf"))
    dis[s] = 0
    q = [(0, s)]
    vis = set()
    while q:
        _, u = heapq.heappop(q)
        if u in vis:
            continue
        vis.add(u)
        for v, w in e[u]:
            if dis[v] > dis[u] + w:
                dis[v] = dis[u] + w
                heapq.heappush(q, (dis[v], v))
    return dis


# --8<-- [end:core]

e = [[] for _ in range(n + 1)]

for _ in range(m):
    u, v, w = map(int, input().split())
    e[u].append((v, w))
dis = dijkstra(e, source)
negative = False
if negative:
    print("NEGATIVE CYCLE")
else:
    print(*(dis[u] if dis[u] != float("inf") else 2147483647 for u in range(1, n + 1)))
