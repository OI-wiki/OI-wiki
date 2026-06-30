# --8<-- [start:full-text]
# --8<-- [start:core]
n, m = 0, 0
a = []  # (n+1) x (m+1)
ps = []  # prefix sum array


# Calculate the prefix sum of 2D array.
def prefix_sum():
    global ps
    ps = [row[:] for row in a]  # Deep copy of a
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1]


# Find the sum of elements in submatrix [x1, y1] to [x2, y2].
def query(x1, y1, x2, y2):
    return ps[x2][y2] - ps[x1 - 1][y2] - ps[x2][y1 - 1] + ps[x1 - 1][y1 - 1]


# --8<-- [end:core]
if __name__ == "__main__":
    n, m = map(int, input().split())

    # Initialize with zero padding for 1-based indexing
    a = [[0] * (m + 1)]
    for _ in range(n):
        row = list(map(int, input().split()))
        a.append([0] + row)

    prefix_sum()
    ans = 0

    for l in range(1, min(n, m) + 1):
        for i in range(l, n + 1):
            for j in range(l, m + 1):
                if query(i - l + 1, j - l + 1, i, j) == l * l:
                    ans = max(ans, l)

    print(ans)

# --8<-- [end:full-text]
