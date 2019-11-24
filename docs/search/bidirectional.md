author: FFjet, ChungZH, frank-xjh, hsfzLZH1, Xarfa, AndrewWayne

### 双向同时搜索

从状态图上起点和终点同时开始进行宽度/深度优先搜索，如果发现相遇了，那么可以认为是获得了可行解。

双向广搜的步骤：

```text
开始结点 和 目标结点 入队列 q
标记开始结点为 1
标记目标结点为 2
while(队列q不为空)
{
  从 q.front() 扩展出新的s个结点
  
  如果 新扩展出的结点已经被其他数字标记过
    那么 表示搜索的两端碰撞
    那么 循环结束
  
  如果 新的s个结点是从开始结点扩展来的
    那么 将这个s个结点标记为1 并且入队q 
    
  如果 新的s个结点是从目标结点扩展来的
    那么 将这个s个结点标记为2 并且入队q
}
```

### 折半搜索

也称 meet in the middle，主要思想是将整个搜索过程分成两半，分别搜索，最后将两半的结果合并。由于搜索的复杂度往往是指数级的，而折半搜索可以使指数减半，也就能使复杂度开方。

???+note "例题 [「USACO09NOV」灯 Lights](https://www.luogu.org/problemnew/show/P2962)"

    有 $n$ 盏灯，每盏灯与若干盏灯相连，每盏灯上都有一个开关，如果按下一盏灯上的开关，这盏灯以及与之相连的所有灯的开关状态都会改变。一开始所有灯都是关着的，你需要将所有灯打开，求最小的按开关次数。

    $1\le n\le 35$。

如果这道题暴力 DFS 找开关灯的状态，时间复杂度就是 $O(2^{n})$ , 显然超时。不过，如果我们用 **meet-in-middle** 的话，时间复杂度可以优化至 $O(n2^{n/2})$ 。 **meet-in-middle** 就是让我们先找一半的状态，也就是找出只使用编号为 $1$ 到 $\mathrm{mid}$ 的开关能够到达的状态，再找出只使用另一半开关能到达的状态。如果前半段和后半段开启的灯互补，将这两段合并起来就得到了一种将所有灯打开的方案。具体实现时，可以把前半段的状态以及达到每种状态的最少按开关次数存储在 `map` 里面，搜索后半段时，每搜出一种方案，就把它与互补的第一段方案合并来更新答案。

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
