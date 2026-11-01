# Sample provenance: Same all-pairs shortest-path demonstration as the C++ implementation.
n, m = map(int, input().split())
INF = float("inf")
f = [[INF] * (n + 1) for _ in range(n + 1)]
for u in range(1, n + 1):
    f[u][u] = 0
for _ in range(m):
    u, v, w = map(int, input().split())
    f[u][v] = min(f[u][v], w)

# --8<-- [start:core]
for k in range(1, n + 1):
    for x in range(1, n + 1):
        for y in range(1, n + 1):
            f[x][y] = min(f[x][y], f[x][k] + f[k][y])
# --8<-- [end:core]

for row in f[1:]:
    print(*(value if value != INF else "INF" for value in row[1:]))
