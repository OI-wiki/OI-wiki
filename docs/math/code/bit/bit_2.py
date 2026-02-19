# --8<-- [start:mul]
def mulPowerOfTwo(n, m):  # 计算 n*(2^m)
    return n << m


def divPowerOfTwo(n, m):  # 计算 n/(2^m)
    return n >> m


# --8<-- [end:mul]
# --8<-- [start:abs]
def Abs(n):
    return (n ^ (n >> 31)) - (n >> 31)
    """
    n>>31 取得 n 的符号，若 n 为正数，n>>31 等于 0，若 n 为负数，n>>31 等于 -1
    若 n 为正数 n^0=n, 数不变，若 n 为负数有 n^(-1)
    需要计算 n 和 -1 的补码，然后进行异或运算，
    结果 n 变号并且为 n 的绝对值减 1，再减去 -1 就是绝对值
    """


# --8<-- [end:abs]
# --8<-- [start:minmax]
# 如果 a >= b, (a - b) >> 31 为 0，否则为 -1
def max(a, b):
    return b & ((a - b) >> 31) | a & (~(a - b) >> 31)


def min(a, b):
    return a & ((a - b) >> 31) | b & (~(a - b) >> 31)


# --8<-- [end:minmax]
# --8<-- [start:sgn]
# 有 0 的情况例外
def isSameSign(x, y):
    return (x ^ y) >= 0


# --8<-- [end:sgn]
# --8<-- [start:get_bit]
# 获取 a 的第 b 位，最低位编号为 0
def getBit(a, b):
    return (a >> b) & 1


# --8<-- [end:get_bit]
# --8<-- [start:unset_bit]
# 将 a 的第 b 位设置为 0 ，最低位编号为 0
def unsetBit(a, b):
    return a & ~(1 << b)


# --8<-- [end:unset_bit]
# --8<-- [start:set_bit]
# 将 a 的第 b 位设置为 1 ，最低位编号为 0
def setBit(a, b):
    return a | (1 << b)


# --8<-- [end:set_bit]
# --8<-- [start:flap_bit]
# 将 a 的第 b 位取反 ，最低位编号为 0
def flapBit(a, b):
    return a ^ (1 << b)


# --8<-- [end:flap_bit]


if __name__ == "__main__":
    a, b = map(int, input().split())

    for i in range(16):
        print(f"{mulPowerOfTwo(a, i)} {divPowerOfTwo(a, i)}")

    assert Abs(-a) == a
    assert Abs(a) == a

    assert max(a, b) == (a if a > b else b)
    assert min(a, b) == (a if a < b else b)

    print(int(isSameSign(a, b)))

    for i in range(32):
        print(f"{getBit(a, i)} {unsetBit(a, i)} {setBit(a, i)} {flapBit(a, i)}")
