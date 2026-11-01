// Sample source: https://www.luogu.com.cn/problem/P4568
#include <algorithm>
#include <cstring>
#include <iostream>
#include <limits>
#include <queue>

// --8<-- [start:state]
struct State {    // 优先队列的结点结构体
  int v, w, cnt;  // cnt 表示已经使用多少次免费通行权限

  State() {}

  State(int v, int w, int cnt) : v(v), w(w), cnt(cnt) {}

  bool operator<(const State &rhs) const { return w > rhs.w; }
};

// --8<-- [end:state]

constexpr int N = 10005, M = 100005, K = 11;
int n, m, k, s, t;
int dis[N][K], head[N], edges;
bool done[N][K];

struct Edge {
  int v, w, next;
} edge[M];

std::priority_queue<State> pq;

void add(int u, int v, int w) {
  edge[++edges] = Edge{v, w, head[u]};
  head[u] = edges;
}

int read() {
  int value;
  std::cin >> value;
  return value;
}

void println(int value) { std::cout << value << '\n'; }

// --8<-- [start:algorithm]

void dijkstra() {
  memset(dis, 0x3f, sizeof dis);
  dis[s][0] = 0;
  pq.push(State(s, 0, 0));  // 到起点不需要使用免费通行权，距离为零
  while (!pq.empty()) {
    const State top = pq.top();
    pq.pop();
    int u = top.v, nowCnt = top.cnt;
    if (done[u][nowCnt]) continue;
    done[u][nowCnt] = true;
    for (int i = head[u]; i; i = edge[i].next) {
      int v = edge[i].v, w = edge[i].w;
      if (nowCnt < k && dis[v][nowCnt + 1] > dis[u][nowCnt]) {  // 可以免费通行
        dis[v][nowCnt + 1] = dis[u][nowCnt];
        pq.push(State(v, dis[v][nowCnt + 1], nowCnt + 1));
      }
      if (dis[v][nowCnt] > dis[u][nowCnt] + w) {  // 不可以免费通行
        dis[v][nowCnt] = dis[u][nowCnt] + w;
        pq.push(State(v, dis[v][nowCnt], nowCnt));
      }
    }
  }
}

int main() {
  n = read(), m = read(), k = read();
  // 笔者习惯从 1 到 n 编号，而这道题是从 0 到 n - 1，所以要处理一下
  s = read() + 1, t = read() + 1;
  while (m--) {
    int u = read() + 1, v = read() + 1, w = read();
    add(u, v, w), add(v, u, w);  // 这道题是双向边
  }
  dijkstra();
  int ans = std::numeric_limits<int>::max();  // ans 取 int 最大值为初值
  for (int i = 0; i <= k; ++i)
    ans = std::min(ans, dis[t][i]);  // 对到达终点的所有情况取最优值
  println(ans);
}

// --8<-- [end:algorithm]
