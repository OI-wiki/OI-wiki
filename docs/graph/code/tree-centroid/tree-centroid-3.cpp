#include <iostream>
#include <vector>
using namespace std;

constexpr int N = 3e5 + 5;

int n, q;  // 点数，询问数
int fa[N];
vector<int> son[N];
int siz[N],     // 子树大小
    ans[N],     // 以结点 u 为根的子树重心是 ans[u]
    weight[N];  // 结点重量（不包括向上的子树）

void dfs(int u) {
  siz[u] = 1, ans[u] = u;
  int hson = 0;  // 重子结点
  for (int v : son[u]) {
    dfs(v);
    siz[u] += siz[v];
    if (siz[v] > weight[u]) weight[u] = siz[v], hson = v;
  }
  if (hson) {
    int p = ans[hson];
    while (p != u) {
      if (max(weight[p], siz[u] - siz[p]) <= siz[u] / 2) {
        ans[u] = p;
        break;
      } else
        p = fa[p];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> q;
  for (int v = 2; v <= n; v++) cin >> fa[v], son[fa[v]].push_back(v);
  dfs(1);
  while (q--) {
    int u;
    cin >> u;
    cout << ans[u] << '\n';
  }
  return 0;
}
