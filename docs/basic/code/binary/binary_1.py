eps = 1e-7
n, l, r = map(float, input().split())
a = tuple(map(float, input().split()))[::-1]


def f(x):
    return sum(x**i * j for i, j in enumerate(a))


while r - l > eps:
    lmid = l + (r - l) / 3
    rmid = r - (r - l) / 3
    if f(lmid) > f(rmid):
        r = rmid
    else:
        l = lmid
print(f"{(l + r) / 2:.6f}")
