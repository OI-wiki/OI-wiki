# --8<-- [start:core]
def selection_sort(a, n):
    for i in range(1, n):
        ith = i
        for j in range(i + 1, n + 1):
            if a[j] < a[ith]:
                ith = j
        a[i], a[ith] = a[ith], a[i]


# --8<-- [end:core]
if __name__ == "__main__":
    n = int(input())
    a = [0] + [int(x) for x in input().split()]

    selection_sort(a, n)
    print(" ".join(map(str, a[1:])))
