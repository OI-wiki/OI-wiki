给你一个长度为 n 的序列 $\left\langle a_i\right\rangle_{i=1}^n$ ，再给你一个满足结合律的运算 $\circ$ （比如 $\gcd,\min,\max,+,\operatorname{and},\operatorname{or},\operatorname{xor}$ 均满足结合律），然后对于每一次区间询问 $[l,r]$ ，我们需要计算 $a_l\circ a_{l+1}\circ\dotsb\circ a_{r}$ 。

Sqrt Tree 可以在 $O(n\log\log n)$ 的时间内预处理，并在 $O(1)$ 的时间内回答询问。

## 描述

### 序列分块

首先我们把整个序列分成 $O(\sqrt{n})$ 个块，每一块的大小为 $O(\sqrt{n})$ 。对于每个块，我们计算：

1.   $P_i$ 块内的前缀区间询问
2.   $S_i$ 块内的后缀区间询问
3.  维护一个额外的数组 $\left\langle B_{i,j}\right\rangle$ 表示第 $i$ 个块到第 $j$ 个块的区间答案。

举个例子，假设 $\circ$ 代表加法运算 $+$ ，序列为 $\{1,2,3,4,5,6,7,8,9\}$ 。

首先我们将序列分成三块，变成了 $\{1,2,3\},\{4,5,6\},\{7,8,9\}$ 。

那么每一块的前缀区间答案和后缀区间答案分别为

$$
\begin{split}
&P_1=\{1,3,6\},S_1=\{6,5,3\}\\
&P_2=\{4,9,15\},S_2=\{15,11,6\}\\
&P_3=\{7,15,24\},S_3=\{24,17,9\}\\
\end{split}
$$

 $B$ 数组为：

$$
B=\begin{bmatrix}
6 & 21 & 45\\
0 & 15 & 39\\
0 & 0 & 24\\
\end{bmatrix}
$$

（对于 $i>j$ 的不合法的情况我们假设答案为 0）

显然我们可以在 $O(n)$ 的时间内预处理这些值，空间复杂度同样是 $O(n)$ 的。处理好之后，我们可以利用它们在 $O(1)$ 的时间内回答一些跨块的询问。但对于那些整个区间都在一个块内的询问我们仍不能处理，因此我们还需要处理一些东西。

### 构建一棵树

容易想到我们在每个块内递归地构造上述结构以支持块内的查询。对于大小为 $1$ 的块我们可以 $O(1)$ 地回答询问。这样我们就建出了一棵树，每一个结点代表序列的一个区间。叶子结点的区间长度为 $1$ 或 $2$ 。一个大小为 $k$ 的结点有 $O(\sqrt{k})$ 个子节点，于是整棵树的高度是 $O(\log\log n)$ 的，每一层的区间总长是 $O(n)$ 的，因此我们构建这棵树的复杂度是 $O(n\log\log n)$ 的。

现在我们可以在 $O(\log\log n)$ 的时间内回答询问。对于询问 $[l,r]$ ，我们只需要快速找到一个区间长度最小的结点 $u$ 使得 $u$ 能包含 $[l,r]$ ，这样 $[l,r]$ 在 $u$ 的分块区间中一定是跨块的，就可以 $O(1)$ 地计算答案了。查询一次的总体复杂度是 $O(\log\log n)$ ，因为树高是 $O(\log\log n)$ 的。不过我们仍可以优化这个过程。

### 优化询问复杂度

容易想到二分高度，然后可以 $O(1)$ 判断是否合法。这样复杂度就变成了 $O(\log\log\log n)$ 。不过我们仍可以进一步加速这一过程。

我们假设

1.  每一块的大小都是 $2$ 的整数幂次；
2.  每一层上的块大小是相同的。

为此我们需要在序列的末位补充一些 $0$ 元素，使得它的长度变成 $2$ 的整数次幂。尽管有些块可能会变成原来的两倍大小，但这样仍是 $O(\sqrt{k})$ 的，于是预处理分块的复杂度仍是 $O(n)$ 的。

现在我们可以轻松地确定一个询问区间是否被整个地包含在一个块中。对于区间 $[l,r]$ （以 0 为起点），我们把端点写为二进制形式。举一个例子，对于 $k=4, l=39, r=46$ ，二进制表示为

$$
l = 39_{10} = 100111_2\\
r = 46_{10} = 101110_2
$$

