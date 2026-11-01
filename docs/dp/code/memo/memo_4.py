import sys

sys.setrecursionlimit(10000)
n = int(input())
a = [0] + list(map(int, input().split()))
mem = [-1] * (n + 1)


# --8<-- [start:core]
def dfs(i):
    if mem[i] != -1:
        return mem[i]
    ret = 1
    for j in range(1, i):
        if a[j] < a[i]:
            ret = max(ret, dfs(j) + 1)
    mem[i] = ret
    return mem[i]


# --8<-- [end:core]

print(max(dfs(i) for i in range(1, n + 1)))
