#include <iostream>

// Obtain multiplicity of p in n!.
int multiplicity_factorial(int n, int p) {
  int count = 0;
  do {
    n /= p;
    count += n;
  } while (n);
  return count;
}

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    int n, p;
    std::cin >> n >> p;
    std::cout << multiplicity_factorial(n, p) << '\n';
  }
  return 0;
}
