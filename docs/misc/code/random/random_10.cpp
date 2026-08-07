constexpr int SEED = 12345;

namespace std {

// ============================================================
// 1. 辅助类：模拟 MSVC 的 _Rng_from_urng
// ============================================================
template <class URNG>
class urng_adapter {
public:
    explicit urng_adapter(URNG&& rng) : rng_(std::move(rng)) {}

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

    // 拒绝采样生成 [0, limit] 的均匀整数（与 MSVC 的 _Generate_random_index 一致）
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
// 3. random_shuffle
// ============================================================
// 3.1 模拟 MSVC 的 rand() 的线性同余引擎
struct msvc_rand_engine {
    unsigned long state = 1;   // 默认种子对应 std::srand(1)

    int operator()() {
        state = state * 214013UL + 2531011UL;
        return static_cast<int>((state >> 16) & 0x7FFF);
    }

    static constexpr int min() { return 0; }
    static constexpr int max() { return 0x7FFF; }
};

// 3.2 适配 rand() 输出为 [0, n) 的函数对象（MSVC 的 _Rand）
template <class Diff>
struct msvc_rand_fn {
    msvc_rand_engine& eng;
    Diff operator()(Diff n) const {
        return static_cast<Diff>(eng() % n);
    }
};

// 3.3 带 RNG 的版本（与 MSVC 算法一致）
template <class RanIt, class RngFn>
void random_shuffle(RanIt first, RanIt last, RngFn&& rng) {
    auto n = last - first;
    for (auto i = n; i > 1; --i) {
        std::iter_swap(first + (i - 1), first + rng(i));
    }
}

// 3.4 无 RNG 版本：使用 MSVC 的 rand() 实现保证一致性
template <class RanIt>
void random_shuffle(RanIt first, RanIt last) {
    msvc_rand_engine eng;          // 固定种子 1，可改为由用户配置
    msvc_rand_fn<decltype(last - first)> rand_fn{eng};
    random_shuffle(first, last, rand_fn);
}

} // namespace std

// --8<-- [start:core]

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

int a[100];

int main() {
  srand(SEED);
  int n = rand() % 99 + 1;
  for (int i = 1; i <= n; i++) a[i] = i;
  std::cout << n << '\n';
  for (int i = 1; i <= n; i++) {
    std::random_shuffle(a + 1, a + i);
    int cnt = rand() % i;
    for (int j = 1; j <= cnt; j++) std::cout << a[j] << ' ';
    std::cout << 0 << '\n';
  }
}

// --8<-- [end:core]