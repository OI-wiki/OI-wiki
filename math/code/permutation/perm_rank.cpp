#include <iostream>
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

// Get the rank of a permutation of 1~n.
long long find_rank(const std::vector<int>& nums) {
  int n = nums.size();
  BIT bit(n);
  long long fac = 1;
  long long res = 0;
  // Reverse iteration.
  for (int i = n - 1; i >= 0; --i) {
    // Count the number of elements smaller than the current one.
    res += bit.query(nums[i] - 1) * fac;
    // Insert the current element into the BIT.
    bit.add(nums[i], 1);
    // Update the factorial.
    fac *= n - i;
  }
  return res + 1;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> nums(n);
  for (int& num : nums) {
    std::cin >> num;
  }
  std::cout << find_rank(nums);
  return 0;
}
