#include "rbtree.hpp"
// --8<-- [start:main]
#include <iostream>
#include <numeric>
#include <vector>

template <bool P6136>  // == false: P3369, == true: P6136
struct IO_luogu_P3369_P6136 {
  int last_ans = 0;
  std::size_t n, m;
  std::vector<int> a;
  std::vector<int> ans_list;

  void init() {
    std::cin >> n;
    if (!P6136) {
      m = n;
      return;
    }
    std::cin >> m;
    a.resize(n);
    for (auto &i : a) std::cin >> i;
  }

  int opt() {
    int x;
    std::cin >> x;
    return x;
  }

  int x() {
    int x;
    std::cin >> x;
    return P6136 ? x ^ last_ans : x;
  }

  void print(int ans) { ans_list.push_back(last_ans = ans); }

  void print_total_ans() {
    if (P6136)
      std::cout << std::accumulate(ans_list.begin(), ans_list.end(), 0,
                                   std::bit_xor<int>{})
                << '\n';
    else
      for (auto &&i : ans_list) std::cout << i << '\n';
  }
};

// 把这里的模板参数改为 false 即为「Luogu P3369【模板】普通平衡树」的代码
IO_luogu_P3369_P6136<true> io;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  io.init();
  std::size_t n = io.n, m = io.m;
  rb_tree<std::pair<int, int>> bt;
  int cnt = 0;
  for (auto i : io.a) bt.insert(std::make_pair(i, cnt++));
  for (int i = 0, opt, x; (std::size_t)i < m; ++i) {
    opt = io.opt(), x = io.x();
    switch (opt) {
      case 1:
        bt.insert({x, cnt++});
        break;
      case 2:
        bt.erase(bt.lower_bound({x, 0}));
        break;
      case 3:
        io.print((int)bt.order_of_key({x, 0}) + 1);
        break;
      case 4:
        io.print(bt.find_by_order((uint32_t)x - 1)->data.first);
        break;
      case 6:
        io.print(bt.upper_bound({x, n + m})->data.first);
        break;
      case 5:
        auto it = bt.lower_bound({x, 0});
        io.print((it ? bt.prev(it) : bt.rightmost(bt.root))->data.first);
        break;
    }
  }
  io.print_total_ans();
  return 0;
}

// --8<-- [end:main]