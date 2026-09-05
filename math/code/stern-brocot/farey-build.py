# FAREY SEQUENCE BUILDING.
# --8<-- [start:core]
# Farey Sequence of Order N.
def build(n, a=0, b=1, c=1, d=1, init=True):
    x, y = a + c, b + d
    if y > n:
        return
    if init:
        print("0/1", end=" ")
    build(n, a, b, x, y, False)
    print(f"{x}/{y}", end=" ")
    build(n, x, y, c, d, False)
    if init:
        print("1/1", end=" ")


# --8<-- [end:core]
if __name__ == "__main__":
    build(int(input()))
