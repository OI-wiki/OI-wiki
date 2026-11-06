# Sample provenance: https://www.luogu.com.cn/problem/P6086 and two-vertex boundary cases.
import heapq
import sys

sys.setrecursionlimit(1000000)
data = iter(map(int, sys.stdin.buffer.read().split()))
n, mode = next(data), next(data)

# --8<-- [start:core]
# 同样以 0 为起点
adj = [[]]
parent = []


def dfs(v):
    for u in adj[v]:
        if u != parent[v]:
            parent[u] = v
            dfs(u)


def pruefer_code():
    global parent
    n = len(adj)
    parent = [0] * n
    parent[n - 1] = -1
    dfs(n - 1)

    ptr = -1
    degree = [0] * n
    for i in range(0, n):
        degree[i] = len(adj[i])
        if degree[i] == 1 and ptr == -1:
            ptr = i

    code = [0] * (n - 2)
    leaf = ptr
    for i in range(0, n - 2):
        next = parent[leaf]
        code[i] = next
        degree[next] = degree[next] - 1
        if degree[next] == 1 and next < ptr:
            leaf = next
        else:
            ptr = ptr + 1
            while degree[ptr] != 1:
                ptr = ptr + 1
            leaf = ptr
    return code


# --8<-- [end:core]


def decode(code):
    degree = [1] * n
    for v in code:
        degree[v] += 1
    leaves = [v for v in range(n) if degree[v] == 1]
    heapq.heapify(leaves)
    tree = [[] for _ in range(n)]
    for v in code:
        u = heapq.heappop(leaves)
        tree[u].append(v)
        tree[v].append(u)
        degree[v] -= 1
        if degree[v] == 1:
            heapq.heappush(leaves, v)
    u, v = leaves
    tree[u].append(v)
    tree[v].append(u)
    parents = [-1] * n
    pending = [n - 1]
    while pending:
        u = pending.pop()
        for v in tree[u]:
            if v != parents[u]:
                parents[v] = u
                pending.append(v)
    return parents


answer = 0
if mode == 1:
    adj = [[] for _ in range(n)]
    for u in range(n - 1):
        v = next(data) - 1
        adj[u].append(v)
        adj[v].append(u)
    code = pruefer_code()
    for i, v in enumerate(code, 1):
        answer ^= i * (v + 1)
else:
    code = [next(data) - 1 for _ in range(n - 2)]
    parents = decode(code)
    for u in range(n - 1):
        answer ^= (u + 1) * (parents[u] + 1)
print(answer)
