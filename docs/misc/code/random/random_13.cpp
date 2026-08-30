constexpr int SEED = 5489;

// --8<-- [start:header]
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
// --8<-- [end:header]

// --8<-- [start:real-using]
using std::back_inserter;
using std::copy;
using std::cout;
using std::mt19937;
using std::string;

// --8<-- [end:real-using]

namespace fake_using {
#if __cplusplus >= 201703L
// --8<-- [start:fake-using]
using std::sample;
// --8<-- [end:fake-using]
#endif
}  // namespace fake_using

template <class RanIt, class OutIt, class URNG>
void sample(RanIt first, RanIt last, OutIt dest, int k, URNG &&rng) {
  size_t n = last - first;
  for (; n; ++first, --n) {
    if (rng() % n < k) {
      --k;
      *dest = *first;
      ++dest;
    }
  }
}

// --8<-- [start:main]

int main() {
  string in{"ABCDEFGHIJK"}, out;
  mt19937 rng{SEED};
  sample(in.begin(), in.end(), back_inserter(out), 4, rng);
  cout << "Four random letters out of " << in << ": " << out << '\n';
}

// --8<-- [end:main]