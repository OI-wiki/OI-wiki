# STERN-BROCOT TREE FRACTION FINDING.
# --8<-- [start:core]
# Locate a given fraction in the Stern-Brocot tree.
def find(x, y, a=0, b=1, c=1, d=0):
    m = a + c
    n = b + d
    if x == m and y == n:
        return ""
    if x * n < y * m:
        return "L" + find(x, y, a, b, m, n)
    else:
        return "R" + find(x, y, m, n, c, d)


# --8<-- [end:core]
if __name__ == "__main__":
    x, y = map(int, input().split())
    print(find(x, y))
