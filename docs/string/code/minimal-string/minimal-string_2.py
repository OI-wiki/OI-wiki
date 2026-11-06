def minimal_rotation(sec):
    n = len(sec)
    # --8<-- [start:core]
    k, i, j = 0, 0, 1
    while k < n and i < n and j < n:
        if sec[(i + k) % n] == sec[(j + k) % n]:
            k += 1
        else:
            if sec[(i + k) % n] > sec[(j + k) % n]:
                i = i + k + 1
            else:
                j = j + k + 1
            if i == j:
                i += 1
            k = 0
    i = min(i, j)
    # --8<-- [end:core]
    return i


if __name__ == "__main__":
    for _ in range(int(input())):
        print(minimal_rotation(input()) + 1)
