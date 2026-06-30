#include <iostream>
#include <vector>

class LinearBasis {
  int K;
  std::vector<long long> a;

 public:
  LinearBasis(int K) : K(K), a(K) {}

  // Insert vector x.
  void insert(long long x) {
    for (int k = K - 1; ~k && x; --k) {
      if ((x >> k) & 1) {
        if (!a[k]) {
          a[k] = x;
        }
        x ^= a[k];
      }
    }
  }

  // Output those not exceeding 2^k.
  void print(int k) const {
    int sz = 0;
    for (int i = 0; i < k; ++i) {
      if (a[i]) {
        ++sz;
      }
    }
    std::cout << sz;
    for (int i = 0; i < k; ++i) {
      if (a[i]) {
        std::cout << ' ' << a[i];
      }
    }
    std::cout << '\n';
  }
};

int main() {
  constexpr int K = 30;
  int t;
  std::cin >> t;
  for (; t; --t) {
    LinearBasis c(K << 1);
    int n;
    std::cin >> n;
    for (; n; --n) {
      int x;
      std::cin >> x;
      c.insert(((long long)x << K) | x);
    }
    int m;
    std::cin >> m;
    for (; m; --m) {
      int x;
      std::cin >> x;
      c.insert((long long)x << K);
    }
    c.print(K);
  }
  return 0;
}
