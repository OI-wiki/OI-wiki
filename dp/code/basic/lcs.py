# --8<-- [start:core]
def dp(n, m, a, b):
    f = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if a[i] == b[j]:
                f[i][j] = f[i - 1][j - 1] + 1
            else:
                f[i][j] = max(f[i - 1][j], f[i][j - 1])
    return f[n][m]


# --8<-- [end:core]
if __name__ == "__main__":
    n, m = map(int, input().split())
    a = [0] + list(map(int, input().split()))
    b = [0] + list(map(int, input().split()))
    print(dp(n, m, a, b))
