本页面将简要介绍如何用 Splay 维护二叉查找树。

## 定义

**Splay 树**, 或 **伸展树**，是一种平衡二叉查找树，它通过 **Splay/伸展操作** 不断将某个节点旋转到根节点，使得整棵树仍然满足二叉查找树的性质，能够在均摊 $O(\log N)$ 时间内完成插入，查找和删除操作，并且保持平衡而不至于退化为链。

Splay 树由 Daniel Sleator 和 Robert Tarjan 于 1985 年发明。

## 结构

### 二叉查找树的性质

Splay 树是一棵二叉搜索树，查找某个值时满足性质：左子树任意节点的值 $<$ 根节点的值 $<$ 右子树任意节点的值。

### 节点维护信息

|   rt  |  tot | fa\[i] | ch\[i]\[0/1] | val\[i] | cnt\[i] | sz\[i] |
| :---: | :--: | :----: | :----------: | :-----: | :-----: | :----: |
| 根节点编号 | 节点个数 |   父亲   |    左右儿子编号    |   节点权值  |  权值出现次数 |  子树大小  |

## 操作

### 基本操作

-   `maintain(x)`：在改变节点位置后，将节点 $x$ 的 $\text{size}$ 更新。
-   `get(x)`：判断节点 $x$ 是父亲节点的左儿子还是右儿子。
-   `clear(x)`：销毁节点 $x$。

???+ note "实现"
    ```cpp
    void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }
    
    bool get(int x) { return x == ch[fa[x]][1]; }
    
    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0; }
    ```

### 旋转操作

为了使 Splay 保持平衡而进行旋转操作，旋转的本质是将某个节点上移一个位置。

**旋转需要保证**：

-   整棵 Splay 的中序遍历不变（不能破坏二叉查找树的性质）。
-   受影响的节点维护的信息依然正确有效。
-   `root` 必须指向旋转后的根节点。

在 Splay 中旋转分为两种：左旋和右旋。

![](./images/splay-rotate.svg)

#### 过程

**具体分析旋转步骤**（假设需要旋转的节点为 $x$，其父亲为 $y$，以右旋为例）

1.  将 $y$ 的左儿子指向 $x$ 的右儿子，且 $x$ 的右儿子（如果 $x$ 有右儿子的话）的父亲指向 $y$；`ch[y][0]=ch[x][1]; fa[ch[x][1]]=y;`
2.  将 $x$ 的右儿子指向 $y$，且 $y$ 的父亲指向 $x$；`ch[x][chk^1]=y; fa[y]=x;`
3.  如果原来的 $y$ 还有父亲 $z$，那么把 $z$ 的某个儿子（原来 $y$ 所在的儿子位置）指向 $x$，且 $x$ 的父亲指向 $z$。`fa[x]=z; if(z) ch[z][y==ch[z][1]]=x;`

#### 实现

```cpp
void rotate(int x) {
  int y = fa[x], z = fa[y], chk = get(x);
  ch[y][chk] = ch[x][chk ^ 1];
  if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
  ch[x][chk ^ 1] = y;
  fa[y] = x;
  fa[x] = z;
  if (z) ch[z][y == ch[z][1]] = x;
  maintain(y);
  maintain(x);
}
```

### Splay 操作

Splay 操作规定：每访问一个节点 $x$ 后都要强制将其旋转到根节点。

Splay 操作即对 $x$ 做一系列的 **splay 步骤**。每次对 $x$ 做一次 splay 步骤，$x$ 到根节点的距离都会更近。定义 $p$ 为 $x$ 的父节点。Splay 步骤有三种，具体分为六种情况：

1.  **zig**: 在 $p$ 是根节点时操作。Splay 树会根据 $x$ 和 $p$ 间的边旋转。$zig$ 存在是用于处理奇偶校验问题，仅当 $x$ 在 splay 操作开始时具有奇数深度时作为 splay 操作的最后一步执行。

    ![splay-zig](./images/splay-zig.svg)

    即直接将 $x$ 左旋或右旋（图 1, 2）

    ![图 1](./images/splay-rotate1.svg)

    ![图 2](./images/splay-rotate2.svg)

