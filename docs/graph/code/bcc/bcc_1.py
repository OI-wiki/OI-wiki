# Sample provenance: DFS reachability demonstration; no original judge problem is attached to this fragment.
# --8<-- [start:core]
def DFS(p):
    visited[p] = True
    for to in edge[p]:
        if visited[to] == False:
            DFS(to)


# --8<-- [end:core]

import sys

sys.setrecursionlimit(1000000)
n, m, start = map(int, input().split())
edge = [[] for _ in range(n + 1)]
visited = [False] * (n + 1)
for _ in range(m):
    u, v = map(int, input().split())
    edge[u].append(v)
    edge[v].append(u)
DFS(start)
print(*(int(flag) for flag in visited[1:]))
