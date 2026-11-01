#include <cassert>
#include <cstring>
#include <iostream>
using LL = long long;
constexpr int sz = 2;
constexpr LL MOD = 1000000007;

// --8<-- [start:core-prefix]
struct mat {
  LL a[sz][sz];

  mat() { memset(a, 0, sizeof a); }

  mat operator-(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
      }
    return res;
  }

  mat operator+(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) {
        res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
      }
    return res;
  }

  // --8<-- [end:core-prefix]

  // --8<-- [start:naive]
  mat multiply_naive(const mat& T) const {
    mat res;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j)
        for (int k = 0; k < sz; ++k) {
          res.a[i][j] += a[i][k] * T.a[k][j];
          res.a[i][j] %= MOD;
        }
    return res;
  }

  // --8<-- [end:naive]

  // --8<-- [start:fast]
  // 不如
  // --8<-- [start:core-suffix]
  mat operator*(const mat& T) const {
    mat res;
    int r;
    for (int i = 0; i < sz; ++i)
      for (int k = 0; k < sz; ++k) {
        r = a[i][k];
        for (int j = 0; j < sz; ++j)
          res.a[i][j] += T.a[k][j] * r, res.a[i][j] %= MOD;
      }
    return res;
  }

  // --8<-- [end:fast]

  mat operator^(LL x) const {
    mat res, bas;
    for (int i = 0; i < sz; ++i) res.a[i][i] = 1;
    for (int i = 0; i < sz; ++i)
      for (int j = 0; j < sz; ++j) bas.a[i][j] = a[i][j] % MOD;
    while (x) {
      if (x & 1) res = res * bas;
      bas = bas * bas;
      x >>= 1;
    }
    return res;
  }
};

// --8<-- [end:core-suffix]

int main() {
  LL n;
  std::cin >> n;
  mat base;
  base.a[0][0] = base.a[0][1] = base.a[1][0] = 1;
  mat squared = base * base, naive = base.multiply_naive(base);
  for (int i = 0; i < sz; ++i)
    for (int j = 0; j < sz; ++j) assert(squared.a[i][j] == naive.a[i][j]);
  mat answer = base ^ (n - 1);
  std::cout << answer.a[0][0] << '\n';
}
