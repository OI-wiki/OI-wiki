# --8<-- [start:sort]
N = 100010
w = n = 0
a = [0] * N
bucket = [[] for i in range(N)]


def insertion_sort(A):
    for i in range(1, len(A)):
        key = A[i]
        j = i - 1
        while j >= 0 and A[j] > key:
            A[j + 1] = A[j]
            j -= 1
        A[j + 1] = key


def bucket_sort():
    if n == 0:
        return
    bucket_size = w // n + 1
    for i in range(0, n):
        bucket[i].clear()
    for i in range(1, n + 1):
        bucket[a[i] // bucket_size].append(a[i])
    p = 0
    for i in range(0, n):
        insertion_sort(bucket[i])
        for j in range(0, len(bucket[i])):
            p += 1
            a[p] = bucket[i][j]


# --8<-- [end:sort]

if __name__ == "__main__":
    import sys

    data = list(map(int, sys.stdin.buffer.read().split()))
    n, w = data[:2]
    a[1 : n + 1] = data[2:]
    bucket_sort()
    print(*a[1 : n + 1])
