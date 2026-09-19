# --8<-- [start:core]
def binpow(a, b, p):
    if b == 0:
        return 1
    res = binpow(a, b // 2, p)
    if (b % 2) == 1:
        return res * res * a % p
    else:
        return res * res % p


# --8<-- [end:core]
if __name__ == "__main__":
    a, b, p = map(int, input().split())
    print(f"{a}^{b} mod {p}={binpow(a, b, p)}")