我们知道每一层的区间长度是相同的，而分块的大小也是相同的（在上述示例中 $2^k=2^4=16$ ）。这些块完全覆盖了整个序列，因此第一块代表的元素为 $[0,15]$ （二进制表示为 $[000000_2,001111_2]$ ），第二个块代表的元素区间为 $[16,31]$ （二进制表示为 $[010000_2,011111_2]$ ），以此类推。我们发现这些在同一个块内的元素的位置在二进制上只有后 $k$ 位不同（上述示例中 $k=4$ ）。而示例的 $l,r$ 也只有后 $k$ 位不同，因此他们在同一个块中。

因此我们需要检查区间两个端点是否只有后 $k$ 位不同，即 $l\oplus r\le 2^k-1$ 。因此我们可以快速找到答案区间所在的层：

1.  对于每个 $i\in [1,n]$ ，我们找到找到 $i$ 最高位上的 $1$ ；
2.  现在对于一个询问 $[l,r]$ ，我们计算 $l\oplus r$ 的最高位，这样就可以快速确定答案区间所在的层。

这样我们就可以在 $O(1)$ 的时间内回答询问啦。

## 更新元素

我们可以在 Sqrt Tree 上更新元素，单点修改和区间修改都是支持的。

### 单点修改

考虑一次单点赋值操作 $a_x=val$ ，我们希望高效更新这个操作的信息。

#### 朴素实现

首先我们来看看在做了一次单点修改后 Sqrt Tree 会变成什么样子。

考虑一个长度为 $l$ 的结点以及对应的序列： $\left\langle P_i\right\rangle,\left\langle S_i\right\rangle,\left\langle B_{i,j}\right\rangle$ 。容易发现在 $\left\langle P_i\right\rangle$ 和 $\left\langle S_i \right\rangle$ 中都只有 $O(\sqrt{l})$ 个元素改变。而在 $\left\langle B_{i,j}\right\rangle$ 中则有 $O(l)$ 个元素被改变。因此有 $O(l)$ 个元素在树上被更新。因此在 Sqrt Tree 上单点修改的复杂度是 $O(n+\sqrt{n}+\sqrt{\sqrt{n}}+\dotsb)=O(n)$ 。

#### 使用 Sqrt Tree 替代 B 数组

注意到单点更新的瓶颈在于更新根结点的 $\left\langle B_{i,j}\right\rangle$ 。因此我们尝试用另一个 Sqrt Tree 代替根结点的 $\left\langle B_{i,j}\right\rangle$ ，称其为 $index$ 。它的作用和原来的二维数组一样，维护整段询问的答案。其他非根结点仍然使用 $\left\langle B_{i,j}\right\rangle$ 维护。注意，如果一个 Sqrt Tree 根结点有 $index$ 结构，称其 Sqrt Tree 是 **含有索引** 的；如果一个 Sqrt Tree 的根结点有 $\left\langle B_{i,j}\right\rangle$ 结构，称其是 **没有索引** 的。而 $index$ 这棵树本身是没有索引的。

因此我们可以这样更新 $index$ 树：

1.  在 $O(\sqrt{n})$ 的时间内更新 $\left\langle P_i\right\rangle$ 和 $\left\langle S_i\right\rangle$ 。
2.  更新 $index$ ，它的长度是 $O(n)$ 的，但我们只需要更新其中的一个元素（这个元素代表了被改变的块），这一步的时间复杂度是 $O(\sqrt{n})$ 的（使用朴素实现的算法）。
3.  进入产生变化的子节点并使用朴素实现的算法在 $O(\sqrt{n})$ 的时间内更新信息。

注意，查询的复杂度仍是 $O(1)$ 的，因为我们最多使用 $index$ 树一次。于是单点修改的复杂度就是 $O(\sqrt{n})$ 的。

### 更新一个区间

Sqrt Tree 也支持区间覆盖操作 $\operatorname{Update}(l,r,x)$ ，即把区间 $[l,r]$ 的数全部变成 $x$ 。对此我们有两种实现方式，其中一种会花费 $O(\sqrt{n}\log\log n)$ 的复杂度更新信息， $O(1)$ 的时间查询；另一种则是 $O(\sqrt{n})$ 更新信息，但查询的时间会增加到 $O(\log\log n)$ 。

