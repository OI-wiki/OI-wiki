constexpr int SEED = 5489;

// --8<-- [start:core]

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::mt19937 g(SEED);

  std::shuffle(v.begin(), v.end(), g);

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}

// --8<-- [end:core]