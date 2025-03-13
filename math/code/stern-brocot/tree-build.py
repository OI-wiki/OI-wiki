# STERN-BROCOT TREE BUILDING.
# In-Order Transversal of Stern-Brocot Tree till Layer N.
def build(n, a=0, b=1, c=1, d=0, level=1):
    if level > n:
        return
    x, y = a + c, b + d
    build(n, a, b, x, y, level + 1)
    print(f"{x}/{y}", end=" ")
    build(n, x, y, c, d, level + 1)


if __name__ == "__main__":
    build(int(input()))
