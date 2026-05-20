constexpr int SEED = 5497u;

// --8<-- [end:core]

#include <iostream>
#include <random>

int main() {
  std::mt19937 gen(SEED);  // 播种标准 mersenne_twister_engine
  std::uniform_int_distribution<> dis(1, 6);

  for (int n = 0; n < 10; ++n)
    // 用 dis 变换 gen 所生成的随机 unsigned int 到 [1, 6] 中的 int
    std::cout << dis(gen) << ' ';
  std::cout << '\n';
  return 0;
}

// --8<-- [end:core]