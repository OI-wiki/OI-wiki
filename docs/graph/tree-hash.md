我们有时需要判断一些树是否同构。这时，选择恰当的哈希方式来将树映射成一个便于储存的哈希值（一般是 32 位或 64 位整数）是一个优秀的方案。

树哈希有很多种哈希方式，下面将选出几种较为常用的方式来加以介绍。

## Method I

### Formula

$$
f_{now}=size_{now} \times \sum f_{son_{now,i}}\times seed^{i-1}
$$

#### Notes

其中 $f_x$ 为以节点 $x$ 为根的子树对应的哈希值。特殊地，我们令叶子节点的哈希值为 $1$ 。

 $size_{x}$ 表示以节点 $x$ 为根的子树大小。

 $son_{x,i}$ 表示 $x$ 所有子节点以 $f$ 作为关键字排序后排名第 $i$ 的儿子。

 $seed$ 为选定的一个合适的种子（最好是质数，对字符串 hash 有了解的人一定不陌生）

上述哈希过程中，可以适当取模避免溢出或加快运行速度。

## Method II

### Formula

$$
f_{now}=\bigoplus f_{son_{now,i}}\times seed+size_{son_{now,i}}
$$

#### Notes

其中 $f_x$ 为以节点 $x$ 为根的子树对应的哈希值。特殊地，我们令叶子节点的哈希值为 $1$ 。

 $size_{x}$ 表示以节点 $x$ 为根的子树大小。

 $son_{x,i}$ 表示 $x$ 所有子节点之一（不用排序）。

 $seed$ 为选定的一个合适的质数。

 $\large\bigoplus$ 表示异或和。

## Example

