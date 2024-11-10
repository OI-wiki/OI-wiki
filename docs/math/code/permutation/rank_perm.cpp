#include <cmath>
#include <iostream>
#include <vector>

// A simple BIT implementation.
class BIT {
  int n;
  std::vector<int> su;

 public:
  BIT(int n) : n(n), su(n + 1) {}

  // Fill the BIT with one.
  void fill() {
    for (int x = 1; x <= n; ++x) {
      su[x] += x & (-x);
    }
  }

  // Add v to the x-th number.
  void add(int x, int v) {
    for (; x <= n; x += x & (-x)) {
      su[x] += v;
    }
  }

  // Get the k-th smallest element.
  int find_kth(int k) {
    int ps = 0, x = 0;
    for (int i = log2(n); i >= 0; --i) {
      x += 1 << i;
      if (x >= n || ps + su[x] >= k) {
        x -= 1 << i;
      } else {
        ps += su[x];
      }
    }
    return x + 1;
  }
};

// Find the k-th permutation of 1~n.
std::vector<int> find_permutation(int n, long long k) {
  --k;
  // Expand rank to Lehmer code.
  std::vector<int> lehmer(n);
  for (int i = 1; i <= n; ++i) {
    lehmer[n - i] = k % i;
    k /= i;
  }
  BIT bit(n);
  // Set all values in BIT to one.
  bit.fill();
  std::vector<int> res(n);
  for (int i = 0; i < n; ++i) {
    // Find the lehmer[i]-th smallest unused element.
    res[i] = bit.find_kth(lehmer[i] + 1);
    // Remove it from the BIT.
    bit.add(res[i], -1);
  }
  return res;
}

int main() {
  int n;
  long long k;
  std::cin >> n >> k;
  auto res = find_permutation(n, k);
  for (int num : res) {
    std::cout << num << ' ';
  }
  return 0;
}
