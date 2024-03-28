#include <cmath>
#include <cstdio>
using namespace std;

const double eps = 0.0000001;
int N;
double l, r, A[20], mid, lmid, rmid;

double f(double x) {
  double res = (double)0;
  for (int i = N; i >= 0; i--) res += A[i] * pow(x, i);
  return res;
}

int main() {
  scanf("%d%lf%lf", &N, &l, &r);
  for (int i = N; i >= 0; i--) scanf("%lf", &A[i]);
  while (r - l > eps) {
    mid = (l + r) / 2;
    lmid = mid - eps;
    rmid = mid + eps;
    if (f(lmid) > f(rmid))
      r = mid;
    else
      l = mid;
  }
  printf("%6lf", l);
  return 0;
}