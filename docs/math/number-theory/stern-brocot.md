## Stern-Brocot 树

Stern-Brocot 树是一种维护分数的优雅的结构。它分别由 Moritz Stern 在 1858 年和 Achille Brocot 在 1861 年发现这个结构。

### 概述

Stern-Borcot 树从两个简单的分数开始：

$$
\frac{0}{1}, \frac{1}{0}
$$

这个 $\frac{1}{0}$ 可能看得你有点懵逼。不过我们不讨论这方面的严谨性，你只需要把它当作 $\infty$ 就行了。

每次我们在相邻的两个分数 $\frac{a}{b},\frac{c}{d}$ 中间插入一个分数 $\frac{a+c}{b+d}$，这样就完成了一次迭代，得到下一个序列。于是它就会变成这样

$$
\begin{array}{c}
\dfrac{0}{1}, \dfrac{1}{1}, \dfrac{1}{0} \\\\
\dfrac{0}{1}, \dfrac{1}{2}, \dfrac{1}{1}, \dfrac{2}{1}, \dfrac{1}{0} \\\\
\dfrac{0}{1}, \dfrac{1}{3}, \dfrac{1}{2}, \dfrac{2}{3}, \dfrac{1}{1}, \dfrac{3}{2}, \dfrac{2}{1}, \dfrac{3}{1}, \dfrac{1}{0}
\end{array}
$$

既然我们称它为 Stern-Brocot 树，那么它总得有一个树的样子对吧。来一张图：

![pic](./images/stern-brocot1.png)

你可以把第 $i$ 层的序列当作是深度为 $i-1$ 的 Stern-Brocot 树的中序遍历。

### 性质

接下来讨论一下 Stern-Brocot 树的性质。

#### 单调性

在每一层的序列中，真分数是单调递增的。

略证：只需要在 $\frac{a}{b}\le \frac{c}{d}$ 的情况下证明

$$
\frac{a}{b}\le \frac{a+c}{b+d}\le \frac{c}{d}
$$

就行了。这个很容易，直接做一下代数变换即可

$$
\begin{array}{rl}
&\frac{a}{b}\le \frac{c}{d}\\
\Rightarrow &ad\le bc\\
\Rightarrow &ad+ab\le bc+ab\\
\Rightarrow &\frac{a}{b}\le\frac{a+c}{b+d}
\end{array}
$$

另一边同理可证。

#### 最简性

序列中的分数（除了 $\frac{0}{1},\frac{1}{0}$）都是最简分数。

略证：为证明最简性，我们首先证明对于序列中连续的两个分数 $\frac{a}{b},\frac{c}{d}$：

$$
bc-ad=1
$$

显然，我们只需要在 $bc-ad=1$ 的条件下证明 $\frac{a}{b}, \frac{a+c}{b+d}, \frac{c}{d}$ 的情况成立即可。

$$
a(b+d)-b(a+c)=ad-bc=1
$$

后半部分同理。证明了这个，利用扩展欧几里德定理，如果上述方程有解，显然 $\gcd(a,b)=\gcd(c,d)=1$。这样就证完了。

有了上面的证明，我们可以证明 $\frac{a}{b}<\frac{c}{d}$。

有了这两个性质，你就可以把它当成一棵平衡树来做了。建立和查询就向平衡树一样做就行了。

### 实现

构建实现

```cpp
// C++ Version
void build(int a = 0, int b = 1, int c = 1, int d = 0, int level = 1) {
  int x = a + c, y = b + d;
  // ... output the current fraction x/y
  // at the current level in the tree
  build(a, b, x, y, level + 1);
  build(x, y, c, d, level + 1);
}
```

```python
# Python Version
def build(a = 1, b = 1, c = 1, d = 0, level = 1):
    x = a + c; y = b + d
    # ... output the current fraction x/y
    # at the current level in the tree
    build(a, b, x, y, level + 1)
    build(x, y, c, d, level + 1)
```

查询实现

```cpp
// C++ Version
string find(int x, int y, int a = 0, int b = 1, int c = 1, int d = 0) {
  int m = a + c, n = b + d;
  if (x == m && y == n) return "";
  if (x * n < y * m)
    return 'L' + find(x, y, a, b, m, n);
  else
    return 'R' + find(x, y, m, n, c, d);
}
```

```python
# Python Version
def find(x, y, a = 0, b = 1, c = 1, d = 0):
    m = a + c; n = b + d
    if x == m and y == n:
        return ""
    if x * n < y * m:
        return 'L' + find(x, y, a, b, m, n)
    else:
        return 'R' + find(x, y, m, n, c, d)
```

## Farey 序列

Stern-Brocot 树与 Farey 序列有着极其相似的特征。第 $i$ 个 Farey 序列记作 $F_i$，表示把分母小于等于 $i$ 的所有最简真分数按大小顺序排列形成的序列。

$$
\begin{array}{lllllllllllll}
F_1=\{&\frac{0}{1},&&&&&&&&&&\frac{1}{1}&\}\\
F_2=\{&\frac{0}{1},&&&&&\frac{1}{2},&&&&&\frac{1}{1}&\}\\
F_3=\{&\frac{0}{1},&&&\frac{1}{3},&&\frac{1}{2},&&\frac{2}{3},&&&\frac{1}{1}&\}\\
F_4=\{&\frac{0}{1},&&\frac{1}{4},&\frac{1}{3},&&\frac{1}{2},&&\frac{2}{3},&\frac{3}{4},&&\frac{1}{1}&\}\\
F_5=\{&\frac{0}{1},&\frac{1}{5},&\frac{1}{4},&\frac{1}{3},&\frac{2}{5},&\frac{1}{2},&\frac{3}{5},&\frac{2}{3},&\frac{3}{4},&\frac{4}{5},&\frac{1}{1}&\}\\
\end{array}
$$

