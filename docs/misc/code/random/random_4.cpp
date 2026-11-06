constexpr unsigned int SEED = 5489u;

// --8<-- [start:header]
#include <iostream>
#include <map>
#include <random>
#include <string>

// --8<-- [end:header]

namespace fake_using {
// --8<-- [start:fake-using]
using std::random_device;
using std::uniform_int_distribution;
// --8<-- [end:fake-using]
}  // namespace fake_using

// 测试支架：固定随机序列及其区间映射，避免平台实现差异．
class random_device {
 private:
  std::mt19937 rng{SEED};

 public:
  using result_type = std::mt19937::result_type;

  static constexpr result_type min() { return std::mt19937::min(); }

  static constexpr result_type max() { return std::mt19937::max(); }

  result_type operator()() { return rng(); }
};

template <class IntType = int>
class uniform_int_distribution {
 private:
  IntType a, b;

 public:
  uniform_int_distribution(IntType a, IntType b) : a(a), b(b) {}

  template <class Rng>
  IntType operator()(Rng& rng) {
    return static_cast<IntType>(rng() % (b - a + 1)) + a;
  }
};

// --8<-- [start:main]
int main() {
  random_device rd;
  std::map<int, int> hist;
  uniform_int_distribution<int> dist(0, 9);
  for (int n = 0; n < 20000; ++n) {
    ++hist[dist(rd)];
  }
  for (auto p : hist) {
    std::cout << p.first << " : " << std::string(p.second / 100, '*') << '\n';
  }
  return 0;
}

// --8<-- [end:main]
