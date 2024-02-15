author: hsfzLZH1, cesonic, AtomAlpaca

## 前言

**Weight Balanced Leafy Tree**，下称 **WBLT**，是一种平衡树，比起其它平衡树主要有实现简单、常数小的优点。

Weight Balanced Leafy Tree 顾名思义是 Weight Balanced Tree 和 Leafy Tree 的结合。

Weight Balanced Tree 的每个结点储存这个结点下子树的大小，并且通过保持左右子树的大小关系在一定范围来保证树高。

Leafy Tree 维护的原始信息仅存储在树的 **叶子节点** 上，而非叶子节点仅用于维护子节点信息和维持数据结构的形态。我们熟知的线段树就是一种 Leafy Tree。

## 平衡树基础操作

### 代码约定

下文中，我们用 `ls[x]` 表示节点 $x$ 的左儿子，`rs[x]` 表示节点 $x$ 的右儿子，`vl[x]` 表示节点 $x$ 的权值，`sz[x]` 表示节点 $x$ 及其子树中叶子节点的个数。

### 建树

正如前言中所说的，WBLT 的原始信息仅存储在叶子节点上。而我们规定每个非叶子节点一定有两个子节点，这个节点要维护其子节点信息的合并。同时，每个节点还要维护自身及其子树中叶子节点的数量，用于实现维护平衡。

和大多数的平衡树一样，每个非叶子节点的右儿子的权值大于等于左儿子的权值，且在 WBLT 中非叶子节点节点的权值等于右儿子的权值。不难看出每个节点的权值就是其子树中的最大权值。

这样听起来就很像一棵维护区间最大值的动态开点线段树了，且所有叶子从左到右是递增的。事实上的建树操作也与线段树十分相似，只需要向下递归，直至区间长度为 $1$ 时把要维护的信息放叶子节点上，回溯的时候合并区间信息即可。

代码实现如下：

```c++
/* 添加一个权值为 v 的节点，返回这个节点的编号 */
int add(int v) {
  ++cnt;
  ls[cnt] = rs[cnt] = 0;
  sz[cnt] = 1;
  vl[cnt] = v;
  return cnt;
}

/* 更新节点编号为 x 的节点的信息 */
void pushup(int x) {
  vl[x] = vl[rs[x]];
  sz[x] = sz[ls[x]] + sz[rs[x]];
}

/* 递归建树 */
int build(int l, int r) {
  if (l == r) {
    return add(a[l]);
  }
  int x = add(0);
  int k = l + ((r - l) >> 1);
  ls[x] = build(l, k);
  rs[x] = build(k + 1, r);
  pushup(x);
}
```

### 插入和删除

由于 WBLT 的信息都存储在叶子节点上，插入和删除一个元素其实就是增加或减少了一个叶子节点。

对于插入操作，我们类似从根节点开始向下递归，直到找到权值大于等于插入元素的权值最小的叶子节点，再新建两个节点，其中一个用来存储新插入的值，另一个作为两个叶子的新父亲替代这个最小叶子节点的位置，再将这两个叶子连接到这个父亲上。

例如我们向以下树中加入一个值为 $4$ 的元素。

![wblt-1](./images/wblt-1.svg)

我们首先找到了叶子节点 $5$，随后新建了一个非叶子节点 $D$，并将 $4$ 和 $5$ 连接到了 $D$ 上。

![wblt-2](./images/wblt-2.svg)

对于删除，我们考虑上面过程的逆过程。即找到与要删除的值权值相等的一个叶子节点，将它和它的父亲节点删除，并用其父亲的另一个儿子代替父亲的位置。

上面提到的建树也可以通过不断往树里插入节点实现，不过如果这样做必须要加入一个权值为 $\infty$⁡ 的节点作为根，否则会导致插入第一个元素的时候找不到大于自己的叶子节点。

代码实现：

```c++
/* 将某一节点的全部信息复制到另一节点上 */
void copynode(int x, int y) {
  ls[x] = ls[y];
  rs[x] = rs[y];
  sz[x] = sz[y];
  vl[x] = vl[y];
}

/* 判断某一节点是否为叶子节点 */
bool leaf(int x) { return !ls[x] || !rs[x]; }

void insert(int v) {
  if (leaf(x)) {
    ls[x] = add(std::min(v, vl[x]));
    rs[x] = add(std::max(v, vl[x]));
    pushup(x);
    maintain(x);
    return;
  }
  if (vl[ls[x]] >= v) {
    insert(ls[x], v);
  } else {
    insert(rs[x], v);
  }
  pushup(x);
  maintain(x);
}

void delete(int x, int v, int fa) {
  if (leaf(x)) {
    if (ls[fa] == x) {
      copynode(fa, rs[fa]);
    } else {
      copynode(fa, ls[fa]);
    }
    pushup(fa);
    return;
  }
  if (vl[ls[x]] >= v) {
    delete (ls[x], v, x);
  } else {
    delete (rs[x], v, x);
  }
  pushup(x);
  maintain(x);
}
```

### 维护平衡

类似替罪羊树地，我们引入重构参数 $\alpha \in (0, \dfrac{1}{2}]$，我们设一个节点的平衡度 $\rho$ 为当前节点左子树大小和节点大小的比值。当一个节点满足 $\rho \in[\alpha, 1-\alpha]$ 时，我们称其为 $\alpha$- 平衡的。如果一棵 WBLT 的每一个节点都是 $\alpha$- 平衡的，那么这棵树的树高一定能保证是 $O(\log n)$ 量级的。证明是显然的，我们从一个叶子节点往父亲方向走，每次走到的节点维护的范围至少扩大到原来的 $\dfrac{1}{1 - \alpha}$ 倍，那么树高就是 $O(\log_{\frac{1}{1-\alpha}}n) = O(\log n)$ 量级的。

