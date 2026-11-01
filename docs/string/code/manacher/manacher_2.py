s = input()
n = len(s)
# --8<-- [start:core]
d1 = [0] * n
l, r = 0, -1
for i in range(0, n):
    k = 1 if i > r else min(d1[l + r - i], r - i + 1)
    while 0 <= i - k and i + k < n and s[i - k] == s[i + k]:
        k += 1
    d1[i] = k
    k -= 1
    if i + k > r:
        l = i - k
        r = i + k
# --8<-- [end:core]
print(*d1)
