author: FFjet, ChungZH, frank-xjh, hsfzLZH1, Xarfa, AndrewWayne

本页面将简要介绍两种双向搜索算法：双向同时搜索和 Meet in the middle。

## 双向同时搜索

双向同时搜索的基本思路是从状态图上的起点和终点同时开始进行 [广搜](bfs.md) 或 [深搜](dfs.md) 。如果发现搜索的两端相遇了，那么可以认为是获得了可行解。

双向广搜的步骤：

```text
将开始结点和目标结点加入队列 q
标记开始结点为 1
标记目标结点为 2
while (队列 q 不为空)
{
  从 q.front() 扩展出新的 s 个结点
  
  如果 新扩展出的结点已经被其他数字标记过
    那么 表示搜索的两端碰撞
    那么 循环结束
  
  如果 新的 s 个结点是从开始结点扩展来的
    那么 将这个 s 个结点标记为 1 并且入队 q 
    
  如果 新的 s 个结点是从目标结点扩展来的
    那么 将这个 s 个结点标记为 2 并且入队 q
}
```

## Meet in the middle

???+warning
    本节要介绍的不是 [ **二分搜索** ](../basic/binary.md) （二分搜索的另外一个译名为“折半搜索”）。

Meet in the middle 算法没有正式译名，常见的翻译为「折半搜索」、「双向搜索」或「中途相遇」。它适用于输入数据较小，但还没小到能直接使用暴力搜索的情况。

主要思想是将整个搜索过程分成两半，分别搜索，最后将两半的结果合并。

暴力搜索的复杂度往往是指数级的，而改用 meet in the middle 算法后复杂度的指数可以减半，即让复杂度从 $O(a^b)$ 降到 $O(a^{b/2})$ 。

???+note "例题 [「USACO09NOV」灯 Lights](https://www.luogu.com.cn/problem/P2962)"
    有 $n$ 盏灯，每盏灯与若干盏灯相连，每盏灯上都有一个开关，如果按下一盏灯上的开关，这盏灯以及与之相连的所有灯的开关状态都会改变。一开始所有灯都是关着的，你需要将所有灯打开，求最小的按开关次数。
    
     $1\le n\le 35$ 。

??? note "解题思路"

    如果这道题暴力 DFS 找开关灯的状态，时间复杂度就是 $O(2^{n})$ , 显然超时。不过，如果我们用 meet in middle 的话，时间复杂度可以优化至 $O(n2^{n/2})$ 。 meet in middle 就是让我们先找一半的状态，也就是找出只使用编号为 $1$ 到 $\mathrm{mid}$ 的开关能够到达的状态，再找出只使用另一半开关能到达的状态。如果前半段和后半段开启的灯互补，将这两段合并起来就得到了一种将所有灯打开的方案。具体实现时，可以把前半段的状态以及达到每种状态的最少按开关次数存储在 map 里面，搜索后半段时，每搜出一种方案，就把它与互补的第一段方案合并来更新答案。

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <iostream>
    #include <map>
    
    using namespace std;
    
    typedef long long ll;
    
    int n, m, ans = 0x7fffffff;
    map<ll, int> f;
    ll a[40];
    
    int main() {
      cin >> n >> m;
    
      for (int i = 0; i < n; ++i) a[i] = (1ll << i);
    
      for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        a[u] |= (1ll << v);
        a[v] |= (1ll << u);
      }
    
      for (int i = 0; i < (1 << (n / 2)); ++i) {
        ll t = 0;
        int cnt = 0;
        for (int j = 0; j < n / 2; ++j) {
          if ((i >> j) & 1) {
            t ^= a[j];
            ++cnt;
          }
        }
        if (!f.count(t))
          f[t] = cnt;
        else
          f[t] = min(f[t], cnt);
      }
    
      for (int i = 0; i < (1 << (n - n / 2)); ++i) {
        ll t = 0;
        int cnt = 0;
        for (int j = 0; j < (n - n / 2); ++j) {
          if ((i >> j) & 1) {
            t ^= a[n / 2 + j];
            ++cnt;
          }
        }
        if (f.count(((1ll << n) - 1) ^ t))
          ans = min(ans, cnt + f[((1ll << n) - 1) ^ t]);
      }
    
      cout << ans;
    
      return 0;
    }
    ```

## 外部链接

-  [What is meet in the middle algorithm w.r.t. competitive programming? - Quora](https://www.quora.com/What-is-meet-in-the-middle-algorithm-w-r-t-competitive-programming) 
-  [Meet in the Middle Algorithm - YouTube](https://www.youtube.com/watch?v=57SUNQL4JFA) 
