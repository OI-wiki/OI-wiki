constexpr int SEED = 12345;

#include <algorithm>
#include <climits>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

namespace std {

template <class _FwdIt1, class _FwdIt2>
void _Oi_iter_swap(_FwdIt1 _Left, _FwdIt2 _Right) {  // swap *_Left and *_Right
  swap(*_Left, *_Right);                             // intentional ADL
}

// ============================================================
// 3. random_shuffle
// ============================================================
// 3.1 模拟 MSVC 的 rand() 的线性同余引擎
struct msvc_rand_engine {
  unsigned long state = SEED;

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

  Diff operator()(Diff n) const { return static_cast<Diff>(eng() % n); }
};

// 3.3 带 RNG 的版本（与 MSVC 算法一致）
template <class RanIt, class RngFn>
void _Oi_random_shuffle(RanIt first, RanIt last, RngFn&& rng) {
  auto n = last - first;
  for (auto i = n; i > 1; --i) {
    std::_Oi_iter_swap(first + (i - 1), first + rng(i));
  }
}

msvc_rand_engine eng;

// 3.4 无 RNG 版本：使用 MSVC 的 rand() 实现保证一致性
template <class RanIt>
void _Oi_random_shuffle(RanIt first, RanIt last) {
  msvc_rand_fn<decltype(last - first)> rand_fn{eng};
  _Oi_random_shuffle(first, last, rand_fn);
}

}  // namespace std

void _Oi_srand(int _seed) { std::eng.state = _seed; }

int _Oi_rand() { return std::eng(); }

#define srand _Oi_srand
#define rand _Oi_rand
#define random_shuffle _Oi_random_shuffle

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