### Problem

 [Luogu P5403](https://www.luogu.org/problemnew/show/P5043) 

### Solution

我们用上述方式任选其一进行哈希，注意到我们求得的是子树的 hash 值，也就是说只有当根一样时同构的两棵子树 hash 值才相同。由于数据范围较小，我们可以暴力求出以每个点为根时的哈希值，排序后比较。

如果数据范围较大，我们可以通过找重心的方式来优化复杂度。（一棵树的重心最多只有两个，分别比较即可）

### Code

#### Method I

??? "例题参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    
    using i64 = long long;
    using u64 = unsigned long long;
    
    constexpr int maxT = 50;
    constexpr int maxn = 50;
    constexpr int SEED = 98243;
    constexpr int inf = 2147483647;
    
    inline int io() {
      static int _;
      return scanf("%d", &_), _;
    }
    
    template <class _Tp>
    inline _Tp Max(const _Tp x, const _Tp y) {
      return x > y ? x : y;
    }
    template <class _Tp>
    inline void chkMax(_Tp &x, const _Tp y) {
      (x < y) && (x = y);
    }
    template <class _Tp>
    inline void chkMin(_Tp &x, const _Tp y) {
      (x > y) && (x = y);
    }
    template <class _Tp>
    inline void swap(_Tp &x, _Tp &y) {
      _Tp z = x;
      x = y;
      y = z;
    }
    
    struct Edge {
      int v;
      Edge *las;
      inline Edge *init(const int to, Edge *const ls) {
        return v = to, las = ls, this;
      }
    } * las[maxn + 1], pool[maxn << 1], *alc = pool - 1;
    
    inline void lnk(const int u, const int v) {
      if (u == 0) return;
      las[u] = (++alc)->init(v, las[u]);
      las[v] = (++alc)->init(u, las[v]);
    }
    
    u64 hval[maxn + 1];
    void calc(const int u, const int fa) {
      static u64 lis[maxn + 1];
      static int sz[maxn + 1];
    
      /* DFS 时计算 size */
      sz[u] = 1;
      for (Edge *o = las[u]; o; o = o->las)
        if (o->v != fa) calc(o->v, u), sz[u] += sz[o->v];
    
      /* 将 u 各个儿子的哈希值排序 */
      int cnt = 0;
      for (Edge *o = las[u]; o; o = o->las)
        if (o->v != fa) lis[++cnt] = hval[o->v];
      std::sort(lis + 1, lis + cnt + 1);
    
      /* 计算 u 的哈希值 */
      u64 val = 0;
      for (int i = 1; i <= cnt; ++i) val = val * SEED + lis[i];
      hval[u] = val ? val * sz[u] : 1;
    }
    
    int sz[maxn + 1], mxsz[maxn + 1];
    void precalc(const int u, const int fa) {
      /* 找树的重心 */
      sz[u] = 1;
      mxsz[u] = 0;
      for (Edge *o = las[u]; o; o = o->las)
        if (o->v != fa) {
          precalc(o->v, u);
          sz[u] += sz[o->v];
          chkMax(mxsz[u], sz[o->v]);
        }
    }
    
    int main() {
      static int n[maxT + 1];
      static u64 val[maxT + 1][2];
    
      const int T = io();
      for (int i = 1; i <= T; ++i) {
        n[i] = io();
        for (int u = 1; u <= n[i]; ++u) lnk(io(), u);
    
        precalc(1, 0);
        int rtsz = inf, cnt = 0;
        for (int u = 1; u <= n[i]; ++u) chkMin(rtsz, Max(mxsz[u], n[i] - sz[u]));
        for (int u = 1; u <= n[i]; ++u)
          if (rtsz == Max(mxsz[u], n[i] - sz[u]))
            calc(u, 0), val[i][cnt++] = hval[u];
        /* 如果这个点是重心就计算其哈希值 */
    
        if (cnt == 2 && val[i][0] > val[i][1]) swap(val[i][0], val[i][1]);
    
        /* 清空数组 */
        for (int u = 1; u <= n[i]; ++u) las[u] = nullptr;
        alc = pool - 1;
      }
    
      for (int i = 1; i <= T; ++i) {
        bool flag = true;
        for (int j = 1; j != i; ++j)
          if (n[i] == n[j] && val[i][0] == val[j][0] && val[i][1] == val[j][1]) {
            /* 若树 j 与树 i 点数相同且重心哈希值相同，则其同构 */
            flag = false;
            printf("%d\n", j);
            break;
          }
        if (flag) printf("%d\n", i);
      }
    
      return 0;
    }
    ```

#### Method II

??? "例题参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <tr1/unordered_map>
    #include <vector>
    
    class Solution {
     private:
      typedef unsigned long long ull;
      typedef std::vector<int>::iterator it;
      static const ull seed = 2333233233;
      static const int maxn = 107;
    
      int n, m, size[maxn], lastRoot, root, lastMax, Max, ans;
      ull hashval[maxn], res;
      std::vector<int> e[maxn];
      std::tr1::unordered_map<ull, int> id;
    
      ull getHash(int now, int fa) {
        size[now] = 1;
        hashval[now] = 1;
        for (register it i = e[now].begin(); i != e[now].end(); ++i) {
          int v = *i;
          if (v == fa) {
            continue;
          }
          hashval[now] ^= getHash(v, now) * seed + size[v];
          size[now] += size[v];
        }
        return hashval[now];
      }
    
      void getRoot(int now, int fa) {
        int max = 0;
        size[now] = 1;
        for (register it i = e[now].begin(); i != e[now].end(); ++i) {
          int v = *i;
          if (v == fa) {
            continue;
          }
          getRoot(v, now);
          size[now] += size[v];
          max = std::max(max, size[v]);
        }
        max = std::max(max, n - size[now]);
        if (max < Max && now != lastRoot) {
          root = now;
          Max = max;
        }
      }
    
     public:
      Solution() {
        get();
        solve();
      }
    
      void get() {
        scanf("%d", &m);
        for (register int i = 1; i <= m; i++) {
          scanf("%d", &n);
          for (register int j = 1; j <= n; j++) {
            std::vector<int>().swap(e[j]);
          }
          for (register int j = 1, fa; j <= n; j++) {
            scanf("%d", &fa);
            if (!fa) {
              root = j;
            } else {
              e[fa].push_back(j);
              e[j].push_back(fa);
            }
          }
          lastRoot = root = 0;
          Max = n;
          getRoot(1, 0);
          lastRoot = root, lastMax = Max;
          res = getHash(root, 0);
          if (!id.count(res)) {
            id[res] = i;
          }
          ans = id[res];
    
          Max = n;
          getRoot(1, 0);
          if (lastMax == Max) {
            res = getHash(root, 0);
            if (!id.count(res)) {
              id[res] = i;
            }
            ans = std::min(ans, id[res]);
          }
          printf("%d\n", ans);
        }
      }
    
      void solve() {}
    };
    Solution sol;
    
    int main() {}
    ```

## At Last

事实上，树哈希是可以很灵活的，可以有各种各样奇怪的姿势来进行 hash，只需保证充分性与必要性，选手完全可以设计出与上述方式不同的 hash 方式。
