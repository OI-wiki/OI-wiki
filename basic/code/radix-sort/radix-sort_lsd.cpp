#include <cstring>
#include <iostream>
using namespace std;
// --8<-- [start:core]
constexpr int N = 100010;
constexpr int W = 100010;
constexpr int K = 100;

int n, w, k, cnt[W];

struct Element {
  int key[K];
} a[N], b[N];

void counting_sort(int p) {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; ++i) ++cnt[a[i].key[p]];
  for (int i = 1; i <= w; ++i) cnt[i] += cnt[i - 1];
  // 为保证排序的稳定性，此处循环i应从n到1
  // 即当两元素关键字的值相同时，原先排在后面的元素在排序后仍应排在后面
  for (int i = n; i >= 1; --i) b[cnt[a[i].key[p]]--] = a[i];
  memcpy(a, b, sizeof(a));
}

void radix_sort() {
  for (int i = k; i >= 1; --i) {
    // 借助计数排序完成对关键字的排序
    counting_sort(i);
  }
}

// --8<-- [end:core]

int main() {
  k = 10;
  w = 9;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    unsigned x;
    cin >> x;
    for (int j = 10; j >= 1; j--) a[i].key[j] = x % 10, x /= 10;
  }
  radix_sort();
  for (int i = 1; i <= n; i++) {
    int l = 1;
    while (!a[i].key[l] && l <= k) l++;
    if (l > k)
      cout << "0";
    else
      for (; l <= k; l++) cout << a[i].key[l];
    cout << " \n"[i == n];
  }
}
