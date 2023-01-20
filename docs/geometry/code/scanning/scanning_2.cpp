#include <bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1
#define N 1000010
using namespace std;

struct node {
  int l, r, ans;
} q[N];

struct t {
  int num, s;
};

vector<t> p[N];
int n, a[N], m, now[N];
int siz[N << 2];

void update(int x, int l, int r, int ad) {
  if (l == r && l == ad) {
    siz[x]++;
    return;
  }
  int mid = l + r >> 1;
  if (ad <= mid) {
    update(ls, l, mid, ad);
  } else {
    update(rs, mid + 1, r, ad);
  }
  siz[x] = siz[ls] + siz[rs];
}

int query(int x, int l, int r, int L, int R) {
  if (l >= L && r <= R) {
    return siz[x];
  }
  int mid = l + r >> 1;
  int res = 0;
  if (L <= mid) {
    res += query(ls, l, mid, L, R);
  }
  if (R > mid) {
    res += query(rs, mid + 1, r, L, R);
  }
  return res;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    p[l - 1].push_back(t{i, -1});
    p[r].push_back(t{i, 1});
    q[i] = node{l, r, 0};
  }
  for (int i = 1; i <= n; i++) {
    update(1, 0, n, now[a[i]]);
    now[a[i]] = i;
    for (auto x : p[i]) {
      int num = x.num;
      q[num].ans += x.s * query(1, 0, n, 0, q[num].l - 1);
    }
  }
  for (int i = 1; i <= m; i++) {
    printf("%d\n", q[i].ans);
  }
  return 0;
}
