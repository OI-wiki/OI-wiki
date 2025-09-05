// Submission: https://judge.yosupo.jp/submission/311622
#include <iostream>
#include <queue>
#include <vector>

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

struct Edge {
  int u, v, c;

  Edge(int u, int v, int c) : u(u), v(v), c(c) {}
};

int n, m, s, t, k;
std::vector<std::vector<int>> gr, ig;  // Graph and inverse graph.
std::vector<Edge> edges;               // Edges.
std::priority_queue<std::pair<long long, int>,
                    std::vector<std::pair<long long, int>>, std::greater<>>
    pq;

std::vector<long long> dist_t;

// Calculate distances to the destination node t. (Dijkstra)
void calc_distances_to_t() {
  dist_t.assign(n, inf);
  dist_t[t] = 0;
  pq.emplace(dist_t[t], t);
  while (!pq.empty()) {
    long long di = pq.top().first;
    int cur = pq.top().second;
    pq.pop();
    if (di > dist_t[cur]) continue;
    for (auto e : ig[cur]) {
      int nxt = edges[e].u;
      auto di_nxt = di + edges[e].c;
      if (di_nxt < dist_t[nxt]) {
        dist_t[nxt] = di_nxt;
        pq.emplace(di_nxt, nxt);
      }
    }
  }
}

std::vector<long long> ans;

// Find the k shortest walk. (A* search)
// Complexity: O(k * n * log(k * n)).
void find_k_shortest_walks() {
  ans.assign(k, -1);
  std::vector<int> cnt(n);
  pq.emplace(dist_t[s], s);
  while (!pq.empty()) {
    long long cost = pq.top().first;
    int cur = pq.top().second;
    pq.pop();
    // Skip unreachable nodes.
    if (cost >= inf) continue;
    if (cur == t) ans[cnt[t]] = cost;
    ++cnt[cur];
    // Terminate when the destination has been visited k times.
    if (cnt[t] >= k) break;
    // Expand the same node at most k times.
    if (cnt[cur] > k) continue;
    for (auto e : gr[cur]) {
      int nxt = edges[e].v;
      auto cost_nxt = cost - dist_t[cur] + edges[e].c + dist_t[nxt];
      pq.emplace(cost_nxt, nxt);
    }
  }
}

int main() {
  // Input.
  std::cin >> n >> m >> s >> t >> k;
  gr.resize(n);
  ig.resize(n);
  edges.reserve(m);
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    std::cin >> u >> v >> c;
    edges.emplace_back(u, v, c);
    gr[u].push_back(i);
    ig[v].push_back(i);
  }
  // Calculate.
  calc_distances_to_t();
  find_k_shortest_walks();
  // Output.
  for (auto x : ans) std::cout << x << '\n';
  return 0;
}
