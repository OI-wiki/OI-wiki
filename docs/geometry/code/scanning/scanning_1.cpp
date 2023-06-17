#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct node {
  ll data;
  ll num;
} f[5000001];

ll n, c[5000001], ans, a[5000001];

bool cmp(node a, node b) {
  if (a.data == b.data) {
    return a.num < b.num;
  }
  return a.data < b.data;
}

ll lowbit(ll i) { return i & (-i); }

ll sum(ll x) {
  ll s = 0;
  for (; x > 0; x -= lowbit(x)) {
    s += c[x];
  }
  return s;
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
    ans += sum(a[i]);
    for (ll j = a[i]; j <= n; j += lowbit(j)) {
      c[j]++;
    }
  }
  cout << ans;
  return 0;
}
