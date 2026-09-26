#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// --8<-- [start:sort]
void sift_down(int arr[], int start, int end) {
  // 计算父结点和子结点的下标
  int parent = start;
  int child = parent * 2 + 1;
  while (child <= end) {  // 子结点下标在范围内才做比较
    // 先比较两个子结点大小，选择最大的
    if (child + 1 <= end && arr[child] < arr[child + 1]) child++;
    // 如果父结点比子结点大，代表调整完毕，直接跳出函数
    if (arr[parent] >= arr[child])
      return;
    else {  // 否则交换父子内容，子结点再和孙结点比较
      swap(arr[parent], arr[child]);
      parent = child;
      child = parent * 2 + 1;
    }
  }
}

void heap_sort(int arr[], int len) {
  // 从最后一个节点的父节点开始 sift down 以完成堆化（heapify）
  for (int i = (len - 1 - 1) / 2; i >= 0; i--) sift_down(arr, i, len - 1);
  // 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    sift_down(arr, 0, i - 1);
  }
}

// --8<-- [end:sort]

int main() {
  int n;
  if (!(cin >> n) || n < 0) return 0;
  vector<int> a(n + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  heap_sort(a.data(), n);
  for (int i = 0; i < n; ++i) cout << a[i] << ' ';
  cout << '\n';
}
