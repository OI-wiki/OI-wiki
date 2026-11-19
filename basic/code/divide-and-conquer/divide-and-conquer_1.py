def merge(a, front, mid, end):
    i, j = front, mid + 1
    tmp = []
    while i <= mid and j <= end:
        if a[j] < a[i]:
            tmp.append(a[j])
            j += 1
        else:
            tmp.append(a[i])
            i += 1
    tmp.extend(a[i : mid + 1])
    tmp.extend(a[j : end + 1])
    a[front : end + 1] = tmp


# --8<-- [start:sort]
# 不使用递归的归并排序算法
def merge_sort_iterative(a):
    n = len(a)
    seg = 1
    while seg < n:
        start = 0
        while start < n - seg:
            merge(a, start, start + seg - 1, min(start + seg + seg - 1, n - 1))
            start = start + seg + seg
        seg = seg + seg


# 使用递归的归并排序算法
def merge_sort(a, front, end):
    if front >= end:
        return
    mid = front + (end - front) // 2
    merge_sort(a, front, mid)
    merge_sort(a, mid + 1, end)
    merge(a, front, mid, end)


# --8<-- [end:sort]

if __name__ == "__main__":
    import sys

    data = list(map(int, sys.stdin.buffer.read().split()))
    a = data[1 : data[0] + 1]
    b = a.copy()
    merge_sort(b, 0, len(b) - 1)
    print(*b)
    merge_sort_iterative(a)
    print(*a)
