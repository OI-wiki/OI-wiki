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
    dsu = Dsu(n + 1)
    for _ in range(m):
        z, x, y = map(int, input().split())
        if z == 1:
            dsu.unite(x, y)
        else:
            print("Y" if dsu.find(x) == dsu.find(y) else "N")
