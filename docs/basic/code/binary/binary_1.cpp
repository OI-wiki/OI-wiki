#include <cmath>
#include <cstdio>
using namespace std;

const double eps = 0.0000001;
int N;
double l, r, A[20], lmid, rmid;

double f(double x) {
  double res = (double)0;
  for (int i = N; i >= 0; i--) res += A[i] * pow(x, i);
  return res;
}

int main() {
  scanf("%d%lf%lf", &N, &l, &r);
  for (int i = N; i >= 0; i--) scanf("%lf", &A[i]);
  while (r - l > eps) {
    lmid = (2 * l + r) / 3;
    rmid = (l + 2 * r) / 3;
    if (f(lmid) > f(rmid))
      r = rmid;
    else
      l = lmid;
  }
  printf("%6lf", l);
  return 0;
}