import sys

data = list(map(int, sys.stdin.buffer.read().split()))
n = data[0]
a = data[1 : n + 1]
ans = 0
MAXN = 100000

# --8<-- [start:core]
for i in range(n):
    for j in range(i):
        if a[i] + a[j] == 0:
            ans += 1
ans *= 2
# --8<-- [end:core]

print(ans)
