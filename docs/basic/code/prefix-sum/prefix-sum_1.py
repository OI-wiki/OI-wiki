# --8<-- [start:core]
n = 0  # Array size
a = []  # Array (indexed from 1)
ps = []  # Prefix sum array


# Calculate prefix sum
def prefix_sum():
    global ps
    ps = a[:]
    # Or simply:
    # ps = list(itertools.accumulate(a))
    for i in range(1, n + 1):
        ps[i] += ps[i - 1]


# Query sum of elements in [l, r]
def query(l, r):
    return ps[r] - ps[l - 1]


# --8<-- [end:core]
if __name__ == "__main__":
    n = int(input())
    a = [0] + list(map(int, input().split()))  # Pad with 0 for 1-based indexing
    prefix_sum()
    t = int(input())
    for _ in range(t):
        l, r = map(int, input().split())
        print(query(l, r))
