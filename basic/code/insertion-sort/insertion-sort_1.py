# --8<-- [start:core]
def insertion_sort(arr, n):
    for i in range(1, n):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key


# --8<-- [end:core]
if __name__ == "__main__":
    n = int(input())
    a = [int(x) for x in input().split()]

    insertion_sort(a, n)
    print(" ".join(map(str, a)))
