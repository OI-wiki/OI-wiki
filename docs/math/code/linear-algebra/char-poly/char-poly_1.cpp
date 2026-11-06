#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
using i64 = int64_t;

Matrix to_upper_Hessenberg(const Matrix &M, int mod) {
  Matrix H(M);
  int n = H.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((H[i][j] %= mod) < 0) H[i][j] += mod;
    }
  }
  for (int i = 0; i < n - 1; ++i) {
    int pivot = i + 1;
    for (; pivot < n; ++pivot) {
      if (H[pivot][i] != 0) break;
    }
    if (pivot == n) continue;
    if (pivot != i + 1) {
      for (int j = i; j < n; ++j) std::swap(H[i + 1][j], H[pivot][j]);
      for (int j = 0; j < n; ++j) std::swap(H[j][i + 1], H[j][pivot]);
    }
    for (int j = i + 2; j < n; ++j) {
      for (;;) {
        if (H[j][i] == 0) break;
        if (H[i + 1][i] == 0) {
          for (int k = i; k < n; ++k) std::swap(H[i + 1][k], H[j][k]);
          for (int k = 0; k < n; ++k) std::swap(H[k][i + 1], H[k][j]);
          break;
        }
        if (H[j][i] >= H[i + 1][i]) {
          int q = H[j][i] / H[i + 1][i], mq = mod - q;
          for (int k = i; k < n; ++k)
            H[j][k] = (H[j][k] + i64(mq) * H[i + 1][k]) % mod;
          for (int k = 0; k < n; ++k)
            H[k][i + 1] = (H[k][i + 1] + i64(q) * H[k][j]) % mod;
        } else {
          int q = H[i + 1][i] / H[j][i], mq = mod - q;
          for (int k = i; k < n; ++k)
            H[i + 1][k] = (H[i + 1][k] + i64(mq) * H[j][k]) % mod;
          for (int k = 0; k < n; ++k)
            H[k][j] = (H[k][j] + i64(q) * H[k][i + 1]) % mod;
        }
      }
    }
  }
  return H;
}

std::vector<int> get_charpoly(const Matrix &M, int mod) {
  Matrix H(to_upper_Hessenberg(M, mod));
  int n = H.size();
  std::vector<std::vector<int>> p(n + 1);
  p[0] = {1 % mod};
  for (int i = 1; i <= n; ++i) {
    const std::vector<int> &pi_1 = p[i - 1];
    std::vector<int> &pi = p[i];
    pi.resize(i + 1, 0);
    int v = mod - H[i - 1][i - 1];
    if (v == mod) v -= mod;
    for (int j = 0; j < i; ++j) {
      pi[j] = (pi[j] + i64(v) * pi_1[j]) % mod;
      if ((pi[j + 1] += pi_1[j]) >= mod) pi[j + 1] -= mod;
    }
    int t = 1;
    for (int j = 1; j < i; ++j) {
      t = i64(t) * H[i - j][i - j - 1] % mod;
      int prod = i64(t) * H[i - j - 1][i - 1] % mod;
      if (prod == 0) continue;
      prod = mod - prod;
      for (int k = 0; k <= i - j - 1; ++k)
        pi[k] = (pi[k] + i64(prod) * p[i - j - 1][k]) % mod;
    }
  }
  return p[n];
}

bool verify(const Matrix &M, const std::vector<int> &charpoly, int mod) {
  if (mod == 1) return true;
  int n = M.size();
  std::vector<int> randvec(n), sum(n, 0);
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dis(1, mod - 1);
  for (int i = 0; i < n; ++i) randvec[i] = dis(gen);
  for (int i = 0; i <= n; ++i) {
    int v = charpoly[i];
    for (int j = 0; j < n; ++j) sum[j] = (sum[j] + i64(v) * randvec[j]) % mod;
    std::vector<int> prod(n, 0);
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        prod[j] = (prod[j] + i64(M[j][k]) * randvec[k]) % mod;
      }
    }
    randvec.swap(prod);
  }
  for (int i = 0; i < n; ++i)
    if (sum[i] != 0) return false;
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, mod;
  std::cin >> n >> mod;
  Matrix M(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) std::cin >> M[i][j];
  std::vector<int> charpoly(get_charpoly(M, mod));
  for (int i = 0; i <= n; ++i) std::cout << charpoly[i] << ' ';
  assert(verify(M, charpoly, mod));
  return 0;
}
