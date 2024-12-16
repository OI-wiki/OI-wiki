# SUM OF FLOOR (Ax+B)/M.
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


# Find convex hull of lattice (x, y) such that C*y <= A*x+B.
def hull(A, B, C, N):
    def diff(x, y):
        return C * y - A * x

    a = fraction(A, C)
    p, q = convergents(a)
    ah = []
    ph = [B // C]
    qh = [0]

    def insert(dq, dp):
        k = (N - qh[-1]) // dq
        if diff(dq, dp) > 0:
            k = min(k, (B - diff(qh[-1], ph[-1])) // diff(dq, dp))
        ah.append(k)
        qh.append(qh[-1] + k * dq)
        ph.append(ph[-1] + k * dp)

    for i in range(1, len(q) - 1):
        if i % 2 == 0:
            while diff(qh[-1] + q[i + 1], ph[-1] + p[i + 1]) <= B:
                t = (B - diff(qh[-1] + q[i + 1], ph[-1] + p[i + 1])) // (
                    -diff(q[i], p[i])
                )
                dp = p[i + 1] - t * p[i]
                dq = q[i + 1] - t * q[i]
                if dq < 0 or qh[-1] + dq > N:
                    break
                insert(dq, dp)

    insert(q[-1], p[-1])

    for i in reversed(range(len(q))):
        if i % 2 == 1:
            while qh[-1] + q[i - 1] <= N:
                t = (N - qh[-1] - q[i - 1]) // q[i]
                dp = p[i - 1] + t * p[i]
                dq = q[i - 1] + t * q[i]
                insert(dq, dp)
    return ah, ph, qh


def solve(N, M, A, B):
    ah, ph, qh = hull(A, B, M, N)

    # The number of lattice points within a vertical right trapezoid
    # on points (0; 0) - (0; y1) - (dx; y2) - (dx; 0) that has
    # a+1 integer points on the segment (0; y1) - (dx; y2) but with
    # the number of points on the vertical right line excluded.
    def picks(y1, y2, dx, a):
        b = y1 + y2 + a + dx
        A = (y1 + y2) * dx
        return (A + b) // 2 - y2  # = (A - b + 2) // 2 + b - (y2 + 1)

    ans = 0
    for i in range(1, len(qh)):
        ans += picks(ph[i - 1], ph[i], qh[i] - qh[i - 1], ah[i - 1])
    return ans - N


if __name__ == "__main__":
    T = int(input())
    for _ in range(T):
        N, M, A, B = map(int, input().split())
        print(solve(N, M, A, B))
