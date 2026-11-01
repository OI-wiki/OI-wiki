MAXN = 1000005
# --8<-- [start:example49]
t1 = [0] * MAXN
t2 = [0] * MAXN
n = 0


def lowbit(x):
    return x & (-x)


def add(k, v):
    v1 = k * v
    while k <= n:
        t1[k] = t1[k] + v
        t2[k] = t2[k] + v1
        k = k + lowbit(k)


def getsum(t, k):
    ret = 0
    while k:
        ret = ret + t[k]
        k = k - lowbit(k)
    return ret


def add1(l, r, v):
    add(l, v)
    add(r + 1, -v)


def getsum1(l, r):
    return (
        (r + 1) * getsum(t1, r)
        - l * getsum(t1, l - 1)
        - (getsum(t2, r) - getsum(t2, l - 1))
    )


# --8<-- [end:example49]

n, q = map(int, input().split())
for j, x in enumerate(map(int, input().split()), 1):
    add1(j, j, x)
for _ in range(q):
    args = list(map(int, input().split()))
    if args[0] == 1:
        add1(*args[1:])
    else:
        print(getsum1(*args[1:]))
