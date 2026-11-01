#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef M_PI
const double M_PI = acos(-1.0);
#endif
using Complex = complex<double>;
// --8<-- [start:core]
#include <cmath>
#include <complex>

using Comp = std::complex<double>;  // STL complex

constexpr Comp I(0, 1);  // i
constexpr int MAX_N = 1 << 20;

Comp tmp[MAX_N];

// rev=1, DFT; rev=-1, IDFT
// 应用完本函数后需要注意归一化系数的处理
void DFT(Comp* f, int n, int rev) {
  if (n == 1) return;
  for (int i = 0; i < n; ++i) tmp[i] = f[i];
  // 偶数放左边，奇数放右边
  for (int i = 0; i < n; ++i) {
    if (i & 1)
      f[n / 2 + i / 2] = tmp[i];
    else
      f[i / 2] = tmp[i];
  }
  Comp *g = f, *h = f + n / 2;
  // 递归 DFT
  DFT(g, n / 2, rev), DFT(h, n / 2, rev);
  // cur 是当前单位复根，对于 k = 0 而言，它对应的单位复根 omega^0_n = 1．
  // step 是两个单位复根的差，即满足 omega^k_n = step*omega^{k-1}*n，
  // 定义等价于 exp(I*(-2*M_PI/n*rev))
  Comp cur(1, 0), step(cos(2 * M_PI / n), sin(-2 * M_PI * rev / n));
  for (int k = 0; k < n / 2;
       ++k) {  // F(omega^k_n) = G(omega^k*{n/2}) + omega^k*n\*H(omega^k*{n/2})
    tmp[k] = g[k] + cur * h[k];
    // F(omega^{k+n/2}*n) = G(omega^k*{n/2}) - omega^k_n*H(omega^k\_{n/2})
    tmp[k + n / 2] = g[k] - cur * h[k];
    cur *= step;
  }
  for (int i = 0; i < n; ++i) f[i] = tmp[i];
}

// --8<-- [end:core]
int main() {
  string a, b;
  while (cin >> a >> b) {
    int len = 1;
    while (len < int(a.size() + b.size())) len <<= 1;
    vector<Complex> x(len), y(len);
    for (size_t i = 0; i < a.size(); ++i) x[i] = a[a.size() - 1 - i] - '0';
    for (size_t i = 0; i < b.size(); ++i) y[i] = b[b.size() - 1 - i] - '0';
    DFT(x.data(), len, 1);
    DFT(y.data(), len, 1);
    for (int i = 0; i < len; ++i) x[i] *= y[i];
    DFT(x.data(), len, -1);
    vector<long long> digits(len + 1);
    for (int i = 0; i < len; ++i) digits[i] = llround(x[i].real() / len);
    for (int i = 0; i < len; ++i) {
      digits[i + 1] += digits[i] / 10;
      digits[i] %= 10;
    }
    int last = len;
    while (last > 0 && digits[last] == 0) --last;
    for (int i = last; i >= 0; --i) cout << digits[i];
    cout << "\n";
  }
}