当某个节点不满足 $\alpha$- 平衡时，说明这个节点是失衡的，我们需要重新维护平衡。但是和替罪羊树不同的是，WBLT 使用旋转操作维护平衡。旋转的大致过程为：将过重的儿子的两个儿子拆下来，一个和过轻的儿子合并，另一个成为一个新的儿子。

我们来举个例子：

![wblt-3](./images/wblt-3.svg)

这是一棵十分不平衡的 WBLT，节点 $A$ 的右儿子显著地重于左儿子。我们先把右儿子及其两个儿子和左儿子都拆下来：

![wblt-4](./images/wblt-4.svg)

然后，我们将 $1$ 和 $2$ 两个节点合并作为 $A$ 节点的左儿子，将 $C$ 作为 $A$ 的右儿子。由于 $B$ 节点原本并不是叶子节点，因此其并不存储原始信息，直接删除就好。

![wblt-5](./images/wblt-5.svg)

旋转之后我们的树就变得十分平衡了。

但是上面的例子中，假设 $A$ 节点的左子树过于大，我们把它合并到 $A$ 的左子树上之后 $A$ 的左子树又会很大，这时 $A$ 依然可能不平衡。

![wblt-6](./images/wblt-6.svg)

不失一般性，我们接下来仅讨论一个方向上的旋转，另一方向的旋转是对称的。我们不妨设 `A` 的平衡度为 $\rho_1$，`B` 的平衡度为 $\rho_2$。那么我们可以得到旋转后 `A` 的平衡度 $\gamma_1= \rho_1+(1 - \rho_1)\rho_2$，`B` 的平衡度 $\gamma_2 =\dfrac{\rho_1}{\rho_1 + (1 - \rho_1)\rho_2}$，推导过程直接将各节点大小用 $siz_A$ 表示后代入定义式化简即可，这里略去。

不难发现仅当 $\rho_2 \le \dfrac{1 - 2\alpha}{1 - \alpha}$ 时 $\gamma_1, \gamma_2 \in [\alpha, 1 - \alpha]$。

为了旋转后仍不平衡的情况出现，我们引入双旋操作。具体地，我们在较大子树上做一次相反方向的旋转操作，然后再维护当前节点的平衡。

![wblt-7](./images/wblt-7.svg)

类似地定义 $\rho_3,\gamma_3$，则有 $\gamma_1=\rho_1+\rho_2\rho_3(1-\rho_1), \gamma_2=\dfrac{\rho_1}{\rho1+(1 - \rho_1)\rho2\rho3}, \gamma_3 = \dfrac{\rho_2(1-\rho_3)}{1-\rho_2\rho_3}$。可以证明当 $\alpha < 1- \dfrac{\sqrt2}{2} \approx 0.292$ 时一定有 $\gamma_1, \gamma_2, \gamma_3 \in [\alpha, 1 - \alpha]$。

实现上，我们在 $\rho_2 \le \dfrac{1 - 2\alpha}{1 - \alpha}$ 时进行单旋，否则进行双旋。

代码实现，这里取 $\alpha = 0.25$：

```c++
const double alpha = 0.25;

void rotate(int x, int flag) {
  if (!flag) {
    rs[x] = merge(rs[ls[x]], rs[x]);
    ls[x] = ls[ls[x]];
  } else {
    ls[x] = merge(ls[x], ls[rs[x]]);
    rs[x] = rs[rs[x]];
  }
}

void maintain(int x) {
  if (sz[ls[x]] > sz[rs[x]] * 3) {
    if (sz[rs[ls[x]]] > sz[ls[ls[x]]] * 2) {
      rotate(ls[x], 1);
    }
    rotate(x, 0);
  } else if (sz[rs[x]] > sz[ls[x]] * 3) {
    if (sz[ls[rs[x]]] > sz[rs[rs[x]]] * 2) {
      rotate(rs[x], 0);
    }
    rotate(x, 1);
  }
}
```

### 查询排名

我们发现 `WBLT` 的形态和线段树十分相似，因此查询排名可以使用类似线段树上二分的方式：如果左子树的最大值比大于等于待查值就往左儿子跳，否则就向右跳，同时答案加上左子树的 `size`。

```c++
int rank(int x, int v) {
  if (leaf(x)) {
    return 1;
  }
  if (vl[ls[x]] >= v) {
    return rank(ls[x], v);
  } else {
    return rank(rs[x], v) + sz[ls[x]];
  }
}
```

### 查询第 k 大的数

依然是利用线段树上二分的思想，只不过这里比较的是节点的大小。

```c++
int kth(int x, int v) {
  if (sz[x] == v) {
    return vl[x];
  }
  if (sz[ls[x]] >= v) {
    return kth(ls[x], v);
  } else {
    return kth(rs[x], v - sz[ls[x]]);
  }
}
```

### 总结

以上，我们利用 WBLT 完成了平衡树基本的几大操作。下面是用 WBLT 实现的 [普通平衡树模板](https://loj.ac/p/104)。

??? note "完整代码"
    ```cpp
    --8<-- "docs/ds/code/wblt/wblt_1.cpp"
    ```
