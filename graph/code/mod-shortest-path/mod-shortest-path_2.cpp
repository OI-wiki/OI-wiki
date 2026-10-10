#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

using ll = long long;

constexpr int maxn = 1e5 + 100;

ll d[maxn];
bool vis[maxn];
ll ans;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

void upd(int step, int M) {
  int D = gcd(step, M);
  int len = M / D;

  for (int st = 0; st < D; st++) {
    if (vis[st]) continue;
    std::vector<int> v;
    int u = st;
    for (int i = 0; i < len; i++) {
      v.push_back(u);
      vis[u] = true;
      u = (u + step) % M;
    }
    for (int r = 0; r < 2; r++) {
      for (int i = 0; i < len; i++) {
        int las = v[i];
        int now = v[(i + 1) % len];
        if (d[las] != LLONG_MAX) {
          // 如果d[las]=LLONG_MAX，d[las]+step会越界，需要特判
          d[now] = std::min(d[now], d[las] + step);
        }
      }
    }
  }
}

int main() {
  ll h;
  std::cin >> h;
  int x[3];
  for (int i = 0; i < 3; i++) {
    std::cin >> x[i];
  }
  std::sort(x, x + 3);
  int M = x[0];

  for (int i = 0; i < M; i++) {
    d[i] = LLONG_MAX;
    // 本题的h达到了ll的上界，如果使用ll的话必需把初值置为LLONG_MAX
  }
  d[0] = 0;

  upd(x[1], M);
  memset(vis, 0, sizeof(vis));
  upd(x[2], M);

  ll H = h - 1;
  ans = 0;
  for (int i = 0; i < M; i++) {
    if (d[i] <= H && d[i] != LLONG_MAX) {
      ans += (H - d[i]) / M + 1;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
