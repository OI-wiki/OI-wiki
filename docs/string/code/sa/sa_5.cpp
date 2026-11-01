#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int N = 1000010;

char s[N];
int n, w, sa[N], rk[N << 1], oldrk[N << 1], height[N];

// 为了防止访问 rk[i+w] 导致数组越界，开两倍数组．
// 当然也可以在访问前判断是否越界，但直接开两倍数组方便一些．

int main() {
  int i, p;

  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];

  for (w = 1; w < n; w <<= 1) {
    sort(sa + 1, sa + n + 1, [](int x, int y) {
      return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
    });  // 这里用到了 lambda
    memcpy(oldrk, rk, sizeof(rk));
    // 由于计算 rk 的时候原来的 rk 会被覆盖，要先复制一份
    // 若两个子串相同，它们对应的 rk 也需要相同，所以要去重
    for (p = 0, i = 1; i <= n; ++i) {
      if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
          oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
        rk[sa[i]] = p;
      } else {
        rk[sa[i]] = ++p;
      }
    }
  }

  for (i = 1; i <= n; ++i) rk[sa[i]] = i;
  int k;
  // --8<-- [start:height]
  for (i = 1, k = 0; i <= n; ++i) {
    if (rk[i] == 1) {
      k = 0;
      continue;
    }
    if (k) --k;
    while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
    height[rk[i]] = k;
  }
  // --8<-- [end:height]
  for (i = 1; i <= n; ++i) printf("%d%s", height[i], i == n ? "\n" : " ");

  return 0;
}
