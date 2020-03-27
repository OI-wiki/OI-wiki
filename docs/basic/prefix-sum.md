## 前缀和

前缀和是一种重要的预处理，能大大降低查询的时间复杂度。我们可以简单理解为“数列的前 n 项的和”。

!!! 例题
    有 N 个的正整数放到数组 A 里，现在要求一个新的数组 B，新数组的第 i 个数 B[i]是原数组 A 第 0 到第 i 个数的和。

对于这道题，我们有两种做法：

-   把对数组 A 的累加依次放入数组 B 中。
-   递推： `B[i] = B[i-1] + A[i]` ，前提 `B[0] = A[0]` 。

参考程序：

```cpp
#include <iostream>

using namespace std;

int N, A[10000], B[10000];
int main() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }

  B[0] = A[0];

  for (int i = 1; i < N; i++) {
    B[i] = B[i - 1] + A[i];
  }

  for (int i = 0; i < N; i++) {
    cout << B[i] << " ";
  }

  return 0;
}
```

输入：

    5
    1 2 3 4 5

输出：

    1 3 6 10 15 

首先， `B[0] = A[0];` ，前缀和数组的第一项和原数组的第一项是相等的。

 `B[i] = B[i-1] + A[i]` 意思就是：前缀和数组的第 i 项 = 原数组的 0 到 i-1 项的和 + 原数组的第 i 项。

### 习题

