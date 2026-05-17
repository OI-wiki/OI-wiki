#include <iostream>

// --8<-- [start:core]

using u64 = unsigned long long;

u64 x;

u64 splitmix64() {
  u64 z = (x += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}

// --8<-- [end:core]

using std::cout;

int main() {
  x = 1;
  for (int i = 0; i < 10; ++i) {
    cout << splitmix64() << " ";
  }
  return 0;
}