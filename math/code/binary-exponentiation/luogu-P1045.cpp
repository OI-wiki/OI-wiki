#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

const int M = 500;

int a[505], b[505], t[505];

// 大整数乘法
void mult(int x[], int y[]) {
  memset(t, 0, sizeof(t));
  for (int i = 1; i <= x[0]; i++) {
    for (int j = 1; j <= y[0]; j++) {
      if (i + j - 1 > M) continue;
      t[i + j - 1] += x[i] * y[j];
      t[i + j] += t[i + j - 1] / 10;
      t[i + j - 1] %= 10;
      t[0] = i + j;
    }
  }
  memcpy(b, t, sizeof(b));
}

// 快速幂
void binpow(int p) {
  if (p == 1) {
    memcpy(b, a, sizeof(b));
    return;
  }
  binpow(p / 2);  // (2^(p/2))^2=2^p
  mult(b, b);     // 对 b 平方
  if (p % 2 == 1) mult(b, a);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int p;
  cin >> p;
  a[0] = 1;  // 记录 a 数组的位数
  a[1] = 2;  // 对 2 进行平方
  b[0] = 1;  // 记录 b 数组的位数
  b[1] = 1;  // 答案数组
  binpow(p);
  cout << (int)(log10(2) * p) + 1 << '\n';
  b[1] -= 1;  // 最后一位减 1
  for (int i = M; i >= 1; i--) {
    cout << b[i];
    if ((i - 1) % 50 == 0) {
      cout << '\n';
    }
  }
}
