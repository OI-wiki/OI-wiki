#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// --8<-- [start:sort]
template <typename T>
int partition(T A[], int low, int high) {
  T pivot = A[low];
  while (low < high) {
    while (low < high && pivot <= A[high]) --high;
    A[low] = A[high];
    while (low < high && A[low] <= pivot) ++low;
    A[high] = A[low];
  }
  A[low] = pivot;
  return low;
}

template <typename T>
void quickSort(T A[], int low, int high) {
  if (low < high) {
    int pivot = partition(A, low, high);
    quickSort(A, low, pivot - 1);
    quickSort(A, pivot + 1, high);
  }
}

template <typename T>
void quickSort(T A[], int len) {
  quickSort(A, 0, len - 1);
}

// --8<-- [end:sort]

int main() {
  int n;
  if (!(cin >> n) || n < 0) return 0;
  vector<int> a(n + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  quickSort(a.data(), n);
  for (int i = 0; i < n; ++i) cout << a[i] << ' ';
  cout << '\n';
}
