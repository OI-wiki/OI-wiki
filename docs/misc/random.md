## 概述

随机化被广泛应用于 OI 中各种 **骗分** ， **偷懒** 的场景下。

当然，也有正经用途，例如：考场上造出随机数据然后对拍。

尤其是当算法期望复杂度正确且 **与输入数据无关** 时可用随机化使复杂度达到期望平衡，比如 Treap 和可并堆等。

## 实现

### rand

用于生成一个伪随机数，缺点是比较慢，使用时需要 `#include<cstdlib>` 。

使用 `rand()` 需要一个随机数种子，可以使用 `srand(seed)` 函数来将随机种子更改为 `seed` ，当然不初始化也是可以的。

相同的 `seed` 两次运行同一程序随机出的结果将会是相同的

有一个选择是使用当前系统时间来作为随机种子： `srand(time(0))` 。

调用 `rand()` 函数会返回一个随机非负整数。在 `Linux` 系统下随机范围为 $\left[0,2^{31}\right)$ 。可以用取模来限制它的大小。

!!! warning
    在 `Windows` 系统下 `rand()` 返回值的取值范围为 $\left[0,2^{15}\right)$ ，当需要生成的数不小于 $2^{15}$ 时建议使用 `(rand() << 15 | rand())` 来生成更大的随机数。

### mt19937

是一个随机数生成器类，效用同 `rand` ，优点是更加随机（出现循环的周期更长）且速度比 `rand()` 快很多。使用时需要 `#include<random>` 。

 `mt19937` 基于[Mersenne Twister algorithm](https://en.wikipedia.org/wiki/Mersenne_Twister)，使用时用其定义一个随机数生成器即可： `std::mt19937 myrand(seed)` ， `seed` 可不填，不填 `seed` 则会使用默认随机种子。

 `mt19937` 重载了 `operator ()` ，需要生成随机数时调用 `myrand()` 即可返回一个随机数。

#### 示例

    #include<ctime>
    #include<iostream>
    #include<random>
     
    using namespace std;
     
    int main()
    {
        mt19937 myrand(time(0));
        cout<<myrand()<<endl;
        return 0;
    }

### random_shuffle

用于随机打乱指定序列。使用时需要 `#include<algorithm>` 。

使用时传入指定区间的首尾指针或迭代器（左闭右开）即可： `std::random_shuffle(first, last)` 或 `std::random_shuffle(first, last, myrand)` 

内部使用的随机数生成器默认为 `rand()` 。当然也可以传入自定义的随机数生成器。

!!! warning `random_shuffle` 已于 C++14 标准中被弃用，于 C++17 标准中被移除。

### shuffle

效用同 `random_shuffle` 。使用时需要 `#include<algorithm>` 。

区别在于必须使用自定义的随机数生成器： `std::shuffle(first, last, myrand())` 。

下面是用 `rand()` 及 `random_shuffle()` 编写的一个数据生成器。生成数据为[「ZJOI2012」灾难](https://www.luogu.org/problemnew/show/P2597)的随机小数据。

```cpp
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

int a[100];

int main() {
  srand(time(0));
  int n = rand() % 99 + 1;
  for (int i = 1; i <= n; i++) a[i] = i;
  std::cout << n << '\n';
  for (int i = 1; i <= n; i++) {
    std::random_shuffle(a + 1, a + i);
    int cnt = rand() % i;
    for (int j = 1; j <= cnt; j++) std::cout << a[j] << ' ';
    std::cout << 0 << '\n';
  }
}
```

## Example I

先来看一道网络流题：[「TJOI2015」线性代数](https://www.lydsy.com/JudgeOnline/problem.php?id=3996)。

我们并不想写网络流，于是开始偷税。建模？不存在的。

### 做法

随机一个位置，把这个位置取反，判断大小并更新答案。

一直重复这个过程直到 TLE 前的最后一秒~~（那不就是没做 2333）~~，然后就 A 了。

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

Treap 的随机很经典了，来一发可并堆 ^\_^

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
