#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
double a, b, c, d;

double f(double x) { return (c * x + d) / (a * x + b); }

// --8<-- [start:core]
double simpson(double l, double r) {
  double mid = (l + r) / 2;
  return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;  // 辛普森公式
}

double asr(double l, double r, double eps, double ans, int step) {
  double mid = (l + r) / 2;
  double fl = simpson(l, mid), fr = simpson(mid, r);
  if (abs(fl + fr - ans) <= 15 * eps && step < 0)
    return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
  return asr(l, mid, eps / 2, fl, step - 1) +
         asr(mid, r, eps / 2, fr, step - 1);  // 否则分割成两段递归求解
}

double calc(double l, double r, double eps) {
  return asr(l, r, eps, simpson(l, r), 12);
}

// --8<-- [end:core]
int main() {
  double L, R;
  cin >> a >> b >> c >> d >> L >> R;
  cout << fixed << setprecision(6) << calc(L, R, 1e-9) << "\n";
}
