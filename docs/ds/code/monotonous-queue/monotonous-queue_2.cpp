#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
typedef long long ll;
int mxq[N], mnq[N];
int D, ans, n, hx, rx, hn, rn;
struct la {
  int x, y;
  bool operator<(const la &y) const { return x < y.x; }
} a[N];
int main() {
  scanf("%d%d", &n, &D);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i].x, &a[i].y);
  }
  sort(a + 1, a + n + 1);
  hx = hn = 1;
  ans = 2e9;
  int L = 1;
  for (int i = 1; i <= n; ++i) {
    while (hx <= rx && a[mxq[rx]].y < a[i].y) rx--;
    mxq[++rx] = i;
    while (hn <= rn && a[mnq[rn]].y > a[i].y) rn--;
    mnq[++rn] = i;
    while (L <= i && a[mxq[hx]].y - a[mnq[hn]].y >= D) {
      ans = min(ans, a[i].x - a[L].x);
      L++;
      while (hx <= rx && mxq[hx] < L) hx++;
      while (hn <= rn && mnq[hn] < L) hn++;
    }
  }
  if (ans < 2e9)
    printf("%d\n", ans);
  else
    puts("-1");
  return 0;
}