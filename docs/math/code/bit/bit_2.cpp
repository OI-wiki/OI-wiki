// --8<-- [start:mul]
int mulPowerOfTwo(int n, int m) {  // 计算 n*(2^m)
  return n << m;
}

int divPowerOfTwo(int n, int m) {  // 计算 n/(2^m)
  return n >> m;
}

// --8<-- [end:mul]
// --8<-- [start:abs]
int Abs(int n) {
  return (n ^ (n >> 31)) - (n >> 31);
  /* n>>31 取得 n 的符号，若 n 为正数，n>>31 等于 0，若 n 为负数，n>>31 等于 -1
    若 n 为正数 n^0=n, 数不变，若 n 为负数有 n^(-1)
    需要计算 n 和 -1 的补码，然后进行异或运算，
    结果 n 变号并且为 n 的绝对值减 1，再减去 -1 就是绝对值 */
}

// --8<-- [end:abs]
// --8<-- [start:minmax]
// 如果 a >= b, (a - b) >> 31 为 0，否则为 -1
int max(int a, int b) { return (b & ((a - b) >> 31)) | (a & (~(a - b) >> 31)); }

int min(int a, int b) { return (a & ((a - b) >> 31)) | (b & (~(a - b) >> 31)); }

// --8<-- [end:minmax]
// --8<-- [start:sgn]
bool isSameSign(int x, int y) {  // 有 0 的情况例外
  return (x ^ y) >= 0;
}

// --8<-- [end:sgn]
// --8<-- [start:swap]
void swap(int& a, int& b) { a ^= b ^= a ^= b; }

// --8<-- [end:swap]
// --8<-- [start:get_bit]
// 获取 a 的第 b 位，最低位编号为 0
int getBit(int a, int b) { return (a >> b) & 1; }

// --8<-- [end:get_bit]
// --8<-- [start:unset_bit]
// 将 a 的第 b 位设置为 0 ，最低位编号为 0
int unsetBit(int a, int b) { return a & ~(1 << b); }

// --8<-- [end:unset_bit]
// --8<-- [start:set_bit]
// 将 a 的第 b 位设置为 1 ，最低位编号为 0
int setBit(int a, int b) { return a | (1 << b); }

// --8<-- [end:set_bit]
// --8<-- [start:flap_bit]
// 将 a 的第 b 位取反 ，最低位编号为 0
int flapBit(int a, int b) { return a ^ (1 << b); }

// --8<-- [end:flap_bit]
namespace popcnt1 {
// --8<-- [start:popcnt1]
// 求 x 的汉明权重
int popcount(int x) {
  int cnt = 0;
  while (x) {
    cnt += x & 1;
    x >>= 1;
  }
  return cnt;
}

// --8<-- [end:popcnt1]
}  // namespace popcnt1

namespace popcnt2 {
// --8<-- [start:popcnt2]
// 求 x 的汉明权重
int popcount(int x) {
  int cnt = 0;
  while (x) {
    cnt++;
    x -= x & -x;
  }
  return cnt;
}

// --8<-- [end:popcnt2]
}  // namespace popcnt2

#include <cassert>
#include <iostream>
#if defined(_MSC_VER) && !defined(__clang__)
#include <immintrin.h>
#define __builtin_popcount __popcnt
#endif

int main() {
  int a, b;
  std::cin >> a >> b;

  for (int i = 0; i < 16; i++) {
    std::cout << mulPowerOfTwo(a, i) << ' ' << divPowerOfTwo(a, i) << std::endl;
  }

  assert(Abs(-a) == a);
  assert(Abs(a) == a);

  assert(max(a, b) == (a > b ? a : b));
  assert(min(a, b) == (a < b ? a : b));

  std::cout << isSameSign(a, b) << std::endl;

  int x = a, y = b;
  swap(x, y);
  assert(x == b && y == a);

  for (int i = 0; i < 32; i++)
    std::cout << getBit(a, i) << ' ' << unsetBit(a, i) << ' ' << setBit(a, i)
              << ' ' << flapBit(a, i) << std::endl;

  assert(popcnt1::popcount(a) == __builtin_popcount(a));
  assert(popcnt2::popcount(a) == __builtin_popcount(a));

  return 0;
}
