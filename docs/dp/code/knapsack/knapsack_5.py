from types import SimpleNamespace

m, W = map(int, input().split())
list = [SimpleNamespace(w=0, v=0) for _ in range(100001)]
# --8<-- [start:core]
index = 0
for i in range(1, m + 1):
    c = 1
    h, p, k = map(int, input().split())
    while k > c:
        k -= c
        index += 1
        list[index].w = c * p
        list[index].v = c * h
        c *= 2
    index += 1
    list[index].w = p * k
    list[index].v = h * k
# --8<-- [end:core]
f = [0] * (W + 1)
for i in range(1, index + 1):
    for weight in range(W, list[i].w - 1, -1):
        f[weight] = max(f[weight], f[weight - list[i].w] + list[i].v)
print(f[W])
