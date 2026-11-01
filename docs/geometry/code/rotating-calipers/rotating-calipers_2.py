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


best_edge = 1


def sqr(p, q, y):
    return abs((a[q] - a[p]) * (a[y] - a[q]))


def dot(p, q, y):
    u, v = a[p] - a[y], a[q] - a[y]
    return u.x * v.x + u.y * v.y


# --8<-- [start:core]
def get_biggest():
    global best_edge
    if top < 4:
        return 0.0
    j = 3
    l = 2
    r = 2
    ans = float("inf")
    for i in range(1, top):
        while sqr(sta[i], sta[i + 1], sta[j]) <= sqr(
            sta[i], sta[i + 1], sta[j % top + 1]
        ):
            j = j % top + 1
        while dot(sta[i + 1], sta[r % top + 1], sta[i]) >= dot(
            sta[i + 1], sta[r], sta[i]
        ):
            r = r % top + 1
        if i == 1:
            l = r
        while dot(sta[i + 1], sta[l % top + 1], sta[i]) <= dot(
            sta[i + 1], sta[l], sta[i]
        ):
            l = l % top + 1
        t1 = sqr(sta[i], sta[i + 1], sta[j])
        t2 = dot(sta[i + 1], sta[r], sta[i]) - dot(sta[i + 1], sta[l], sta[i])
        t3 = dot(sta[i + 1], sta[i + 1], sta[i])
        if t1 * t2 / t3 < ans:
            ans = t1 * t2 / t3
            best_edge = i
    return ans


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


data = list(map(float, sys.stdin.buffer.read().split()))
a = [Point(x, y) for x, y in sorted(set(zip(data[1::2], data[2::2])))]
convex_hull()
area = get_biggest()
start = a[sta[best_edge]]
edge = a[sta[best_edge + 1]] - start
length = hypot(edge.x, edge.y)
u = Point(edge.x / length, edge.y / length) if length else Point(1, 0)
v = Point(-u.y, u.x)
projected = [
    Point(
        (p.x - start.x) * u.x + (p.y - start.y) * u.y,
        (p.x - start.x) * v.x + (p.y - start.y) * v.y,
    )
    for p in a
]
lo_u, hi_u = min(p.x for p in projected), max(p.x for p in projected)
lo_v, hi_v = min(p.y for p in projected), max(p.y for p in projected)
corners = [
    Point(start.x + x * u.x + y * v.x, start.y + x * u.y + y * v.y)
    for x, y in [(lo_u, lo_v), (hi_u, lo_v), (hi_u, hi_v), (lo_u, hi_v)]
]
first = min(range(4), key=lambda i: (round(corners[i].y, 8), corners[i].x))
print(f"{area:.5f}")
for i in range(4):
    p = corners[(first + i) % 4]
    x = p.x if abs(p.x) >= 0.000005 else 0.0
    y = p.y if abs(p.y) >= 0.000005 else 0.0
    print(f"{x:.5f} {y:.5f}")
