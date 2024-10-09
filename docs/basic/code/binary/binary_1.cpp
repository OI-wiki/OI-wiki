#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

constexpr double eps = 1e-7;
int N;
double l, r, A[20], mid, lmid, rmid;

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
    mid = (l + r) / 2;
    lmid = mid - eps;
    rmid = mid + eps;
    if (f(lmid) > f(rmid))
      r = mid;
    else
      l = mid;
  }
  cout << fixed << setprecision(6) << l;
  return 0;
}