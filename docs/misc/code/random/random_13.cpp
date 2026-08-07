constexpr int SEED = 5489;

#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>
#include <climits>

#if __cplusplus > 201103L && __cplusplus <= 201402L  // C++14
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
// 4. sample
// ============================================================
// 前向迭代器：蓄水池抽样（与 MSVC 的 _Sample_fwd 一致）
template <class PopIt, class SampleIt, class Diff, class Adapter>
SampleIt sample_fwd(PopIt first, PopIt last, SampleIt out, Diff n,
                    Adapter& rng) {
  Diff k = 0;
  // 先填满前 n 个
  for (; first != last && k < n; ++first, ++k) {
    out[k] = *first;
  }
  if (k < n) return out + k;  // 总体不够 n 个

  Diff size = n;
  for (; first != last; ++first) {
    ++size;
    Diff rand = rng(size);  // [0, size]
    if (rand < n) {
      out[rand] = *first;
    }
  }
  return out + n;
}

// 随机访问迭代器：部分 Fisher‑Yates 选索引（与 MSVC 的 _Sample_ra 一致）
template <class PopIt, class SampleIt, class Diff, class Adapter>
SampleIt sample_ra(PopIt first, PopIt last, SampleIt out, Diff n,
                   Adapter& rng) {
  Diff N = last - first;
  if (n >= N) {
    for (Diff i = 0; i < N; ++i) *out++ = first[i];
    return out;
  }

  std::unique_ptr<Diff[]> indices(new Diff[n]);
  for (Diff i = 0; i < n; ++i) indices[i] = i;

  for (Diff i = n; i < N; ++i) {
    Diff rand = rng(i);  // [0, i]
    if (rand < n) {
      indices[rand] = i;
    }
  }

  // 排序以保持原始相对顺序（与 MSVC STL 一致）
  std::sort(indices.get(), indices.get() + n);
  for (Diff i = 0; i < n; ++i) {
    *out++ = first[indices[i]];
  }
  return out;
}

// 标签分发
template <class PopIt, class SampleIt, class Size, class URNG>
SampleIt sample_impl(PopIt first, PopIt last, SampleIt out, Size n,
                     urng_adapter<std::remove_reference_t<URNG>>& adapter,
                     std::forward_iterator_tag) {
  return sample_fwd(first, last, out, static_cast<decltype(last - first)>(n),
                    adapter);
}

template <class PopIt, class SampleIt, class Size, class URNG>
SampleIt sample_impl(PopIt first, PopIt last, SampleIt out, Size n,
                     urng_adapter<std::remove_reference_t<URNG>>& adapter,
                     std::random_access_iterator_tag) {
  return sample_ra(first, last, out, static_cast<decltype(last - first)>(n),
                   adapter);
}

// sample 入口
template <class PopIt, class SampleIt, class Size, class URNG>
SampleIt sample(PopIt first, PopIt last, SampleIt out, Size n, URNG&& rng) {
  using diff_t = typename std::iterator_traits<PopIt>::difference_type;
  urng_adapter<std::remove_reference_t<URNG>> adapter(std::forward<URNG>(rng));
  return sample_impl(first, last, out, static_cast<diff_t>(n), adapter,
                     typename std::iterator_traits<PopIt>::iterator_category());
}

}  // namespace std
#endif

// --8<-- [start:core]

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>

int main() {
  std::string in{"ABCDEFGHIJK"}, out;
  std::sample(in.begin(), in.end(), std::back_inserter(out), 4,
              std::mt19937{SEED});
  std::cout << "Four random letters out of " << in << " : " << out << '\n';
}

// --8<-- [end:core]