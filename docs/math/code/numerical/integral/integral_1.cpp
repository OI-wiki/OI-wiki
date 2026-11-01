#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
double a, b, c, d;

double f(double x) { return (c * x + d) / (a * x + b); }

// --8<-- [start:core]
constexpr int N = 1000 * 1000;

double simpson_integration(double a, double b) {
  double h = (b - a) / N;
  double s = f(a) + f(b);
  for (int i = 1; i <= N - 1; ++i) {
    double x = a + h * i;
    s += f(x) * ((i & 1) ? 4 : 2);
  }
  s *= h / 3;
  return s;
}

// --8<-- [end:core]
int main() {
  double L, R;
  cin >> a >> b >> c >> d >> L >> R;
  cout << fixed << setprecision(6) << simpson_integration(L, R) << "\n";
}
