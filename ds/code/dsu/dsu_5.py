M = 998244353


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

    def check(self, x: int, y: int) -> int:
        self.find(x)
        self.find(y)
        if self.pa[x] != self.pa[y]:
            return -1
        return (self.dist[y] - self.dist[x] + M) % M


if __name__ == "__main__":
    n, m = map(int, input().split())
    dsu = DSU(n)
    for _ in range(m):
        op, *rest = map(int, input().split())
        if op:
            u, v = rest
            print(dsu.check(u, v))
        else:
            u, v, x = rest
            print(int(dsu.unite(u, v, x)))
