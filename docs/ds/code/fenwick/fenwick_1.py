# --8<-- [start:example43]
def lowbit(x):
    """
    x 的二进制中，最低位的 1 以及后面所有 0 组成的数．
    lowbit(0b01011000) == 0b00001000
            ~~~~~^~~
    lowbit(0b01110010) == 0b00000010
            ~~~~~~~^~
    """
    return x & -x


# --8<-- [end:example43]
# --8<-- [start:example45]
def getsum(x):  # a[1]..a[x]的和
    ans = 0
    while x > 0:
        ans = ans + c[x]
        x = x - lowbit(x)
    return ans


# --8<-- [end:example45]
# --8<-- [start:example47]
def add(x, k):
    while x <= n:  # 不能越界
        c[x] = c[x] + k
        x = x + lowbit(x)


# --8<-- [end:example47]

n, q = map(int, input().split())
c = [0] * (n + 1)
for j, x in enumerate(map(int, input().split()), 1):
    add(j, x)
for _ in range(q):
    op, x, y = map(int, input().split())
    if op == 1:
        add(x, y)
    else:
        print(getsum(y) - getsum(x - 1))
