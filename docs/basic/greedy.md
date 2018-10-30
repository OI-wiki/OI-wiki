贪心算法顾名思义就是用计算机来模拟一个 “贪心” 的人做出决策的过程。

这个人每一步行动总是按某种指标选取最优的操作，他总是 ** 只看眼前，并不考虑以后可能造成的影响 ** 。

可想而知，并不是所有的时候贪心法都能获得最优解，所以一般使用贪心法的时候，都要确保自己能证明其正确性。

## 常见做法

在提高组难度以下的题目中，最常见的贪心有两种。一种是：「我们将 XXX 按照某某顺序排序，然后按某种顺序（例如从小到大）处理」。另一种是：「我们每次都取 XXX 中最大 / 小的东西，并更新 XXX」，有时「XXX 中最大 / 小的东西」可以优化，比如用优先队列维护。

为啥分成两种？你可以发现，一种是离线的，一种是在线的。

## 证明方法

~~从来都是大胆猜想，从来不会小心求证~~

以下套路请按照题目自行斟酌，一般情况下一道题只会用到其中的一种方法来证明。

1. 运用反证法，如果交换方案中任意两个元素 / 相邻的两个元素后，答案不会变得更好，那么可以发现目前的解已经是最优解了。
2. 运用归纳法，先手算得出边界情况（例如 $n = 1$ ）的最优解 $F_1$ ，然后再证明：对于每个 $n$ ，$F_{n+1}$ 都可以由 $F_{n}$ 推导出结果。

## [排序法](https://goldimax.github.io/atricle.html?5b82a0a49f54540031c06bd8)

用排序法常见的情况是输入一个包含几个（一般一到两个）权值的数组，通过排序然后遍历模拟计算的方法求出最优值。

有些题的排序方法非常显然，如 [ luogu P1209 ](https://www.luogu.org/problemnew/show/P1209) 就是将输入数组差分后排序模拟求值。

然而有些时候很难直接一下子看出排序方法，比如 [ luogu P1080 ](https://www.luogu.org/problemnew/show/P1080) 就很容易凭直觉而错误地以 $a$ 或 $b$ 为关键字排序，过样例之后提交就发现 WA 了 QAQ。一个 ~~众所周知的~~ 常见办法就是尝试交换数组相邻的两个元素来**推导**出正确的排序方法。我们假设这题输入的俩个数用一个结构体来保存

```c++
struct {
  int a, b;
} v[n];
```

用 $m$ 表示 $i$ 前面所有的 $a$ 的乘积，那么第 $i$ 个大臣得到的奖赏就是 

$$
\frac{m} {v[i].b}
$$

第 $i + 1$ 个大臣得到的奖赏就是 

$$
\frac{m \cdot v[i].a} {v[i + 1].b}
$$

如果我们交换第 $i$ 个大臣与第 $i + 1$ 个大臣的位置，那么第 $i + 1$ 个大臣得到的奖赏就是 

$$
\frac{m} {v[i + 1].b}
$$

第 $i + 1$ 个大臣得到的奖励就是 

$$
\frac{m \cdot v[i + 1].a} {v[i].b}
$$

如果交前更优当且仅当 

$$
\max (\frac{m} {v[i].b}, \frac{m \times v[i].a} {v[i + 1].b})  < \max (\frac{m} {v[i + 1].b}, \frac{m \times v[i + 1].a} {v[i].b})
$$

提取出相同的 $m$ 并约分得到 

$$
\max(\frac{1} {v[i].b}, \frac{v[i].a} {v[i + 1].b}) < \max(\frac{1} {v[i + 1].b}, \frac{v[i + 1].a} {v[i].b})
$$

然后分式化成整式得到 

$$
\max(v[i + 1].b, v[i].a \times v[i].b) < \max(v[i].b, v[i + 1].a \times v[i + 1].b)
$$

于是我们就成功得到排序函数了！

```c++
struct uv {
  int a, b;
  bool operator<(const uv &x) const {
    return max(x.b, a * b) < max(b, x.a * x.b);
  }
};
```

~~看上去是不是很简单呢（这题高精度卡常……）~~ ，如果看懂了就可以尝试下一道类似的题 [luogu P2123](https://www.luogu.org/problemnew/show/P2123)（请不要翻题解……。

## 后悔法

??? note " 例题 [luogu P2949 \[USACO09OPEN\] 工作调度 Work Scheduling ](https://www.luogu.org/problemnew/show/P2949)"

贪心思想：

- **1** . 先假设每一项工作都做，将各项工作按截止时间排序后入队。      
- **2** . 在判断第 i 项工作做与不做时，若其截至时间符合条件，则将其与队中报酬最小的元素比较，若第 i 项工作报酬较高（后悔），则 ans+=a[i].p-q.top()。      

**PS** ： 用优先队列（小根堆）来维护队首元素最小。          

### code:

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
struct f {
  long long d;
  long long x;
} a[100005];
bool cmp(f A, f B) { return A.d < B.d; }
priority_queue<long long, vector<long long>, greater<long long> > q;
int main() {
  long long n, i, j;
  cin >> n;
  for (i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].d, &a[i].x);
  }
  sort(a + 1, a + n + 1, cmp);
  long long ans = 0;
  for (i = 1; i <= n; i++) {
    if (a[i].d <= q.size()) {
      if (q.top() < a[i].x) {
        ans += a[i].x - q.top();
        q.pop();
        q.push(a[i].x);
      }
    } else {
      ans += a[i].x;
      q.push(a[i].x);
    }
  }
  cout << ans << endl;
  return 0;
}
```
