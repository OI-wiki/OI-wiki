#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

// --8<-- [start:core]
template <typename T>
void shell_sort(T array[], int length) {
  int h = 1;
  while (h < length / 3) {
    h = 3 * h + 1;
  }
  while (h >= 1) {
    for (int i = h; i < length; i++) {
      for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
        std::swap(array[j], array[j - h]);
      }
    }
    h = h / 3;
  }
}

// --8<-- [end:core]

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  shell_sort(a.data(), n);
  for (int i = 0; i < n; ++i) cout << (i ? " " : "") << a[i];
  cout << "\n";
}
