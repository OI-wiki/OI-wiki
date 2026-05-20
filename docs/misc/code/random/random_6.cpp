#include <iostream>

// --8<-- [start:core]

#include <cstdint>

using u32 = std::uint32_t;
using u64 = std::uint64_t;

class xorshift32 {

private:
  u32 x;

public:
  xorshift32(): x(2463534242) {}
  xorshift32(u32 s): x(s) {}

  u32 operator()() {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
  }
};

class xorshift64 {

private:
  u64 x;

public:
  xorshift64(): x(88172645463325252) {}
  xorshift64(u64 s): x(s) {}

  u64 operator()() {
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return x;
  }
};

// --8<-- [end:core]

using std::cout;

int main() {
  
  xorshift32 rng32;
  xorshift64 rng64;

  for (int i = 0; i < 10; ++i) {
    cout << rng32() << " ";
  }
  cout << "\n";
  for (int i = 0; i < 10; ++i) {
    cout << rng64() << " ";
  }
  return 0;
}