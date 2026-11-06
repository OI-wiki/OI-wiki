MAXN = 100010
INF = float("inf")

# --8<-- [start:sort]
n = 0
a = [0] * MAXN
tmp = [0] * MAXN * 2


def winner(pos1, pos2):
    u = pos1 if pos1 >= n else tmp[pos1]
    v = pos2 if pos2 >= n else tmp[pos2]
    if tmp[u] <= tmp[v]:
        return u
    return v


def create_tree():
    for i in range(0, n):
        tmp[n + i] = a[i]
    for i in range(2 * n - 1, 1, -2):
        k = i // 2
        j = i - 1
        tmp[k] = winner(i, j)
    value = tmp[tmp[1]]
    tmp[tmp[1]] = INF
    return value


def recreate():
    i = tmp[1]
    while i > 1:
        j = k = i // 2
        if i % 2 == 0:
            j = i + 1
        else:
            j = i - 1
        tmp[k] = winner(i, j)
        i = k
    value = tmp[tmp[1]]
    tmp[tmp[1]] = INF
    return value


def tournament_sort():
    if n <= 1:
        return
    value = create_tree()
    for i in range(0, n):
        a[i] = value
        value = recreate()


# --8<-- [end:sort]

if __name__ == "__main__":
    import sys

    data = list(map(int, sys.stdin.buffer.read().split()))
    n = data[0]
    a[:n] = data[1:]
    tournament_sort()
    print(*a[:n])
