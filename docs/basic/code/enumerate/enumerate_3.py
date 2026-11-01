import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
a = data[1 : n + 1]
ans = 0
MAXN = 100000

# --8<-- [start:core]
met = [False] * (MAXN * 2 + 1)
for i in range(n):
    if met[MAXN - a[i]]:
        ans += 1
    met[a[i] + MAXN] = True
ans *= 2
# --8<-- [end:core]

print(ans)
