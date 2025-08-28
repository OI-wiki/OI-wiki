#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

std::mt19937_64 rng(static_cast<std::mt19937_64::result_type>(time(nullptr)));

constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

struct PersistentRandomizedHeap {
  static constexpr int N = 1e7;
  int id;
  std::vector<int> rt, lc, rc, to;
  std::vector<long long> va;

  int new_node(long long cost, int _to) {
    ++id;
    va[id] = cost;
    to[id] = _to;
    return id;
  }

  int copy_node(int x) {
    ++id;
    lc[id] = lc[x];
    rc[id] = rc[x];
    va[id] = va[x];
    to[id] = to[x];
    return id;
  }

  PersistentRandomizedHeap() : id(0), rt(N), lc(N), rc(N), to(N), va(N) {}

  int meld(int x, int y, std::mt19937_64::result_type rand) {
    if (!x || !y) return x | y;
    if (va[x] > va[y]) std::swap(x, y);
    x = copy_node(x);
    if (rand & 1) std::swap(lc[x], rc[x]);
    rc[x] = meld(rc[x], y, rand >> 1);
    return x;
  }

  void insert(int i, long long cost, int _to) {
    rt[i] = meld(rt[i], new_node(cost, _to), rng());
  }

  void merge(int i, int j) { rt[i] = meld(rt[i], rt[j], rng()); }

} heaps;

struct Edge {
  int u, v, c;
};

int n, m, s, t, k;
std::vector<std::vector<int>> gr, ig;
std::vector<Edge> edges;
std::priority_queue<std::pair<long long, int>,
                    std::vector<std::pair<long long, int>>, std::greater<>>
    pq;

std::vector<long long> dist_t;
std::vector<int> out;

void calc_distances_to_t() {
  dist_t.assign(n, inf);
  dist_t[t] = 0;
  out.assign(n, -1);
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
        out[nxt] = e;
        pq.emplace(di_nxt, nxt);
      }
    }
  }
}

void build_sidetracks() {
  for (int i = 0; i < m; ++i) {
    auto edge = edges[i];
    if (out[edge.u] != i && dist_t[edge.u] < inf && dist_t[edge.v] < inf) {
      heaps.insert(edge.u, edge.c + dist_t[edge.v] - dist_t[edge.u], edge.v);
    }
  }
  std::queue<int> q;
  q.push(t);
  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    for (auto e : ig[cur]) {
      auto nxt = edges[e].u;
      if (out[nxt] == e) {
        heaps.merge(nxt, cur);
        q.push(nxt);
      }
    }
  }
}

std::vector<long long> ans;

void find_k_shortest_walks() {
  int cnt = 0;
  ans.assign(k, -1);
  if (dist_t[s] >= inf) return;
  ans[cnt++] = dist_t[s];
  if (heaps.rt[s]) pq.emplace(dist_t[s] + heaps.va[heaps.rt[s]], heaps.rt[s]);
  while (!pq.empty() && cnt < k) {
    auto cost = pq.top().first;
    int cur = pq.top().second;
    pq.pop();
    ans[cnt++] = cost;
    if (heaps.lc[cur])
      pq.emplace(cost - heaps.va[cur] + heaps.va[heaps.lc[cur]], heaps.lc[cur]);
    if (heaps.rc[cur])
      pq.emplace(cost - heaps.va[cur] + heaps.va[heaps.rc[cur]], heaps.rc[cur]);
    int nxt = heaps.rt[heaps.to[cur]];
    if (nxt) pq.emplace(cost + heaps.va[nxt], nxt);
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
  build_sidetracks();
  find_k_shortest_walks();
  // Output.
  for (auto x : ans) std::cout << x << '\n';
  return 0;
}
