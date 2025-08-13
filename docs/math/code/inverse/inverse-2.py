# --8<-- [start:core]
# Binary exponentiation.
def pow_mod(a, b, m):
    res = 1
    po = a
    while b:
        if b & 1:
            res = (res * po) % m
        po = (po * po) % m
        b >>= 1
    return res


# Returns the modular inverse of a prime modulo p.
def inverse(a, p):
    return pow_mod(a, p - 2, p)


# --8<-- [end:core]

if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        a, p = map(int, input().split())
        print(inverse(a, p))
