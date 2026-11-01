# --8<-- [start:core]
# smallest_cyclic_string
def min_cyclic_string(s):
    s += s
    n = len(s)
    i, ans = 0, 0
    while i < n // 2:
        ans = i
        j, k = i + 1, i
        while j < n and s[k] <= s[j]:
            if s[k] < s[j]:
                k = i
            else:
                k += 1
            j += 1
        while i <= k:
            i += j - k
    return s[ans : ans + n // 2]


# --8<-- [end:core]

if __name__ == "__main__":
    for _ in range(int(input())):
        s = input()
        print((s + s).find(min_cyclic_string(s)) + 1)
