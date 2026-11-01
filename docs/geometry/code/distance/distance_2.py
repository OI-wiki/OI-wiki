minx = float("inf")
maxx = -float("inf")
miny = float("inf")
maxy = -float("inf")
n = int(input())
for i in range(1, n + 1):
    a, b = map(lambda x: int(x), input().split())
    x = a + b
    y = a - b
    minx = min(minx, x)
    maxx = max(maxx, x)
    miny = min(miny, y)
    maxy = max(maxy, y)
print(max(maxx - minx, maxy - miny))
