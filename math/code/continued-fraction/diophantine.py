# DIOPHANTINE EQUATION SOLVER.
# --8<-- [start:fraction]
# Find the continued fraction representation of P/Q.
def fraction(p, q):
    a = []
    while q:
        a.append(p // q)
        p, q = q, p % q
    return a


# --8<-- [end:fraction]
# --8<-- [start:convergents]
# Find the convergents of a continued fraction A.
# Numerators and denominators stored separately in P and Q.
def convergents(a):
    p = [0, 1]
    q = [1, 0]
    for it in a:
        p.append(p[-1] * it + p[-2])
        q.append(q[-1] * it + q[-2])
    return p, q


# --8<-- [end:convergents]
# --8<-- [start:dio]
# Return (x, y) such that Ax+By=C.
# Assume that such (x, y) exists.
def dio(A, B, C):
    p, q = convergents(fraction(A, B))
    C //= A // p[-1]  # divide by gcd(A, B)
    t = (-1) if len(p) % 2 else 1
    return t * C * q[-2], -t * C * p[-2]


# --8<-- [end:dio]
if __name__ == "__main__":
    A, B, C = map(int, input().split())
    x, y = dio(A, B, C)
    print(A * x + B * y - C)  # Should be 0
