#include <algorithm>
#include <iostream>
using ll = long long;
using namespace std;

struct node {
  ll data;
  ll num;
} f[500010];

ll n, ans, a[500010];

bool cmp(node a, node b) {
  if (a.data == b.data) {
    return a.num < b.num;
  }
  return a.data < b.data;
}

ll sum[500010];

int lowbit(int x) { return x & (-x); }

void add(int x, int k) {
  while (x <= n) {
    sum[x] = sum[x] + k;
    x = x + lowbit(x);
  }
}

int getsum(int x) {
  int ret = 0;
  while (x > 0) {
    ret = ret + sum[x];
    x = x - lowbit(x);
  }
  return ret;
}

int main() {
  cin >> n;
  for (ll i = 1; i <= n; i++) {
    cin >> f[i].data;
    f[i].num = i;
  }
  sort(f + 1, f + 1 + n, cmp);
  for (int i = 1; i <= n; i++) {
    a[f[i].num] = i;
  }
  for (ll i = n; i > 0; i--) {
    ans += getsum(a[i]);
    add(a[i], 1);
  }
  cout << ans;
  return 0;
}
