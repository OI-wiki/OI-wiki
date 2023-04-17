n, l, r = map(float, input().split())
a = [i * float(j) for i, j in enumerate(input().split()[::-1])][1:]
while r - l > 1e-6:
    mid = (l + r) / 2
    if sum(mid ** i * j for i, j in enumerate(a)) < 0:
        r = mid
    else:
        l = mid
print(l)