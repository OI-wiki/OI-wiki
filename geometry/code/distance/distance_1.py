minx = 0x7FFFFFFF
maxx = -0x7FFFFFFF
miny = 0x7FFFFFFF
maxy = -0x7FFFFFFF
n = int(input())
for i in range(1, n + 1):
    x, y = map(lambda x: int(x), input().split())
    minx = min(minx, x + y)
    maxx = max(maxx, x + y)
    miny = min(miny, x - y)
    maxy = max(maxy, x - y)
print(max(maxx - minx, maxy - miny))
