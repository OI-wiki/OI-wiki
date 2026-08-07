# --8<-- [start:core]
def ex_gcd(a, b):
    """
    Extended Euclidean Algorithm.
    Finds integers x, y such that a*x + b*y = gcd(a, b),
    and returns (gcd, x, y).
    """
    if b == 0:
        return a, 1, 0
    d, x1, y1 = ex_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return d, x, y


def solve_linear_congruence_equation(a, b, n):
    """
    Solves the linear congruence equation:
        a * x ≡ b (mod n), where n > 0.
    Returns the smallest non-negative solution x,
    or -1 if there is no solution.
    """
    d, x, y = ex_gcd(a, n)
    if b % d != 0:
        return -1
    n //= d
    return (x * (b // d) % n + n) % n


# --8<-- [end:core]


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        a, b, n = map(int, input().split())
        print(solve_linear_congruence_equation(a, b, n))
