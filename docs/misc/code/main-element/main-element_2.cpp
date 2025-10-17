#include <cstdio>
#include <vector>
using namespace std;

// --8<-- [start:core]
class Solution {
 public:
  vector<int> majorityElement(vector<int>& nums) {
    // 将多数投票算法的「抵消2个不同元素」变为「抵消3个两两不同的元素」
    int maj1, maj2;
    int cnt1 = 0, cnt2 = 0;
    for (int num : nums) {
      if (num == maj1) {
        ++cnt1;
      } else if (num == maj2) {
        ++cnt2;
      } else if (cnt1 == 0) {
        maj1 = num;
        ++cnt1;
      } else if (cnt2 == 0) {
        maj2 = num;
        ++cnt2;
      } else {
        --cnt1;
        --cnt2;
      }
    }

    // 由于题目没有保证存在2个超过 ⌊ n/3 ⌋ 次的元素，故需检验
    vector<int> ans;
    cnt1 = 0, cnt2 = 0;
    for (int num : nums) {
      if (num == maj1)
        ++cnt1;
      else if (num == maj2)
        ++cnt2;
    }
    int n = nums.size();
    if (cnt1 > n / 3) ans.push_back(maj1);
    if (cnt2 > n / 3) ans.push_back(maj2);

    return ans;
  }
};

// --8<-- [end:core]
int main() {
  int n;
  scanf("%d", &n);
  vector<int> nums(n);
  for (int& i : nums) scanf("%d", &i);
  Solution sol;
  vector<int> ans = sol.majorityElement(nums);
  for (int i = 0; i < ans.size(); i++)
    printf("%d%c", ans[i], " \n"[i + 1 == ans.size()]);
  return 0;
}
