import sys
import random

random.seed(1)
test_time = 10
quickPow = pow


# --8<-- [start:core]
def fermat(n):
    if n < 3:
        return n == 2
    # test_time 为测试次数,建议设为不小于 8
    # 的整数以保证正确率,但也不宜过大,否则会影响效率
    for i in range(1, test_time + 1):
        a = random.randint(0, 32767) % (n - 2) + 2
        if quickPow(a, n - 1, n) != 1:
            return False
    return True


# --8<-- [end:core]

data = list(map(int, sys.stdin.buffer.read().split()))
print(sum(fermat(x) for x in data[1 : 1 + data[0]]))
