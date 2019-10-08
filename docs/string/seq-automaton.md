在阅读本文之前，请先阅读 [自动机](./automaton.md) 。

## 定义

序列自动机是接受且仅接受一个字符串的子序列的自动机。

本文中用 $s$ 代指这个字符串。

### 状态

若 $s$ 包含 $n$ 个字符，那么序列自动机包含 $n+1$ 个状态。

令 $t$ 是 $s$ 的一个子序列，那么 $\delta(start, t)$ 是 $t$ 在 $s$ 中第一次出现时末端的位置。

也就是说，一个状态 $i$ 表示前缀 $s[1..i]$ 的子序列与前缀 $s[1..i-1]$ 的子序列的差集。

序列自动机上的所有状态都是接受状态。

### 转移

由状态定义可以得到， $\delta(u, c)=\min\{i|i>u,s[i]=c\}$ ，也就是字符 $c$ 下一次出现的位置。

为什么是“下一次”出现的位置呢？因为若 $i>j$ ，后缀 $s[i..|s|]$ 的子序列是后缀 $s[j..|s|]$ 的子序列的子集，一定是选尽量靠前的最优。

## 构建

从后向前扫描，过程中维护每个字符最前的出现位置：

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{A string } S\\
2 & \textbf{Output. } \text{The state transition of the sequence automaton of }S \\
3 & \textbf{Method. }  \\
4 & \textbf{for }c\in\Sigma\\
5 & \qquad next[c]\gets null\\
6 & \textbf{for }i\gets|S|\textbf{ downto }1\\
7 & \qquad next[S[i]]\gets i\\
8 & \qquad \textbf{for }c\in\Sigma\\
9 & \qquad\qquad \delta(i-1,c)\gets next[c]\\
10 & \textbf{return }\delta
\end{array}
$$

这样构建的复杂度是 $O(n|\Sigma|)$ 。

## 例题

???+note "[「HEOI2015」最短不公共子串](https://loj.ac/problem/2123)"

    给你两个由小写英文字母组成的串 $A$ 和 $B$，求：

    1. $A$ 的一个最短的子串，它不是 $B$ 的子串；
    2. $A$ 的一个最短的子串，它不是 $B$ 的子序列；
    3. $A$ 的一个最短的子序列，它不是 $B$ 的子串；
    4. $A$ 的一个最短的子序列，它不是 $B$ 的子序列。

    $1\le |A|, |B|\le 2000$。

    ??? mdui-shadow-6 "题解"
        这题的 (1) 和 (3) 两问需要后缀自动机，而且做法类似，在这里只讲解 (2) 和 (4) 两问。

        (2) 比较简单，枚举 A 的子串输入进 B 的序列自动机，若不接受则计入答案。

        (4) 需要 DP。令 $f(i, j)$ 表示在 A 的序列自动机中处于状态 $i$ ，在 B 的序列自动机中处于状态 $j$ ，需要再添加多少个字符能够不是公共子序列。

        $f(i, null)=0$ 

        $f(i, j)=\min\limits_{\delta_A(i,c)\ne null}f(\delta_A(i, c), \delta_B(j, c))+1$ 

    ??? mdui-shadow-6 "参考代码"
        ```cpp
        #include <algorithm>
        #include <cstdio>
        #include <cstring>
        #include <iostream>
        
        using namespace std;
        
        const int N = 2005;
        
        char s[N], t[N];
        int na[N][26], nb[N][26], nxt[26];
        int n, m, a[N], b[N], tot = 1, p = 1, f[N][N << 1];
        
        struct SAM {
          int par, ch[26], len;
        } sam[N << 1];
        
        void insert(int x) {
          int np = ++tot;
          sam[np].len = sam[p].len + 1;
          while (p && !sam[p].ch[x]) {
            sam[p].ch[x] = np;
            p = sam[p].par;
          }
          if (p == 0)
            sam[np].par = 1;
          else {
            int q = sam[p].ch[x];
            if (sam[q].len == sam[p].len + 1)
              sam[np].par = q;
            else {
              int nq = ++tot;
              sam[nq].len = sam[p].len + 1;
              memcpy(sam[nq].ch, sam[q].ch, sizeof(sam[q].ch));
              sam[nq].par = sam[q].par;
              sam[q].par = sam[np].par = nq;
              while (p && sam[p].ch[x] == q) {
                sam[p].ch[x] = nq;
                p = sam[p].par;
              }
            }
          }
          p = np;
        }
        
        int main() {
          scanf("%s%s", s + 1, t + 1);
        
          n = strlen(s + 1);
          m = strlen(t + 1);
        
          for (int i = 1; i <= n; ++i) a[i] = s[i] - 'a';
          for (int i = 1; i <= m; ++i) b[i] = t[i] - 'a';
        
          for (int i = 1; i <= m; ++i) insert(b[i]);
        
          for (int i = 0; i < 26; ++i) nxt[i] = n + 1;
          for (int i = n; i >= 0; --i) {
            memcpy(na[i], nxt, sizeof(nxt));
            nxt[a[i]] = i;
          }
        
          for (int i = 0; i < 26; ++i) nxt[i] = m + 1;
          for (int i = m; i >= 0; --i) {
            memcpy(nb[i], nxt, sizeof(nxt));
            nxt[b[i]] = i;
          }
        
          int ans = N;
        
          for (int l = 1; l <= n; ++l) {
            for (int r = l, u = 1; r <= n; ++r) {
              u = sam[u].ch[a[r]];
              if (!u) {
                ans = min(ans, r - l + 1);
                break;
              }
            }
          }
        
          printf("%d\n", ans == N ? -1 : ans);
        
          ans = N;
        
          for (int l = 1; l <= n; ++l) {
            for (int r = l, u = 0; r <= n; ++r) {
              u = nb[u][a[r]];
              if (u == m + 1) {
                ans = min(ans, r - l + 1);
                break;
              }
            }
          }
        
          printf("%d\n", ans == N ? -1 : ans);
        
          for (int i = n; i >= 0; --i) {
            for (int j = 1; j <= tot; ++j) {
              f[i][j] = N;
              for (int c = 0; c < 26; ++c) {
                int u = na[i][c];
                int v = sam[j].ch[c];
                if (u <= n) f[i][j] = min(f[i][j], f[u][v] + 1);
              }
            }
          }
        
          printf("%d\n", f[0][1] == N ? -1 : f[0][1]);
        
          memset(f, 0, sizeof(f));
        
          for (int i = n; i >= 0; --i) {
            for (int j = 0; j <= m; ++j) {
              f[i][j] = N;
              for (int c = 0; c < 26; ++c) {
                int u = na[i][c];
                int v = nb[j][c];
                if (u <= n) f[i][j] = min(f[i][j], f[u][v] + 1);
              }
            }
          }
        
          printf("%d\n", f[0][0] == N ? -1 : f[0][0]);
        
          return 0;
        }
        ```
