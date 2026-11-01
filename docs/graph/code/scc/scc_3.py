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


stack1 = [0] * N
stack2 = [0] * N


# --8<-- [start:core]
def garbow(u):
    global p1, p2, dfs_clock, scc_cnt
    p1 = p1 + 1
    p2 = p2 + 1
    stack1[p1] = u
    stack2[p2] = u
    dfs_clock = dfs_clock + 1
    low[u] = dfs_clock
    i = head[u]
    while i:
        v = e[i].to
        if low[v] == False:
            garbow(v)
        elif sccno[v] == False:
            while low[stack2[p2]] > low[v]:
                p2 = p2 - 1
        i = e[i].next
    if stack2[p2] == u:
        p2 = p2 - 1
        scc_cnt = scc_cnt + 1
        while True:
            v = stack1[p1]
            sccno[v] = scc_cnt
            p1 = p1 - 1
            if v == u:
                break


def find_scc(n):
    global dfs_clock, scc_cnt, p1, p2, sccno, low
    dfs_clock = scc_cnt = 0
    p1 = p2 = 0
    sccno = [0] * (n + 1)
    low = [0] * (n + 1)
    for i in range(1, n + 1):
        if low[i] == False:
            garbow(i)


# --8<-- [end:core]

find_scc(n)
answer(sccno, scc_cnt)
