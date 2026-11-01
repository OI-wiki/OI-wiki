#include <cassert>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>
using namespace std;
constexpr int p = 998244353;

int power(int a, int b) {
  int r = 1;
  for (; b; b >>= 1, a = 1LL * a * a % p)
    if (b & 1) r = 1LL * r * a % p;
  return r;
}

// --8<-- [start:bm]
vector<int> berlekamp_massey(const vector<int> &a) {
  vector<int> v, last;  // v is the answer, 0-based, p is the module
  int k = -1, delta = 0;

  for (int i = 0; i < (int)a.size(); i++) {
    int tmp = 0;
    for (int j = 0; j < (int)v.size(); j++)
      tmp = (tmp + (long long)a[i - j - 1] * v[j]) % p;

    if (a[i] == tmp) continue;

    if (k < 0) {
      k = i;
      delta = (a[i] - tmp + p) % p;
      v = vector<int>(i + 1);

      continue;
    }

    vector<int> u = v;
    int val = (long long)(a[i] - tmp + p) * power(delta, p - 2) % p;

    if (v.size() < last.size() + i - k) v.resize(last.size() + i - k);

    (v[i - k - 1] += val) %= p;

    for (int j = 0; j < (int)last.size(); j++) {
      v[i - k + j] = (v[i - k + j] - (long long)val * last[j]) % p;
      if (v[i - k + j] < 0) v[i - k + j] += p;
    }

    if ((int)u.size() - i < (int)last.size() - k) {
      last = u;
      k = i;
      delta = a[i] - tmp;
      if (delta < 0) delta += p;
    }
  }

  for (auto &x : v) x = (p - x) % p;
  v.insert(v.begin(), 1);

  return v;  // $\forall i, \sum_{j = 0} ^ m a_{i - j} v_j = 0$
}

// --8<-- [end:bm]
// --8<-- [start:sparse]
vector<int> solve_sparse_equations(const vector<tuple<int, int, int>> &A,
                                   const vector<int> &b) {
  int n = (int)b.size();  // 0-based

  vector<vector<int>> f({b});

  for (int i = 1; i < 2 * n; i++) {
    vector<int> v(n);
    auto &u = f.back();

    for (const auto &entry : A) {  // [x, y, value]
      int x, y, z;
      tie(x, y, z) = entry;
      v[x] = (v[x] + (long long)u[y] * z) % p;
    }

    f.push_back(v);
  }

  vector<int> w(n);
  mt19937 gen;
  for (auto &x : w) x = uniform_int_distribution<int>(1, p - 1)(gen);

  vector<int> a(2 * n);
  for (int i = 0; i < 2 * n; i++)
    for (int j = 0; j < n; j++) a[i] = (a[i] + (long long)f[i][j] * w[j]) % p;

  auto c = berlekamp_massey(a);
  int m = (int)c.size();

  vector<int> ans(n);

  for (int i = 0; i < m - 1; i++)
    for (int j = 0; j < n; j++)
      ans[j] = (ans[j] + (long long)c[m - 2 - i] * f[i][j]) % p;

  int inv = power(p - c[m - 1], p - 2);

  for (int i = 0; i < n; i++) ans[i] = (long long)ans[i] * inv % p;

  return ans;
}

// --8<-- [end:sparse]
// Derived demonstration: recover the Fibonacci recurrence and solve a sparse
// Fibonacci transition matrix. These are article-based checks, not an OJ
// sample.
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &x : a) cin >> x;
  auto c = berlekamp_massey(a);
  for (size_t i = 0; i < c.size(); ++i)
    cout << c[i] << (i + 1 == c.size() ? '\n' : ' ');
  vector<tuple<int, int, int>> A{{0, 0, 1}, {0, 1, 1}, {1, 0, 1}};
  vector<int> b{5, 3};
  auto x = solve_sparse_equations(A, b);
  assert((x[0] + x[1]) % p == 5 && x[0] == 3);
  cout << x[0] << ' ' << x[1] << '\n';
}
