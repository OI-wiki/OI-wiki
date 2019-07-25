Stern-Brocot 树是一种维护分数的优雅的数据结构。它分别由 Moritz Stern 在 1858 年和 Achille Brocot 在 1861 年发现这个结构。

# 概述

Stern-Borcot 树从两个简单的分数开始：

$$
\frac{0}{1}, \frac{1}{0}
$$

这个 $\frac{1}{0}$ 可能看得你有点懵逼。不过我们不讨论这方面的严谨性，你只需要把它当作 $\infty$ 就行了。

每次我们在相邻的两个分数 $\frac{a}{b},\frac{c}{d}$ 中间插入一个分数 $\frac{a+c}{b+d}$ ，这样就完成了一次迭代，得到下一个序列。于是它就会变成这样

$$
\begin{array}{c}
\dfrac{0}{1}, \dfrac{1}{1}, \dfrac{1}{0} \\\\
\dfrac{0}{1}, \dfrac{1}{2}, \dfrac{1}{1}, \dfrac{2}{1}, \dfrac{1}{0} \\\\
\dfrac{0}{1}, \dfrac{1}{3}, \dfrac{1}{2}, \dfrac{2}{3}, \dfrac{1}{1}, \dfrac{3}{2}, \dfrac{2}{1}, \dfrac{3}{1}, \dfrac{1}{0}
\end{array}
$$

既然我们叫这个数据结构 Stern-Brocot 树，那么它总得有一个树的样子对吧。来一张图：

![pic](./images/stern-brocot1.png)

你可以把第 $i$ 层的序列当作是深度为 $i-1$ 的 Stern-Brocot 树的中序遍历。

# 性质

接下来讨论一下 Stern-Brocot 树的性质。

## 单调性

在每一层的序列中，真分数是单调递增的。

略证：只需要在 $\frac{a}{b}\le \frac{c}{d}$ 的情况下证明

$$
\frac{a}{b}\le \frac{a+c}{b+d}\le \frac{c}{d}
$$

就行了。这个很容易，直接做一下代数变换即可

$$
\begin{array}{l}
&\frac{a}{b}\le \frac{c}{d}\\
\Rightarrow &ad\le bc\\
\Rightarrow &ad+ab\le bc+ab\\
\Rightarrow &\frac{a}{b}\le\frac{a+c}{b+d}
\end{array}
$$

另一边同理可证。

## 最简性

序列中的分数（除了 $\frac{0}{1},\frac{1}{0}$ ）都是最简分数。

略证：为证明最简性，我们首先证明对于序列中连续的两个分数 $\frac{a}{b},\frac{c}{d}$ ：

$$
bc-ad=1
$$

显然，我们只需要在 $bc-ad=1$ 的条件下证明 $\frac{a}{b}, \frac{a+c}{b+d}, \frac{c}{d}$ 的情况成立即可。

$$
a(b+d)-b(a+c)=ad-bc=1
$$

后半部分同理。证明了这个，利用扩展欧几里德定理，如果上述方程有解，显然 $\gcd(a,b)=\gcd(c,d)=1$ 。这样就证完了。

有了上面的证明，我们可以证明 $\frac{a}{b}<\frac{c}{d}$ 。

有了这两个性质，你就可以把它当成一棵平衡树来做了。建立和查询就向平衡树一样做就行了。

# 实现

构建实现

```cpp
void build(int a = 0, int b = 1, int c = 1, int d = 0, int level = 1) {
  int x = a + c, y = b + d;
  //... output the current fraction x/y
  // at the current level in the tree
  build(a, b, x, y, level + 1);
  build(x, y, c, d, level + 1);
}
```

查询实现

```cpp
string find(int x, int y, int a = 0, int b = 1, int c = 1, int d = 0) {
  int m = a + c, n = b + d;
  if (x == m && y == n) return "";
  if (x * n < y * m)
    return 'L' + find(x, y, a, b, m, n);
  else
    return 'R' + find(x, y, m, n, c, d);
}
```

# Farey 序列

Stern-Brocot 树与 Farey 序列有着极其相似的特征。第 $i$ 个 Farey 序列记作 $F_i$ ，表示把分母小于等于 $i$ 的所有最简真分数按大小顺序排列形成的序列。

$$
\begin{array}{l}
F_1=\{&\frac{0}{1},&&&&&&&&&&\frac{1}{1}&\}\\
F_2=\{&\frac{0}{1},&&&&&\frac{1}{2},&&&&&\frac{1}{1}&\}\\
F_3=\{&\frac{0}{1},&&&\frac{1}{3},&&\frac{1}{2},&&\frac{2}{3},&&&\frac{1}{1}&\}\\
F_4=\{&\frac{0}{1},&&\frac{1}{4},&\frac{1}{3},&&\frac{1}{2},&&\frac{2}{3},&\frac{3}{4},&&\frac{1}{1}&\}\\
F_5=\{&\frac{0}{1},&\frac{1}{5},&\frac{1}{4},&\frac{1}{3},&\frac{2}{5},&\frac{1}{2},&\frac{3}{5},&\frac{2}{3},&\frac{3}{4},&\frac{4}{5},&\frac{1}{1}&\}\\
\end{array}
$$

显然，上述构建 Stern-Brocot 树的算法同样适用于构建 Farey 序列。因为 Stern-Brocot 树中的数是最简分数，因此在边界条件（分母）稍微修改一下就可以形成构造 Farey 序列的代码。你可以认为 Farey 序列 $F_i$ 是 Stern-Brocot 第 $i-1$ 次迭代后得到的序列的子序列。

Farey 序列同样满足最简性和单调性，并且满足一个与 Stern-Brocot 树相似的性质：对于序列中连续的三个数 $\frac ab,\frac xy,\frac cd$ ，有 $x=a+c,y=b+d$ 。这个可以轻松证明，不再赘述。

由 Farey 序列的定义，我们可以得到 $F_i$ 的长度 $L_i$ 公式为：

$$
L_i=L_{i-1}+\varphi(i)\\
L_i=1+\sum_{k=1}^i\varphi(k)
$$

 **本页面主要译自博文[Дерево Штерна-Броко. Ряд Фарея](http://e-maxx.ru/algo/stern_brocot_farey)与其英文翻译版[The Stern-Brocot Tree and Farey Sequences](https://cp-algorithms.com/others/stern_brocot_tree_farey_sequences.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
