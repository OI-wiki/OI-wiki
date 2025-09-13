eps = 1e-6
n, l, r = map(float, input().split())
a = tuple(map(float, input().split()))[::-1]


def f(x):
    return sum(x**i * j for i, j in enumerate(a))


while r - l > eps:
    mid = (l + r) / 2
    if f(mid - eps) > f(mid + eps):
        r = mid
    else:
        l = mid
print(l)
