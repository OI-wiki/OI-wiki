#include <iostream>
#include <vector>
// --8<-- [start:core]
#include <algorithm>
#include <cstdio>

#include "gap.h"

long long findGap(int T, int N) {
  static long long a[100005] = {}, ans = 0;
  long long s = 0, t = 1e18, s1, t1;
  if (T == 1) {
    int l = 1, r = N;
    while (l <= r) {
      MinMax(s, t, &s1, &t1);
      a[l++] = s1, a[r--] = t1;
      s = s1 + 1, t = t1 - 1;
    }
    for (int i = 2; i <= N; i++) ans = std::max(ans, a[i] - a[i - 1]);
  } else if (T == 2) {
    MinMax(s, t, &s1, &t1);
    ans = (t1 - s1) / (N - 1);
    long long l = s1 + 1, r = t1, last = s1;
    for (long long i = l; i <= r;) {
      MinMax(i, i + ans, &s1, &t1);
      i += ans + 1;
      if (s1 != -1) ans = std::max(ans, s1 - last), last = t1;
    }
  }
  return ans;
}

// --8<-- [end:core]

// Local grader: T, N, then the hidden increasing sequence.
std::vector<long long> hidden;

void MinMax(long long l, long long r, long long* mn, long long* mx) {
  auto a = std::lower_bound(hidden.begin(), hidden.end(), l);
  auto b = std::upper_bound(hidden.begin(), hidden.end(), r);
  if (a == b) {
    *mn = *mx = -1;
    return;
  }
  *mn = *a;
  *mx = *--b;
}

int main() {
  int t, n;
  std::cin >> t >> n;
  hidden.resize(n);
  for (auto& v : hidden) std::cin >> v;
  std::cout << findGap(t, n) << '\n';
}
