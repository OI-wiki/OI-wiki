#include <iostream>

int n, a[100005], d[270000], b[270000];

void build(int l, int r, int p) {  // 建树
  if (l == r) {
    d[p] = a[l];
    return;
  }
  int m = l + ((r - l) >> 1);
  build(l, m, p << 1), build(m + 1, r, (p << 1) | 1);
  d[p] = d[p << 1] + d[(p << 1) | 1];
}

void update(int l, int r, int c, int s, int t,
            int p) {  // 更新，可以参考前面两个例题
  if (l <= s && t <= r) {
    d[p] = (t - s + 1) * c, b[p] = c;
    return;
  }
  int m = s + ((t - s) >> 1);
  if (b[p]) {
    d[p << 1] = b[p] * (m - s + 1), d[(p << 1) | 1] = b[p] * (t - m);
    b[p << 1] = b[(p << 1) | 1] = b[p];
    b[p] = 0;
  }
  if (l <= m) update(l, r, c, s, m, p << 1);
  if (r > m) update(l, r, c, m + 1, t, (p << 1) | 1);
  d[p] = d[p << 1] + d[(p << 1) | 1];
}

int getsum(int l, int r, int s, int t, int p) {  // 取得答案，和前面一样
  if (l <= s && t <= r) return d[p];
  int m = s + ((t - s) >> 1);
  if (b[p]) {
    d[p << 1] = b[p] * (m - s + 1), d[(p << 1) | 1] = b[p] * (t - m);
    b[p << 1] = b[(p << 1) | 1] = b[p];
    b[p] = 0;
  }
  int sum = 0;
  if (l <= m) sum = getsum(l, r, s, m, p << 1);
  if (r > m) sum += getsum(l, r, m + 1, t, (p << 1) | 1);
  return sum;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin >> n;
  for (int i = 1; i <= n; i++) std::cin >> a[i];
  build(1, n, 1);
  int q, i1, i2, i3, i4;
  std::cin >> q;
  while (q--) {
    std::cin >> i1 >> i2 >> i3;
    if (i1 == 0)
      std::cout << getsum(i2, i3, 1, n, 1) << std::endl;
    else
      std::cin >> i4, update(i2, i3, i4, 1, n, 1);
  }
  return 0;
}