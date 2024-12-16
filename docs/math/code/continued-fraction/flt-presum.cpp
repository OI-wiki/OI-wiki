#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

constexpr int M = 1e9 + 7;

// FLTs. Essentially 2x2 matrix.
struct FracLinearTrans {
  int mat[4];

  FracLinearTrans() : mat{} {}

  FracLinearTrans(int x) : mat{x, 1, 1, 0} {}

  FracLinearTrans(int a, int b, int c, int d) : mat{a, b, c, d} {}

  FracLinearTrans operator*(const FracLinearTrans& rhs) const {
    return FracLinearTrans(
        ((long long)mat[0] * rhs.mat[0] + (long long)mat[1] * rhs.mat[2]) % M,
        ((long long)mat[0] * rhs.mat[1] + (long long)mat[1] * rhs.mat[3]) % M,
        ((long long)mat[2] * rhs.mat[0] + (long long)mat[3] * rhs.mat[2]) % M,
        ((long long)mat[2] * rhs.mat[1] + (long long)mat[3] * rhs.mat[3]) % M);
  }

  FracLinearTrans inv() const {
    return FracLinearTrans(mat[3], M - mat[1], M - mat[2], mat[0]);
  }
};

int main() {
  int n, q;
  std::cin >> n >> q;
  // Get prefix sum of FLTs.
  std::vector<FracLinearTrans> ps(1, {1, 0, 0, 1});
  ps.reserve(n + 1);
  for (int i = 1; i <= n; ++i) {
    int a;
    std::cin >> a;
    ps[i] = ps[i - 1] * FracLinearTrans(a);
  }
  // Query.
  for (; q; --q) {
    int l, r;
    std::cin >> l >> r;
    // Difference.
    auto res = ps[l - 1].inv() * ps[r];
    int u = res.mat[0], d = res.mat[2];
    // Correct signs.
    if (!(l & 1)) {
      if (u) u = M - u;
      if (d) d = M - d;
    }
    printf("%d %d\n", u, d);
  }
  return 0;
}
