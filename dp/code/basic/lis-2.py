import bisect

MAXN = 100

# --8<-- [start:core]
n = 0
a = [0] * MAXN
d = [0] * MAXN
di = [0] * MAXN
pre = [0] * MAXN
res = [0] * MAXN


def dp():
    ans = 0
    for i in range(1, n + 1):
        tmp = bisect.bisect_right(d, a[i], 0, ans)
        pre[i] = di[tmp - 1] if tmp else -1
        d[tmp] = a[i]
        di[tmp] = i
        if tmp == ans:
            ans += 1

    # Construct the subsequence
    k = ans
    i = di[ans - 1]
    while k:
        res[k] = a[i]
        i = pre[i]
        k -= 1

    return ans


# --8<-- [end:core]
if __name__ == "__main__":
    t = int(input())
    while t:
        t -= 1
        n = int(input())
        a = [0] + list(map(int, input().split()))

        ans = dp()
        print(ans)
        for i in range(1, ans + 1):
            if i == ans:
                print(res[i])
            else:
                print(res[i], end=" ")
