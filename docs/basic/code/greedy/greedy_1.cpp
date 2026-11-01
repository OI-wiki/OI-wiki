#include <algorithm>
#include <iostream>
#include <vector>

// --8<-- [start:core]
struct uv {
  int a, b;

  bool operator<(const uv& x) const { return 1LL * a * b < 1LL * x.a * x.b; }
};

// --8<-- [end:core]

// Nonnegative decimal integers, stored least significant digit first.
using BigInt = std::vector<int>;

void multiply(BigInt& value, int factor) {
  int carry = 0;
  for (int& digit : value) {
    int product = digit * factor + carry;
    digit = product % 10;
    carry = product / 10;
  }
  while (carry) {
    value.push_back(carry % 10);
    carry /= 10;
  }
}

BigInt divide(const BigInt& value, int divisor) {
  BigInt quotient(value.size());
  int remainder = 0;
  for (int i = static_cast<int>(value.size()) - 1; i >= 0; --i) {
    int current = remainder * 10 + value[i];
    quotient[i] = current / divisor;
    remainder = current % divisor;
  }
  while (quotient.size() > 1 && quotient.back() == 0) quotient.pop_back();
  return quotient;
}

bool less(const BigInt& left, const BigInt& right) {
  if (left.size() != right.size()) return left.size() < right.size();
  return std::lexicographical_compare(left.rbegin(), left.rend(),
                                      right.rbegin(), right.rend());
}

int main() {
  int n, a, b;
  std::cin >> n >> a >> b;
  std::vector<uv> ministers(n);
  for (uv& minister : ministers) std::cin >> minister.a >> minister.b;
  std::sort(ministers.begin(), ministers.end());
  BigInt product{1}, answer{0};
  multiply(product, a);
  for (const uv& minister : ministers) {
    BigInt reward = divide(product, minister.b);
    if (less(answer, reward)) answer = reward;
    multiply(product, minister.a);
  }
  for (auto it = answer.rbegin(); it != answer.rend(); ++it) std::cout << *it;
  std::cout << '\n';
}
