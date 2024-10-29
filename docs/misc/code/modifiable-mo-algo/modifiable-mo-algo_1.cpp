#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

long long qsize;

struct query {
  long long id, t, l, r;

  bool operator<(query b) const {
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
  long long p, x;
} r[150009];

char op;
long long n, m, x, y, cur, qcnt, rcnt, mp[1500009], a[150009], ans[150009];

void add(long long x) {
  if (!mp[x]) {
    cur += 1;
  }
  mp[x] += 1;
}

void del(long long x) {
  mp[x] -= 1;
  if (!mp[x]) {
    cur -= 1;
  }
}

void process() {
  sort(q + 1, q + qcnt + 1);
  long long L = 1, R = 0, last = 0;
  for (long long i = 1; i <= qcnt; i++) {
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
  cin.tie(nullptr);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  qsize = pow(n, 2.0 / 3.0);
  for (long long i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (long long i = 1; i <= m; i++) {
    cin >> op >> x >> y;
    if (op == 'Q') {
      ++qcnt, q[qcnt] = {qcnt, rcnt, x, y};
    } else if (op == 'R') {
      r[++rcnt] = {x, y};
    }
  }
  process();
  for (long long i = 1; i <= qcnt; i++) {
    cout << ans[i] << '\n';
  }
}
