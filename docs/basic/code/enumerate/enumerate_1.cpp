#include <cstring>
constexpr int MAXN = 100000;  // 此处 MAXN 是数组内元素的界

int solve(int n, int a[]) {
  bool met[MAXN * 2 + 1];  // 创建一个能装下 [-MAXN, MAXN] 的桶
  memset(met, 0, sizeof(met));
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (met[MAXN - a[i]]) ++ans;  // 如果桶内有想要的元素，答案加一
    met[MAXN + a[i]] = true;  // 无论如何，都要把当前元素放进桶里
  }
  return ans;
}
