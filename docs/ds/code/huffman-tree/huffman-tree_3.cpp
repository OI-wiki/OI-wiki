#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 10005;

// --8<-- [start:example72]
int getWPL(int arr[], int n) {  // 对于未建好的霍夫曼树，直接求其 WPL
  priority_queue<int, vector<int>, greater<int>> huffman;  // 小根堆
  for (int i = 0; i < n; i++) huffman.push(arr[i]);

  int res = 0;
  for (int i = 0; i < n - 1; i++) {
    int x = huffman.top();
    huffman.pop();
    int y = huffman.top();
    huffman.pop();
    int temp = x + y;
    res += temp;
    huffman.push(temp);
  }
  return res;
}

// --8<-- [end:example72]

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int& value : a) cin >> value;
  cout << getWPL(a.data(), n) << "\n";
}
