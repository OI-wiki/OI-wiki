#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

// --8<-- [start:core]
void insertion_sort(int arr[], int len) {
  if (len < 2) return;
  for (int i = 1; i != len; ++i) {
    int key = arr[i];
    auto index = upper_bound(arr, arr + i, key) - arr;
    // 使用 memmove 移动元素，比使用 for 循环速度更快，时间复杂度仍为 O(n)
    memmove(arr + index + 1, arr + index, (i - index) * sizeof(int));
    arr[index] = key;
  }
}

// --8<-- [end:core]

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  insertion_sort(a.data(), n);
  for (int i = 0; i < n; ++i) cout << (i ? " " : "") << a[i];
  cout << "\n";
}
