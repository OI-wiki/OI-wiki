#include <algorithm>
#include <deque>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;

struct Node {
  int key = 0, leaf[2] = {0, 0}, size = 0;
  unsigned fix = 0;
  void _update();
};

deque<Node> _trp(1);
int _cnt;

int new_node() {
  _trp.emplace_back();
  return ++_cnt;
}

void Node::_update() { size = _trp[leaf[0]].size + _trp[leaf[1]].size + 1; }

// --8<-- [start:example129]
static std::pair<int, int> _split(int _x, int k) {
  if (_x == 0)
    return std::make_pair(0, 0);
  else {
    int _vs = new_node();  // 新建节点（可持久化的精髓）
    _trp[_vs] = _trp[_x];
    std::pair<int, int> _y;
    if (_trp[_vs].key <= k) {
      _y = _split(_trp[_vs].leaf[1], k);
      _trp[_vs].leaf[1] = _y.first;
      _y.first = _vs;
    } else {
      _y = _split(_trp[_vs].leaf[0], k);
      _trp[_vs].leaf[0] = _y.second;
      _y.second = _vs;
    }
    _trp[_vs]._update();
    return _y;
  }
}

// --8<-- [end:example129]
// --8<-- [start:example130]
static int _merge(int _x, int _y) {
  if (_x == 0 || _y == 0)
    return _x ^ _y;
  else {
    if (_trp[_x].fix < _trp[_y].fix) {
      int copy = new_node();
      _trp[copy] = _trp[_x];
      _x = copy;
      _trp[_x].leaf[1] = _merge(_trp[_x].leaf[1], _y);
      _trp[_x]._update();
      return _x;
    } else {
      int copy = new_node();
      _trp[copy] = _trp[_y];
      _y = copy;
      _trp[_y].leaf[0] = _merge(_x, _trp[_y].leaf[0]);
      _trp[_y]._update();
      return _y;
    }
  }
}

// --8<-- [end:example130]
int kth(int x, int k) {
  while (x) {
    int left = _trp[_trp[x].leaf[0]].size;
    if (k == left + 1) return _trp[x].key;
    if (k <= left)
      x = _trp[x].leaf[0];
    else
      k -= left + 1, x = _trp[x].leaf[1];
  }
  return 0;
}

int rank_of(int x, int key) {
  int ans = 1;
  while (x) {
    if (_trp[x].key < key)
      ans += _trp[_trp[x].leaf[0]].size + 1, x = _trp[x].leaf[1];
    else
      x = _trp[x].leaf[0];
  }
  return ans;
}

int main() {
  int n;
  cin >> n;
  vector<int> root(n + 1);
  mt19937 rng(0);
  for (int i = 1; i <= n; ++i) {
    int v, op, x;
    cin >> v >> op >> x;
    root[i] = root[v];
    if (op == 1) {
      auto p = _split(root[i], x);
      int node = new_node();
      _trp[node].key = x;
      _trp[node].fix = rng();
      _trp[node].size = 1;
      root[i] = _merge(_merge(p.first, node), p.second);
    } else if (op == 2) {
      auto p = _split(root[i], x - 1), q = _split(p.second, x);
      if (q.first)
        q.first = _merge(_trp[q.first].leaf[0], _trp[q.first].leaf[1]);
      root[i] = _merge(p.first, _merge(q.first, q.second));
    } else if (op == 3)
      cout << rank_of(root[i], x) << "\n";
    else if (op == 4)
      cout << kth(root[i], x) << "\n";
    else {
      int u = root[i], ans = op == 5 ? -2147483647 : 2147483647;
      while (u) {
        if (op == 5) {
          if (_trp[u].key < x)
            ans = _trp[u].key, u = _trp[u].leaf[1];
          else
            u = _trp[u].leaf[0];
        } else {
          if (_trp[u].key > x)
            ans = _trp[u].key, u = _trp[u].leaf[0];
          else
            u = _trp[u].leaf[1];
        }
      }
      cout << ans << "\n";
    }
  }
}
