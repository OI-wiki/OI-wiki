学习状压 dp 之前，请确认你已经完成了 [动态规划基础](./basic.md) 部分内容的学习。

（同时建议学习 [位运算](../math/bit.md) 部分的内容）

## 状压 DP 简介

状压 dp 是动态规划的一种，通过将状态压缩为整数来达到优化转移的目的。

## 例题

???+note "[「SCOI2005」互不侵犯](https://loj.ac/problem/2153)"
    在 $N\times N$ 的棋盘里面放 $K$ 个国王，使他们互不攻击，共有多少种摆放方案。国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各一个格子，共 $8$ 个格子。

我们用 $f(i,j,l)$ 表示只考虑前 $i$ 行，第 $i$ 行按照编号为 $j$ 的状态放置国王，且已经放置 $l$ 个国王时的方案数。

对于编号为 $j$ 的状态，我们用二进制整数 $sit(j)$ 表示国王的放置情况，$sit(j)$ 的某个二进制位为 $0$ 表示对应位置不放国王，为 $1$ 表示在对应位置上放置国王；用 $sta(j)$ 表示该状态的国王个数，即二进制数 $sit(j)$ 中 $1$ 的个数。例如，如下图所示的状态可用二进制数 $100101$ 来表示（棋盘左边对应二进制低位），则有 $sit(j)=100101_{(2)}=37, sta(j)=3$。

![](./images/SCOI2005-互不侵犯.png)

我们需要在刚开始的时候枚举出所有的合法状态（即排除同一行内两个国王相邻的不合法情况），并计算这些状态的 $sit(j)$ 和 $sta(j)$。

设上一行的状态编号为 $x$，在保证当前行和上一行不冲突的前提下，枚举所有可能的 $x$ 进行转移，转移方程：

$$
f(i,j,l) = \sum f(i-1,x,l-sta(j))
$$

??? "参考代码"
    ```cpp
    #include <algorithm>
    #include <iostream>
    using namespace std;
    long long sta[2005], sit[2005], f[15][2005][105];
    int n, k, cnt;
    void dfs(int x, int num, int cur) {
      if (cur >= n) {  // 有新的合法状态
        sit[++cnt] = x;
        sta[cnt] = num;
        return;
      }
      dfs(x, num, cur + 1);  // cur位置不放国王
      dfs(x + (1 << cur), num + 1,
          cur + 2);  // cur位置放国王，与它相邻的位置不能再放国王
    }
    bool compatible(int j, int x) {
      if (sit[j] & sit[x]) return false;
      if ((sit[j] << 1) & sit[x]) return false;
      if (sit[j] & (sit[x] << 1)) return false;
      return true;
    }
    int main() {
      cin >> n >> k;
      dfs(0, 0, 0);  // 先预处理一行的所有合法状态
      for (int j = 1; j <= cnt; j++) f[1][j][sta[j]] = 1;
      for (int i = 2; i <= n; i++)
        for (int j = 1; j <= cnt; j++)
          for (int x = 1; x <= cnt; x++) {
            if (!compatible(j, x)) continue;  // 排除不合法转移
            for (int l = sta[j]; l <= k; l++) f[i][j][l] += f[i - 1][x][l - sta[j]];
          }
      long long ans = 0;
      for (int i = 1; i <= cnt; i++) ans += f[n][i][k];  // 累加答案
      cout << ans << endl;
      return 0;
    }
    ```

## 习题

[NOI2001 炮兵阵地](https://loj.ac/problem/10173)

[「USACO06NOV」玉米田 Corn Fields](https://www.luogu.com.cn/problem/P1879)

[九省联考 2018 一双木棋](https://loj.ac/problem/2471)

[UVA10817 校长的烦恼 Headmaster's Headache](https://www.luogu.com.cn/problem/UVA10817)

[UVA1252 20 个问题 Twenty Questions](https://www.luogu.com.cn/problem/UVA1252)