2.  **zig-zig**: 在 $p$ 不是根节点且 $x$ 和 $p$ 都是右侧子节点或都是左侧子节点时操作。下方例图显示了 $x$ 和 $p$ 都是左侧子节点时的情况。Splay 树首先按照连接 $p$ 与其父节点 $g$ 边旋转，然后按照连接 $x$ 和 $p$ 的边旋转。

    ![splay-zig-zig](./images/splay-zig-zig.svg)

    即首先将 $g$ 左旋或右旋，然后将 $x$ 右旋或左旋（图 3, 4）。

    ![图 3](./images/splay-rotate3.svg)

    ![图 4](./images/splay-rotate4.svg)

3.  **zig-zag**: 在 $p$ 不是根节点且 $x$ 和 $p$ 一个是右侧子节点一个是左侧子节点时操作。Splay 树首先按 $p$ 和 $x$ 之间的边旋转，然后按 $x$ 和 $g$ 新生成的结果边旋转。

    ![splay-zig-zag](./images/splay-zig-zag.svg)

    即将 $x$ 先左旋再右旋、或先右旋再左旋（图 5, 6）。

    ![图 5](./images/splay-rotate5.svg)

    ![图 6](./images/splay-rotate6.svg)

    ??? tip
        请读者尝试自行模拟 $6$ 种旋转情况，以理解 Splay 的基本思想。

#### 实现

```cpp
void splay(int x) {
  for (int f = fa[x]; f = fa[x], f; rotate(x))
    if (fa[f]) rotate(get(x) == get(f) ? f : x);
  rt = x;
}
```

#### Splay 操作的时间复杂度

