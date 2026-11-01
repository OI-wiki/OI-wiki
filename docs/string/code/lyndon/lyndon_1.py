# --8<-- [start:core]
# duval_algorithm
def duval(s):
    n, i = len(s), 0
    factorization = []
    while i < n:
        j, k = i + 1, i
        while j < n and s[k] <= s[j]:
            if s[k] < s[j]:
                k = i
            else:
                k += 1
            j += 1
        while i <= k:
            factorization.append(s[i : i + j - k])
            i += j - k
    return factorization


# --8<-- [end:core]

if __name__ == "__main__":
    for factor in duval(input()):
        print(factor)
