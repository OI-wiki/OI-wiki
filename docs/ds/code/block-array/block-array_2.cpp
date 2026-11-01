#include <algorithm>
#include <cmath>
#include <iostream>
using std::cin;
using std::cout;
using std::fill;
using std::lower_bound;
using std::sort;
using std::sqrt;
constexpr int N = 1000005;
int n, num, st[N], ed[N], belong[N], size[N];
long long a[N], t[N], delta[N];

void init() {
  // --8<-- [start:example11]
  num = sqrt(n);
  for (int i = 1; i <= num; i++)
    st[i] = n / num * (i - 1) + 1, ed[i] = n / num * i;
  ed[num] = n;
  for (int i = 1; i <= num; i++) {
    for (int j = st[i]; j <= ed[i]; j++) {
      belong[j] = i;
    }
    size[i] = ed[i] - st[i] + 1;
  }
  // --8<-- [end:example11]
}

// --8<-- [start:example13]
void Sort(int k) {
  for (int i = st[k]; i <= ed[k]; i++) t[i] = a[i];
  sort(t + st[k], t + ed[k] + 1);
}

void PushDown(int x) {
  if (delta[x] != 0x3f3f3f3f3f3f3f3fll)  // 用该值标记块内没有被整体赋值
    for (int i = st[x]; i <= ed[x]; i++) a[i] = t[i] = delta[x];
  delta[x] = 0x3f3f3f3f3f3f3f3fll;
}

void Modify(int l, int r, int c) {
  int x = belong[l], y = belong[r];
  PushDown(x);
  if (x == y) {
    for (int i = l; i <= r; i++) a[i] = c;
    Sort(x);
    return;
  }
  PushDown(y);
  for (int i = l; i <= ed[x]; i++) a[i] = c;
  for (int i = st[y]; i <= r; i++) a[i] = c;
  Sort(x);
  Sort(y);
  for (int i = x + 1; i < y; i++) delta[i] = c;
}

int Binary_Search(int l, int r, int c) {
  int ans = l - 1, mid;
  while (l <= r) {
    mid = (l + r) / 2;
    if (t[mid] <= c)
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  return ans;
}

int Answer(int l, int r, int c) {
  int ans = 0, x = belong[l], y = belong[r];
  PushDown(x);
  if (x == y) {
    for (int i = l; i <= r; i++)
      if (a[i] <= c) ans++;
    return ans;
  }
  PushDown(y);
  for (int i = l; i <= ed[x]; i++)
    if (a[i] <= c) ans++;
  for (int i = st[y]; i <= r; i++)
    if (a[i] <= c) ans++;
  for (int i = x + 1; i <= y - 1; i++) {
    if (0x3f3f3f3f3f3f3f3fll == delta[i])
      ans += Binary_Search(st[i], ed[i], c) - st[i] + 1;
    else if (delta[i] <= c)
      ans += size[i];
  }
  return ans;
}

// --8<-- [end:example13]

int main() {
  int q;
  cin >> n >> q;
  for (int j = 1; j <= n; ++j) cin >> a[j];
  init();
  fill(delta, delta + N, 0x3f3f3f3f3f3f3f3fll);
  for (int k = 1; k <= num; ++k) Sort(k);
  while (q--) {
    char op;
    int l, r, c;
    cin >> op >> l >> r >> c;
    if (op == 'M')
      Modify(l, r, c);
    else
      cout << Answer(l, r, c) << "\n";
  }
}
