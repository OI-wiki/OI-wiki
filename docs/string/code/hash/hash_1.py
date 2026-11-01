# --8<-- [start:core]
M = int(1e9 + 7)
B = 233


def get_hash(s):
    res = 0
    for char in s:
        res = (res * B + ord(char)) % M
    return res


def cmp(s, t):
    return get_hash(s) == get_hash(t)


# --8<-- [end:core]

if __name__ == "__main__":
    unique = []
    for _ in range(int(input())):
        s = input()
        if not any(cmp(s, t) for t in unique):
            unique.append(s)
    print(len(unique))
