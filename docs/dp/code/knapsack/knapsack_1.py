n, W = map(int, input().split())
w, v = [0], [0]
for _ in range(n):
    weight, value = map(int, input().split())
    w.append(weight)
    v.append(value)


def wrong_order():
    # 故意保留错误的枚举顺序：这实际上是完全背包．
    f = [0] * (W + 1)
    # --8<-- [start:wrong]
    for i in range(1, n + 1):
        for l in range(0, W - w[i] + 1):
            f[l + w[i]] = max(f[l] + v[i], f[l + w[i]])
    # 由 f[i][l + w[i]] = max(max(f[i - 1][l + w[i]], f[i - 1][l] + v[i]),
    # f[i][l + w[i]]) 简化而来
    # --8<-- [end:wrong]
    return f[W]


f = [0] * (W + 1)
# --8<-- [start:core]
for i in range(1, n + 1):
    for l in range(W, w[i] - 1, -1):
        f[l] = max(f[l], f[l - w[i]] + v[i])
# --8<-- [end:core]
assert wrong_order() >= f[W]
print(f[W])
