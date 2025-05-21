author: ChungZH, billchenchina, Chrogeek, Early0v0, ethan-enhe, HeRaNO, hsfzLZH1, iamtwz, Ir1d, konnyakuxzy, luoguojie, Marcythm, orzAtalod, StudyingFather, wy-luke, Xeonacid, CCXXXI, chenryang, chenzheAya, CJSoft, cjsoft, countercurrent-time, DawnMagnet, Enter-tainer, GavinZhengOI, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, ksyx, megakite, Menci, moon-dim, NachtgeistW, onelittlechildawa, ouuan, shadowice1984, shawlleyw, shuzhouliu, SukkaW, Tiphereth-A, x2e6, Ycrpro, yifan0305, zeningc

线段树的合并与分裂是线段树的常用技巧，常见于权值线段树维护可重集的场景。

例如，树上某些结点处有若干操作，如果需要自下而上地将子节点信息传递给亲节点，而单个结点处的信息又方便用线段树维护时，就可以应用线段树合并的技巧控制整体的复杂度。

## 线段树合并

### 过程

顾名思义，线段树合并是指建立一棵新的线段树，这棵线段树的每个节点都是两棵原线段树对应节点合并后的结果。它常常被用于维护树上或是图上的信息。

显然，我们不可能真的每次建满一颗新的线段树，因此我们需要使用上文的动态开点线段树。

线段树合并的过程本质上相当暴力：

假设两颗线段树为 A 和 B，我们从 1 号节点开始递归合并。

递归到某个节点时，如果 A 树或者 B 树上的对应节点为空，直接返回另一个树上对应节点，这里运用了动态开点线段树的特性。

如果递归到叶子节点，我们合并两棵树上的对应节点。

最后，根据子节点更新当前节点并且返回。

???+ note "线段树合并的复杂度"
    显然，对于两颗满的线段树，合并操作的复杂度是 $O(n\log n)$ 的。但实际情况下使用的常常是权值线段树，总点数和 $n$ 的规模相差并不大。并且合并时一般不会重复地合并某个线段树，所以我们最终增加的点数大致是 $n\log n$ 级别的。这样，总的复杂度就是 $O(n\log n)$ 级别的。当然，在一些情况下，可并堆可能是更好的选择。

### 实现

```cpp
int merge(int a, int b, int l, int r) {
  if (!a) return b;
  if (!b) return a;
  if (l == r) {
    // do something...
    return a;
  }
  int mid = (l + r) >> 1;
  tr[a].l = merge(tr[a].l, tr[b].l, l, mid);
  tr[a].r = merge(tr[a].r, tr[b].r, mid + 1, r);
  pushup(a);
  return a;
}
```

### 例题

???+ note "[luogu P4556 \[Vani 有约会\] 雨天的尾巴/【模板】线段树合并](https://www.luogu.com.cn/problem/P4556)"
    ??? "解题思路"
        线段树合并模板题，用差分把树上修改转化为单点修改，然后向上 dfs 线段树合并统计答案即可。
    
    ??? "参考代码"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_6.cpp"
        ```

## 线段树分裂

### 过程

线段树分裂实质上是线段树合并的逆过程。线段树分裂只适用于有序的序列，无序的序列是没有意义的，常用在动态开点的权值线段树。

注意当分裂和合并都存在时，我们在合并的时候必须回收节点，以避免分裂时会可能出现节点重复占用的问题。

从一颗区间为 $[1,N]$ 的线段树中分裂出 $[l,r]$，建一颗新的树：

从 1 号结点开始递归分裂，当节点不存在或者代表的区间 $[s,t]$ 与 $[l,r]$ 没有交集时直接回溯。

当 $[s,t]$ 与 $[l,r]$ 有交集时需要开一个新结点。

当 $[s,t]$ 包含于 $[l,r]$ 时，需要将当前结点直接接到新的树下面，并把旧边断开。

???+ note "线段树分裂的复杂度"
    可以发现被断开的边最多只会有 $\log n$ 条，所以最终每次分裂的时间复杂度就是 $O(\log⁡ n)$，相当于区间查询的复杂度。

### 实现

```cpp
void split(int &p, int &q, int s, int t, int l, int r) {
  if (t < l || r < s) return;
  if (!p) return;
  if (l <= s && t <= r) {
    q = p;
    p = 0;
    return;
  }
  if (!q) q = New();
  int m = s + t >> 1;
  if (l <= m) split(ls[p], ls[q], s, m, l, r);
  if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
  push_up(p);
  push_up(q);
}
```

### 例题

???+ note "[P5494【模板】线段树分裂](https://www.luogu.com.cn/problem/P5494)"
    ??? "解题思路"
        线段树分裂模板题，将 $[x,y]$ 分裂出来。
        
        -   将 $t$ 树合并入 $p$ 树：单次合并即可。
        -   $p$ 树中插入 $x$ 个 $q$：单点修改。
        -   查询 $[x,y]$ 中数的个数：区间求和。
        -   查询第 $k$ 小。
    
    ??? "参考代码"
        ```cpp
        --8<-- "docs/ds/code/seg/seg_7.cpp"
        ```

## 习题

-   [Luogu P4556 \[Vani 有约会\] 雨天的尾巴/【模板】线段树合并](https://www.luogu.com.cn/problem/P4556)
-   [Luogu P5494【模板】线段树分裂](https://www.luogu.com.cn/problem/P5494)
-   [Luogu P1600 天天爱跑步](https://www.luogu.com.cn/problem/P1600)
-   [Luogu P4577 \[FJOI2018\] 领导集团问题](https://www.luogu.com.cn/problem/P4577)
-   [Luogu P2824 \[HEOI2016/TJOI2016\] 排序](https://www.luogu.com.cn/problem/P2824)
