#include <iostream>
#include <vector>

// Merge sort and count inversions.
long long merge_sort(std::vector<int>& nums, int b, int e) {
  // Return 0 when length <= 1.
  if (e - b <= 1) return 0;
  long long res = 0;
  int m = (b + e) / 2;
  // Merge_sort two halves.
  res += merge_sort(nums, b, m);
  res += merge_sort(nums, m, e);
  // Temporary vector to store sorted array.
  std::vector<int> tmp(e - b);
  int i = b, j = m, k = 0;
  while (i < m && j < e) {
    if (nums[j] < nums[i]) {
      tmp[k] = nums[j++];
      // In this case, all elements in [i,m) are larger than element j.
      res += m - i;
    } else {
      tmp[k] = nums[i++];
    }
    ++k;
  }
  // Deal with remaining elements.
  for (; i < m; ++i, ++k) {
    tmp[k] = nums[i];
  }
  for (; j < e; ++j, ++k) {
    tmp[k] = nums[j];
  }
  // Copy back to original vector.
  for (i = b, k = 0; i < e; ++i, ++k) {
    nums[i] = tmp[k];
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
  std::cout << merge_sort(nums, 0, n);
  return 0;
}
