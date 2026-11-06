#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

// --8<-- [start:core]
double sqrt_newton(double n) {
  if (n == 0) return 0;
  constexpr static double eps = 1E-15;
  double x = 1;
  while (true) {
    double nx = (x + n / x) / 2;
    if (abs(x - nx) < eps * max(1.0, abs(nx))) break;
    x = nx;
  }
  return x;
}

// --8<-- [end:core]
int main() {
  double n;
  cin >> n;
  cout << fixed << setprecision(6) << sqrt_newton(n) << "\n";
}
