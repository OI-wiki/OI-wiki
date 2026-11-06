# FIND Q IN [1,N] MINIMIZING Q*R MOD M.
# Find the continued fraction representation of P/Q.
def fraction(p, q):
    a = []
    while q:
        a.append(p // q)
        p, q = q, p % q
    return a


# Find the convergents of a continued fraction A.
# Numerators and denominators stored separately in P and Q.
def convergents(a):
    p = [0, 1]
    q = [1, 0]
    for it in a:
        p.append(p[-1] * it + p[-2])
        q.append(q[-1] * it + q[-2])
    return p, q


# --8<-- [start:core]
# Find Q that minimizes Q*r mod m for 1 <= k <= n < m.
def mod_min(r, n, m):
    a = fraction(r, m)
    p, q = convergents(a)
    for i in range(2, len(q)):
        if i % 2 == 1 and (i + 1 == len(q) or q[i + 1] > n):
            t = (n - q[i - 1]) // q[i]
            return q[i - 1] + t * q[i]
    return 0


# --8<-- [end:core]
if __name__ == "__main__":
    r, n, m = map(int, input().split())
    q = mod_min(r, n, m)
    p = r * q % m
    print(p, q)