我们可以像线段树一样在 Sqrt Tree 上打懒标记。但是在 Sqrt Tree 上有一点不同。因为下传一个结点的懒标记，复杂度可能达到 $O(\sqrt{n})$ ，因此我们不是在询问的时侯下传标记，而是看父节点是否有标记，如果有标记就把它下传。

#### 第一种实现

在第一种实现中，我们只会给第 $1$ 层的结点（结点区间长度为 $O(\sqrt{n})$ ）打懒标记，在下传标记的时侯直接更新整个子树，复杂度为 $O(\sqrt{n}\log\log n)$ 。操作过程如下：

1.  考虑第 $1$ 层上的结点，对于那些被修改区间完全包含的结点，给他们打一个懒标记；

2.  有两个块只有部分区间被覆盖，我们直接在 $O(\sqrt{n}\log\log n)$ 的时间内 **重建** 这两个块。如果它本身带有之前修改的懒标记，就在重建的时侯顺便下传标记；

3.  更新根结点的 $\left\langle P_i\right\rangle$ 和 $\left\langle S_i\right\rangle$ ，时间复杂度 $O(\sqrt{n})$ ；

4.  重建 $index$ 树，时间复杂度 $O(\sqrt{n}\log\log n)$ 。

现在我们可以高效完成区间修改了。那么如何利用懒标记回答询问？操作如下：

1.  如果我们的询问被包含在一个有懒标记的块内，可以利用懒标记计算答案；

2.  如果我们的询问包含多个块，那么我们只需要关心最左边和最右边不完整块的答案。中间的块的答案可以在 $index$ 树中查询（因为 $index$ 树在每次修改完后会重建），复杂度是 $O(1)$ 。

因此询问的复杂度仍为 $O(1)$ 。

#### 第二种实现

在这种实现中，每一个结点都可以被打上懒标记。因此在处理一个询问的时侯，我们需要考虑祖先中的懒标记，那么查询的复杂度将变成 $O(\log\log n)$ 。不过更新信息的复杂度就会变得更快。操作如下：

1.  被修改区间完全包含的块，我们把懒标记添加到这些块上，复杂度 $O(\sqrt{n})$ ；
2.  被修改区间部分覆盖的块，更新 $\left\langle P_i\right\rangle$ 和 $\left\langle S_i\right\rangle$ ，复杂度 $O(\sqrt{n})$ （因为只有两个被修改的块）；
3.  更新 $index$ 树，复杂度 $O(\sqrt{n})$ （使用同样的更新算法）；
4.  对于没有索引的子树更新他们的 $\left\langle B_{i,j}\right\rangle$ ；
5.  递归地更新两个没有被完全覆盖的区间。

时间复杂度是 $O(\sqrt{n}+\sqrt{\sqrt{n}}+\dotsb)=O(\sqrt{n})$ 。

## 代码实现

下面的实现在 $O(n\log\log n)$ 的时间内建树，在 $O(1)$ 的时间内回答询问，在 $O(\sqrt{n})$ 的时间内单点修改。

