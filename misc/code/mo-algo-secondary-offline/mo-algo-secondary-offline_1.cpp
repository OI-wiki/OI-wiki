#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

constexpr int MAX = 1e5 + 5;
constexpr int MAXX = 4e2 + 5;
constexpr int MX = 1e5;
typedef long long ll;

int n, m, sz, _sz;
int a[MAX], b[MAX], bl[MAX], st[MAXX], ed[MAXX], b1[MAXX], b2[MAX], p1[MAX],
    p2[MAX];
ll ans[MAX];

struct N {
  int l, r, id, x, y;
};

std::vector<N> v[MAX];

struct Q {
  int l, r, id;
  ll ans = 0;
} q[MAX];

bool cmp(Q a, Q b) {
  if (a.l / _sz != b.l / _sz) {
    return a.l < b.l;
  }
  return ((a.l / _sz) & 1) ? a.r < b.r : a.r > b.r;
}

void init() {
  sz = sqrt(MX);
  for (int i = 1; i <= sz; ++i) {
    st[i] = (MX / sz) * (i - 1) + 1;
    ed[i] = (MX / sz) * i;
  }
  ed[sz] = MX;
  for (int i = 1; i <= sz; ++i) {
    for (int j = st[i]; j <= ed[i]; ++j) {
      bl[j] = i;
    }
  }
}

void clear() {
  memset(b1, 0, sizeof(b1));
  memset(b2, 0, sizeof(b2));
}

void mdf(int x) {
  for (int i = bl[x]; i <= sz; ++i) {
    ++b1[i];
  }
  for (int i = x; i <= ed[bl[x]]; ++i) {
    ++b2[i];
  }
}

int qry(int x) {
  if (!x) {
    return 0;
  }
  return b1[bl[x] - 1] + b2[x];
}

int main() {
  scanf("%d%d", &n, &m);
  init();
  _sz = sqrt(m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    b[i] = a[i];
  }
  std::sort(b + 1, b + n + 1);
  int len = std::unique(b + 1, b + n + 1) - b - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = std::lower_bound(b + 1, b + len + 1, a[i]) - b;
  }
  for (int i = 1; i <= n; ++i) {
    p1[i] = qry(a[i] - 1);
    p2[i] = qry(n) - qry(a[i]);
    mdf(a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d%d", &q[i].l, &q[i].r);
    q[i].id = i;
  }
  std::sort(q + 1, q + m + 1, cmp);
  clear();
  for (int i = 1, L = 1, R = 0; i <= m; ++i) {
    int l = q[i].l, r = q[i].r;
    if (L > l) {
      v[R].push_back({l, L - 1, i, 1, 0});
    }
    while (L > l) {
      --L;
      q[i].ans -= p1[L];
    }
    if (R < r) {
      v[L - 1].push_back({R + 1, r, i, -1, 1});
    }
    while (R < r) {
      ++R;
      q[i].ans += p2[R];
    }
    if (L < l) {
      v[R].push_back({L, l - 1, i, -1, 0});
    }
    while (L < l) {
      q[i].ans += p1[L];
      ++L;
    }
    if (R > r) {
      v[L - 1].push_back({r + 1, R, i, 1, 1});
    }
    while (R > r) {
      q[i].ans -= p2[R];
      --R;
    }
  }
  for (int i = 1; i <= n; ++i) {
    mdf(a[i]);
    for (N j : v[i]) {
      for (int k = j.l; k <= j.r; ++k) {
        if (j.y == 0) {
          q[j.id].ans += j.x * qry(a[k] - 1);
        } else {
          q[j.id].ans += j.x * (i - qry(a[k]));
        }
      }
    }
  }
  for (int i = 2; i <= m; ++i) {
    q[i].ans += q[i - 1].ans;
  }
  for (int i = 1; i <= m; ++i) {
    ans[q[i].id] = q[i].ans;
  }
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", ans[i]);
  }
}
