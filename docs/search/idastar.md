学习 IDA\*之前，请确保您已经学完了[A\*](/search/astar)算法和[迭代加深搜索](/search/iterative)。

## IDA\*简介

IDA\*，即采用迭代加深的 A\*算法。相对于 A\*算法，由于 IDA\*改成了深度优先的方式，所以 IDA\*更实用：

1.  不需要判重，不需要排序；
2.  空间需求减少。

**大致框架**（伪代码）：

```text
Procedure IDA_STAR(StartState)
Begin
PathLimit := H(StartState) - 1;
Succes := False;
Repeat
inc(PathLimit);
StartState.g = 0;
Push(OpenStack , StartState);
Repeat
CurrentState := Pop(OpenStack);
If Solution(CurrentState) then
Success = True
Elseif PathLimit >= CurrentState.g + H(CurrentState) then
For each Child(CurrentState) do
Push(OpenStack , Child(CurrentState));
until Successor empty(OpenStack);
until Success or ResourceLimtsReached;
end;
```

### 优点

1.  空间开销小，每个深度下实际上是一个深度优先搜索，不过深度有限制，而 DFS 的空间消耗小是众所周知的；
2.  利于深度剪枝。

### 缺点

重复搜索：回溯过程中每次 depth 变大都要再次从头搜索。

> 其实，前一次搜索跟后一次相差是微不足道的。

## 例题

??? note "埃及分数"**题目描述**

    在古埃及，人们使用单位分数的和（即 $\frac{1}{a}$，$a$ 是自然数）表示一切有理数。例如，$\frac{2}{3}=\frac{1}{2}+\frac{1}{6}$，但不允许 $\frac{2}{3}=\frac{1}{3}+\frac{1}{3}$，因为在加数中不允许有相同的。 

    对于一个分数 $\frac{a}{b}$ ，表示方法有很多种，其中加数少的比加数多的好，如果加数个数相同，则最小的分数越大越好。 例如，$\frac{19}{45}=\frac{1}{5}+\frac{1}{6}+\frac{1}{18}$ 是最优方案。 

    输入整数 $a,b$ （$0<a<b<500$），试编程计算最佳表达式。

    输入样例：

    ```text
    495 499
    ```

    输出样例：

    ```text
    Case 1: 495/499=1/2+1/5+1/6+1/8+1/3992+1/14970
    ```

**分析**

这道题目理论上可以用回溯法求解，但是**解答树**会非常“恐怖”—不仅深度没有明显的上界，而且加数的选择理论上也是无限的。换句话说，如果用宽度优先遍历，连一层都扩展不完，因为每一层都是**无限大**的。

解决方案是采用迭代加深搜索：从小到大枚举深度上限$maxd$，每次执行只考虑深度不超过$maxd$的节点。这样，只要解的深度优先，则一定可以在有限时间内枚举到。

深度上限$maxd$还可以用来**剪枝**。按照分母递增的顺序来进行扩展，如果扩展到 i 层时，前$i$个分数之和为$\frac{c}{d}$，而第$i$个分数为$\frac{1}{e}$，则接下来至少还需要$\frac{\frac{a}{b}-\frac{c}{d}}{\frac{1}{e}}$个分数，总和才能达到$\frac{a}{b}$。例如，当前搜索到$\frac{19}{45}=\frac{1}{5}+\frac{1}{100}+\cdots$，则后面的分数每个最大为$\frac{1}{101}$，至少需要$\frac{\frac{19}{45}-\frac{1}{5}}{\frac{1}{101}}=23$项总和才能达到$\frac{19}{45}$，因此前$22$次迭代是根本不会考虑这棵子树的。这里的关键在于：可以估计至少还要多少步才能出解。

注意，这里的估计都是乐观的，因为用了**至少**这个词。说得学术一点，设深度上限为$maxd$，当前结点$n$的深度为$g(n)$，乐观估价函数为$h(n)$，则当$g(n)+h(n)>maxd$时应该剪枝。这样的算法就是 IDA\*。当然，在实战中不需要严格地在代码里写出$g(n)$和$h(n)$，只需要像刚才那样设计出乐观估价函数，想清楚在什么情况下不可能在当前的深度限制下出解即可。

> 如果可以设计出一个乐观估价函数，预测从当前结点至少还需要扩展几层结点才有可能得到解，则迭代加深搜索变成了 IDA\*算法。

**代码**

```cpp
// 埃及分数问题
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int a, b, maxd;

typedef long long LL;

LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

// 返回满足1/c <= a/b的最小c
inline int get_first(LL a, LL b) { return b / a + 1; }

const int maxn = 100 + 5;

LL v[maxn], ans[maxn];

// 如果当前解v比目前最优解ans更优，更新ans
bool better(int d) {
  for (int i = d; i >= 0; i--)
    if (v[i] != ans[i]) {
      return ans[i] == -1 || v[i] < ans[i];
    }
  return false;
}

// 当前深度为d，分母不能小于from，分数之和恰好为aa/bb
bool dfs(int d, int from, LL aa, LL bb) {
  if (d == maxd) {
    if (bb % aa) return false;  // aa/bb必须是埃及分数
    v[d] = bb / aa;
    if (better(d)) memcpy(ans, v, sizeof(LL) * (d + 1));
    return true;
  }
  bool ok = false;
  from = max(from, get_first(aa, bb));  // 枚举的起点
  for (int i = from;; i++) {
    // 剪枝：如果剩下的maxd+1-d个分数全部都是1/i，加起来仍然不超过aa/bb，则无解
    if (bb * (maxd + 1 - d) <= i * aa) break;
    v[d] = i;
    // 计算aa/bb - 1/i，设结果为a2/b2
    LL b2 = bb * i;
    LL a2 = aa * i - bb;
    LL g = gcd(a2, b2);  // 以便约分
    if (dfs(d + 1, i + 1, a2 / g, b2 / g)) ok = true;
  }
  return ok;
}

int main() {
  int kase = 0;
  while (cin >> a >> b) {
    int ok = 0;
    for (maxd = 1; maxd <= 100; maxd++) {
      memset(ans, -1, sizeof(ans));
      if (dfs(0, get_first(a, b), a, b)) {
        ok = 1;
        break;
      }
    }
    cout << "Case " << ++kase << ": ";
    if (ok) {
      cout << a << "/" << b << "=";
      for (int i = 0; i < maxd; i++) cout << "1/" << ans[i] << "+";
      cout << "1/" << ans[maxd] << "\n";
    } else
      cout << "No solution.\n";
  }
  return 0;
}
```

## 练习题

[旋转游戏 UVa1343](https://www.luogu.org/problem/show?pid=uva1343)
