constexpr int SEED = 5489;

#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>
#include <climits>

namespace std {

template <class _FwdIt1, class _FwdIt2>
void _Oi_iter_swap(_FwdIt1 _Left, _FwdIt2 _Right) { // swap *_Left and *_Right
    swap(*_Left, *_Right); // intentional ADL
}

// ============================================================
// 1. 辅助类：模拟 MSVC 的 _Rng_from_urng
// ============================================================
template <class URNG>
class urng_adapter {
 public:
  explicit urng_adapter(URNG& rng) : rng_(rng) {}

  // 返回 [0, limit] 范围的随机索引，与 MSVC 的 operator() 行为一致
  template <class Diff>
  Diff operator()(Diff limit) {
    return static_cast<Diff>(
        generate_random_index(static_cast<unsigned int>(limit)));
  }

 private:
  URNG rng_;

  // 从 URNG 获取 32 位随机数（与 MSVC 的 _Get_bits 完全一致）
  unsigned int get_bits() noexcept {
    if constexpr (sizeof(typename URNG::result_type) == sizeof(unsigned int)) {
      return rng_();
    } else {
      constexpr int src_bits = CHAR_BIT * sizeof(typename URNG::result_type);
      constexpr int need_bits = CHAR_BIT * sizeof(unsigned int);
      unsigned int val = rng_();
      int bits = src_bits;
      while (bits < need_bits) {
        val <<= src_bits;
        val |= rng_();
        bits += src_bits;
      }
      return val;
    }
  }

  // 拒绝采样生成 [0, limit] 的均匀整数（与 MSVC 的 _Generate_random_index
  // 一致）
  unsigned int generate_random_index(const unsigned int limit) noexcept {
    unsigned int ret = get_bits();
    if (limit == UINT_MAX) {
      return ret;
    }
    const unsigned int divisor = UINT_MAX / (limit + 1);
    unsigned int quotient;
    unsigned int remainder;
    do {
      quotient = ret / (limit + 1);
      remainder = ret % (limit + 1);
      if (quotient != divisor) {
        return remainder;
      }
      ret = get_bits();
    } while (true);
  }
};

// ============================================================
// 2. shuffle（基于 MSVC 的 _Shuffle）
// ============================================================
template <class RanIt, class URNG>
void _Oi_shuffle(RanIt first, RanIt last, URNG&& rng) {
  urng_adapter<std::remove_reference_t<URNG>> adapter(std::forward<URNG>(rng));
  if (first == last) return;
  for (auto i = last - first - 1; i > 0; --i) {
    auto idx = adapter(i);  // 返回 [0, i]
    std::_Oi_iter_swap(first + i, first + idx);
  }
}

}  // namespace std

#define shuffle _Oi_shuffle

// --8<-- [start:core]

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::mt19937 g(SEED);

  std::shuffle(v.begin(), v.end(), g);

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}

// --8<-- [end:core]