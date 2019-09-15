字典树，英文名 Trie。顾名思义，就是一个像字典一样的树。

## 简介

先放一张图：

![trie1](./images/trie1.png)

可以发现，这棵字典树用边来代表字母，而从根结点到树上某一结点的路径就代表了一个字符串。举个例子， $1\to4\to 8\to 12$ 表示的就是字符串 `caa` 。

Trie 的结构非常好懂，我们用 $\delta(u,c)$ 表示结点 $u$ 的 $c$ 字符指向的下一个结点，或着说是结点 $u$ 代表的字符串后面添加一个字符 $c$ 形成的字符串的结点。（ $c$ 的取值范围和字符集大小有关，不一定是 $0\sim 26$ 。）

有时需要标记插入进 Trie 的是哪些字符串，每次插入完成时在这个字符串所代表的节点处打上标记即可。

## 代码实现

放一个结构体封装的模板：

```cpp
struct trie {
  int nex[100000][26], cnt;
  bool exist[100000];  // 该结点结尾的字符串是否存在

  void insert(char *s, int l) {  // 插入字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) nex[p][c] = ++cnt;  // 如果没有，就添加结点
      p = nex[p][c];
    }
    exist[p] = 1;
  }
  bool find(char *s, int l) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) return 0;
      p = nex[p][c];
    }
    return exist[p];
  }
};
```

## 应用

### 检索字符串

字典树最基础的应用——查找一个字符串是否在“字典”中出现过。

???+note "[于是他错误的点名开始了](https://www.luogu.org/problemnew/show/P2580)"
    给你 $n$ 个名字串，然后进行 $m$ 次点名，每次你需要回答“名字不存在”、“第一次点到这个名字”、“已经点过这个名字”之一。

    $1\le n\le 10^4$, $1\le m\le 10^5$，所有字符串长度不超过 $50$。

    ??? mdui-shadow-6 "题解"
        对所有名字建 Trie，再在 Trie 中查询字符串是否存在、是否已经点过名，第一次点名时标记为点过名。

    ??? mdui-shadow-6 "参考代码"
        ```cpp
        #include <cstdio>
        
        const int N = 500010;
        
        char s[60];
        int n, m, ch[N][26], tag[N], tot = 1;
        
        int main() {
          scanf("%d", &n);
        
          for (int i = 1; i <= n; ++i) {
            scanf("%s", s + 1);
            int u = 1;
            for (int j = 1; s[j]; ++j) {
              int c = s[j] - 'a';
              if (!ch[u][c]) ch[u][c] = ++tot;
              u = ch[u][c];
            }
            tag[u] = 1;
          }
        
          scanf("%d", &m);
        
          while (m--) {
            scanf("%s", s + 1);
            int u = 1;
            for (int j = 1; s[j]; ++j) {
              int c = s[j] - 'a';
              u = ch[u][c];
              if (!u) break;  // 不存在对应字符的出边说明名字不存在
            }
            if (tag[u] == 1) {
              tag[u] = 2;
              puts("OK");
            } else if (tag[u] == 2)
              puts("REPEAT");
            else
              puts("WRONG");
          }
        
          return 0;
        }
        ```

### AC 自动机

Trie 是 [AC 自动机](./ac-automaton.md) 的一部分。

### 异或相关

将数的二进制表示看做一个字符串，就可以建出字符集为 $\{0,1\}$ 的 Trie 树。

???+note "[BZOJ1954 最长异或路径](https://www.luogu.org/problem/P4551)"
    给你一棵带边权的树，求 $(u, v)$ 使得 $u$ 到 $v$ 的路径上的边权异或和最大，输出这个最大值。

    点数不超过 $10^5$，边权在 $[0,2^{31})$ 内。

    ??? mdui-shadow-6 "题解"
        随便指定一个根 $root$ ，用 $T(u, v)$ 表示 $u$ 和 $v$ 之间的路径的边权异或和，那么 $T(u,v)=T(root, u)\oplus T(root,v)$ ，因为 [LCA](../graph/lca.md) 以上的部分异或两次抵消了。

        那么，如果将所有 $T(root, u)$ 插入到一棵 Trie 中，就可以对每个 $T(root, u)$ 快速求出和它异或和最大的 $T(root, v)$ ：

        从 Trie 的根开始，如果能向和 $T(root, u)$ 的当前位不同的子树走，就向那边走，否则没有选择。

        贪心的正确性：如果这么走，这一位为 $1$ ；如果不这么走，这一位就会为 $0$ 。而高位是需要优先尽量大的。

    ??? mdui-shadow-6 "参考代码"
        ```cpp
        #include <algorithm>
        #include <cstdio>
        
        const int N = 100010;
        
        int head[N], nxt[N << 1], to[N << 1], weight[N << 1], cnt;
        int n, dis[N], ch[N << 5][2], tot = 1, ans;
        
        void insert(int x) {
          for (int i = 30, u = 1; i >= 0; --i) {
            int c = ((x >> i) & 1);
            if (!ch[u][c]) ch[u][c] = ++tot;
            u = ch[u][c];
          }
        }
        
        void get(int x) {
          int res = 0;
          for (int i = 30, u = 1; i >= 0; --i) {
            int c = ((x >> i) & 1);
            if (ch[u][c ^ 1]) {
              u = ch[u][c ^ 1];
              res |= (1 << i);
            } else
              u = ch[u][c];
          }
          ans = std::max(ans, res);
        }
        
        void add(int u, int v, int w) {
          nxt[++cnt] = head[u];
          head[u] = cnt;
          to[cnt] = v;
          weight[cnt] = w;
        }
        
        void dfs(int u, int fa) {
          insert(dis[u]);
          get(dis[u]);
          for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (v == fa) continue;
            dis[v] = dis[u] ^ weight[i];
            dfs(v, u);
          }
        }
        
        int main() {
          scanf("%d", &n);
        
          for (int i = 1; i < n; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
          }
        
          dfs(1, 0);
        
          printf("%d", ans);
        
          return 0;
        }
        ```

### 可持久化字典树

参见 [可持久化字典树](../ds/persistent-trie.md) 。