```cpp
SqrtTreeItem op(const SqrtTreeItem &a, const SqrtTreeItem &b);

inline int log2Up(int n) {
  int res = 0;
  while ((1 << res) < n) {
    res++;
  }
  return res;
}

class SqrtTree {
 private:
  int n, lg, indexSz;
  vector<SqrtTreeItem> v;
  vector<int> clz, layers, onLayer;
  vector<vector<SqrtTreeItem> > pref, suf, between;

  inline void buildBlock(int layer, int l, int r) {
    pref[layer][l] = v[l];
    for (int i = l + 1; i < r; i++) {
      pref[layer][i] = op(pref[layer][i - 1], v[i]);
    }
    suf[layer][r - 1] = v[r - 1];
    for (int i = r - 2; i >= l; i--) {
      suf[layer][i] = op(v[i], suf[layer][i + 1]);
    }
  }

  inline void buildBetween(int layer, int lBound, int rBound, int betweenOffs) {
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int bSz = 1 << bSzLog;
    int bCnt = (rBound - lBound + bSz - 1) >> bSzLog;
    for (int i = 0; i < bCnt; i++) {
      SqrtTreeItem ans;
      for (int j = i; j < bCnt; j++) {
        SqrtTreeItem add = suf[layer][lBound + (j << bSzLog)];
        ans = (i == j) ? add : op(ans, add);
        between[layer - 1][betweenOffs + lBound + (i << bCntLog) + j] = ans;
      }
    }
  }

  inline void buildBetweenZero() {
    int bSzLog = (lg + 1) >> 1;
    for (int i = 0; i < indexSz; i++) {
      v[n + i] = suf[0][i << bSzLog];
    }
    build(1, n, n + indexSz, (1 << lg) - n);
  }

  inline void updateBetweenZero(int bid) {
    int bSzLog = (lg + 1) >> 1;
    v[n + bid] = suf[0][bid << bSzLog];
    update(1, n, n + indexSz, (1 << lg) - n, n + bid);
  }

  void build(int layer, int lBound, int rBound, int betweenOffs) {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSz = 1 << ((layers[layer] + 1) >> 1);
    for (int l = lBound; l < rBound; l += bSz) {
      int r = min(l + bSz, rBound);
      buildBlock(layer, l, r);
      build(layer + 1, l, r, betweenOffs);
    }
    if (layer == 0) {
      buildBetweenZero();
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
  }

  void update(int layer, int lBound, int rBound, int betweenOffs, int x) {
    if (layer >= (int)layers.size()) {
      return;
    }
    int bSzLog = (layers[layer] + 1) >> 1;
    int bSz = 1 << bSzLog;
    int blockIdx = (x - lBound) >> bSzLog;
    int l = lBound + (blockIdx << bSzLog);
    int r = min(l + bSz, rBound);
    buildBlock(layer, l, r);
    if (layer == 0) {
      updateBetweenZero(blockIdx);
    } else {
      buildBetween(layer, lBound, rBound, betweenOffs);
    }
    update(layer + 1, l, r, betweenOffs, x);
  }

  inline SqrtTreeItem query(int l, int r, int betweenOffs, int base) {
    if (l == r) {
      return v[l];
    }
    if (l + 1 == r) {
      return op(v[l], v[r]);
    }
    int layer = onLayer[clz[(l - base) ^ (r - base)]];
    int bSzLog = (layers[layer] + 1) >> 1;
    int bCntLog = layers[layer] >> 1;
    int lBound = (((l - base) >> layers[layer]) << layers[layer]) + base;
    int lBlock = ((l - lBound) >> bSzLog) + 1;
    int rBlock = ((r - lBound) >> bSzLog) - 1;
    SqrtTreeItem ans = suf[layer][l];
    if (lBlock <= rBlock) {
      SqrtTreeItem add =
          (layer == 0) ? (query(n + lBlock, n + rBlock, (1 << lg) - n, n))
                       : (between[layer - 1][betweenOffs + lBound +
                                             (lBlock << bCntLog) + rBlock]);
      ans = op(ans, add);
    }
    ans = op(ans, pref[layer][r]);
    return ans;
  }

 public:
  inline SqrtTreeItem query(int l, int r) { return query(l, r, 0, 0); }

  inline void update(int x, const SqrtTreeItem &item) {
    v[x] = item;
    update(0, 0, n, 0, x);
  }

  SqrtTree(const vector<SqrtTreeItem> &a)
      : n((int)a.size()), lg(log2Up(n)), v(a), clz(1 << lg), onLayer(lg + 1) {
    clz[0] = 0;
    for (int i = 1; i < (int)clz.size(); i++) {
      clz[i] = clz[i >> 1] + 1;
    }
    int tlg = lg;
    while (tlg > 1) {
      onLayer[tlg] = (int)layers.size();
      layers.push_back(tlg);
      tlg = (tlg + 1) >> 1;
    }
    for (int i = lg - 1; i >= 0; i--) {
      onLayer[i] = max(onLayer[i], onLayer[i + 1]);
    }
    int betweenLayers = max(0, (int)layers.size() - 1);
    int bSzLog = (lg + 1) >> 1;
    int bSz = 1 << bSzLog;
    indexSz = (n + bSz - 1) >> bSzLog;
    v.resize(n + indexSz);
    pref.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
    suf.assign(layers.size(), vector<SqrtTreeItem>(n + indexSz));
    between.assign(betweenLayers, vector<SqrtTreeItem>((1 << lg) + bSz));
    build(0, 0, n, 0);
  }
};
```

## 习题

 [CodeChef - SEGPROD](https://www.codechef.com/NOV17/problems/SEGPROD) 

 **本页面主要译自 [Sqrt Tree](https://cp-algorithms.com/data_structures/sqrt-tree.html) ，版权协议为 CC-BY-SA 4.0。** 
