#include <iostream>

constexpr int MAXN = 100;

int t;
int n;
char a[MAXN + 10][MAXN + 10];
int c[MAXN + 10][MAXN + 10];
int ans;

namespace graph {
struct Vertex {
  int head;
  int deg;
  int vis[MAXN + 10];
} vertex[2 * MAXN + 10], e;

struct Edge {
  int head;
  int next;
  int col;
} edge[2 * MAXN * MAXN + 10];

int ecnt;

void init() {
  for (int i = 0; i < MAXN + 10; i++) std::fill(c[i], c[i] + MAXN + 10, 0);
  for (int i = 1; i <= 2 * MAXN; i++) vertex[i] = e;
  for (int i = 0; i <= 2 * MAXN * MAXN; i++) edge[i].col = 0;
  ecnt = 1;
  ans = 0;
  return;
}

void addEdge(int tail, int head) {
  ecnt++;
  edge[ecnt].head = head;
  edge[ecnt].next = vertex[tail].head;
  vertex[tail].head = ecnt;
  vertex[tail].deg++;
  return;
}

int get(int u) {
  for (int i = 1; i <= n; i++)
    if (!vertex[u].vis[i]) return i;
  exit(1);
}

void DFS(int u, int ori, int upd) {
  if (vertex[u].vis[ori] == 0) {
    vertex[u].vis[upd] = 0;
    return;
  }
  int e = vertex[u].vis[ori];
  int v = edge[e].head;
  DFS(v, upd, ori);
  edge[e].col = upd;
  edge[e ^ 1].col = upd;
  vertex[u].vis[upd] = e;
  vertex[v].vis[upd] = e ^ 1;
  return;
}

void AddEdge(int u, int v) {
  addEdge(u, v);
  addEdge(v, u);
  return;
}

void solve() {
  for (int u = 1; u <= n; u++) {
    for (int e = vertex[u].head; e; e = edge[e].next) {
      int v = edge[e].head;
      if (edge[e].col) continue;
      int lu = get(u);
      int lv = get(v);
      if (lu < lv) DFS(v, lu, lv);
      if (lu > lv) DFS(u, lv, lu);
      int l = std::min(lu, lv);
      vertex[u].vis[l] = e;
      vertex[v].vis[l] = e ^ 1;
      edge[e].col = l;
      edge[e ^ 1].col = l;
    }
  }
}

void generate() {
  for (int u = 1; u <= n; u++) {
    for (int e = vertex[u].head; e; e = edge[e].next) {
      int v = edge[e].head;
      c[u][v - n] = edge[e].col;
    }
  }
  return;
}
}  // namespace graph

void mian() {
  graph::init();
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) std::cin >> a[i][j];
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (a[i][j] == '*') graph::AddEdge(i, j + n);
  for (int i = 1; i <= n * 2; i++) ans = std::max(ans, graph::vertex[i].deg);
  graph::solve();
  graph::generate();
  std::cout << ans << '\n';
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) std::cout << c[i][j] << ' ';
    std::cout << '\n';
  }
  return;
}

int main() {
  std::cin >> t;
  while (t--) mian();
  return 0;
}