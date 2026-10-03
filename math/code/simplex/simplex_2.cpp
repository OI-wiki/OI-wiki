// Verified by https://uoj.ac/submission/779760
// --8<-- [start:full-text]
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

// --8<-- [start:core]
int m, n;  // Number of constraints and variables.
std::vector<std::vector<long double>>
    tab;                             // Compressed tableau (transposed) with
                                     // first-phase objective attached.
std::vector<int> B, N;               // Basic and nonbasic variables.
constexpr long double eps = 1e-12l;  // Precision.

// --8<-- [start:pivot]
// Pivot on (N[x], B[y]).
void pivot(int x, int y) {
  std::swap(N[x], B[y]);
  long double v = -1 / tab[x][y];
  for (int j = 0; j <= m; ++j) {
    tab[x][j] = j == y ? -v : v * tab[x][j];
  }
  for (int i = 0; i <= n; ++i) {
    if (i == x) continue;
    v = tab[i][y];
    tab[i][y] = 0;
    for (int j = 0; j <= m; ++j) {
      tab[i][j] += v * tab[x][j];
    }
  }
}

// --8<-- [end:pivot]
// --8<-- [start:initialize]
// First phase: find an initial BFS.
// Return false if no feasible solution.
bool initialize() {
  while (true) {
    int y = -1;
    long double mi = -eps;
    for (int j = 0; j < m; ++j) {
      if (tab[n][j] <= mi) {
        y = j;
        mi = tab[n][j];
      }
    }
    // No row with a negative basic variable => Feasible.
    if (y == -1) break;
    int x = -1;
    for (int i = 0; i < n; ++i) {
      if (tab[i][y] < -eps && (x == -1 || N[i] > N[x])) {
        x = i;
      }
    }
    // No column with a negative entry => Infeasible.
    if (x == -1) return false;
    pivot(x, y);
  }
  return true;
}

// --8<-- [end:initialize]
// --8<-- [start:simplex]
// Second phase: find an optimal BFS.
// Return false if the problem is unbounded.
bool simplex() {
  while (true) {
    int x = -1;
    long double mi = -eps;
    for (int i = 0; i < n; ++i) {
      if (tab[i][m] < mi) {
        x = i;
        mi = tab[i][m];
      }
    }
    // No column with a negative reduced cost => Optimal.
    if (x == -1) break;
    int y = -1;
    mi = INFINITY;
    for (int j = 0; j < m; ++j) {
      if (tab[x][j] <= eps) continue;
      if (tab[n][j] / tab[x][j] < mi) {
        y = j;
        mi = tab[n][j] / tab[x][j];
      }
    }
    // No row with a positive ratio => Unbounded.
    if (y == -1) return false;
    pivot(x, y);
  }
  return true;
}

// --8<-- [end:simplex]
int solve() {
  B.resize(m);
  N.resize(n);
  std::iota(B.begin(), B.end(), n);
  std::iota(N.begin(), N.end(), 0);
  return initialize() ? (simplex() ? 0 : 1) : -1;
}

// --8<-- [end:core]
int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(8);
  int t;
  std::cin >> n >> m >> t;
  tab.assign(n + 1, std::vector<long double>(m + 1));
  for (int i = 0; i < n; ++i) {
    std::cin >> tab[i][m];
    tab[i][m] = -tab[i][m];
  }
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i <= n; ++i) {
      std::cin >> tab[i][j];
    }
  }
  switch (solve()) {
    case -1:
      std::cout << "Infeasible" << std::endl;
      break;
    case 1:
      std::cout << "Unbounded" << std::endl;
      break;
    case 0: {
      std::cout << tab[n][m] << std::endl;
      if (t) {
        std::vector<long double> x(n);
        for (int j = 0; j < m; ++j) {
          if (B[j] < n) x[B[j]] = tab[n][j];
        }
        for (int i = 0; i < n; ++i) {
          std::cout << x[i] << ' ';
        }
      }
    }
  }
  return 0;
}

// --8<-- [end:full-text]
