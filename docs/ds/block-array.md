## 建立块状数组

块状数组，即把一个数组分为几个块，块内信息整体保存，若查询时遇到两边不完整的块直接暴力查询．一般情况下，块的长度为 $O(\sqrt{n})$．详细分析可以阅读 2017 年国家集训队论文中徐明宽的《非常规大小分块算法初探》．

下面直接给出一种建立块状数组的代码．

???+ note "实现"
    ```cpp
    --8<-- "docs/ds/code/block-array/block-array_1.cpp:example11"
    ```

其中 `st[i]` 和 `ed[i]` 为块的起点和终点，`size[i]` 为块的大小．

## 保存与修改块内信息

### 例题 1：[教主的魔法](https://www.luogu.com.cn/problem/P2801)

两种操作：

1.  区间 $[x,y]$ 每个数都加上 $z$；
2.  查询区间 $[x,y]$ 内大于等于 $z$ 的数的个数．

我们要询问一个块内大于等于一个数的数的个数，所以需要一个 `t` 数组对块内排序，`a` 为原来的（未被排序的）数组．对于整块的修改，使用类似于标记永久化的方式，用 `delta` 数组记录现在块内整体加上的值．设 $q$ 为查询和修改的操作次数总和，则时间复杂度 $O(q\sqrt{n}\log n)$．

用 `delta` 数组记录每个块的整体赋值情况．

???+ note "实现"
    ```cpp
    --8<-- "docs/ds/code/block-array/block-array_1.cpp:example12"
    ```

### 例题 2：寒夜方舟

两种操作：

1.  区间 $[x,y]$ 每个数都变成 $z$；
2.  查询区间 $[x,y]$ 内小于等于 $z$ 的数的个数．

用 `delta` 数组记录现在块内被整体赋值为何值．当该块未被整体赋值时，用一个特殊值（如 `0x3f3f3f3f3f3f3f3fll`）加以表示．对于边角块，查询前要 `pushdown`，把块内存的信息下放到每一个数上．赋值之后记得重新 `sort` 一遍．其他方面同上题．

???+ note "实现"
    ```cpp
    --8<-- "docs/ds/code/block-array/block-array_2.cpp:example13"
    ```

## 练习

1.  [单点修改，区间查询](https://loj.ac/problem/130)
2.  [区间修改，区间查询](https://loj.ac/problem/132)
3.  [【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)
4.  [「Ynoi2019 模拟赛」Yuno loves sqrt technology III](https://www.luogu.com.cn/problem/P5048)
5.  [「Violet」蒲公英](https://www.luogu.com.cn/problem/P4168)
6.  [作诗](https://www.luogu.com.cn/problem/P4135)
