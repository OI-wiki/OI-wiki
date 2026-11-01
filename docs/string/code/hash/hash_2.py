# --8<-- [start:core]
def get_hash1(s: str) -> int:
    base = 131
    mod1 = 212370440130137957
    ans = 0
    for char in s:
        ans = (ans * base + ord(char)) % mod1
    return ans


def get_hash2(s: str) -> int:
    base = 131
    mod2 = 1000000007
    ans = 0
    for char in s:
        ans = (ans * base + ord(char)) % mod2
    return ans


def cmp(s: str, t: str) -> bool:
    f1 = get_hash1(s) != get_hash1(t)
    f2 = get_hash2(s) != get_hash2(t)
    return f1 or f2


# --8<-- [end:core]

if __name__ == "__main__":
    unique = []
    for _ in range(int(input())):
        s = input()
        if not any(not cmp(s, t) for t in unique):
            unique.append(s)
    print(len(unique))
