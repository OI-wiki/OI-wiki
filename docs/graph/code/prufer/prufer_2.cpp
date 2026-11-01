// Sample provenance: https://www.luogu.com.cn/problem/P6086; additional
// two-vertex boundary cases.
#include <cassert>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

// --8<-- [start:core]
// 从原文摘的代码，同样以 0 为起点
vector<vector<int>> adj;
vector<int> parent;

void dfs(int v) {
  for (int u : adj[v]) {
    if (u != parent[v]) parent[u] = v, dfs(u);
  }
}

vector<int> pruefer_code() {
  int n = adj.size();
  parent.resize(n), parent[n - 1] = -1;
  dfs(n - 1);

  int ptr = -1;
  vector<int> degree(n);
  for (int i = 0; i < n; i++) {
    degree[i] = adj[i].size();
    if (degree[i] == 1 && ptr == -1) ptr = i;
  }

  vector<int> code(n - 2);
  int leaf = ptr;
  for (int i = 0; i < n - 2; i++) {
    int next = parent[leaf];
    code[i] = next;
    if (--degree[next] == 1 && next < ptr) {
      leaf = next;
    } else {
      ptr++;
      while (degree[ptr] != 1) ptr++;
      leaf = ptr;
    }
  }
  return code;
}

// --8<-- [end:core]
// 原文摘代码
vector<pair<int, int>> pruefer_decode(vector<int> const& code) {
  int n = code.size() + 2;
  vector<int> degree(n, 1);
  for (int i : code) degree[i]++;

  int ptr = 0;
  while (degree[ptr] != 1) ptr++;
  int leaf = ptr;

  vector<pair<int, int>> edges;
  for (int v : code) {
    edges.emplace_back(leaf, v);
    if (--degree[v] == 1 && v < ptr) {
      leaf = v;
    } else {
      ptr++;
      while (degree[ptr] != 1) ptr++;
      leaf = ptr;
    }
  }
  edges.emplace_back(leaf, n - 1);
  return edges;
}

// P6086 uses vertices 1..n and parents rooted at n; algorithms below use
// 0..n-1.
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, mode;
  cin >> n >> mode;
  long long answer = 0;
  if (mode == 1) {
    adj.resize(n);
    for (int u = 0; u < n - 1; ++u) {
      int v;
      cin >> v;
      --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    vector<int> code = pruefer_code();
    for (int i = 0; i < n - 2; ++i) answer ^= (i + 1LL) * (code[i] + 1);
  } else {
    vector<int> code(n - 2);
    for (int& v : code) {
      cin >> v;
      --v;
    }
    auto edges = pruefer_decode(code);
    vector<vector<int>> tree(n);
    for (auto edge : edges) {
      tree[edge.first].push_back(edge.second);
      tree[edge.second].push_back(edge.first);
    }
    vector<int> parents(n, -1), pending{n - 1};
    while (!pending.empty()) {
      int u = pending.back();
      pending.pop_back();
      for (int v : tree[u])
        if (v != parents[u]) {
          parents[v] = u;
          pending.push_back(v);
        }
    }
    for (int u = 0; u < n - 1; ++u) answer ^= (u + 1LL) * (parents[u] + 1);
  }
  cout << answer << '\n';
}
