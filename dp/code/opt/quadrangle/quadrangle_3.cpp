#include <deque>
#include <iostream>
#define all \
  for (auto i : {&q, &l, &r}) (*i)
using namespace std;
long long n, m, a[500009], s[500009], u, v, w, sum[500009], cnt[500009];
deque<int> q, l, r;

long long f(int i, int j) {
  int k = (i + j) >> 1;
  return sum[i - 1] + v + a[k] * (k - i + 1) - (s[k] - s[i - 1]) +
         (s[j] - s[k]) - a[k] * (j - k);
}

void work() {
  all.clear();
  for (int i = 1; i <= n; ++i) {
    if (q.size() && r.front() < i) all.pop_front();  // 队首出队
    if (q.size()) l.front() = i;
    for (; q.size() && f(q.back(), l.back()) >= f(i, l.back());)  // 队尾出队
      all.pop_back();
    if (q.empty())  // 入队
      q.emplace_back(i), l.emplace_back(i), r.emplace_back((int)n);
    else if (f(q.back(), n) >= f(i, n)) {
      int ll = l.back(), rr = n, mid;
      for (; ll <= rr;) {
        mid = (ll + rr) >> 1;
        if (f(q.back(), mid) >= f(i, mid))
          rr = mid - 1;
        else
          ll = mid + 1;
      }
      r.back() = rr;
      q.emplace_back(i), l.emplace_back(ll), r.emplace_back((int)n);
    }
    sum[i] = f(q.front(), i);
    cnt[i] = cnt[q.front() - 1] + 1;
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; cin >> a[i], s[i] = s[i - 1] + a[i], ++i);
  for (w = 2e12; u <= w;) {  // wqs二分
    v = (u + w) >> 1;
    work();
    if (cnt[n] < m)
      w = v - 1;
    else
      u = v + 1;
  }
  v = w;
  work();
  cout << sum[n] - m * v;
}
