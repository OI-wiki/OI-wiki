constexpr int SEED = 5489;

// --8<-- [start:header]
#include <algorithm>
#include <iostream>
#include <random>
// --8<-- [end:header]

// --8<-- [start:real-using]
using std::cout;
using std::mt19937;
// --8<-- [end:real-using]

namespace fake_using {
// --8<-- [start:fake-using]
using std::shuffle;
// --8<-- [end:fake-using]
}

template<class RanIt, class URNG>
void shuffle(RanIt first, RanIt last, URNG &rng) {
  size_t n = last - first;
  for(; n; --n) {
    std::swap(first[rng() % n], first[n - 1]);
  }
}

// --8<-- [start:main]

int a[100];

int main() {
  mt19937 rng(SEED);
  int n = rng() % 99 + 1;
  for (int i = 1; i <= n; i++) a[i] = i;
  cout << n << '\n';
  for (int i = 1; i <= n; i++) {
    shuffle(a + 1, a + i, rng);
    int cnt = rng() % i;
    for (int j = 1; j <= cnt; j++) cout << a[j] << ' ';
    cout << 0 << '\n';
  }
}

// --8<-- [end:main]