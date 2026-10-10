#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

constexpr double eps = 1e-7;
int N;
double l, r, A[20], lmid, rmid;

double f(double x) {
  double res = (double)0;
  for (int i = N; i >= 0; i--) res += A[i] * pow(x, i);
  return res;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> N >> l >> r;
  for (int i = N; i >= 0; i--) cin >> A[i];
  while (r - l > eps) {
    lmid = l + (r - l) / 3;
    rmid = r - (r - l) / 3;
    if (f(lmid) > f(rmid))
      r = rmid;
    else
      l = lmid;
  }
  cout << fixed << setprecision(6) << (l + r) / 2;
  return 0;
}
