#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;

ll fat[1005];  // 定义父亲
ll n, m, k, ecnt = 0;

struct Edge {  // 结构体存边
  ll u, v, w;
} edge[10005];

bool cmp(Edge a, Edge b) {  // sort排序结构体用
  return a.w < b.w;
}

void init(ll n) {  // 初始化并查集
  for (int i = 0; i < n; ++i) fat[i] = i;
}

ll find(int a) {  // 并查集查询
  if (fat[a] != a) fat[a] = find(fat[a]);
  return fat[a];
}

void merge(ll a, ll b) {  // 并查集合并
  fat[find(a)] = find(b);
}

ll kruskal() {            // kruskal最小生成树算法
  ll cost = 0, tcnt = n;  // tcnt存储当前有几棵树
  for (int i = 0; i < m; ++i) {
    if (find(edge[i].u) == find(edge[i].v)) continue;  // 查询是否在同一棵树上
    merge(edge[i].u, edge[i].v);                       // 合并两集合
    cost += edge[i].w;                                 // 合并的费用
    if (tcnt == k) return cost;                        // 有k棵树时返回
    tcnt--;  // 每合并一次树的数量减一
  }
  return -1;  // 无解
}

signed main() {
  cin >> n >> m >> k;
  init(n);  // 初始化
  for (int i = 0; i < m; ++i) {
    cin >> edge[ecnt].u >> edge[ecnt].v >> edge[ecnt].w;
    ecnt++;  // 添加边
  }
  sort(edge, edge + m, cmp);  // 先按边权排序
  ll ans = kruskal();
  if (ans == -1)
    cout << "No Answer\n";
  else
    cout << ans << "\n";
  return 0;
}
