# --8<-- [start:core]
def dp(n, a):
    d = [0] * (n + 1)
    d[1] = 1
    ans = 1
    for i in range(2, n + 1):
        d[i] = 1
        for j in range(1, i):
            if a[j] <= a[i]:
                d[i] = max(d[i], d[j] + 1)
                ans = max(ans, d[i])
    return ans


# --8<-- [end:core]
if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        n = int(input())
        a = [0] + list(map(int, input().split()))
        print(dp(n, a))
