#include <iostream>

// --8<-- [start:core]

using u32 = unsigned int;
using u64 = unsigned long long;

u32 x;

u32 xorshift32() {
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

u64 y;

u64 xorshift64() {
  y ^= y << 13;
  y ^= y >> 7;
  y ^= y << 17;
  return y;
}

// --8<-- [end:core]

using std::cout;

int main() {
  x = 1;
  y = 1;
  for (int i = 0; i < 10; ++i) {
    cout << xorshift32() << " ";
  }
  cout << "\n";
  for (int i = 0; i < 10; ++i) {
    cout << xorshift64() << " ";
  }
  return 0;
}