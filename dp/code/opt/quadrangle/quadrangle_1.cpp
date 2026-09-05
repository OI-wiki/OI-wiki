#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#define all \
  for (auto i : {&q, &l, &r}) (*i)
using namespace std;
int n, a[500009], ans[500009];
deque<int> q, l, r;

double f(int i, int j) { return a[i] + sqrtl(j - i); }

void work() {
  all.clear();
  for (int i = 0; i < n; ++i) {
    if (q.size() && r.front() < i) all.pop_front();  // 队首出队
    if (q.size()) l.front() = i;
    for (; q.size() && f(q.back(), l.back()) <= f(i, l.back());)  // 队尾出队
      all.pop_back();
    if (q.empty())  // 入队
      q.emplace_back(i), l.emplace_back(i), r.emplace_back(n);
    else if (f(q.back(), n) < f(i, n)) {
      int ll = l.back(), rr = n, mid;
      for (; ll <= rr;) {
        mid = (ll + rr) >> 1;
        if (f(q.back(), mid) < f(i, mid))
          rr = mid - 1;
        else
          ll = mid + 1;
      }
      r.back() = rr;
      q.emplace_back(i), l.emplace_back(ll), r.emplace_back(n);
    }
    ans[i] = max(ans[i], (int)(ceil(f(q.front(), i))) - a[i]);
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; cin >> a[i++]);
  work();
  reverse(a, a + n);
  reverse(ans, ans + n);
  work();
  reverse(ans, ans + n);
  for (int i = 0; i < n; cout << ans[i++] << '\n');
}
