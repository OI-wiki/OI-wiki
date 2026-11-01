# --8<-- [start:core]
def match(s, t, n, m):
    if m < 1:
        return []

    ans = []
    for i in range(0, n - m + 1):
        for j in range(0, m):
            if s[i + j] != t[j]:
                break
        else:
            ans.append(i)
    return ans


# --8<-- [end:core]

if __name__ == "__main__":
    s = input()
    t = input()
    for pos in match(s, t, len(s), len(t)):
        print(pos)
