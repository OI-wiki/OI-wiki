constexpr int SEED = 5489;

// --8<-- [start:header]
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
// --8<-- [end:header]

// --8<-- [start:real-using]
using std::copy;
using std::cout;
using std::mt19937;
using std::ostream_iterator;
using std::vector;

// --8<-- [end:real-using]

namespace fake_using {
// --8<-- [start:fake-using]
using std::shuffle;
// --8<-- [end:fake-using]
}  // namespace fake_using

template <class RanIt, class URNG>
void shuffle(RanIt first, RanIt last, URNG &rng) {
  size_t n = last - first;
  for (; n; --n) {
    std::swap(first[rng() % n], first[n - 1]);
  }
}

// --8<-- [start:core]

int main() {
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  mt19937 g(SEED);

  shuffle(v.begin(), v.end(), g);

  copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
  cout << "\n";
}

// --8<-- [end:core]