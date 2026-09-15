class Dsu:
    def __init__(self, size):
        self.pa = list(range(size))
        self.size = [1] * size

    def find(self, x):
        if self.pa[x] != x:
            self.pa[x] = self.find(self.pa[x])
        return self.pa[x]

    def unite(self, x, y):
        x, y = self.find(x), self.find(y)
        if x == y:
            return
        if self.size[x] < self.size[y]:
            x, y = y, x
        self.pa[y] = x
        self.size[x] += self.size[y]


if __name__ == "__main__":
    n, m = map(int, input().split())
    dsu = Dsu(n * 3 + 1)
    res = 0
    for _ in range(m):
        op, x, y = map(int, input().split())
        if x > n or y > n:
            res += 1
        elif op == 1:
            if dsu.find(x) == dsu.find(y + n) or dsu.find(x) == dsu.find(y + (n << 1)):
                res += 1
            else:
                dsu.unite(x, y)
                dsu.unite(x + n, y + n)
                dsu.unite(x + n * 2, y + n * 2)
        else:
            if dsu.find(x) == dsu.find(y) or dsu.find(x) == dsu.find(y + n):
                res += 1
            else:
                dsu.unite(x, y + n * 2)
                dsu.unite(x + n, y)
                dsu.unite(x + n * 2, y + n)
    print(res)
