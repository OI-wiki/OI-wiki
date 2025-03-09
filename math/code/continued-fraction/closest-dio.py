# CLOSEST Ax+By<=N.
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


# Find (x, y) such that y = (A*x+B) // C,
# such that Cy - Ax is max and 0 <= x <= N.
def closest(A, B, C, N):
    # y <= (A*x + B)/C <=> diff(x, y) <= B
    def diff(x, y):
        return C * y - A * x

    p, q = convergents(fraction(A, C))
    qh, ph = 0, B // C
    for i in range(2, len(q) - 1):
        if i % 2 == 0:
            while diff(qh + q[i + 1], ph + p[i + 1]) <= B:
                t = 1 + (diff(qh + q[i - 1], ph + p[i - 1]) - B - 1) // (
                    -diff(q[i], p[i])
                )
                dp = p[i - 1] + t * p[i]
                dq = q[i - 1] + t * q[i]
                k = (N - qh) // dq
                if k == 0:
                    return qh, ph
                if diff(dq, dp) != 0:
                    k = min(k, (B - diff(qh, ph)) // diff(dq, dp))
                qh, ph = qh + k * dq, ph + k * dp
    return qh, ph


def solve(A, B, N):
    x, y = closest(A, N % A, B, N // A)
    return N // A - x, y


if __name__ == "__main__":
    A, B, N = map(int, input().split())
    x, y = solve(A, B, N)
    print(x, y)
