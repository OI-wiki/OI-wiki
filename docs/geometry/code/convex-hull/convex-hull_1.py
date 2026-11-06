from dataclasses import dataclass
from math import hypot
import sys


@dataclass(order=True)
class Point:
    x: float
    y: float

    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        return self.x * other.y - self.y * other.x


data = list(map(float, sys.stdin.buffer.read().split()))
points = sorted(set(zip(data[1::2], data[2::2])))
n = len(points)
p = [Point(0, 0)] + [Point(x, y) for x, y in points]
h = [None] * (2 * n + 2)
used = [False] * (n + 1)

# --8<-- [start:core]
stk = [0] * (2 * n + 2)  # 是整型，存的是下标

tp = 0  # 初始化栈
p[1:] = sorted(p[1:])  # 对点进行排序
tp = tp + 1
stk[tp] = 1
# 栈内添加第一个元素，且不更新 used，使得 1 在最后封闭凸包时也对单调栈更新
for i in range(2, n + 1):
    while tp >= 2 and (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0:
        # 下一行 * 操作符被重载为叉积
        used[stk[tp]] = 0
        tp = tp - 1
    used[i] = 1  # used 表示在凸壳上
    tp = tp + 1
    stk[tp] = i
tmp = tp  # tmp 表示下凸壳大小
for i in range(n - 1, 0, -1):
    if used[i] == False:
        #      ↓求上凸壳时不影响下凸壳
        while tp > tmp and (p[stk[tp]] - p[stk[tp - 1]]) * (p[i] - p[stk[tp]]) <= 0:
            used[stk[tp]] = 0
            tp = tp - 1
        used[i] = 1
        tp = tp + 1
        stk[tp] = i
for i in range(1, tp + 1):
    h[i] = p[stk[i]]
ans = tp - 1
# --8<-- [end:core]

perimeter = sum(
    hypot(h[i].x - h[i + 1].x, h[i].y - h[i + 1].y) for i in range(1, ans + 1)
)
print(f"{perimeter:.2f}")
