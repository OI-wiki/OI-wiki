#include <iostream>
#include <queue>
#include <vector>

// Solver for stable marriage problems.
// Assume strict preferences with incomplete lists.
struct StableMatching {
  int nx, ny;
  std::vector<std::vector<int>> pref_x,
      pref_y;  // Preferences: preferred first, only acceptable.
  std::vector<int> match_x, match_y;  // Matching: -1 means unmatched.

  StableMatching(int nx, int ny)
      : nx(nx),
        ny(ny),
        pref_x(nx),
        pref_y(ny),
        match_x(nx, -1),
        match_y(ny, -1) {}

  // Gale-Shapley algorithm.
  // Complexity: O(nx * ny).
  void solve() {
    // Compute Y's ranks over X.
    std::vector<std::vector<int>> ranks(ny, std::vector<int>(nx));
    for (int j = 0; j != ny; ++j) {
      for (int i = 0; i != pref_y[j].size(); ++i) {
        ranks[j][pref_y[j][i]] = nx - i;
      }
    }
    // Initialize.
    std::vector<int> waitlist(ny);  // Best proposal rank for j in Y.
    std::vector<int> ids(nx);       // Next j in Y for i in X to propose to.
    std::queue<int> q;              // Currently active i's in X.
    for (int i = 0; i != nx; ++i) q.push(i);
    // Loop.
    while (!q.empty()) {
      auto i = q.front();
      q.pop();
      auto j = pref_x[i][ids[i]++];
      if (ranks[j][i] > waitlist[j]) {
        if (waitlist[j]) q.push(pref_y[j][nx - waitlist[j]]);
        waitlist[j] = ranks[j][i];
      } else {
        q.push(i);
      }
    }
    // Output.
    for (int j = 0; j != ny; ++j) {
      if (waitlist[j]) {
        int i = pref_y[j][nx - waitlist[j]];
        match_x[i] = j;
        match_y[j] = i;
      }
    }
  }
};

void solve() {
  // Input.
  int n;
  std::cin >> n;
  StableMatching solver(n, n);
  for (int j = 0, x; j < n; ++j) {
    auto& cur = solver.pref_y[j];
    std::cin >> x;
    for (int i = 0; i < n; ++i) {
      std::cin >> x;
      cur.push_back(x - 1);
    }
  }
  for (int i = 0, y; i < n; ++i) {
    auto& cur = solver.pref_x[i];
    std::cin >> y;
    for (int j = 0; j < n; ++j) {
      std::cin >> y;
      cur.push_back(y - 1);
    }
  }
  // Solve the problem.
  solver.solve();
  // Output.
  for (int i = 0; i < n; ++i) {
    std::cout << (i + 1) << ' ' << (solver.match_x[i] + 1) << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  for (; t; --t) {
    solve();
  }
  return 0;
}
