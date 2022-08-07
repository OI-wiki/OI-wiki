#include <iostream>
using namespace std;

int N, A[10000], B[10000];

int main() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  // 前缀和数组的第一项和原数组的第一项是相等的。
  B[0] = A[0];

  for (int i = 1; i < N; i++) {
    // 前缀和数组的第 i 项 = 原数组的 0 到 i-1 项的和 + 原数组的第 i 项。
    B[i] = B[i - 1] + A[i];
  }

  for (int i = 0; i < N; i++) {
    cout << B[i] << " ";
  }

  return 0;
}