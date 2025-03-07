# STERN-BROCOT TREE FRACTION FINDING.
# Locate a given fraction in the Stern-Brocot tree.
def find(x, y):
    res = []
    a, b, c, d = 0, 1, 1, 0
    right = True
    while x != a + c or y != b + d:
        if right:
            t = (b * x - a * y - 1) // (y * c - x * d)
            res.append((t, "R"))
            a += t * c
            b += t * d
        else:
            t = (y * c - x * d - 1) // (b * x - a * y)
            res.append((t, "L"))
            c += t * a
            d += t * b
        right ^= 1
    return res


if __name__ == "__main__":
    x, y = map(int, input().split())
    print("".join(ch * t for t, ch in find(x, y)))
