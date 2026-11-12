# --8<-- [start:core]
# Precomputes modular inverses of all integers from 1 to n modulo prime p.
def precompute_inverses(n, p):
    res = [0] * (n + 1)
    res[1] = 1
    for i in range(2, n + 1):
        res[i] = (p - p // i) * res[p % i] % p
    return res


# --8<-- [end:core]

if __name__ == "__main__":
    n, p = map(int, input().split())
    res = precompute_inverses(n, p)
    for i in range(1, n + 1):
        print(res[i])
