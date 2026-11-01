# --8<-- [start:example29]
class Dsu:
    def __init__(self, size):
        self.pa = list(range(size))

    # --8<-- [end:example29]
    # --8<-- [start:example31]
    def find(self, x):
        return x if self.pa[x] == x else self.find(self.pa[x])

    # --8<-- [end:example31]
    # --8<-- [start:example35]
    def unite(self, x, y):
        self.pa[self.find(x)] = self.find(y)

    # --8<-- [end:example35]


if __name__ == "__main__":
    n, m = map(int, input().split())
    d = Dsu(n + 1)
    for _ in range(m):
        z, x, y = map(int, input().split())
        if z == 1:
            d.unite(x, y)
        else:
            print("Y" if d.find(x) == d.find(y) else "N")
