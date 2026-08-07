#include <iostream>
#include <unordered_map>

// --8<-- [start:core]
#include <cstdint>

using u64 = std::uint64_t;

struct MyHash {
  u64 mix64(u64 x) const {
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(size_t x) const {
    // 推荐使用 <chrono> 库的 std::chrono::steady_clock::now().time_since_epoch().count()
    // 作为 FIXED_RANDOM
    static const u64 FIXED_RANDOM = 0x9e3779b97f4a7c15;
    return mix64(x + FIXED_RANDOM);
  }
};

// --8<-- [end:core]

int main() {
  std::unordered_map<u64, u64, MyHash> kvs;
  for (u64 i = 0; i < 10; ++i) {
    kvs[i] = i;
  }
  for (u64 i = 0; i < 10; ++i) {
    std::cout << kvs[i] << " ";
  }
  return 0;
}