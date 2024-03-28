#include <algorithm>
#include <cmath>
#include <iostream>

#define int long long
#define endl '\n'

using namespace std;

int qsize;

struct query {
  int id, t, l, r;

  inline bool operator<(query b) {
    if (l / qsize != b.l / qsize) {
      return l / qsize > b.l / qsize;
    } else if (r / qsize != b.r / qsize) {
      return r / qsize > b.r / qsize;
    } else {
      return t > b.t;
    }
  }
} q[150009];

struct operation {
  int p, x;
} r[150009];

char op;
int n, m, x, y, cur, qcnt, rcnt, mp[1500009], a[150009], ans[150009];

inline void add(int x) {
  if (!mp[x]) {
    cur += 1;
  }
  mp[x] += 1;
}

inline void del(int x) {
  mp[x] -= 1;
  if (!mp[x]) {
    cur -= 1;
  }
}

inline void process() {
  sort(q + 1, q + qcnt + 1);
  int L = 1, R = 0, last = 0;
  for (int i = 1; i <= qcnt; i++) {
    while (R < q[i].r) {
      add(a[++R]);
    }
    while (R > q[i].r) {
      del(a[R--]);
    }
    while (L > q[i].l) {
      add(a[--L]);
    }
    while (L < q[i].l) {
      del(a[L++]);
    }
    while (last < q[i].t) {
      last += 1;
      if (r[last].p >= L && r[last].p <= R) {
        add(r[last].x);
        del(a[r[last].p]);
      }
      swap(a[r[last].p], r[last].x);
    }
    while (last > q[i].t) {
      if (r[last].p >= L && r[last].p <= R) {
        add(r[last].x);
        del(a[r[last].p]);
      }
      swap(a[r[last].p], r[last].x);
      last -= 1;
    }
    ans[q[i].id] = cur;
  }
}

signed main() {
  cin.tie(0);
  cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  qsize = pow(n, 2.0 / 3.0);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> op >> x >> y;
    if (op == 'Q') {
      q[++qcnt] = {qcnt, rcnt, x, y};
    } else if (op == 'R') {
      r[++rcnt] = {x, y};
    }
  }
  process();
  for (int i = 1; i <= qcnt; i++) {
    cout << ans[i] << endl;
  }
}
