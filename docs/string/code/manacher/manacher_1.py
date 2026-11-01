s = input()
n = len(s)
# --8<-- [start:core]
d1 = [0] * n
d2 = [0] * n
for i in range(0, n):
    d1[i] = 1
    while 0 <= i - d1[i] and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]:
        d1[i] += 1

    d2[i] = 0
    while 0 <= i - d2[i] - 1 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]:
        d2[i] += 1
# --8<-- [end:core]
print(*d1)
print(*d2)
