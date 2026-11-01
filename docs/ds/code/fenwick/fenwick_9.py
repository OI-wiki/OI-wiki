MAXN = 1000005


def lowbit(x):
    return x & -x


# --8<-- [start:example62]
# 时间戳优化
tag = [0] * MAXN
t = [0] * MAXN
Tag = 0


def reset():
    global Tag
    Tag = Tag + 1


def add(k, v):
    while k <= n:
        if tag[k] != Tag:
            t[k] = 0
        t[k] = t[k] + v
        tag[k] = Tag
        k = k + lowbit(k)


def getsum(k):
    ret = 0
    while k:
        if tag[k] == Tag:
            ret = ret + t[k]
        k = k - lowbit(k)
    return ret


# --8<-- [end:example62]

n, q = map(int, input().split())
for _ in range(q):
    args = list(map(int, input().split()))
    if args[0] == 0:
        reset()
    elif args[0] == 1:
        add(*args[1:])
    else:
        print(getsum(args[1]))