-    [洛谷 U53525 前缀和（例题）](https://www.luogu.org/problemnew/show/U53525) 
-    [洛谷 U69096 前缀和的逆](https://www.luogu.org/problemnew/show/U69096) 
-    [AT2412 最大の和](https://www.luogu.org/problemnew/show/AT2412) 
-    [「USACO16JAN」子共七 Subsequences Summing to Sevens](https://www.luogu.org/problemnew/show/P3131) 

### 参考

感谢南海区青少年信息学奥林匹克内部训练教材。

## 二维/多维前缀和

其实前缀和几乎都是基于容斥原理，所以各种拓展自己手推一下就行了。  
这里用二维前缀和为例讲解一下前缀和扩展到多维的方式。

比如我们有这样一个矩阵 $a$ ，可以视为二维数组：

```plain
1 2 4 3
5 1 2 4
6 3 5 9
```

我们定义一个矩阵 $sum$ ， $sum_{x,y} = \sum\limits_{i=1}^x \sum\limits_{j=1}^y a_{i,j}$ ，  
那么这个矩阵长这样：

```plain
1 3 7 10
6 9 15 22
12 18 29 45
```

第一个问题就是递推求 $sum$ 的过程， $sum_{i,j} = sum_{i - 1,j} + sum_{i,j - 1} - sum_{i - 1,j - 1} + a_{i,j}$ 。  
因为加了 $sum_{i - 1,j}$ 和 $sum_{i,j - 1}$ 重复了 $sum_{i - 1,j - 1}$ ，所以减去。

第二个问题就是如何应用，譬如求 $(x1,y1) - (x2,y2)$ 子矩阵的和。  
那么，根据类似的思考过程，易得答案为 $sum_{x2,y2} - sum_{x1 - 1,y2} - sum_{x2,y1 - 1} + sum_{x1 - 1,y1 - 1}$ 。

下面给出 [洛谷 P1387 最大正方形](https://www.luogu.org/problemnew/show/P1387) 这道题目的参考程序来帮助大家理解二维前缀和。

```cpp
#include <algorithm>
#include <iostream>
using namespace std;
int a[103][103];
int b[103][103];  // 前缀和数组，相当于上文的 sum[]
int main() {
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      b[i][j] =
          b[i][j - 1] + b[i - 1][j] - b[i - 1][j - 1] + a[i][j];  // 求前缀和
    }
  }

  int ans = 1;

  int l = 2;
  while (l <= min(n, m)) {
    for (int i = l; i <= n; i++) {
      for (int j = l; j <= m; j++) {
        if (b[i][j] - b[i - l][j] - b[i][j - l] + b[i - l][j - l] == l * l) {
          ans = max(ans, l);
        }
      }
    }
    l++;
  }

  cout << ans << endl;
  return 0;
}
```

### 习题

-    [CodeVS 1373. 射命丸文](http://www.joyoi.cn/problem/codevs-1373) 
-    [洛谷 P1387 最大正方形](https://www.luogu.com.cn/problem/P1387) 
-    [「HNOI2003」激光炸弹](https://www.luogu.com.cn/problem/P2280) 

### 基于 DP 计算高维前缀和

前一节方法本质上是基于容斥原理来计算高维前缀和，其优点在于形式较为简单，无需特别记忆，但当维数升高时，其复杂度较高。这里介绍一种基于 DP 计算高维前缀和的方法。该方法即通常语境中所称的 **高维前缀和** 。

设高维空间 $U$ 共有 $D$ 维，需要对 $f[\cdot]$ 求高维前缀和 $\text{sum}[\cdot]$ 。令 $\text{sum}[i][\text{state}]$ 表示同 $\text{state}$ 后 $D - i$ 维相同的所有点对于 $\text{state}$ 点高维前缀和的贡献。由定义可知 $\text{sum}[0][\text{state}] = f[\text{state}]$ ，以及 $\text{sum}[\text{state}] = \text{sum}[D][\text{state}]$ 。

其递推关系为 $\text{sum}[i][\text{state}] = \text{sum}[i - 1][\text{state}] + \text{sum}[i][\text{state}']$ ，其中 $\text{state}'$ 为第 $i$ 维恰好比 $\text{state}$ 少 $1$ 的点。该方法的复杂度为 $O(D \times |U|)$ ，其中 $|U|$ 为高维空间 $U$ 的大小。

其一种实现的伪代码如下：

    for state
    	sum[state] = f[state];
    for(i = 0;i <= D;i += 1)
    	for 以字典序从小到大枚举 state
    		sum[state] += sum[state'];

## 树上前缀和

设 $sum_i$ 表示结点 $i$ 到根节点的权值总和。  
然后若是点权， $x,y$ 路径上的和为 $sum_x + sum_y - sum_{lca} - sum_{fa_{lca}}$ ；  
否则若是边权， $x,y$ 路径上的和为 $sum_x + sum_y - 2sum_{lca}$ 。

至于 lca 的求法请移步 [最近公共祖先](../graph/lca.md) 。

### 习题

-    [LOJ 10134.Dis](https://loj.ac/problem/10134) 
-    [LOJ 2491. 求和](https://loj.ac/problem/2491) 

## 差分

差分，是一种和前缀和相对的策略。  
这种策略是，令 $b_i = a_i - a_{i - 1}$ ，即相邻两数的差。  
易得对这个序列做一遍前缀和就得到了原来的 $a$ 序列。

它可以维护多次对序列的一个区间加上一个数，并在最后询问某一位的数或是多次询问某一位的数。（总之修改操作一定要在查询操作之前）  
具体怎么搞？譬如使 $[l,r]$ 每个数加上一个 $k$ ，就是 $b_l \leftarrow b_l + k,b_{r + 1} \leftarrow b_{r + 1} - k$ 。  
最后做一遍前缀和就好了。

### 习题

-    [树状数组 3：区间修改，区间查询](https://loj.ac/problem/132) 
-    [P3397 地毯](https://www.luogu.com.cn/problem/P3397) 
-    [「Poetize6」IncDec Sequence](https://www.luogu.com.cn/problem/P4552) 

## 树上差分

我以前一直以为树上差分也是树上前缀和相对的策略，但是不知道怎么搞。

后来发现还是有点区别的。

至少人家是基于子树和而非到根的和。

如果使 $x,y$ 路径上的点权增加 $k$ ， $b_x \leftarrow b_x + k,b_y \leftarrow b_y + k,b_{lca} \leftarrow b_{lca} - k,b_{fa_{lca}} \leftarrow b_{fa_{lca}} - k$ ，
如果是边权， $b_x \leftarrow b_x + k,b_y \leftarrow b_y + k,b_{lca} \leftarrow b_{lca} - 2k$ 。

然后一遍搜索求一下子树和答案就出来了。

### 习题

-    [洛谷 3128. 最大流](https://www.luogu.org/problemnew/show/P3128) 