因为 zig 和 zag 是 **对称** 操作，我们只需要对 zig，zig−zig，zig−zag 操作分析复杂度。采用 [势能分析](../basic/complexity.md#势能分析)，定义一个 $n$ 个节点的 splay 树进行了 $m$ 次 splay 步骤。可记 $w(x)=[\log(\operatorname{size}(x))]$, 定义势能函数为 $\varphi =\sum w(x)$,$\varphi (0) \leq n \log n$，在第 $i$ 次操作后势能为 $\varphi (i)$, 则我们只需要求出初始势能和每次的势能变化量的和即可。

1.  **zig**: 势能的变化量为

    $$
    \begin{aligned}
    1+w'(x)+w'(fa)−w(x)−w(fa) & \leq 1+w'(fa)−w(x) \\
    & \leq 1+w'(x)−w(x)
    \end{aligned}
    $$

2.  **zig-zig**:  势能变化量为

    $$
    \begin{aligned}
    1+w'(x)+w'(fa)+w'(g)−w(x)−w(fa)−w(g) & \leq 1+w'(fa)+w'(g)−w(x)−w(fa) \\
    & \leq 1+ w'(x)+w'(g)−2w(x) \\
    & \leq 3(w'(x)−w(x))
    \end{aligned}
    $$

3.  **zig-zag**:  势能变化量为

    $$
    \begin{aligned}
    1+w'(x)+w'(fa)+w'(g)−w(x)−w(fa)−w(g) & \leq 1+w'(fa)+w'(g)−w(x)−w(fa) \\
    & \leq 1+w'(g)+w'(fa)−2w(x) \\
    & \leq 2 w'(x)−w'(g)−w'(fa) + w'(fa)+w'(g)−w(x)−w(fa) \\
    & \leq 2(w'(x)−w(x))
    \end{aligned}
    $$

由此可见，三种 splay 步骤的势能全部可以缩放为 $\leq 3(w'(x)−w(x))$. 令 $w^{(n)}(x)=w'^{(n-1)}(x)$,$w^{(0)}(x)=w(x)$, 假设 splay 操作一次依次访问了 $x_{1}, x_{2}, \cdots, x_{n}$, 最终 $x_{1}$ 成为根节点，我们可以得到：

$$
\begin{aligned}
3\left(\sum_{i=0}^{n-2}\left(w^{(i+1)}(x_{1})-w^{(i)}(x_{1})\right)+w(n)−w^{(n-1)}(x_{1})\right)+1 & = 3(w(n)−w(x_{1}))+1 \\
& \leq \log n
\end{aligned}
$$

继而可得：

$$
\sum_{i=1}^m (\varphi (m-i+1)−\varphi (m−i)) +\varphi (0) = n \log n+m \log n
$$

因此，对于 $n$ 个节点的 splay 树，做一次 splay 操作的均摊复杂度为 $O(\log n)$。因此基于 splay 的插入，查询，删除等操作的时间复杂度也为均摊 $O(\log n)$。

### 插入操作

#### 过程

插入操作是一个比较复杂的过程，具体步骤如下（假设插入的值为 $k$）：

-   如果树空了，则直接插入根并退出。
-   如果当前节点的权值等于 $k$ 则增加当前节点的大小并更新节点和父亲的信息，将当前节点进行 Splay 操作。
-   否则按照二叉查找树的性质向下找，找到空节点就插入即可（请不要忘记 Splay 操作）。

#### 实现

```cpp
void ins(int k) {
  if (!rt) {
    val[++tot] = k;
    cnt[tot]++;
    rt = tot;
    maintain(rt);
    return;
  }
  int cur = rt, f = 0;
  while (1) {
    if (val[cur] == k) {
      cnt[cur]++;
      maintain(cur);
      maintain(f);
      splay(cur);
      break;
    }
    f = cur;
    cur = ch[cur][val[cur] < k];
    if (!cur) {
      val[++tot] = k;
      cnt[tot]++;
      fa[tot] = f;
      ch[f][val[f] < k] = tot;
      maintain(tot);
      maintain(f);
      splay(tot);
      break;
    }
  }
}
```

### 查询 x 的排名

#### 过程

根据二叉查找树的定义和性质，显然可以按照以下步骤查询 $x$ 的排名：

-   如果 $x$ 比当前节点的权值小，向其左子树查找。
-   如果 $x$ 比当前节点的权值大，将答案加上左子树（$size$）和当前节点（$cnt$）的大小，向其右子树查找。
-   如果 $x$ 与当前节点的权值相同，将答案加 $1$ 并返回。

注意最后需要进行 Splay 操作。

#### 实现

```cpp
int rk(int k) {
  int res = 0, cur = rt;
  while (1) {
    if (k < val[cur]) {
      cur = ch[cur][0];
    } else {
      res += sz[ch[cur][0]];
      if (!cur) return res + 1;
      if (k == val[cur]) {
        splay(cur);
        return res + 1;
      }
      res += cnt[cur];
      cur = ch[cur][1];
    }
  }
}
```

### 查询排名 x 的数

#### 过程

设 $k$ 为剩余排名，具体步骤如下：

-   如果左子树非空且剩余排名 $k$ 不大于左子树的大小 $size$，那么向左子树查找。
-   否则将 $k$ 减去左子树的和根的大小。如果此时 $k$ 的值小于等于 $0$，则返回根节点的权值，否则继续向右子树查找。

#### 实现

```cpp
int kth(int k) {
  int cur = rt;
  while (1) {
    if (ch[cur][0] && k <= sz[ch[cur][0]]) {
      cur = ch[cur][0];
    } else {
      k -= cnt[cur] + sz[ch[cur][0]];
      if (k <= 0) {
        splay(cur);
        return val[cur];
      }
      cur = ch[cur][1];
    }
  }
}
```

### 查询前驱

#### 过程

前驱定义为小于 $x$ 的最大的数，那么查询前驱可以转化为：将 $x$ 插入（此时 $x$ 已经在根的位置了），前驱即为 $x$ 的左子树中最右边的节点，最后将 $x$ 删除即可。

#### 实现

```cpp
int pre() {
  int cur = ch[rt][0];
  if (!cur) return cur;
  while (ch[cur][1]) cur = ch[cur][1];
  splay(cur);
  return cur;
}
```

### 查询后继

#### 过程

后继定义为大于 $x$ 的最小的数，查询方法和前驱类似：$x$ 的右子树中最左边的节点。

#### 实现

```cpp
int nxt() {
  int cur = ch[rt][1];
  if (!cur) return cur;
  while (ch[cur][0]) cur = ch[cur][0];
  splay(cur);
  return cur;
}
```

### 合并两棵树

#### 过程

合并两棵 Splay 树，设两棵树的根节点分别为 $x$ 和 $y$，那么我们要求 $x$ 树中的最大值小于 $y$ 树中的最小值。合并操作如下：

-   如果 $x$ 和 $y$ 其中之一或两者都为空树，直接返回不为空的那一棵树的根节点或空树。
-   否则将 $x$ 树中的最大值 $\operatorname{Splay}$ 到根，然后把它的右子树设置为 $y$ 并更新节点的信息，然后返回这个节点。

### 删除操作

#### 过程

删除操作也是一个比较复杂的操作，具体步骤如下：

首先将 $x$ 旋转到根的位置。

-   如果 $cnt[x]>1$（有不止一个 $x$），那么将 $cnt[x]$ 减 $1$ 并退出。
-   否则，合并它的左右两棵子树即可。

#### 实现

```cpp
void del(int k) {
  rk(k);
  if (cnt[rt] > 1) {
    cnt[rt]--;
    maintain(rt);
    return;
  }
  if (!ch[rt][0] && !ch[rt][1]) {
    clear(rt);
    rt = 0;
    return;
  }
  if (!ch[rt][0]) {
    int cur = rt;
    rt = ch[rt][1];
    fa[rt] = 0;
    clear(cur);
    return;
  }
  if (!ch[rt][1]) {
    int cur = rt;
    rt = ch[rt][0];
    fa[rt] = 0;
    clear(cur);
    return;
  }
  int cur = rt, x = pre();
  fa[ch[cur][1]] = x;
  ch[x][1] = ch[cur][1];
  clear(cur);
  maintain(rt);
}
```

## 实现

```cpp
#include <cstdio>
const int N = 100005;
int rt, tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];

struct Splay {
  void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x]; }

  bool get(int x) { return x == ch[fa[x]][1]; }

  void clear(int x) {
    ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0;
  }

  void rotate(int x) {
    int y = fa[x], z = fa[y], chk = get(x);
    ch[y][chk] = ch[x][chk ^ 1];
    if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
    ch[x][chk ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if (z) ch[z][y == ch[z][1]] = x;
    maintain(y);
    maintain(x);
  }

  void splay(int x) {
    for (int f = fa[x]; f = fa[x], f; rotate(x))
      if (fa[f]) rotate(get(x) == get(f) ? f : x);
    rt = x;
  }

  void ins(int k) {
    if (!rt) {
      val[++tot] = k;
      cnt[tot]++;
      rt = tot;
      maintain(rt);
      return;
    }
    int cur = rt, f = 0;
    while (1) {
      if (val[cur] == k) {
        cnt[cur]++;
        maintain(cur);
        maintain(f);
        splay(cur);
        break;
      }
      f = cur;
      cur = ch[cur][val[cur] < k];
      if (!cur) {
        val[++tot] = k;
        cnt[tot]++;
        fa[tot] = f;
        ch[f][val[f] < k] = tot;
        maintain(tot);
        maintain(f);
        splay(tot);
        break;
      }
    }
  }

  int rk(int k) {
    int res = 0, cur = rt;
    while (1) {
      if (k < val[cur]) {
        cur = ch[cur][0];
      } else {
        res += sz[ch[cur][0]];
        if (!cur) return res + 1;
        if (k == val[cur]) {
          splay(cur);
          return res + 1;
        }
        res += cnt[cur];
        cur = ch[cur][1];
      }
    }
  }

  int kth(int k) {
    int cur = rt;
    while (1) {
      if (ch[cur][0] && k <= sz[ch[cur][0]]) {
        cur = ch[cur][0];
      } else {
        k -= cnt[cur] + sz[ch[cur][0]];
        if (k <= 0) {
          splay(cur);
          return val[cur];
        }
        cur = ch[cur][1];
      }
    }
  }

  int pre() {
    int cur = ch[rt][0];
    if (!cur) return cur;
    while (ch[cur][1]) cur = ch[cur][1];
    splay(cur);
    return cur;
  }

  int nxt() {
    int cur = ch[rt][1];
    if (!cur) return cur;
    while (ch[cur][0]) cur = ch[cur][0];
    splay(cur);
    return cur;
  }

  void del(int k) {
    rk(k);
    if (cnt[rt] > 1) {
      cnt[rt]--;
      maintain(rt);
      return;
    }
    if (!ch[rt][0] && !ch[rt][1]) {
      clear(rt);
      rt = 0;
      return;
    }
    if (!ch[rt][0]) {
      int cur = rt;
      rt = ch[rt][1];
      fa[rt] = 0;
      clear(cur);
      return;
    }
    if (!ch[rt][1]) {
      int cur = rt;
      rt = ch[rt][0];
      fa[rt] = 0;
      clear(cur);
      return;
    }
    int cur = rt;
    int x = pre();
    fa[ch[cur][1]] = x;
    ch[x][1] = ch[cur][1];
    clear(cur);
    maintain(rt);
  }
} tree;

int main() {
  int n, opt, x;
  for (scanf("%d", &n); n; --n) {
    scanf("%d%d", &opt, &x);
    if (opt == 1)
      tree.ins(x);
    else if (opt == 2)
      tree.del(x);
    else if (opt == 3)
      printf("%d\n", tree.rk(x));
    else if (opt == 4)
      printf("%d\n", tree.kth(x));
    else if (opt == 5)
      tree.ins(x), printf("%d\n", val[tree.pre()]), tree.del(x);
    else
      tree.ins(x), printf("%d\n", val[tree.nxt()]), tree.del(x);
  }
  return 0;
}
```

## 序列操作

Splay 也可以运用在序列上，用于维护区间信息。与线段树对比，Splay 常数较大，但是支持更复杂的序列操作，如区间翻转等。

将序列建成的 Splay 有如下性质：

-   Splay 的中序遍历相当于原序列从左到右的遍历。

-   Splay 上的一个节点代表原序列的一个元素；Splay 上的一颗子树，代表原序列的一段区间。

因为有 splay 操作，可以快速提取出代表某个区间的 Splay 子树。

在操作之前，你需要先把这颗 Splay 建出来。根据 Splay 的特性，直接建出一颗只有右儿子的链即可，时间复杂度仍然是正确的。

### 一些进阶操作

Splay 的一颗子树代表原序列的一段区间。现在想找到序列区间 $[L, R]$ 代表的子树，只需要将代表 $a_{L - 1}$ 的节点 Splay 到根，再将代表 $a_{R + 1}$ 的节点 splay 到根的右儿子即可。根据「Splay 的中序遍历相当于原序列从左到右的遍历」，对应 $a_{R + 1}$ 的节点的左子树中序遍历为序列 $a[L, R]$，故其为区间 $[L, R]$ 代表的子树。

一般会建立左右两个哨兵节点 $0$ 和 $n + 1$，放在数列的最开头和最结尾，防止 $L - 1$ 或 $R + 1$ 超出数列范围。

所以要将 splay 函数进行一些修改，能够实现将节点旋转到目标点的儿子。如果目标点 `goal` 为 $0$ 说明旋转到根节点。

#### 实现

```cpp
void splay(int x, int goal = 0) {
  if (goal == 0) rt = x;
  while (fa[x] != goal) {
    int f = fa[x], g = fa[fa[x]];
    if (g != goal) {
      if (get(f) == get(x))
        rotate(f);
      else
        rotate(x);
    }
    rotate(x);
  }
}
```

### 区间翻转

Splay 常见的应用之一，模板题目是 [文艺平衡树](https://loj.ac/problem/105)。

#### 过程

先将询问区间的子树提取出来。因为是区间翻转，我们需要将这颗子树的中序遍历顺序翻转。

一个暴力做法是每次将根节点的左右儿子交换，然后递归左右子树做同样的操作，这样复杂度为 $O(n)$，不可承受。可以考虑使用懒标记，先给根打上「翻转标记」并交换其左右儿子。当递归到一个带懒标记的点时，将懒标记下传即可。

#### 实现

```cpp
void tagrev(int x) {
  swap(ch[x][0], ch[x][1]);
  lazy[x] ^= 1;
}

void pushdown(int x) {
  if (lazy[x]) {
    tagrev(ch[x][0]);
    tagrev(ch[x][1]);
    lazy[x] = 0;
  }
}

void reverse(int l, int r) {
  int L = kth(l - 1), R = kth(r + 1);
  splay(L), splay(R, L);
  int tmp = ch[ch[L][1]][0];
  tagrev(tmp);
}
```

## 实现

注意 $\operatorname{kth}$ 中要下传翻转标记。

```cpp
#include <algorithm>
#include <cstdio>
const int N = 100005;

int n, m, l, r, a[N];

int rt, tot, fa[N], ch[N][2], val[N], sz[N], lazy[N];

struct Splay {
  void maintain(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1; }

  bool get(int x) { return x == ch[fa[x]][1]; }

  void clear(int x) {
    ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = lazy[x] = 0;
  }

  void rotate(int x) {
    int y = fa[x], z = fa[y], chk = get(x);
    ch[y][chk] = ch[x][chk ^ 1];
    if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
    ch[x][chk ^ 1] = y;
    fa[y] = x;
    fa[x] = z;
    if (z) ch[z][y == ch[z][1]] = x;
    maintain(y);
    maintain(x);
  }

  void splay(int x, int goal = 0) {
    if (goal == 0) rt = x;
    while (fa[x] != goal) {
      int f = fa[x], g = fa[fa[x]];
      if (g != goal) {
        if (get(f) == get(x))
          rotate(f);
        else
          rotate(x);
      }
      rotate(x);
    }
  }

  void tagrev(int x) {
    std::swap(ch[x][0], ch[x][1]);
    lazy[x] ^= 1;
  }

  void pushdown(int x) {
    if (lazy[x]) {
      tagrev(ch[x][0]);
      tagrev(ch[x][1]);
      lazy[x] = 0;
    }
  }

  int build(int l, int r, int f) {
    if (l > r) return 0;
    int mid = (l + r) / 2, cur = ++tot;
    val[cur] = a[mid], fa[cur] = f;
    ch[cur][0] = build(l, mid - 1, cur);
    ch[cur][1] = build(mid + 1, r, cur);
    maintain(cur);
    return cur;
  }

  int kth(int k) {
    int cur = rt;
    while (1) {
      pushdown(cur);
      if (ch[cur][0] && k <= sz[ch[cur][0]]) {
        cur = ch[cur][0];
      } else {
        k -= 1 + sz[ch[cur][0]];
        if (k <= 0) {
          splay(cur);
          return cur;
        }
        cur = ch[cur][1];
      }
    }
  }

  void reverse(int l, int r) {
    int L = kth(l), R = kth(r + 2);
    splay(L), splay(R, L);
    int tmp = ch[ch[L][1]][0];
    tagrev(tmp);
  }

  void print(int x) {
    pushdown(x);
    if (ch[x][0]) print(ch[x][0]);
    if (val[x] >= 1 && val[x] <= n) printf("%d ", val[x]);
    if (ch[x][1]) print(ch[x][1]);
  }
} tree;

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i <= n + 1; i++) a[i] = i;
  rt = tree.build(0, n + 1, 0);
  while (m--) {
    scanf("%d%d", &l, &r);
    tree.reverse(l, r);
  }
  tree.print(rt);
  return 0;
}
```

## 例题

以下题目都是裸的 Splay 维护二叉查找树。

-   [【模板】普通平衡树](https://loj.ac/problem/104)
-   [【模板】文艺平衡树](https://loj.ac/problem/105)
-   [「HNOI2002」营业额统计](https://loj.ac/problem/10143)
-   [「HNOI2004」宠物收养所](https://loj.ac/problem/10144)

## 习题

-   [「Cerc2007」robotic sort 机械排序](https://www.luogu.com.cn/problem/P4402)
-   [二逼平衡树（树套树）](https://loj.ac/problem/106)
-   [bzoj 2827 千山鸟飞绝](https://hydro.ac/d/bzoj/p/2827)
-   [「Lydsy1706 月赛」K 小值查询](https://hydro.ac/d/bzoj/p/4923)
-   [POJ3580 SuperMemo](http://poj.org/problem?id=3580)

## 参考资料与注释

本文部分内容引用于 [algocode 算法博客](https://algocode.net)，特别鸣谢！
