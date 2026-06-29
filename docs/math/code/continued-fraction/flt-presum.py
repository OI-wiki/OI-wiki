# PYTHON IS TOO SLOW TO PASS THIS PROBLEM.
# JUST FOR REFERENCE.
M = 10**9 + 7


def mul(a, b):
    return (
        (a[0] * b[0] + a[1] * b[2]) % M,
        (a[0] * b[1] + a[1] * b[3]) % M,
        (a[2] * b[0] + a[3] * b[2]) % M,
        (a[2] * b[1] + a[3] * b[3]) % M,
    )


def inv(a):
    return (a[3], M - a[1], M - a[2], a[0])


n, q = map(int, input().split())
ps = [(1, 0, 0, 1)]
# Get presum.
for a in map(int, input().split()):
    ps.append(mul(ps[-1], (a, 1, 1, 0)))
for _ in range(q):
    l, r = map(int, input().split())
    res = mul(inv(ps[l - 1]), ps[r])
    u, d = res[0], res[2]
    if l % 2 == 0:
        if u:
            u = M - u
        if d:
            d = M - d
    print(u, d)
