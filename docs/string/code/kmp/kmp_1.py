# --8<-- [start:core]
def prefix_function(s):
    n = len(s)
    pi = [0] * n
    for i in range(1, n):
        for j in range(i, -1, -1):
            if s[0:j] == s[i - j + 1 : i + 1]:
                pi[i] = j
                break
    return pi


# --8<-- [end:core]

if __name__ == "__main__":
    print(*prefix_function(input()))
