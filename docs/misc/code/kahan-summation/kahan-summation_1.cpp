#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

// Demonstration: recover eight unit increments after 100000000.
// --8<-- [start:core]
float kahanSum(vector<float> nums) {
  float sum = 0.0f;
  float c = 0.0f;
  for (auto num : nums) {
    float y = num - c;
    float t = sum + y;
    c = (t - sum) - y;
    sum = t;
  }
  return sum;
}

// --8<-- [end:core]

int main() {
  int n;
  if (!(cin >> n)) return 0;
  vector<float> nums(n);
  for (float& value : nums) cin >> value;
  cout << setprecision(9) << kahanSum(nums) << '\n';
}
