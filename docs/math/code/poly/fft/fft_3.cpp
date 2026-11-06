#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
const double PI = acos(-1.0);
using Complex = complex<double>;

// --8<-- [start:reverse-loop]
/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
void change_loop(Complex y[], int len) {
  // 一开始 i 是 0...01，而 j 是 10...0，在二进制下相反对称．
  // 之后 i 逐渐加一，而 j 依然维持着和 i 相反对称，一直到 i = 1...11．
  for (int i = 1, j = len / 2, k; i < len - 1; i++) {
    // 交换互为小标反转的元素，i < j 保证交换一次
    if (i < j) swap(y[i], y[j]);
    // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的．
    // 这里 k 代表了 0 出现的最高位．j 先减去高位的全为 1 的数字，
    // 直到遇到了 0，之后再加上即可．
    // 考虑 j 中比特位的翻转次数，最高位将会翻转 n 次，
    // 第二高位将会翻转 n/2 次，以此类推，所以时间复杂度为：
    // T(n) = n + n/2 + n/4 + ... = O(n)
    k = len / 2;
    while (j >= k) {
      j = j - k;
      k = k / 2;
    }
    j += k;
  }
}

// --8<-- [end:reverse-loop]
// --8<-- [start:reverse-table]
// 同样需要保证 len 是 2 的幂
// 记 rev[i] 为 i 翻转后的值
void change_table(Complex y[], int len) {
  vector<int> rev(len);
  for (int i = 0; i < len; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1) {  // 如果最后一位是 1，则翻转成 len/2
      rev[i] |= len >> 1;
    }
  }
  for (int i = 0; i < len; ++i) {
    if (i < rev[i]) {  // 保证每对数只翻转一次
      swap(y[i], y[rev[i]]);
    }
  }
  return;
}

// --8<-- [end:reverse-table]
void change(Complex y[], int len) {
  vector<Complex> copy(y, y + len);
  change_loop(y, len);
  change_table(copy.data(), len);
  assert(equal(copy.begin(), copy.end(), y));
}

// --8<-- [start:fft]
/*
 * 做 FFT
 * len 必须是 2^k 形式
 * on == 1 时是 DFT，on == -1 时是 IDFT
 */
void fft(Complex y[], int len, int on) {
  change(y, len);
  for (int h = 2; h <= len; h <<= 1) {             // 模拟合并过程
    Complex wn(cos(2 * PI / h), sin(2 * PI / h));  // 计算当前单位复根
    for (int j = 0; j < len; j += h) {
      Complex w(1, 0);  // 计算当前单位复根
      for (int k = j; k < j + h / 2; k++) {
        Complex u = y[k];
        Complex t = w * y[k + h / 2];
        y[k] = u + t;  // 这就是把两部分分治的结果加起来
        y[k + h / 2] = u - t;
        // 后半个 「step」 中的ω一定和 「前半个」 中的成相反数
        // 「红圈」上的点转一整圈「转回来」，转半圈正好转成相反数
        // 一个数相反数的平方与这个数自身的平方相等
        w = w * wn;
      }
    }
  }
  if (on == -1) {
    reverse(y + 1, y + len);
    for (int i = 0; i < len; i++) {
      y[i] /= len;
    }
  }
}

// --8<-- [end:fft]
int main() {
  string a, b;
  while (cin >> a >> b) {
    int len = 1;
    while (len < int(a.size() + b.size())) len <<= 1;
    vector<Complex> x(len), y(len);
    for (size_t i = 0; i < a.size(); ++i) x[i] = a[a.size() - 1 - i] - '0';
    for (size_t i = 0; i < b.size(); ++i) y[i] = b[b.size() - 1 - i] - '0';
    fft(x.data(), len, 1);
    fft(y.data(), len, 1);
    for (int i = 0; i < len; ++i) x[i] *= y[i];
    fft(x.data(), len, -1);
    vector<long long> digits(len + 1);
    for (int i = 0; i < len; ++i) digits[i] = llround(x[i].real());
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
