// Sample provenance: https://www.luogu.com.cn/problem/P6086; additional
// two-vertex boundary cases.
#include <cassert>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

// 代码摘自原文，结点是从 0 标号的
vector<vector<int>> adj;

vector<int> pruefer_code() {
  int n = adj.size();
  set<int> leafs;
  vector<int> degree(n);
  vector<bool> killed(n);
  for (int i = 0; i < n; i++) {
    degree[i] = adj[i].size();
    if (degree[i] == 1) leafs.insert(i);
  }

  vector<int> code(n - 2);
  for (int i = 0; i < n - 2; i++) {
    int leaf = *leafs.begin();
    leafs.erase(leafs.begin());
    killed[leaf] = true;
    int v = -1;
    for (int u : adj[leaf])
      if (!killed[u]) v = u;
    assert(v >= 0);
    code[i] = v;
    if (--degree[v] == 1) leafs.insert(v);
  }
  return code;
}

// --8<-- [start:core]
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

// --8<-- [end:core]

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
