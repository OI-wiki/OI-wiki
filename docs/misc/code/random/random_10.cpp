constexpr int SEED = 12345;

// --8<-- [start:header]
#include <algorithm>
#include <cstdlib>
#include <iostream>
// --8<-- [end:header]

#include <random>

std::minstd_rand rng;

// --8<-- [start:real-using]
using std::cout;

// --8<-- [end:real-using]

namespace fake_using {
#if (defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || (!defined(_MSVC_LANG) && __cplusplus < 201703L)
// --8<-- [start:fake-using]
using std::random_shuffle;
// --8<-- [end:fake-using]
#endif
}  // namespace fake_using

void _Oi_srand(int _seed) { rng.seed(_seed); }

int _Oi_rand() { return rng(); }

template <class RanIt>
void random_shuffle(RanIt first, RanIt last) {
  size_t n = last - first;
  for (; n; --n) {
    std::swap(first[rng() % n], first[n - 1]);
  }
}

#define srand _Oi_srand
#define rand _Oi_rand

// --8<-- [start:main]

int a[100];

int main() {
  srand(SEED);
  int n = rand() % 99 + 1;
  for (int i = 1; i <= n; i++) a[i] = i;
  cout << n << '\n';
  for (int i = 1; i <= n; i++) {
    random_shuffle(a + 1, a + i);
    int cnt = rand() % i;
    for (int j = 1; j <= cnt; j++) cout << a[j] << ' ';
    cout << 0 << '\n';
  }
}

// --8<-- [end:main]