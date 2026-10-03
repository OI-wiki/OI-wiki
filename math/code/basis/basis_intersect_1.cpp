#include <array>
#include <iostream>

class LinearBasis {
  static constexpr int K = 30;
  std::array<int, K> a;

  // Size of basis.
  int size() const {
    int res = 0;
    for (auto x : a) {
      if (x) {
        ++res;
      }
    }
    return res;
  }

 public:
  LinearBasis() : a{} {}

  // Insert vector x.
  void insert(int x) {
    for (int k = K - 1; ~k && x; --k) {
      if ((x >> k) & 1) {
        if (!a[k]) {
          a[k] = x;
        }
        x ^= a[k];
      }
    }
  }

  // Return a basis for *THIS intersecting RHS.
  LinearBasis intersect(const LinearBasis& rhs) const {
    LinearBasis res;
    std::array<int, K> c = a, b_parts = {};
    for (int i = K - 1; ~i; --i) {
      int x = rhs.a[i], b_part = x;
      for (int k = i; ~k && x; --k) {
        if ((x >> k) & 1) {
          if (!c[k]) {
            c[k] = x;
            b_parts[k] = b_part;
          }
          x ^= c[k];
          b_part ^= b_parts[k];
        }
      }
      res.insert(b_part);
    }
    return res;
  }

  // Output.
  void print() const {
    std::cout << size();
    for (auto x : a) {
      if (x) {
        std::cout << ' ' << x;
      }
    }
    std::cout << '\n';
  }
};

int main() {
  int t;
  std::cin >> t;
  for (; t; --t) {
    LinearBasis a, b;
    int n;
    std::cin >> n;
    for (; n; --n) {
      int x;
      std::cin >> x;
      a.insert(x);
    }
    int m;
    std::cin >> m;
    for (; m; --m) {
      int x;
      std::cin >> x;
      b.insert(x);
    }
    a.intersect(b).print();
  }
  return 0;
}
