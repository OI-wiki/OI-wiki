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
dfn = [0] * N
low = [0] * N
dfncnt = 0
s = [0] * N
in_stack = [0] * N
tp = 0
scc = [0] * N
sc = 0  # 结点 i 所在 SCC 的编号
sz = [0] * N  # 强连通 i 的大小


def tarjan(u):
    global dfncnt, tp, sc
    dfncnt = dfncnt + 1
    tp = tp + 1
    low[u] = dfn[u] = dfncnt
    s[tp] = u
    in_stack[u] = 1
    i = h[u]
    while i:
        v = e[i].t
        if dfn[v] == False:
            tarjan(v)
            low[u] = min(low[u], low[v])
        elif in_stack[v]:
            low[u] = min(low[u], dfn[v])
        i = e[i].nex
    if dfn[u] == low[u]:
        sc = sc + 1
        while s[tp] != u:
            scc[s[tp]] = sc
            sz[sc] = sz[sc] + 1
            in_stack[s[tp]] = 0
            tp = tp - 1
        scc[s[tp]] = sc
        sz[sc] = sz[sc] + 1
        in_stack[s[tp]] = 0
        tp = tp - 1


# --8<-- [end:core]

for u in range(1, n + 1):
    if not dfn[u]:
        tarjan(u)
answer(scc, sc)
