#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
// Fixed-width driver; the displayed algorithm also accepts a Big integer type.
using Big = unsigned long long;
// --8<-- [start:ctz]
constexpr int loghash[64] = {0,  1,  48, 2,  57, 49, 28, 3,  61, 58, 50, 42, 38,
                             29, 17, 4,  62, 55, 59, 36, 53, 51, 43, 22, 45, 39,
                             33, 30, 24, 18, 12, 5,  63, 47, 56, 27, 60, 41, 37,
                             16, 54, 35, 52, 21, 44, 32, 23, 11, 46, 26, 40, 15,
                             34, 20, 31, 10, 25, 14, 19, 9,  13, 8,  7,  6};

int countr_zero(unsigned long long x) {
  if (x == 0) return 64;
  return loghash[(x & -x) * 0x03F79D71B4CB0A89ULL >> 58];
}

// --8<-- [end:ctz]
template <class Big, class = decltype(std::declval<Big>().begin())>
// --8<-- [start:ctz-big-limbs]
// 以小端序实现的二进制 Big，要求能枚举每一个元素
int countr_zero(Big a) {
  int ans = 0;
  for (auto x : a) {
    if (x == 0) {
      ans += 32;  // 每一位数据类型的位长
    } else {
      return ans + countr_zero(x);
    }
  }
  return ans;
}

// --8<-- [end:ctz-big-limbs]
namespace slow {
// --8<-- [start:ctz-big-slow]
// 暴力计算，如需使用建议直接写进 gcd 加快常数
int countr_zero(Big a) {
  if (a == 0) return 64;
  int ans = 0;
  while ((a & 1) == 0) {
    a >>= 1;
    ++ans;
  }
  return ans;
}

// --8<-- [end:ctz-big-slow]
}  // namespace slow

// --8<-- [start:core]
Big gcd(Big a, Big b) {
  if (a == 0) return b;
  if (b == 0) return a;
  // 记录a和b的公因数2出现次数，countr_zero表示二进制末位0的个数
  int atimes = countr_zero(a);
  int btimes = countr_zero(b);
  int mintimes = min(atimes, btimes);
  a >>= atimes;
  for (;;) {
    // a和b公因数中的2已经计算过了，后面不可能出现a为偶数的情况
    b >>= btimes;
    // 确保 a<=b
    if (a > b) swap(a, b);
    b -= a;
    if (b == 0) break;
    btimes = countr_zero(b);
  }
  return a << mintimes;
}

// --8<-- [end:core]
int main() {
  Big a, b;
  if (!(cin >> a >> b)) return 0;
  for (Big x : {a, b}) {
    assert(countr_zero(x) == slow::countr_zero(x));
    vector<uint32_t> limbs{static_cast<uint32_t>(x),
                           static_cast<uint32_t>(x >> 32)};
    assert(countr_zero(x) == countr_zero(limbs));
  }
  cout << gcd(a, b) << '\n';
}
