from math import sqrt, floor


# --8<-- [start:core]
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


# --8<-- [end:core]
if __name__ == "__main__":
    a, L = quadratic_irrational(-3, 1, 7, 331)
    print(f"{L}\n{' '.join(map(str, a))}")
