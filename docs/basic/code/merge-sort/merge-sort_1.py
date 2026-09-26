# --8<-- [start:merge]
def merge(a, b):
    i, j = 0, 0
    c = []
    while i < len(a) and j < len(b):
        # <!> 先判断 b[j] < a[i]，保证稳定性
        if b[j] < a[i]:
            c.append(b[j])
            j += 1
        else:
            c.append(a[i])
            i += 1
    # 此时一个数组已空，另一个数组非空，将非空的数组并入 c 中
    c.extend(a[i:])
    c.extend(b[j:])
    return c


# --8<-- [end:merge]


# --8<-- [start:recursive]
def merge_sort(a, ll, rr):
    if rr - ll <= 1:
        return
    # 分解
    mid = (rr + ll) // 2
    merge_sort(a, ll, mid)
    merge_sort(a, mid, rr)
    # 合并
    a[ll:rr] = merge(a[ll:mid], a[mid:rr])


# --8<-- [end:recursive]


# --8<-- [start:iterative]
def merge_sort_iterative(a):
    seg = 1
    while seg < len(a):
        for l1 in range(0, len(a) - seg, seg + seg):
            r1 = l1 + seg
            l2 = r1
            r2 = l2 + seg
            a[l1:r2] = merge(a[l1:r1], a[l2:r2])
        seg <<= 1


# --8<-- [end:iterative]

if __name__ == "__main__":
    import sys

    data = list(map(int, sys.stdin.buffer.read().split()))
    a = data[1 : data[0] + 1]
    mid = len(a) // 2
    print(*merge(sorted(a[:mid]), sorted(a[mid:])))
    b = a.copy()
    merge_sort(b, 0, len(b))
    print(*b)
    merge_sort_iterative(a)
    print(*a)
