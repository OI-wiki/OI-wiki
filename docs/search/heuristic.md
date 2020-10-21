本页面将简要介绍启发式搜索及其用法。

## 简介

启发式搜索（英文：heuristic search）是一种改进的搜索算法。它在普通搜索算法的基础上引入了启发式函数，该函数的作用是基于已有的信息对搜索的每一个分支选择都做估价，进而选择分支。简单来说，启发式搜索就是对取和不取都做分析，从中选取更优解或删去无效解。

## 例题

由于概念过于抽象，这里使用例题讲解。

???+note "[「NOIP2005 普及组」采药](https://www.luogu.com.cn/problem/P1048)"
    题目大意：有 $N$ 种物品和一个容量为 $W$ 的背包，每种物品有重量 $w_i$ 和价值 $v_i$ 两种属性，要求选若干个物品（每种物品只能选一次）放入背包，使背包中物品的总价值最大，且背包中物品的总重量不超过背包的容量。

??? note "解题思路"

    我们写一个估价函数 $f$ ，可以剪掉所有无效的 $0$ 枝条（就是剪去大量无用不选枝条）。

    估价函数 $f$ 的运行过程如下：

    我们在取的时候判断一下是不是超过了规定体积（可行性剪枝）；在不取的时候判断一下不取这个时，剩下的药所有的价值 + 现有的价值是否大于目前找到的最优解（最优性剪枝）。

??? note "示例代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    using namespace std;
    const int N = 105;
    int n, m, ans;
    struct Node {
      int a, b;  // a 代表时间，b 代表价值
      double f;
    } node[N];
    
    bool operator<(Node p, Node q) { return p.f > q.f; }
    
    int f(int t, int v) {
      int tot = 0;
      for (int i = 1; t + i <= n; i++)
        if (v >= node[t + i].a) {
          v -= node[t + i].a;
          tot += node[t + i].b;
        } else
          return (int)(tot + v * node[t + i].f);
      return tot;
    }
    
    void work(int t, int p, int v) {
      ans = max(ans, v);
      if (t > n) return;
      if (f(t, p) + v > ans) work(t + 1, p, v);
      if (node[t].a <= p) work(t + 1, p - node[t].a, v + node[t].b);
    }
    
    int main() {
      scanf("%d %d", &m, &n);
      for (int i = 1; i <= n; i++) {
        scanf("%d %d", &node[i].a, &node[i].b);
        node[i].f = 1.0 * node[i].b / node[i].a;
      }
      sort(node + 1, node + n + 1);
      work(1, m, 0);
      printf("%d\n", ans);
      return 0;
    }
    ```
