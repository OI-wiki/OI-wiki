# --8<-- [start:core]
# Returns the modular inverse of a prime modulo p.
# Use built-in pow function.
def inverse(a, p):
    return pow(a, p - 2, p)


# --8<-- [end:core]

if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        a, p = map(int, input().split())
        print(inverse(a, p))
