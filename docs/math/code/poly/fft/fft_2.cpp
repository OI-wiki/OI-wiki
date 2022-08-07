#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const double PI = acos(-1.0);

struct Complex {
  double x, y;

  Complex(double _x = 0.0, double _y = 0.0) {
    x = _x;
    y = _y;
  }

  Complex operator-(const Complex &b) const {
    return Complex(x - b.x, y - b.y);
  }

  Complex operator+(const Complex &b) const {
    return Complex(x + b.x, y + b.y);
  }

  Complex operator*(const Complex &b) const {
    return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
  }
};

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 *len 必须为 2 的幂
 */
void change(Complex y[], int len) {
  int i, j, k;
  for (int i = 1, j = len / 2; i < len - 1; i++) {
    if (i < j) swap(y[i], y[j]);
    // 交换互为小标反转的元素，i<j 保证交换一次
    // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的
    k = len / 2;
    while (j >= k) {
      j = j - k;
      k = k / 2;
    }
    if (j < k) j += k;
  }
}

/*
 * 做 FFT
 *len 必须是 2^k 形式
 *on == 1 时是 DFT，on == -1 时是 IDFT
 */
void fft(Complex y[], int len, int on) {
  change(y, len);
  for (int h = 2; h <= len; h <<= 1) {
    Complex wn(cos(2 * PI / h), sin(on * 2 * PI / h));
    for (int j = 0; j < len; j += h) {
      Complex w(1, 0);
      for (int k = j; k < j + h / 2; k++) {
        Complex u = y[k];
        Complex t = w * y[k + h / 2];
        y[k] = u + t;
        y[k + h / 2] = u - t;
        w = w * wn;
      }
    }
  }
  if (on == -1) {
    for (int i = 0; i < len; i++) {
      y[i].x /= len;
    }
  }
}

const int MAXN = 200020;
Complex x1[MAXN], x2[MAXN];
char str1[MAXN / 2], str2[MAXN / 2];
int sum[MAXN];

int main() {
  while (scanf("%s%s", str1, str2) == 2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = 1;
    while (len < len1 * 2 || len < len2 * 2) len *= 2;
    // a * b 三次变两次优化
    // 适用于将两个多项式乘法中的三次FFT变成两次
    // 原理是：(a+bi)^2= (a^2-b^2) + 2abi
    // FFT系数转点值乘法 转系数之后虚部除以2（乘0.5/len）即是结果
    for (int i = 0; i < len1 && i < len2; i++)
      x1[i] = Complex(str1[len1 - 1 - i] - '0', str2[len2 - 1 - i] - '0');
    if (len1 >= len2)
      for (int i = len2; i < len1; i++)
        x1[i] = Complex(str1[len1 - 1 - i] - '0', 0);
    else
      for (int i = len1; i < len2; i++)
        x1[i] = Complex(0, str2[len2 - 1 - i] - '0');
    for (int i = max(len1, len2); i < len; i++) x1[i] = Complex(0, 0);
    fft(x1, len, 1);
    for (int i = 0; i < len; i++) x1[i] = x1[i] * x1[i];
    fft(x1, len, -1);
    double ilen = 0.5 / len;
    // 除len是因为IDFT(第64行)的时候没有处理虚部
    for (int i = 0; i < len; i++) sum[i] = int(x1[i].y * ilen + 0.5);
    for (int i = 0; i < len; i++) {
      sum[i + 1] += sum[i] / 10;
      sum[i] %= 10;
    }
    len = len1 + len2 - 1;
    while (sum[len] == 0 && len > 0) len--;
    for (int i = len; i >= 0; i--) printf("%c", sum[i] + '0');
    printf("\n");
  }
  return 0;
}

// 加油加油！
