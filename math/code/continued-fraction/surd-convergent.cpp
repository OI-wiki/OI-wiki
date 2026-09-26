#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

// Return the continued fraction and minimal positive period
//   of a quadratic irrational (x + y * sqrt(n)) / z.
auto quadratic_irrational(int x, int y, int z, int n) {
  int p = x * z;
  int d = n * y * y * z * z;
  int q = z * z;
  int dd = (int)sqrt(n) * y * z;
  int i = 0;
  std::vector<int> a;
  std::unordered_map<size_t, int> used;
  while (!used.count(((1LL << 32) * p) | q)) {
    a.emplace_back((p + dd) / q);
    used[((1LL << 32) * p) | q] = i++;
    p = a.back() * q - p;
    q = (d - p * p) / q;
  }
  return std::make_pair(a, i - used[((1LL << 32) * p) | q]);
}

// Fractional Linear Transformation.
struct FracLinearTrans {
  static constexpr int M = 1e9 + 7;
  int mat[4];

  FracLinearTrans(int a, int b, int c, int d) : mat{a, b, c, d} {}

  FracLinearTrans operator*(const FracLinearTrans& rhs) const {
    return FracLinearTrans(
        ((long long)mat[0] * rhs.mat[0] + (long long)mat[1] * rhs.mat[2]) % M,
        ((long long)mat[0] * rhs.mat[1] + (long long)mat[1] * rhs.mat[3]) % M,
        ((long long)mat[2] * rhs.mat[0] + (long long)mat[3] * rhs.mat[2]) % M,
        ((long long)mat[2] * rhs.mat[1] + (long long)mat[3] * rhs.mat[3]) % M);
  }
};

int main() {
  int x, k, L;
  std::cin >> x >> k;
  std::vector<int> a;
  std::tie(a, L) =
      quadratic_irrational(0, 1, 1, x);  // L==a.size()-1 for sqrt(x)
  FracLinearTrans cyc(1, 0, 0, 1);
  for (int i = a.size() - 1; i; --i) {
    cyc = FracLinearTrans(a[i], 1, 1, 0) * cyc;
  }
  // 1/0=Inf.
  FracLinearTrans res(0, 1, 0, 0);
  // Tail terms.
  for (int i = k % L; i; --i) {
    res = FracLinearTrans(a[i], 1, 1, 0) * res;
  }
  // Binary exponentiation.
  for (int b = k / L; b; b >>= 1) {
    if (b & 1) res = cyc * res;
    cyc = cyc * cyc;
  }
  // First term.
  res = FracLinearTrans(a[0], 1, 1, 0) * res;
  printf("%d/%d", res.mat[1], res.mat[3]);
  return 0;
}
