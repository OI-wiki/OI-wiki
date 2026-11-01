from dataclasses import dataclass
from math import hypot
import sys

N = 100005


@dataclass(order=True)
class Point:
    x: float
    y: float

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        return self.x * other.y - self.y * other.x


mx = 0

# --8<-- [start:core]
sta = [0] * N
top = 0  # 将凸包上的节点编号存在栈里，第一个和最后一个节点编号相同


def pf(x):
    return x * x


def dis(p, q):
    return pf(a[p].x - a[q].x) + pf(a[p].y - a[q].y)


def sqr(p, q, y):
    return abs((a[q] - a[p]) * (a[y] - a[q]))


def get_longest():  # 求凸包直径
    global mx
    j = 3
    if top < 4:
        mx = dis(sta[1], sta[2])
        return
    for i in range(1, top):
        while sqr(sta[i], sta[i + 1], sta[j]) <= sqr(
            sta[i], sta[i + 1], sta[j % top + 1]
        ):
            j = j % top + 1
        mx = max(mx, max(dis(sta[i + 1], sta[j]), dis(sta[i], sta[j])))


# --8<-- [end:core]


def convex_hull():
    global sta, top
    h = []
    for i in range(len(a)):
        while len(h) >= 2 and (a[h[-1]] - a[h[-2]]) * (a[i] - a[h[-1]]) <= 0:
            h.pop()
        h.append(i)
    lower = len(h)
    for i in range(len(a) - 2, -1, -1):
        while len(h) > lower and (a[h[-1]] - a[h[-2]]) * (a[i] - a[h[-1]]) <= 0:
            h.pop()
        h.append(i)
    if len(a) == 1:
        h.append(0)
    sta = [0] + h
    top = len(h)


data = list(map(int, sys.stdin.buffer.read().split()))
a = [Point(x, y) for x, y in sorted(set(zip(data[1::2], data[2::2])))]
convex_hull()
get_longest()
print(mx)
