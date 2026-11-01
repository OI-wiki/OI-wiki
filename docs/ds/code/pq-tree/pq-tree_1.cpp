#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

template <class T>
void checkmin(T &x, const T &y) {
  x = std::min(x, y);
}

template <class T>
void checkmax(T &x, const T &y) {
  x = std::max(x, y);
}

// --8<-- [start:example133]
class PQTree {
 public:
  PQTree() {}

  void Init(int n) {
    n_ = n, rt_ = tot_ = n + 1;
    for (int i = 1; i <= n; i++) g_[rt_].emplace_back(i);
  }

  void Insert(const std::string &s) {
    s_ = s;
    Dfs0(rt_);
    Work(rt_);
    while (g_[rt_].size() == 1) rt_ = g_[rt_][0];
    Remove(rt_);
  }

  std::vector<int> ans() {
    DfsAns(rt_);
    return ans_;
  }

  ~PQTree() {}

 private:
  int n_, rt_, tot_, pool_[100001], top_, typ_[100001] /* 0-P 1-Q */,
      col_[100001] /* 0-black 1-white 2-grey */;
  std::vector<int> g_[100001], ans_;
  std::string s_;

  void Fail() {
    std::cout << "NO\n";
    std::exit(0);
  }

  int NewNode(int ty) {
    int x = top_ ? pool_[top_--] : ++tot_;
    typ_[x] = ty;
    return x;
  }

  void Delete(int u) { g_[u].clear(), pool_[++top_] = u; }

  void Dfs0(int u) {  // get color of each node
    if (u >= 1 && u <= n_) {
      col_[u] = s_[u] == '1';
      return;
    }
    bool c0 = false, c1 = false;
    for (auto &&v : g_[u]) {
      Dfs0(v);
      if (col_[v]) c1 = true;
      if (col_[v] != 1) c0 = true;
    }
    if (c0 && !c1)
      col_[u] = 0;
    else if (!c0 && c1)
      col_[u] = 1;
    else
      col_[u] = 2;
  }

  bool Check(const std::vector<int> &v) {
    int p2 = -1;
    for (int i = 0; i < static_cast<int>(v.size()); i++)
      if (col_[v[i]] == 2) {
        if (p2 != -1) return false;
        p2 = i;
      }
    if (p2 == -1)
      for (int i = 0; i < static_cast<int>(v.size()); i++)
        if (col_[v[i]]) {
          p2 = i;
          break;
        }
    for (int i = 0; i < p2; i++)
      if (col_[v[i]]) return false;
    for (int i = p2 + 1; i < static_cast<int>(v.size()); i++)
      if (col_[v[i]] != 1) return false;
    return true;
  }

  std::vector<int> Split(int u) {
    if (col_[u] != 2) return {u};
    std::vector<int> ng;
    if (typ_[u]) {  // Q
      if (!Check(g_[u])) {
        std::reverse(g_[u].begin(), g_[u].end());
        if (!Check(g_[u])) Fail();
      }
      for (auto &&v : g_[u])
        if (col_[v] != 2) {
          ng.emplace_back(v);
        } else {
          auto s = Split(v);
          ng.insert(ng.end(), s.begin(), s.end());
        }
    } else {  // P
      std::vector<int> son[3];
      for (auto &&x : g_[u]) son[col_[x]].emplace_back(x);
      if (son[2].size() > 1) Fail();
      if (!son[0].empty()) {
        int n0 = NewNode(0);
        g_[n0] = son[0];
        ng.emplace_back(n0);
      }
      if (!son[2].empty()) {
        auto s = Split(son[2][0]);
        ng.insert(ng.end(), s.begin(), s.end());
      }
      if (!son[1].empty()) {
        int n1 = NewNode(0);
        g_[n1] = son[1];
        ng.emplace_back(n1);
      }
    }
    Delete(u);
    return ng;
  }

  void Work(int u) {
    if (col_[u] != 2) return;
    if (typ_[u]) {  // Q
      int l = 1e9, r = -1e9;
      for (int i = 0; i < static_cast<int>(g_[u].size()); i++)
        if (col_[g_[u][i]]) checkmin(l, i), checkmax(r, i);
      for (int i = l + 1; i < r; i++)
        if (col_[g_[u][i]] != 1) Fail();
      if (l == r && col_[g_[u][l]] == 2) {
        Work(g_[u][l]);
        return;
      }
      std::vector<int> ng;
      for (int i = 0; i < l; i++) ng.emplace_back(g_[u][i]);
      auto s = Split(g_[u][l]);
      ng.insert(ng.end(), s.begin(), s.end());
      for (int i = l + 1; i < r; i++) ng.emplace_back(g_[u][i]);
      if (l != r) {
        s = Split(g_[u][r]);
        std::reverse(s.begin(), s.end());
        ng.insert(ng.end(), s.begin(), s.end());
      }
      for (int i = r + 1; i < static_cast<int>(g_[u].size()); i++)
        ng.emplace_back(g_[u][i]);
      g_[u] = ng;
    } else {  // P
      std::vector<int> son[3];
      for (auto &&x : g_[u]) son[col_[x]].emplace_back(x);
      if (son[1].empty() && son[2].size() == 1) {
        Work(son[2][0]);
        return;
      }
      g_[u].clear();
      if (son[2].size() > 2) Fail();
      g_[u] = son[0];
      int n1 = NewNode(1);
      g_[u].emplace_back(n1);
      if (son[2].size() >= 1) {
        auto s = Split(son[2][0]);
        g_[n1].insert(g_[n1].end(), s.begin(), s.end());
      }
      if (son[1].size()) {
        int n2 = NewNode(0);
        g_[n1].emplace_back(n2);
        g_[n2] = son[1];
      }
      if (son[2].size() >= 2) {
        auto s = Split(son[2][1]);
        std::reverse(s.begin(), s.end());
        g_[n1].insert(g_[n1].end(), s.begin(), s.end());
      }
    }
  }

  void Remove(int u) {  // remove the nodes with only one child
    for (auto &&v : g_[u]) {
      int tv = v;
      while (g_[tv].size() == 1) {
        int t = tv;
        tv = g_[tv][0];
        Delete(t);
      }
      v = tv, Remove(v);
    }
  }

  void DfsAns(int u) {
    if (u >= 1 && u <= n_) {
      ans_.emplace_back(u);
      return;
    }
    for (auto &&v : g_[u]) DfsAns(v);
  }
} T;

// --8<-- [end:example133]

int main() {
  int n;
  std::cin >> n;
  T.Init(n);
  std::vector<std::string> a(n);
  for (auto &row : a) {
    std::cin >> row;
    T.Insert(" " + row);
  }
  auto order = T.ans();
  std::cout << "YES\n";
  for (const auto &row : a) {
    for (int column : order) std::cout << row[column - 1];
    std::cout << '\n';
  }
}
