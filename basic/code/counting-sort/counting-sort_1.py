# --8<-- [start:core]
def counting_sort(a, n, w):
    b = [0] * n
    cnt = [0] * (w + 1)
    for i in range(1, n + 1):
        cnt[a[i]] += 1
    for i in range(1, w + 1):
        cnt[i] += cnt[i - 1]
    for i in range(n, 0, -1):
        b[cnt[a[i]] - 1] = a[i]
        cnt[a[i]] -= 1
    return b


# --8<-- [end:core]
if __name__ == "__main__":
    n, w = [int(x) for x in input().split()]
    a = [0] + [int(x) for x in input().split()]

    b = counting_sort(a, n, w)
    print(" ".join(map(str, b)))
