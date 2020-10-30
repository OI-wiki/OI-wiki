author: Ir1d, partychicken, Xeonacid, Henry-ZHR, ouuan, Marcythm, VivianHeleneto, zj713300, abc1763613206, R-G-Mocoratioen, StudyingFather, TianyiQ

## 概述

随机化被广泛应用于 OI 中各种 **骗分** ， **偷懒** 的场景下。

当然，也有正经用途，例如：考场上造出随机数据然后对拍。

尤其是当算法期望复杂度正确且 **与输入数据无关** 时可用随机化使复杂度达到期望平衡，比如 Treap 和可并堆等。

## Example I

先来看一道网络流题： [「TJOI2015」线性代数](https://loj.ac/problem/2100) 。

我们并不想写网络流，于是开始偷税。建模？不存在的。

### 做法

随机一个位置，把这个位置取反，判断大小并更新答案。

### 代码

```cpp
#include <algorithm>
#include <cstdlib>
#include <iostream>

int n;

int a[510], b[510], c[510][510], d[510];
int p[510], q[510];

int maxans = 0;

void check() {
  memset(d, 0, sizeof d);
  int nowans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) d[i] += a[j] * c[i][j];
  for (int i = 1; i <= n; i++) nowans += (d[i] - b[i]) * a[i];
  maxans = std::max(maxans, nowans);
}

int main() {
  srand(19260817);
  std::cin >> n;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) std::cin >> c[i][j];
  for (int i = 1; i <= n; i++) std::cin >> b[i];
  for (int i = 1; i <= n; i++) a[i] = 1;
  check();
  for (int T = 1000; T; T--) {
    int tmp = rand() % n + 1;
    a[tmp] ^= 1;
    check();
  }
  std::cout << maxans << '\n';
}
```

## Example II

当一个算法的期望复杂度正确且与输入数据无关时，我们可以通过随机化达到期望上的平衡（就是随机卡不掉的意思

Treap 的随机很经典了，来一发可并堆

### 做法

可并堆最常用的写法应该是左偏树了，通过维护树高让树左偏来保证合并的复杂度。然而…… **维护树高什么的好烦啊** 。

那么我们可以考虑使用极其难卡的随机堆，即不按照树高来交换儿子，而是随机交换。

### 代码

```cpp
struct Node {
  int child[2];
  long long val;
} nd[100010];
int root[100010];

int merge(int u, int v) {
  if (!(u && v)) return u | v;
  int x = rand() & 1, p = nd[u].val > nd[v].val ? u : v;
  nd[p].child[x] = merge(nd[p].child[x], u + v - p);
  return p;
}

void pop(int &now) { now = merge(nd[now].child[0], nd[now].child[1]); }
```