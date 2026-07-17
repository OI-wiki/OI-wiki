constexpr int SEED = 5489;

// --8<-- [start:core]

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>

int main() {
  std::string in{"ABCDEFGHIJK"}, out;
  std::sample(in.begin(), in.end(), std::back_inserter(out), 4,
              std::mt19937{SEED});
  std::cout << "Four random letters out of " << in << " : " << out << '\n';
}

// --8<-- [end:core]