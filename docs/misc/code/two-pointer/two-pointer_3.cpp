#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Sample source:
// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/ Input: array
// length, target, then the array elements.
// --8<-- [start:core]
vector<int> twoSum(vector<int>& numbers, int target) {
  int r = numbers.size() - 1, l = 0;
  vector<int> ans;
  ans.clear();
  while (l < r) {
    if (numbers[l] + numbers[r] > target)
      r--;
    else if (numbers[l] + numbers[r] == target) {
      ans.push_back(l + 1), ans.push_back(r + 1);
      return ans;
    } else
      l++;
  }
  return ans;
}

// --8<-- [end:core]

int main() {
  int n, target;
  if (!(cin >> n >> target)) return 0;
  vector<int> values(n);
  for (int& value : values) cin >> value;
  vector<int> result = twoSum(values, target);
  for (int j = 0; j < static_cast<int>(result.size()); ++j) {
    if (j) cout << ' ';
    cout << result[j];
  }
  cout << '\n';
}
