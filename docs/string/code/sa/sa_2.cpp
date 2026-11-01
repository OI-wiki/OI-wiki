#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

constexpr int N = 1000010;

char s[N];
int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];

int main() {
  int i, m, p, w;

  scanf("%s", s + 1);
  n = strlen(s + 1);
  m = 127;
  for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
  for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
  memcpy(oldrk + 1, rk + 1, n * sizeof(int));
  for (p = 0, i = 1; i <= n; ++i) {
    if (oldrk[sa[i]] == oldrk[sa[i - 1]]) {
      rk[sa[i]] = p;
    } else {
      rk[sa[i]] = ++p;
    }
  }

  for (w = 1; w < n; w <<= 1, m = n) {
    // 对第二关键字：id[i] + w进行计数排序
    memset(cnt, 0, sizeof(cnt));
    memcpy(id + 1, sa + 1,
           n * sizeof(int));  // id保存一份儿sa的拷贝，实质上就相当于oldsa
    for (i = 1; i <= n; ++i) ++cnt[rk[id[i] + w]];
    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) sa[cnt[rk[id[i] + w]]--] = id[i];

    // 对第一关键字：id[i]进行计数排序
    memset(cnt, 0, sizeof(cnt));
    memcpy(id + 1, sa + 1, n * sizeof(int));
    for (i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];

    memcpy(oldrk + 1, rk + 1, n * sizeof(int));
    for (p = 0, i = 1; i <= n; ++i) {
      if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
          oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
        rk[sa[i]] = p;
      } else {
        rk[sa[i]] = ++p;
      }
    }
  }

  for (i = 1; i <= n; ++i) printf("%d ", sa[i]);

  return 0;
}
