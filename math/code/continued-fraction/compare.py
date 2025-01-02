# CONTINUED FRACTION COMPARISON.
# Expand [..., n] to [..., n-1, 1] if needed.
def expand(a):
    if a[-1] != 1 or len(a) == 1:
        a[-1] -= 1
        a.append(1)
    return a


# Check if a is smaller than b.
def less_than(a, b):
    a = expand(a)
    b = expand(b)
    a = [(-1) ** i * a[i] for i in range(len(a))]
    b = [(-1) ** i * b[i] for i in range(len(b))]
    return a < b


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        input()
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        print(int(less_than(a, b)), int(less_than(b, a)))
