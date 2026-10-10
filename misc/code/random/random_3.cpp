#include <cstdint>
#include <iostream>
#include <random>

using std::cout;

int main() {
  std::independent_bits_engine<std::minstd_rand, 32, std::uint_fast32_t> rng;
  for (int i = 0; i < 10; ++i) {
    cout << rng() << " ";
  }
  return 0;
}