显然，上述构建 Stern-Brocot 树的算法同样适用于构建 Farey 序列。因为 Stern-Brocot 树中的数是最简分数，因此在边界条件（分母）稍微修改一下就可以形成构造 Farey 序列的代码。你可以认为 Farey 序列 $F_i$ 是 Stern-Brocot 第 $i-1$ 次迭代后得到的序列的子序列。

Farey 序列同样满足最简性和单调性，并且满足一个与 Stern-Brocot 树相似的性质：对于序列中连续的三个数 $\frac ab,\frac xy,\frac cd$，有 $x=a+c,y=b+d$。这个可以轻松证明，不再赘述。

由 Farey 序列的定义，我们可以得到 $F_i$ 的长度 $L_i$ 公式为：

$$
\begin{aligned}
L_i=L_{i-1}+\varphi(i)\\
L_i=1+\sum_{k=1}^i\varphi(k)
\end{aligned}
$$

## 最佳有理逼近

讨论如何用有理数“最佳地”逼近无理数，不妨假设无理数落入 $(0,1)$ 区间。

“最佳”一词的概念：选定的有理数必须保证，比它与无理数的距离更近的有理数，分母都比它大。不存在分母比它小的有理数，到给定无理数的距离更近。

**最佳有理数：在 Farey 数列的某一行中，与给定无理数距离最近的那个有理数。**

这个有理数可能在下面几行依旧与无理数“距离最近”，但一定有某一行，会找到一个新的有理数，与无理数距离更近。因此去重复后可以得到 **最佳逼近有理数列**，分母严格递增，距离递减。

比无理数大的称为上逼近，否则为下逼近。由于无理数和有理数之间一定有有理数，最佳逼近有理数列必然为若干个上逼近，之后若干个下逼近，交替进行的形式。

有结论：

**渐进分数必然为最佳逼近。偶项渐进分数全都是下逼近，奇项渐进分数全都是上逼近。渐进分数列是下上交错的逼近。**

在最佳逼近有理数列中，渐进分数是下上关系改变之前的倒数第一个数。如果将最佳逼近有理数列都写成有限简单连分数，那么在渐进分数之后（下上关系改变之后），连分数长度加一。

例如，$[0,2,4,2]$ 是 $\sqrt{6}$ 减去 $2$ 的一个渐进分数。

那么它的渐进分数列是：

$$
[0,2]=\frac{1}{2},[0,2,4]=\frac{4}{9},[0,2,4,2]=\frac{9}{20}\ldots
$$

它的最佳逼近有理数列是：

$$
\left[0,1\right]=1,\left[0,2\right]=\frac{1}{2}
$$

$$
\left[0,2,1\right]=\frac{1}{3},\left[0,2,2\right]=\frac{2}{5},\left[0,2,3\right]=\frac{3}{7},\left[0,2,4\right]=\frac{4}{9}
$$

$$
\left[0,2,4,1\right]=\frac{5}{11},\left[0,2,4,2\right]=\frac{9}{20},\ldots
$$

从每个渐进分数（不包含）开始，到下一个渐进分数（包含）为止，同为上逼近，或同为下逼近。

在最佳逼近列中，每一个最佳分数是上一个最佳分数与再往前一个渐进分数的分子分母对应求和。

## Dirichlet 逼近定理

Dirichlet 逼近定理是说，对于任意的一个无理数 $\theta$，均能找到无穷个有理数逼近它，满足不等式：

$\left|\frac{p}{q}-\theta\right|\leqslant\frac{1}{q^2}$

更强的结论是，在右边的分母上能放一个 $\sqrt{5}$。这个 $\sqrt{5}$ 是最优的，在无理数为黄金分割的时候取等。因此，在上式中的小于等于号事实上也可以是小于号。

更进一步的定理是 Kronecker 的逼近定理。

如果 $\theta$ 为无理数，$\alpha$ 为实数，则对任意正数 $\varepsilon$, 存在整数 $n$ 和整数 $m$，使得：

$\left|n\theta−m−\alpha\right|<\varepsilon$

这两个定理都可以用抽屉原理来解决。事实上，历史上第一次正式提出抽屉原理，就是 Dirichlet 为了解决 [Pell 方程](./pell-equation.md) 而研究这个有理数逼近条件才正式提出来抽屉原理的。

当然，采用抽屉原理的证明可以发现，上文中提到的最佳逼近有理数列，每项满足定理中右边改成分母为一次式的不等式。

进一步有结论，渐进有理数列中，每一项均满足 Dirichlet 逼近定理的不等式。

**本页面主要译自博文 [Дерево Штерна-Броко. Ряд Фарея](http://e-maxx.ru/algo/stern_brocot_farey) 与其英文翻译版 [The Stern-Brocot Tree and Farey Sequences](https://cp-algorithms.com/others/stern_brocot_tree_farey_sequences.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
