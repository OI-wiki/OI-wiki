author: mwsht, sshwy, ouuan, Ir1d, Henry-ZHR, hsfzLZH1

悬线法的适用范围是单调栈的子集。具体来说，悬线法可以应用于满足以下条件的题目：

- 需要在扫描序列时维护单调的信息；
- 可以使用单调栈解决；
- 不需要在单调栈上二分。

看起来悬线法可以被替代，用处不大，但是悬线法概念比单调栈简单，更适合初学 OI 的选手理解并解决最大子矩阵等问题。

???+note "[SP1805 HISTOGRA - Largest Rectangle in a Histogram](https://www.luogu.com.cn/problem/SP1805)"
    大意：在一条水平线上有 $n$ 个宽为 $1$ 的矩形，求包含于这些矩形的最大子矩形面积。

悬线，就是一条竖线，这条竖线有初始位置和高度两个性质，可以在其上端点不超过当前位置的矩形高度的情况下左右移动。

对于一条悬线，我们在这条上端点不超过当前位置的矩形高度且不移出边界的前提下，将这条悬线左右移动，求出其最多能向左和向右扩展到何处，此时这条悬线扫过的面积就是包含这条悬线的尽可能大的矩形。容易发现，最大子矩形必定是包含一条初始位置为 $i$ ，高度为 $h_i$ 的悬线。枚举实现这个过程的时间复杂度为 $O(n ^ 2)$ ，但是我们可以用悬线法将其优化到 $O(n)$ 。

我们考虑如何快速找到悬线可以到达的最左边的位置。

定义 $l_i$ 为当前找到的 $i$ 位置的悬线能扩展到的最左边的位置，容易得到 $l_i$ 初始为 $i$ ，我们需要进一步判断还能不能进一步往左扩展。

- 如果当前 $l_i = 1$ ，则已经扩展到了边界，不可以。
- 如果当前 $a_i > a_{l_i - 1}$ ，则从当前悬线扩展到的位置不能再往左扩展了。
- 如果当前 $a_i \le a_{l_i - 1}$ ，则从当前悬线还可以往左扩展，并且 $l_i - 1$ 位置的悬线能向左扩展到的位置， $i$ 位置的悬线一定也可以扩展到，于是我们将 $l_i$ 更新为 $l_{l_i - 1}$ ，并继续执行判断。

通过摊还分析，可以证明每个 $l_i$ 最多会被其他的 $l_j$ 遍历到一次，因此时间复杂度为 $O(n)$ 。

??? 参考代码
    ```cpp
    #include <algorithm>
    #include <cstdio>
    using std::max;
    const int N = 100010;
    int n, a[N];
    int l[N], r[N];
    long long ans;
    int main() {
      while (scanf("%d", &n) != EOF && n) {
        ans = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]), l[i] = r[i] = i;
        for (int i = 1; i <= n; i++)
          while (l[i] > 1 && a[i] <= a[l[i] - 1]) l[i] = l[l[i] - 1];
        for (int i = n; i >= 1; i--)
          while (r[i] < n && a[i] <= a[r[i] + 1]) r[i] = r[r[i] + 1];
        for (int i = 1; i <= n; i++)
          ans = max(ans, (long long)(r[i] - l[i] + 1) * a[i]);
        printf("%lld\n", ans);
      }
      return 0;
    }
    ```

???+note "[UVA1619 感觉不错 Feel Good](https://www.luogu.com.cn/problem/UVA1619)"
    对于一个长度为 $n$ 的数列，找出一个子区间，使子区间内的最小值与子区间长度的乘积最大，要求在满足舒适值最大的情况下最小化长度，最小化长度的情况下最小化左端点序号。

本题中我们可以考虑枚举最小值，将每个位置的数 $a_i$ 当作最小值，并考虑从 $i$ 向左右扩展，找到满足 $\min\limits _ {j = l} ^ r a_j = a_i$ 的尽可能向左右扩展的区间 $[l, r]$ 。这样本题就被转化成了悬线法模型。

??? 参考代码
    ```cpp
    #include <cstdio>
    #include <cstring>
    const int N = 100010;
    int n, a[N], l[N], r[N];
    long long sum[N];
    long long ans;
    int ansl, ansr;
    bool fir = 1;
    int main() {
      while (scanf("%d", &n) != EOF) {
        memset(a, -1, sizeof(a));
        if (!fir)
          printf("\n");
        else
          fir = 0;
        ans = 0;
        ansl = ansr = 1;
        for (int i = 1; i <= n; i++) {
          scanf("%d", &a[i]);
          sum[i] = sum[i - 1] + a[i];
          l[i] = r[i] = i;
        }
        for (int i = 1; i <= n; i++)
          while (a[l[i] - 1] >= a[i]) l[i] = l[l[i] - 1];
        for (int i = n; i >= 1; i--)
          while (a[r[i] + 1] >= a[i]) r[i] = r[r[i] + 1];
        for (int i = 1; i <= n; i++) {
          long long x = a[i] * (sum[r[i]] - sum[l[i] - 1]);
          if (ans < x || (ans == x && ansr - ansl > r[i] - l[i]))
            ans = x, ansl = l[i], ansr = r[i];
        }
        printf("%lld\n%d %d\n", ans, ansl, ansr);
      }
      return 0;
    }
    ```

## 最大子矩形

???+note "[P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147)"
    给定一个 $n \times m$ 的包含 `'F'` 和 `'R'` 的矩阵，求其面积最大的子矩阵的面积 $\times 3$ ，使得这个子矩阵中的每一位的值都为 `'F'` 。

我们会发现本题的模型和第一题的模型很像。仔细分析，发现如果我们每次只考虑某一行的所有元素，将位置 $(x, y)$ 的元素尽可能向上扩展的距离作为该位置的悬线长度，那最大子矩阵一定是这些悬线向左右扩展得到的尽可能大的矩形中的一个。

??? 参考代码
    ```cpp
    #include <algorithm>
    #include <cstdio>
    int m, n, a[1010], l[1010], r[1010], ans;
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) {
        char s[3];
        for (int j = 1; j <= m; j++) {
          scanf("%s", s);
          if (s[0] == 'F')
            a[j]++;
          else if (s[0] == 'R')
            a[j] = 0;
        }
        for (int j = 1; j <= m; j++)
          while (a[l[j] - 1] >= a[j]) l[j] = l[l[j] - 1];
        for (int j = m; j >= 1; j--)
          while (a[r[j] + 1] >= a[j]) r[j] = r[r[j] + 1];
        for (int j = 1; j <= m; j++) ans = std::max(ans, (r[j] + l[j] - 1) * a[j]);
      }
      printf("%d", ans * 3);
      return 0;
    }
    ```

## 习题

-  [P1169「ZJOI2007」棋盘制作](https://www.luogu.com.cn/problem/P1169) 
