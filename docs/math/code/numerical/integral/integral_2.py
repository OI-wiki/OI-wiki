import sys

a, b, c, d, L, R = map(float, sys.stdin.buffer.read().split())


def f(x):
    return (c * x + d) / (a * x + b)


# --8<-- [start:core]
def simpson(l, r):
    mid = (l + r) / 2
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6  # 辛普森公式


def asr(l, r, eps, ans, step):
    mid = (l + r) / 2
    fl = simpson(l, mid)
    fr = simpson(mid, r)
    if abs(fl + fr - ans) <= 15 * eps and step < 0:
        return fl + fr + (fl + fr - ans) / 15  # 足够相似的话就直接返回
    return asr(l, mid, eps / 2, fl, step - 1) + asr(
        mid, r, eps / 2, fr, step - 1
    )  # 否则分割成两段递归求解


def calc(l, r, eps):
    return asr(l, r, eps, simpson(l, r), 12)


# --8<-- [end:core]
print(f"{calc(L,R,1e-9):.6f}")
