from math import log2


# --8<-- [start:example54]
# 权值树状数组查询第 k 小
def kth(k):
    sum = 0
    x = 0
    i = int(log2(n))
    while ~i:
        x = x + (1 << i)  # 尝试扩展
        if x > n or sum + t[x] >= k:  # 如果扩展失败
            x = x - (1 << i)
        else:
            sum = sum + t[x]
        i = i - 1
    return x + 1  # 找不到就返回 n + 1


# --8<-- [end:example54]

n, q = map(int, input().split())
t = [0] * (n + 1)
for j, count in enumerate(map(int, input().split()), 1):
    k = j
    while k <= n:
        t[k] += count
        k += k & -k
for k in map(int, input().split()):
    print(kth(k))
