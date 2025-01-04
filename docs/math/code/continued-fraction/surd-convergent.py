from math import sqrt, floor


# Return the continued fraction and minimal positive period
#   of a quadratic irrational (x + y * sqrt(n)) / z.
def quadratic_irrational(x, y, z, n):
    p = x * z
    d = n * y * y * z * z
    q = z * z
    dd = floor(sqrt(n)) * y * z
    i = 0
    a = []
    used = dict()
    while (p, q) not in used:
        a.append((p + dd) // q)
        used[p, q] = i
        p = a[-1] * q - p
        q = (d - p * p) // q
        i += 1
    return a, i - used[p, q]


# Compose (A[0]*x + A[1]) / (A[2]*x + A[3]) and (B[0]*x + B[1]) / (B[2]*x + B[3])
def combine(A, B):
    return [
        t % mod
        for t in [
            A[0] * B[0] + A[1] * B[2],
            A[0] * B[1] + A[1] * B[3],
            A[2] * B[0] + A[3] * B[2],
            A[2] * B[1] + A[3] * B[3],
        ]
    ]


# Binary exponentiation.
def bpow(A, n):
    return (
        [1, 0, 0, 1]
        if not n
        else combine(A, bpow(A, n - 1))
        if n % 2
        else bpow(combine(A, A), n // 2)
    )


mod = 10**9 + 7
x, k = map(int, input().split())
a, T = quadratic_irrational(0, 1, 1, x)

A = (1, 0, 0, 1)  # (x + 0) / (0*x + 1) = x

# apply ak + 1/x = (ak*x+1)/(1x+0) to (Ax + B) / (Cx + D)
for i in reversed(range(1, len(a))):
    A = combine([a[i], 1, 1, 0], A)

C = (0, 1, 0, 0)  # = 1 / 0
while k % T:
    i = k % T
    C = combine([a[i], 1, 1, 0], C)
    k -= 1

C = combine(bpow(A, k // T), C)
C = combine((a[0], 1, 1, 0), C)
print(str(C[1]) + "/" + str(C[3]))
