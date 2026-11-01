# Sample provenance: https://www.luogu.com.cn/problem/P2341 (same Popular Cows exercise linked in the article); additional disconnected/singleton cases.
import sys
from types import SimpleNamespace

sys.setrecursionlimit(1000000)
n, m = map(int, input().split())
N = n + 1
h = [0] * N
head = h
e = [None]
edges = []
g = [[] for _ in range(N)]
g2 = [[] for _ in range(N)]
for _ in range(m):
    u, v = map(int, input().split())
    edges.append((u, v))
    e.append(SimpleNamespace(t=v, nex=h[u], to=v, next=h[u]))
    h[u] = len(e) - 1
    g[u].append(v)
    g2[v].append(u)


def answer(component, count):
    sizes = [0] * (count + 1)
    outgoing = [False] * (count + 1)
    for u in range(1, n + 1):
        sizes[component[u]] += 1
    for u, v in edges:
        if component[u] != component[v]:
            outgoing[component[u]] = True
    sinks = [c for c in range(1, count + 1) if not outgoing[c]]
    print(sizes[sinks[0]] if len(sinks) == 1 else 0)


# --8<-- [start:core]
# g 是原图，g2 是反图
N = 100005
vis = [False] * N
color = [0] * N
s = []  # 后序遍历
sccCnt = 0


def dfs1(u):
    vis[u] = True
    for v in g[u]:
        if not vis[v]:
            dfs1(v)
    s.append(u)


def dfs2(u):
    color[u] = sccCnt
    for v in g2[u]:
        if color[v] == 0:
            dfs2(v)


def kosaraju():
    global sccCnt
    sccCnt = 0
    for i in range(1, n + 1):
        if not vis[i]:
            dfs1(i)
    for i in range(len(s) - 1, -1, -1):
        if color[s[i]] == 0:
            sccCnt = sccCnt + 1
            dfs2(s[i])


# --8<-- [end:core]

kosaraju()
answer(color, sccCnt)
