#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

#ifdef _MSC_VER
#include <intrin.h>
#define __builtin_popcountll __popcnt64
#endif

struct Bits {
  vector<unsigned long long> b;
  vector<int> sum;
  int len;

  Bits(int n) {
    len = n >> 6;
    b.resize(len + 1, 0);
    sum.resize(len + 1, 0);
  }

  // 第 k 位（从 1 开始编号）设为 1
  void set(int k) {
    k--;  // 内部从 0 开始存储
    b[k >> 6] |= (1ull << (k & 0x3f));
  }
  // 设定完毕后调用
  void prepare() {
    for (int i = 0; i < b.size(); i++) {
      if (i) sum[i] = sum[i - 1];
      sum[i] += __builtin_popcountll(b[i]);
    }
  }

  int rank1(int k) {
    int res = 0;
    int hi = (k >> 6), lo = (k & 0x3f);
    if (hi) res += sum[hi - 1];
    // (1 << lo) - 1 取了小于 lo 的位，正好符合从 0 开始存储
    res += __builtin_popcountll(b[hi] & ((1ull << lo) - 1ull));
    return res;
  }
  int rank0(int k) { return k - rank1(k); }
};

struct WaveletMatrix {
  vector<Bits> b;
  int n;

  // 注意 a 将被修改
  WaveletMatrix(int n, int *a) {
    this->n = n;
    b.resize(32, Bits(n));
    for (int j = 31; j >= 0; j--) {
      for (int i = 1; i <= n; i++)
        if ((a[i] >> j) & 1) b[j].set(i);
      b[j].prepare();
      stable_partition(a + 1, a + n + 1, [&](int x) { return (x >> j) & 1; });
    }
  }

  int id(int j, int c, int i) {
    return c ? b[j].rank1(i) : b[j].rank0(i) + b[j].rank1(n);
  }
  // 与上面讲的不完全相同，返回大于 w 的数的个数
  int ranking(int l, int r, int w) {
    int res = 0;
    for (int j = 31; j >= 0; j--) {
      int c = (w >> j) & 1;
      if (c) {
        l = id(j, 1, l - 1) + 1;
        r = id(j, 1, r);
      } else {
        res += b[j].rank1(r) - b[j].rank1(l - 1);
        l = id(j, 0, l - 1) + 1;
        r = id(j, 0, r);
      }
    }
    return res;
  }
};

const int MAXN(1e6 + 5);

int a[MAXN], nxt[MAXN], lst[MAXN];
int n, m;

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    lst[a[i]] = n + 1;
  }
  for (int i = n; i >= 1; i--) {
    nxt[i] = lst[a[i]];
    lst[a[i]] = i;
  }
  WaveletMatrix w(n, nxt);
  
  scanf("%d", &m);
  while (m--) {
    int l, r;
    scanf("%d %d", &l, &r);
    printf("%d\n", w.ranking(l, r, r));
  }
  return 0;
}
