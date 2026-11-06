def lowbit(x):
    """
    x 的二进制中，最低位的 1 以及后面所有 0 组成的数．
    lowbit(0b01011000) == 0b00001000
            ~~~~~^~~
    lowbit(0b01110010) == 0b00000010
            ~~~~~~~^~
    """
    return x & -x


def getsum(x):  # a[1]..a[x]的和
    ans = 0
    while x > 0:
        ans = ans + c[x]
        x = x - lowbit(x)
    return ans


def add(x, k):
    while x <= n:  # 不能越界
        c[x] = c[x] + k
        x = x + lowbit(x)


# --8<-- [start:example58]
# Θ(n) 建树
def init():
    for i in range(1, n + 1):
        t[i] = t[i] + a[i]
        j = i + lowbit(i)
        if j <= n:
            t[j] = t[j] + t[i]


# --8<-- [end:example58]

n, q = map(int, input().split())
c = [0] * (n + 1)
t = c
a = [0] + list(map(int, input().split()))
sum = [0] * (n + 1)
for j in range(1, n + 1):
    sum[j] = sum[j - 1] + a[j]
init()
for _ in range(q):
    op, x, y = map(int, input().split())
    if op == 1:
        add(x, y)
    else:
        print(getsum(y) - getsum(x - 1))
