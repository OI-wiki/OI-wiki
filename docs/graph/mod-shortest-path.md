当出现形如“给定 $n$ 个整数，求这 $n$ 个整数能拼凑出多少的其他整数（ $n$ 个整数可以重复取）”，以及“给定 $n$ 个整数，求这 $n$ 个整数不能拼凑出的最小（最大）的整数”的问题时可以使用同余最短路的方法。

同余最短路利用同余来构造一些状态，可以达到优化空间复杂度的目的。

类比 [差分约束](./diff-constraints.md) 方法，利用同余构造的这些状态可以看作单源最短路中的点。同余最短路的状态转移通常是这样的 $f(i+y) = f(i) + y$ ，类似单源最短路中 $f(v) = f(u) +edge(u,v)$ 。

## 例题

???+note "[P3403 跳楼机](https://www.luogu.com.cn/problem/P3403)"
    题目大意：给定 $x，y，z，h$ ，对于 $k \in [1,h]$ ，有多少个 $k$ 能够满足 $ax+by+cz=k$ 。

不妨假设 $x < y < z$ 。

令 $d_i$ 为只通过 **操作 2** 和 **操作 3** 能够达到的最低楼层 $p$ ，并且满足 $p\bmod x=i$ 。

可以得到两个状态：

-  $i \xrightarrow{y} (i+y) \bmod x$ 

-  $i \xrightarrow{z} (i+z) \bmod x$ 

注意通常选取一组 $a_i$ 中最小的那个数对它取模，也就是此处的 $x$ ，这样可以尽量减小空间复杂度（剩余系最小）。

那么实际上相当于执行了最短路中的建边操作：

 `add(i, (i+y) % x, y)` 

 `add(i, (i+z) % x, z)` 

接下来只需要求出 $d_0, d_1, d_2, \dots, d_{x-1}$ ，只需要跑一次最短路就可求出相应的 $d_i$ 。答案即为：

$$
\sum_{i=0}^{x-1}\frac{h-d_i}{x} + 1
$$

加一是由于当前所在楼层也算一次。

???+note "参考实现"
    ```cpp
    #include <bits/stdc++.h>
    
    using namespace std;
    typedef long long ll;
    const int maxn = 100010;
    const int INF = 0x3f3f3f3f;
    
    ll h, x, y, z;
    ll head[maxn << 1], tot;
    ll dis[maxn], vis[maxn];
    queue<int> q;
    
    struct edge {
      ll to, next, w;
    } e[maxn << 1];
    
    void add(ll u, ll v, ll w) {
      e[++tot] = edge{v, head[u], w};
      head[u] = tot;
    }
    
    void spfa() {
      dis[1] = 1;
      vis[1] = 1;
      q.push(1);
      while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = head[u]; i; i = e[i].next) {
          int v = e[i].to, w = e[i].w;
          if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w;
            if (!vis[v]) {
              q.push(v);
              vis[v] = 1;
            }
          }
        }
      }
    }
    
    int main() {
      memset(dis, INF, sizeof(dis));
      scanf("%lld", &h);
      scanf("%lld %lld %lld", &x, &y, &z);
      if (x == 1 || y == 1 || z == 1) {
        printf("%d\n", h);
        return 0;
      }
      for (int i = 0; i < x; i++) {
        add(i, (i + z) % x, z);
        add(i, (i + y) % x, y);
      }
      spfa();
      ll ans = 0;
      for (int i = 0; i < x; i++) {
        if (h >= dis[i]) ans += (h - dis[i]) / x + 1;
      }
      printf("%lld\n", ans);
      return 0;
    }
    ```

## 习题

 [洛谷 P3403 跳楼机](https://www.luogu.com.cn/problem/P3403) 

 [洛谷 P2662 牛场围栏](https://www.luogu.com.cn/problem/P2662) 

 [\[国家集训队\]墨墨的等式](https://www.luogu.com.cn/problem/P2371) 

 [「NOIP2018」货币系统](https://loj.ac/problem/2951) 
