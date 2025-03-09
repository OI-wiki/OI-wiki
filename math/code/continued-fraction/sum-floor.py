# SUM FLOOR.
# Find the convergents of a continued fraction A.
# Numerators and denominators stored separately in P and Q.
def convergents(a):
    p = [0, 1]
    q = [1, 0]
    for it in a:
        p.append(p[-1] * it + p[-2])
        q.append(q[-1] * it + q[-2])
    return p, q


# Find [ah, ph, qh] such that points r[i]=(ph[i], qh[i]) constitute
# upper convex hull of lattice points on 0 <= x <= N and 0 <= y <= r * x,
# where r = [a0, a1, a2, ...] and there are ah[i]-1 integer points on the
# segment between r[i] and r[i+1].
def hull(a, N):
    p, q = convergents(a)
    t = N // q[-1]
    ah = [t]
    ph = [0, t * p[-1]]
    qh = [0, t * q[-1]]
    for i in reversed(range(len(q))):
        if i % 2 == 1:
            while qh[-1] + q[i - 1] <= N:
                t = (N - qh[-1] - q[i - 1]) // q[i]
                dp = p[i - 1] + t * p[i]
                dq = q[i - 1] + t * q[i]
                k = (N - qh[-1]) // dq
                ah.append(k)
                ph.append(ph[-1] + k * dp)
                qh.append(qh[-1] + k * dq)
    return ah, ph, qh


# Find sum of floor(k * x) for k in [1, N] and x = [a0; a1, a2, ...].
def sum_floor(a, N):
    N += 1
    ah, ph, qh = hull(a, N)

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


# Get the continued fraction of e.
def cf_e(N):
    i, a = 0, 0
    q, qq = 0, 1
    while True:
        if i == 0:
            a = 2
        elif i % 3 == 2:
            a = (i + 1) // 3 * 2
        else:
            a = 1
        yield a
        q, qq = a * q + qq, q
        if q > N:
            return
        i += 1


if __name__ == "__main__":
    N = int(input())
    print(sum_floor(cf_e(N), N))
