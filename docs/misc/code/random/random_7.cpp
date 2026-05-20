#include <iostream>

// --8<-- [start:core]

#include <cstdint>

using u64 = std::uint64_t;

class splitmix64 {

private:
  u64 x;

public:
  splitmix64(): x(0) {}
  splitmix64(u64 s): x(s) {}

  u64 operator()() {
    u64 z = (x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
  }
};

// --8<-- [end:core]

using std::cout;

int main() {
  splitmix64 rng;
  for (int i = 0; i < 10; ++i) {
    cout << rng() << " ";
  }
  return 0;
}