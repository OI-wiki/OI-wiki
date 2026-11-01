#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

constexpr int N = 100005;
int n;

// --8<-- [start:core]
// 这份代码默认节点编号从 1 开始，即 i ∈ [1,n]，使用vector存图
int d1[N], d2[N], up[N], x, y, mini = 1e9;  // d1,d2对应上文中的len1,len2

struct node {
  int to, val;  // to为边指向的节点，val为边权
};

vector<node> nbr[N];

void dfsd(int cur, int fa) {  // 求取len1和len2
  for (node nxtn : nbr[cur]) {
    int nxt = nxtn.to, w = nxtn.val;  // nxt为这条边通向的节点，val为边权
    if (nxt == fa) {
      continue;
    }
    dfsd(nxt, cur);
    if (d1[nxt] + w > d1[cur]) {  // 可以更新最长链
      d2[cur] = d1[cur];
      d1[cur] = d1[nxt] + w;
    } else if (d1[nxt] + w > d2[cur]) {  // 不能更新最长链，但可更新次长链
      d2[cur] = d1[nxt] + w;
    }
  }
}

void dfsu(int cur, int fa) {
  for (node nxtn : nbr[cur]) {
    int nxt = nxtn.to, w = nxtn.val;
    if (nxt == fa) {
      continue;
    }
    up[nxt] = up[cur] + w;
    if (d1[nxt] + w != d1[cur]) {  // 如果自己子树里的最长链不在nxt子树里
      up[nxt] = max(up[nxt], d1[cur] + w);
    } else {  // 自己子树里的最长链在nxt子树里，只能使用次长链
      up[nxt] = max(up[nxt], d2[cur] + w);
    }
    dfsu(nxt, cur);
  }
}

void GetTreeCenter() {  // 统计树的中心，记为x和y（若存在）
  dfsd(1, 0);
  dfsu(1, 0);
  for (int i = 1; i <= n; i++) {
    if (max(d1[i], up[i]) < mini) {  // 找到了当前max(len1[x],up[x])最小点
      mini = max(d1[i], up[i]);
      x = i;
      y = 0;
    } else if (max(d1[i], up[i]) == mini) {  // 另一个中心
      y = i;
    }
  }
}

// --8<-- [end:core]

int main() {
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    nbr[u].push_back(node{v, w});
    nbr[v].push_back(node{u, w});
  }
  GetTreeCenter();
  cout << x;
  if (y) cout << ' ' << y;
  cout << '\n';
}
