#include <iostream>

void solve(int a, int b, int& p, int& q, int c, int d) {
  if ((a / b + 1) * d < c) {
    p = a / b + 1;
    q = 1;
  } else {
    solve(d, c - d * (a / b), q, p, b, a % b);
    p += q * (a / b);
  }
}

int main() {
  int a, b, c, d, p, q;
  while (std::cin >> a >> b >> c >> d) {
    solve(a, b, p, q, c, d);
    std::cout << p << '/' << q << '\n';
  }
  return 0;
}
