n, m = map(int, input().split())
a = [list(map(int, input().split())) for _ in range(n)]
b = [a[0]] + [[i[0]] + [0] * (m - 1) for i in a[1:]]
ans = 0
for i in range(1, n):
    for j in range(1, m):
        if a[i][j]:
            b[i][j] = min(b[i - 1][j], b[i][j - 1], b[i - 1][j - 1]) + 1
            ans = max(ans, b[i][j])
print(ans)
