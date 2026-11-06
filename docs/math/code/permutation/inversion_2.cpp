#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// A simple BIT implementation.
class BIT {
  int n;
  std::vector<int> su;

 public:
  BIT(int n) : n(n), su(n + 1) {}

  // Add v to the x-th number.
  void add(int x, int v) {
    for (; x <= n; x += x & (-x)) {
      su[x] += v;
    }
  }

  // Get the cumulative sum till the x-th number.
  int query(int x) {
    int res = 0;
    for (; x; x &= x - 1) {
      res += su[x];
    }
    return res;
  }
};

// Count inversions.
long long solve(const std::vector<int>& nums) {
  // Discretization.
  std::vector<int> sorted(nums);
  std::sort(sorted.begin(), sorted.end());
  sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());
  std::unordered_map<int, int> ids;
  int m = sorted.size();
  for (int i = 0; i < m; ++i) {
    // Reverse the order.
    // Now a smaller id means a larger element.
    ids[sorted[i]] = m - i;
  }
  // Main part.
  BIT bit(m);
  long long res = 0;
  for (int num : nums) {
    int id = ids[num];
    // Get inversion pair (i,j) with j the current element.
    // Namely, count the number of elements larger than
    //     the current one but located before it.
    res += bit.query(id - 1);
    // Insert the current element to the BIT.
    bit.add(id, 1);
  }
  return res;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  for (int& num : nums) {
    std::cin >> num;
  }
  std::cout << solve(nums);
  return 0;
}
