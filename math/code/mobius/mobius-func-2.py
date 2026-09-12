# --8<-- [start:core]
def get_mu(n):
    mu = [0] * (n + 1)
    primes = []
    not_prime = [False] * (n + 1)

    mu[1] = 1
    for x in range(2, n + 1):
        if not not_prime[x]:
            primes.append(x)
            mu[x] = -1
        for p in primes:
            if x * p > n:
                break
            not_prime[x * p] = True
            if x % p == 0:
                mu[x * p] = 0
                break
            else:
                mu[x * p] = -mu[x]
    return mu


# --8<-- [end:core]
if __name__ == "__main__":
    n = int(input())
    mu = get_mu(n)
    for i in range(1, n + 1):
        print(mu[i])
