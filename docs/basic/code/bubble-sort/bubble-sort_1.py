# --8<-- [start:core]
def bubble_sort(a, n):
    flag = True
    while flag:
        flag = False
        for i in range(1, n):
            if a[i] > a[i + 1]:
                flag = True
                a[i], a[i + 1] = a[i + 1], a[i]


# --8<-- [end:core]
if __name__ == "__main__":
    n = int(input())
    a = [0] + [int(x) for x in input().split()]

    bubble_sort(a, n)
    print(" ".join(map(str, a[1:])))
