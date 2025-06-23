// --8<-- [start:full-tex]
#include <algorithm>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

// --8<-- [start:core]
// A linear programming solver using simplex tableau.
// The problem is in the form as min_x c^Tx s.t. Ax <= b, x >= 0.
// A in R^{m x n}, b in R^m, c in R^n are all 0-indexed.
// Complexity: O(m * n * #pivots).
template <typename T>
class SimplexLPSolver {
 public:
  enum class Status { Infeasible = -1, Bounded = 0, Unbounded = 1 };

 private:
  int m, n;                         // Number of constraints and variables.
  std::vector<std::vector<T>> tab;  // Compressed tableau (transposed) with
                                    // first-phase objective attached.
  std::vector<int> B, N;            // Basic and nonbasic variables.
  T eps;                            // Precision.
  int neg_count;                    // Number of infeasible basic variables.
  Status status;                    // Solvability status of the problem.
 private:
  // Helper function to check the sign of a floating-point number, up to eps.
  int sgn(T v) const { return v > eps ? 1 : (v < -eps ? -1 : 0); }

  // Gain from moving along an edge. (steepest edge rule)
  // Used to choose the entering variable.
  // Column Y is used as the reduced costs.
  T gain(int i, int y) const {
    if (sgn(tab[i][y]) != -1) return T(0);
    T ssq(0);
    for (int j = 0; j != m; ++j) {
      ssq += tab[i][j] * tab[i][j];
    }
    return tab[i][y] * tab[i][y] / ssq;
  }

  // Leaving rule. (effectively no rule implemented)
  bool leaving_first(int y1, int y2) const { return B[y1] < B[y2]; }

  // Pivot on (N[x], B[y]).
  void pivot(int x, int y, bool neg = false) {
    std::swap(N[x], B[y]);
    T v = T(-1) / tab[x][y];
    for (int j = 0; j <= m + 1; ++j) {
      tab[x][j] = j == y ? -v : v * tab[x][j];
    }
    for (int i = 0; i <= n; ++i) {
      if (i == x) continue;
      v = tab[i][y];
      tab[i][y] = T(0);
      for (int j = 0; j <= m + 1; ++j) {
        tab[i][j] += v * tab[x][j];
      }
    }
    // Special treatment: infeasible variable leaving basis.
    if (neg) tab[x][m + 1] += T(1);
  }

  // First phase: find an initial BFS.
  // Return false if the problem is infeasible.
  bool initialize() {
    // Use count of infeasible basic variables as the objective.
    while (neg_count) {
      int x = -1;
      T max_gain(0);
      for (int i = 0; i < n; ++i) {
        auto tmp = gain(i, m + 1);
        if (tmp > max_gain) {
          max_gain = tmp;
          x = i;
        }
      }
      if (x == -1) return false;
      int y = -1, sy = -1;
      for (int j = 0; j < m; ++j) {
        int sj = sgn(tab[x][j]);
        if (sj == (B[j] < 0 ? -1 : 1)) {
          if (y == -1) {
            y = j;
            sy = sj;
          } else {
            auto s =
                sj * sy * sgn(tab[n][j] * tab[x][y] - tab[n][y] * tab[x][j]);
            if (s == -1 || (!s && leaving_first(j, y))) {
              y = j;
              sy = sj;
            }
          }
        }
      }
      if (B[y] < 0) {
        --neg_count;
        B[y] = ~B[y];
        pivot(x, y, true);
      } else {
        pivot(x, y);
      }
    }
    return true;
  }

  // Second phase: find an optimal BFS.
  // Return false if the problem is unbounded.
  bool simplex() {
    while (true) {
      int x = -1;
      T max_gain(0);
      for (int i = 0; i < n; ++i) {
        auto tmp = gain(i, m);
        if (tmp > max_gain) {
          max_gain = tmp;
          x = i;
        }
      }
      if (x == -1) break;
      int y = -1;
      for (int j = 0; j < m; ++j) {
        if (sgn(tab[x][j]) != 1) continue;
        if (y == -1) {
          y = j;
        } else {
          auto s = sgn(tab[n][j] * tab[x][y] - tab[n][y] * tab[x][j]);
          if (s == -1 || (!s && leaving_first(j, y))) {
            y = j;
          }
        }
      }
      if (y == -1) return false;
      pivot(x, y);
    }
    return true;
  }

 public:
  SimplexLPSolver(const std::vector<std::vector<T>>& A, const std::vector<T>& b,
                  const std::vector<T>& c, T eps)
      : m(b.size()),
        n(c.size()),
        tab(1 + n, std::vector<T>(2 + m)),
        B(m),
        N(n),
        eps(eps),
        neg_count(0) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        tab[i][j] = A[j][i];
      }
      tab[i][m] = c[i];
    }
    std::copy(b.begin(), b.end(), tab[n].begin());
    std::iota(N.begin(), N.end(), 0);
    std::iota(B.begin(), B.end(), n);
    for (int j = 0; j < m; ++j) {
      if (sgn(tab[n][j]) == -1) {
        for (int i = 0; i <= n; ++i) {
          tab[i][m + 1] += tab[i][j];
        }
        B[j] = ~B[j];
        ++neg_count;
      }
    }
  }

  // Solve the problem by two-phase simplex method.
  void solve() {
    status = initialize() ? (simplex() ? Status::Bounded : Status::Unbounded)
                          : Status::Infeasible;
  }

  // Obtain solvability status of the problem.
  Status get_status() const { return status; }

  // Obtain minimum value.
  T optimum_value() const {
    if (status == Status::Infeasible) return static_cast<T>(INFINITY);
    if (status == Status::Unbounded) return -static_cast<T>(INFINITY);
    return -tab[n][m];
  }

  // Obtain optimal solutions.
  std::vector<T> solution() const {
    if (status != Status::Bounded) return {};
    std::vector<T> x(n);
    for (int j = 0; j < m; ++j) {
      if (B[j] < n) x[B[j]] = tab[n][j];
    }
    return x;
  }
};

// --8<-- [end:core]
int main() {
  std::cout << std::fixed << std::setprecision(10);
  int n, m, t;
  std::cin >> n >> m >> t;
  std::vector<std::vector<long double>> A(m, std::vector<long double>(n));
  std::vector<long double> b(m), c(n);
  for (auto& x : c) {
    std::cin >> x;
    x = -x;
  }
  for (int i = 0; i < m; ++i) {
    for (auto& x : A[i]) {
      std::cin >> x;
    }
    std::cin >> b[i];
  }
  SimplexLPSolver<long double> solver(A, b, c, 1e-10l);
  solver.solve();
  switch (solver.get_status()) {
    case SimplexLPSolver<long double>::Status::Infeasible:
      std::cout << "Infeasible" << std::endl;
      break;
    case SimplexLPSolver<long double>::Status::Unbounded:
      std::cout << "Unbounded" << std::endl;
      break;
    case SimplexLPSolver<long double>::Status::Bounded:
      std::cout << -solver.optimum_value() << std::endl;
      if (t) {
        for (auto x : solver.solution()) {
          std::cout << x << ' ';
        }
        std::cout << std::endl;
      }
  }
  return 0;
}

// --8<-- [end:full-tex]
