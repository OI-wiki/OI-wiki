# Sample source: https://www.luogu.com.cn/problem/P1993
# --8<-- [start:core]
def Bellman_Ford():
    for i in range(0, n):
        jud = False
        for j in range(1, n + 1):
            k = h[j]
            while ~k:
                if dist[j] > dist[p[k]] + w[k]:
                    dist[j] = dist[p[k]] + w[k]
                    jud = True
                k = nxt[k]
        if jud == False:
            break
    for i in range(1, n + 1):
        j = h[i]
        while ~j:
            if dist[i] > dist[p[j]] + w[j]:
                return False
            j = nxt[j]
    return True


# --8<-- [end:core]

n, m = map(int, input().split())
h = [-1] * (n + 1)
nxt, p, w = [], [], []
dist = [0] * (n + 1)


def add(target, source, weight):
    nxt.append(h[target])
    p.append(source)
    w.append(weight)
    h[target] = len(p) - 1


for _ in range(m):
    operation = list(map(int, input().split()))
    kind, a, b = operation[:3]
    if kind == 1:
        add(b, a, -operation[3])
    elif kind == 2:
        add(a, b, operation[3])
    else:
        add(a, b, 0)
        add(b, a, 0)
print("Yes" if Bellman_Ford() else "No")
