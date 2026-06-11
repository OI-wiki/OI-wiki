#include <iostream>
#include <vector>
using namespace std;

int n, m, k, a, b, w, arr[1000010], dfn[4000040], low[4000040], dcnt,
    bel[4000040], scnt;
vector<int> to[4000040], stk;

// 真节点占据 1~n，假节点占据 (n+1)~2n，前缀节点占据 (2n+1)~3n，后缀节点占据
// (3n+1)~4n
int T(int x) { return (x - 1) % n + 1; }

int F(int x) { return T(x) + n; }

int P(int x) { return T(x) + 2 * n; }

int S(int x) { return T(x) + 3 * n; }

int N(int x) { return x <= n ? F(x) : T(x); }

void DFS(int x) {
  dfn[x] = low[x] = ++dcnt, stk.push_back(x);
  for (auto i : to[x]) {
    if (!dfn[i]) {
      DFS(i);
      low[x] = min(low[x], low[i]);
    } else if (!bel[i])
      low[x] = min(low[x], dfn[i]);
  }
  if (dfn[x] == low[x]) {
    scnt++;
    for (; stk.size() && dfn[stk.back()] >= dfn[x]; stk.pop_back())
      bel[stk.back()] = scnt;
  }
}

signed main() {
  cin >> n >> m >> k;
  for (; m--;) {
    cin >> a >> b;
    to[N(a)].push_back(b);
    to[N(b)].push_back(a);
  }
  for (; k--;) {
    cin >> w;
    for (int i = 1; i <= w; i++) cin >> arr[i];
    for (int i = 1; i <= w; i++) {  // 建前缀点
      if (i > 1) to[P(arr[i])].push_back(P(arr[i - 1]));
      to[P(arr[i])].push_back(N(arr[i]));
    }
    for (int i = w; i >= 1; i--) {  // 建后缀点
      if (i < w) to[S(arr[i])].push_back(S(arr[i + 1]));
      to[S(arr[i])].push_back(N(arr[i]));
    }
    for (int i = 1; i <= w; i++) {  // 连接上面的点和前后缀点
      if (i > 1) to[arr[i]].push_back(P(arr[i - 1]));
      if (i < w) to[arr[i]].push_back(S(arr[i + 1]));
    }
  }
  for (int i = 1; i <= 4 * n; i++) {
    if (!dfn[i]) DFS(i);
  }
  for (int i = 1; i <= n; i++) {
    if (bel[i] == bel[N(i)]) {
      cout << "NIE" << '\n';
      return 0;
    }
  }
  cout << "TAK" << '\n';
  return 0;
}