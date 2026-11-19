M = 2


class DSU:
    def __init__(self, size: int):
        self.pa = list(range(size))
        self.size = [1] * size
        self.dist = [0] * size

    def find(self, x: int) -> int:
        if self.pa[x] == x:
            return x
        y = self.find(self.pa[x])
        self.dist[x] = (self.dist[x] + self.dist[self.pa[x]]) % M
        self.pa[x] = y
        return y

    def unite(self, x: int, y: int, d: int) -> bool:
        self.find(x)
        self.find(y)
        d = (d + M - self.dist[y]) % M
        d = (d + self.dist[x]) % M
        x, y = self.pa[x], self.pa[y]
        if x == y:
            return d == 0
        if self.size[x] < self.size[y]:
            x, y = y, x
            d = (M - d) % M
        self.pa[y] = x
        self.size[x] += self.size[y]
        self.dist[y] = d
        return True


if __name__ == "__main__":
    n, m = map(int, input().split())
    dsu = DSU((n + 1) << 5)
    for _ in range(m):
        x, y, z = map(int, input().split())
        for i in range(31):
            if not dsu.unite((x << 5) | i, (y << 5) | i, (z >> i) & 1):
                print(-1)
                exit()

    a = [0] * (n + 1)
    cnt = [0] * ((n + 1) << 5)

    for i in range(1, (n + 1) << 5):
        dsu.find(i)
        if dsu.dist[i]:
            cnt[dsu.pa[i]] += 1

    for i in range(1, n + 1):
        for j in range(31):
            x = (i << 5) | j
            y = dsu.pa[x]
            if (cnt[y] > dsu.size[y] // 2) ^ dsu.dist[x]:
                a[i] |= 1 << j

    print(" ".join(map(str, a[1:])))
