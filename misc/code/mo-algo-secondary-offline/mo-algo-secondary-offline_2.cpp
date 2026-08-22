#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

constexpr int MAX = 1e5 + 5;
constexpr int MAXX = 4e2 + 5;
constexpr int MX = 1e5;

typedef long long ll;

ll n, m, sz, _sz, sm;
ll st[MAXX], ed[MAXX], bl[MAX], a[MAX], ans[MAX], sm1[MAXX], sm3[MAXX],
    sm2[MAX], sm4[MAX], s[MAX], pre[MAX];

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

void mdf(ll x) {
  sm += x;
  for (int i = bl[x]; i <= sz; ++i) {
    ++sm1[i];
    sm3[i] += x;
  }
  for (int i = x; i <= ed[bl[x]]; ++i) {
    ++sm2[i];
    sm4[i] += x;
  }
}

ll qry(ll x) {
  if (!x) {
    return 0;
  }
  return sm1[bl[x] - 1] + sm2[x];
}

ll _qry(ll x) {
  if (!x) {
    return 0;
  }
  return sm3[bl[x] - 1] + sm4[x];
}

void clear() {
  sm = 0;
  memset(sm1, 0, sizeof(sm1));
  memset(sm2, 0, sizeof(sm2));
  memset(sm3, 0, sizeof(sm3));
  memset(sm4, 0, sizeof(sm4));
}

struct Q {
  ll l, r, id, ans;
} q[MAX];

struct N {
  ll l, r, id, x;
};

std::vector<N> v[MAX];

bool cmp(Q a, Q b) {
  if (a.l / _sz != b.l / _sz) {
    return a.l < b.l;
  } else {
    return ((a.l / _sz) & 1) ? a.r < b.r : a.r > b.r;
  }
}

int main() {
  scanf("%lld%lld", &n, &m);
  _sz = n / sqrt(m);
  init();
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
    s[i] = s[i - 1] + a[i];
  }
  for (int i = 1; i <= n; ++i) {
    pre[i] = qry(a[i] - 1) * a[i] + sm - _qry(a[i]);
    mdf(a[i]);
  }
  clear();
  for (int i = 1; i <= m; ++i) {
    scanf("%lld%lld", &q[i].l, &q[i].r);
    q[i].id = i;
  }
  std::sort(q + 1, q + m + 1, cmp);
  for (int i = 1, L = 1, R = 0; i <= m; ++i) {
    int l = q[i].l, r = q[i].r;
    if (L > l) {
      v[R].push_back({l, L - 1, i, 1});
    }
    while (L > l) {
      --L;
      q[i].ans -= pre[L];
    }
    if (R < r) {
      v[L - 1].push_back({R + 1, r, i, -1});
    }
    while (R < r) {
      ++R;
      q[i].ans += pre[R];
    }
    if (L < l) {
      v[R].push_back({L, l - 1, i, -1});
    }
    while (L < l) {
      q[i].ans += pre[L];
      ++L;
    }
    if (R > r) {
      v[L - 1].push_back({r + 1, R, i, 1});
    }
    while (R > r) {
      q[i].ans -= pre[R];
      --R;
    }
  }
  for (int i = 1; i <= n; ++i) {
    mdf(a[i]);
    for (N j : v[i]) {
      for (int k = j.l; k <= j.r; ++k) {
        q[j.id].ans += 1ll * j.x * (qry(a[k] - 1) * a[k] + sm - _qry(a[k]));
      }
    }
  }
  for (int i = 2; i <= m; ++i) {
    q[i].ans += q[i - 1].ans;
  }
  for (int i = 1; i <= m; ++i) {
    ans[q[i].id] = q[i].ans + s[q[i].r] - s[q[i].l - 1];
  }
  for (int i = 1; i <= m; ++i) {
    printf("%lld\n", ans[i]);
  }
  return 0;
}
