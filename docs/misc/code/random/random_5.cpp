constexpr int SEED = 5497u;

#include <climits>
#include <random>
#include <type_traits>

namespace std {

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
  URNG& rng_;

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

template <class _Ty = int>
class _Oi_UID {
 private:
  _Ty a, b;

 public:
  _Oi_UID(int _a, int _b) : a(_a), b(_b) {}

  template <class _Engine>
  _Ty operator()(_Engine& _Eng) {
    urng_adapter<std::remove_reference_t<_Engine>> adapter(_Eng);
    return a + adapter(b - a);
  }
};

}  // namespace std

#define uniform_int_distribution _Oi_UID

// --8<-- [start:core]

#include <iostream>
#include <random>

int main() {
  std::mt19937 gen(SEED);  // 播种标准 mersenne_twister_engine
  std::uniform_int_distribution<> dis(1, 6);

  for (int n = 0; n < 10; ++n)
    // 用 dis 变换 gen 所生成的随机 unsigned int 到 [1, 6] 中的 int
    std::cout << dis(gen) << ' ';
  std::cout << '\n';
  return 0;
}

// --8<-- [end:core]