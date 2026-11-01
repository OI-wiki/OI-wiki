#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int minimal_rotation(const string &sec) {
  int n = sec.size();
  // --8<-- [start:core]
  int k = 0, i = 0, j = 1;
  while (k < n && i < n && j < n) {
    if (sec[(i + k) % n] == sec[(j + k) % n]) {
      k++;
    } else {
      sec[(i + k) % n] > sec[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
      if (i == j) i++;
      k = 0;
    }
  }
  i = min(i, j);
  // --8<-- [end:core]
  return i;
}

// Problem: https://onlinejudge.org/external/7/719.pdf
int main() {
  int t;
  cin >> t;
  while (t--) {
    string sec;
    cin >> sec;
    cout << minimal_rotation(sec) + 1 << "\n";
  }
}
