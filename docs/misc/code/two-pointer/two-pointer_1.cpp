#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Sample source: https://leetcode.com/problems/subarray-product-less-than-k/
// Input: array length, target, then the array elements.
// --8<-- [start:core]
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
  long long ji = 1ll, ans = 0;
  int l = 0;
  for (int i = 0; i < nums.size(); ++i) {
    ji *= nums[i];
    while (l <= i && ji >= k) ji /= nums[l++];
    ans += i - l + 1;
  }
  return ans;
}

// --8<-- [end:core]

int main() {
  int n, target;
  if (!(cin >> n >> target)) return 0;
  vector<int> values(n);
  for (int& value : values) cin >> value;
  cout << numSubarrayProductLessThanK(values, target) << '\n';
}
