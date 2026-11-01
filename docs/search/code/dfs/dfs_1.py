n = int(input())

# --8<-- [start:core]
for i in range(1, n + 1):
    for j in range(i, n + 1):
        for k in range(j, n + 1):
            if i + j + k == n:
                print("%d = %d + %d + %d" % (n, i, j, k))
# --8<-- [end:core]
