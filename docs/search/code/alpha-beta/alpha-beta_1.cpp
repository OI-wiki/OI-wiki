#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using std::max;
using std::min;
std::vector<int> son_num, val;
std::vector<std::vector<int>> son;

// --8<-- [start:core]
int alpha_beta(int u, int alph, int beta, bool is_max) {
  if (!son_num[u]) return val[u];
  if (is_max) {
    for (int i = 0; i < son_num[u]; ++i) {
      int d = son[u][i];
      alph = max(alph, alpha_beta(d, alph, beta, !is_max));
      if (alph >= beta) break;
    }
    return alph;
  } else {
    for (int i = 0; i < son_num[u]; ++i) {
      int d = son[u][i];
      beta = min(beta, alpha_beta(d, alph, beta, !is_max));
      if (alph >= beta) break;
    }
    return beta;
  }
}

// --8<-- [end:core]

// Input: node count, then for each node its child count and child indices.
// A leaf instead gives a zero child count followed by its score. Root is
// node 1.
int main() {
  int n;
  if (!(std::cin >> n)) return 0;
  son_num.resize(n + 1);
  val.resize(n + 1);
  son.resize(n + 1);
  for (int u = 1; u <= n; ++u) {
    std::cin >> son_num[u];
    son[u].resize(son_num[u]);
    for (int &v : son[u]) std::cin >> v;
    if (!son_num[u]) std::cin >> val[u];
  }
  std::cout << alpha_beta(1, std::numeric_limits<int>::lowest(),
                          std::numeric_limits<int>::max(), true)
            << '\n';
}
