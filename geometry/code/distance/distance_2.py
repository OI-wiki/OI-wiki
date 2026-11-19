minx = 0x7FFFFFFF
maxx = -0x7FFFFFFF
miny = 0x7FFFFFFF
maxy = -0x7FFFFFFF
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
