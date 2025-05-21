# STERN-BROCOT TREE FRACTION FINDING.
# --8<-- [start:core]
# Locate a given fraction in the Stern-Brocot tree.
def find(x, y):
    res = []
    right = True
    while y:
        res.append([x // y, ("R" if right else "L")])
        x, y = y, x % y
        right ^= 1
    res[-1][0] -= 1
    return res


# --8<-- [end:core]
if __name__ == "__main__":
    x, y = map(int, input().split())
    print("".join(ch * t for t, ch in find(x, y)))
