# --8<-- [start:core]
def binpow(a, b, p):
    res = 1
    while b > 0:
        if b & 1:
            res = res * a % p
        a = a * a % p
        b >>= 1
    return res


# --8<-- [end:core]
if __name__ == "__main__":
    a, b, p = map(int, input().split())
    print(f"{a}^{b} mod {p}={binpow(a, b, p)}")
