## OI 中常用的几类距离

### 曼哈顿距离

对于平面上两点 $A(x_1, y_1)$ , $B(x_2, y_2)$  $Dis(A, B) = |x_1-x_2| + |y_1-y_2|$ 

一般来讲，我们只会用到二维平面上的曼哈顿距离

### 切比雪夫距离

对于平面上两点 $A(x_1, y_1)$ , $B(x_2, y_2)$  $Dis(A, B) = \max(|x_1-x_2| , |y_1-y_2|)$ 

对于两个 $n$ 维向量 $\vec A(x_{11}, x_{12}, \cdots,x_{1n})$  $\vec B(x_{21}, x_{22}, \cdots,x_{2n})$ 

 $Dis(A, B) = \max\limits_i(|x_{1i}-x_{2i}|)$ 

### 欧几里得距离（又称欧氏距离）

欧几里得距离是两点的直线距离。

对于平面上两点 $A(x_1, y_1)$ , $B(x_2, y_2)$  $Dis(A, B) = \sqrt{(x_1-x2)^2+(y1-y2)^2}$ 

对于两个 $n$ 维向量 $\vec A(x_{11}, x_{12}, \cdots,x_{1n})$  $\vec B(x_{21}, x_{22}, \cdots,x_{2n})$ 

 $Dis(A, B) = \sqrt{\sum\limits_{k=1}^n(x_{1k}-x_{2k})^2}$ 

###  $L_m$ 距离

一般地，我们定义平面上两点 $A(x_1, y_1)$ , $B(x_2, y_2)$ 之间的 $L_m$ 距离为

 $dist~L_m = (|x_1-x_2|^m+|y1-y2|^m)^{\frac{1}{m}}$ 

特殊的， $L_2$ 距离就是欧几里得距离， $L_1$ 距离就是曼哈顿距离。

### 汉明距离

汉明距离是两个字符串之间的距离，它表示两个长度相同的字符串对应位字符不同的数量

我们可以简单的认为对两个串进行异或运算，结果为 1 的数量就是两个串的汉明距离。

* * *

当然， 还有其他的一些距离，但是在 OI 中并不常用，有兴趣的话可以了解一下。

* * *

## 一、欧氏距离

在平面直角坐标系中，设点 $A,B$ 的坐标分别为 $A(x_1,y_1),B(x_2,y_2)$ ，则两点间的**欧氏距离**为：

$\left | AB \right | = \sqrt{\left ( x_2 - x_1 \right )^2 + \left ( y_2 - y_1 \right )^2}$

举个例子，若在平面直角坐标系中，有两点 $A(6,5),B(2,2)$，通过公式，我们很容易得到 $A,B$ 两点间的欧氏距离：

$\left | AB \right | = \sqrt{\left ( 2 - 6 \right )^2 + \left ( 2 - 5 \right )^2} = \sqrt{4^2+3^2} = 5$ 

除此之外，$P(x,y)$ 到原点的欧氏距离可以用公式表示为：

$|P| = \sqrt{x^2+y^2}$ 

那么，三维空间中两点的欧氏距离公式呢？我们来观察下图。

<p><img src="[https://cdn.luogu.org/upload/pic/47571.png](https://cdn.luogu.org/upload/pic/47571.png)" alt="" /></p>

我们很容易发现，在 $\triangle ADC$ 中， $\angle ADC = 90^\circ$ ；在 $\triangle ACB$ 中， $\angle ACB = 90^\circ$ 。

$\therefore |AB|=\sqrt{|AC|^2+|BC|^2}$

$=\sqrt{|AD|^2+|CD|^2+|BC|^2}$ 

由此可得，三维空间中欧氏距离的距离公式为：

$\left | AB \right | = \sqrt{\left ( x_2 - x_1 \right )^2 + \left ( y_2 - y_1 \right )^2 + \left ( z_2 - z_1 \right )^2}$ 

$|P| = \sqrt{x^2+y^2+z^2}$ 

[NOIP2017 提高组 奶酪](https://www.luogu.org/problemnew/show/P3958) 就运用了这一知识，可以作为欧氏距离的例题。

以此类推，我们就得到了 $n$ 维空间中欧氏距离的距离公式：

$d(x,y) = \sqrt{\left ( x_1 - y_1 \right )^2 + \left ( x_2 - y_2 \right )^2 + \cdot \cdot \cdot +\left ( x_n - y_n \right )^2}$

$= \sqrt{\sum_{i = 1}^{n}(x_i - y_i)^2}$ 

欧氏距离虽然很有用，但也有明显的缺点。两个整点计算其欧氏距离时，往往答案是浮点型，会存在一定误差。

## 二、曼哈顿距离

在二维空间内，两个点之间的曼哈顿距离为它们横坐标之差的绝对值与纵坐标之差的绝对值之和。设点 $A(x_1,y_1),B(x_2,y_2)$ ，则 $A,B$ 之间的曼哈顿距离用公式可以表示为：

<p>$$d(A,B) = |x_1 - x_2| + |y_1 - y_2|$$ 

观察下图：

<p><img src="[https://cdn.luogu.org/upload/pic/47609.png](https://cdn.luogu.org/upload/pic/47609.png)" alt="" /></p>

在 $A,B$ 间，

$\color{yellow}\colorbox{white}{黄线}$ ，

$\color{orange}\colorbox{white}{橙线}$ 都表示曼哈顿距离，而

$\color{red}\colorbox{white}{红线}$ ， $\color{blue}\colorbox{white}{蓝线}$ 表示 等价 的曼哈顿距离， $\color{green}\colorbox{white}{绿线}$ 表示欧氏距离。

同样的栗子，在下图中 $A,B$ 的坐标分别为 $A(6,5),B(2,2)$ 。

<p><img src="[https://cdn.luogu.org/upload/pic/47570.png](https://cdn.luogu.org/upload/pic/47570.png)" alt="" /></p>

通过公式，我们很容易得到 $A,B$ 两点间的曼哈顿距离：

$d(A,B) = |6 - 2| + |5 - 2| = 4 + 3 = 7$ 

经过推导，我们得到 $n$ 维空间 的曼哈顿距离公式为：

$d(A,B) = |x_1 - y_1| + |x_2 - y_2| + \cdot \cdot \cdot + |x_n - y_n|$

$=\sum_{i = 1}^{n}|x_i - y_i|$ 

除了公式之外，曼哈顿距离还具有以下数学性质：

<ul>

<li>

<p><strong>非负性</strong></p>

曼哈顿距离是一个非负数。

<p>$d(i,j)\geq 0$ 

</li>

<li>

<p><strong>统一性</strong></p>

点到自身的曼哈顿距离为 $0$ 。

<p>$d(i,i) = 0$ 

</li>

<li>

<p><strong>对称性</strong></p>

<p>$A$ 到 $B$ 与 $B$ 到 $A$ 的曼哈顿距离相等，且是对称函数。

<p>$d(i,j) = d(j,i)$ 

</li>

<li>

<p><strong>三角不等式</strong></p>

从点 $i$ 到 $j$ 的直接距离不会大于途经的任何其它点 $k$ 的距离。

<p>$d(i,j)\leq d(i,k)+d(k,j)$ 

</li>

</ul>

<p><strong>例题：<a href="[https://www.luogu.org/problemnew/show/P5098](https://www.luogu.org/problemnew/show/P5098)">P5098</a></strong></p>

<p><strong>解析：</strong></p>

<p><del>（不要被难度吓住，是假的）</del></p>

根据题意，对于式子 $|x_1-x_2|+|y_1-y_2|$ ，我们可以假设 $x_1 - x_2 \geq 0$ ，根据 $y_1 - y_2$ 的符号分成两种情况：

<ul>

<li>

<p>$(y_1 - y_2 \geq 0)\rightarrow |x_1-x_2|+|y_1-y_2|=x_1 + y_1 - (x_2 + y_2)$ 

</li>

<li>

<p>$(y_1 - y_2&lt; 0)\rightarrow |x_1-x_2|+|y_1-y_2|=x_1 - y_1 - (x_2 - y_2)$ 

</li>

</ul>

只要分别求出 $x+y, x-y$ 的最大值和最小值即能得出答案。

<p><strong>Code</strong></p>

<pre><code class="language-cpp">#include &lt;bits/stdc++.h&gt;

using namespace std;

  

template &lt; class T &gt; inline void read(T &amp;x) {

x = 0;

char c = getchar();

bool f = 0;

for (; !isdigit(c); c = getchar()) f ^= c == '-';

for (; isdigit(c); c = getchar()) x = (x &lt;&lt; 3) + (x &lt;&lt; 1) + (c ^ 48);

x = f ? -x : x;

}

  

int n, x, y, minx = 0x7fffffff, maxx, miny = 0x7fffffff, maxy;

  

int main() {

read(n);

for (int i = 1; i &lt;= n; i++) {

read(x), read(y);

minx = min(minx, x + y), maxx = max(maxx, x + y);

miny = min(miny, x - y), maxy = max(maxy, x - y);

}

printf("%d\n", max(maxx - minx, maxy - miny));

return 0;

}</code></pre>

其实还有第二种做法，那就是把 曼哈顿距离 转化为 切比雪夫距离 求解，最后部分会讲到。

<hr />

<h2>三、切比雪夫距离</h2>

<p><strong>切比雪夫距离 是向量空间中的一种度量，二个点之间的距离定义是其各坐标数值差绝对值的最大值。—— <em><strong>来源：<a href="[https://baike.baidu.com/item/%E5%88%87%E6%AF%94%E9%9B%AA%E5%A4%AB%E8%B7%9D%E7%A6%BB](https://baike.baidu.com/item/%E5%88%87%E6%AF%94%E9%9B%AA%E5%A4%AB%E8%B7%9D%E7%A6%BB)">百度百科</a></strong></em> 

在 二维空间 内，两个点之间的切比雪夫距离为它们横坐标之差的绝对值与纵坐标之差的绝对值的最大值。设点 $A(x_1,y_1),B(x_2,y_2)$ ，则 $A,B$ 之间的切比雪夫距离用公式可以表示为：

<p>$$d(A,B) = max(|x_1 - x_2|, |y_1 - y_2|)$$ 

仍然是这个栗子，下图中 $A,B$ 的坐标分别为 $A(6,5),B(2,2)$ 。

<img src="[https://cdn.luogu.org/upload/pic/47570.png](https://cdn.luogu.org/upload/pic/47570.png)" alt="" /></p>

<p>$$d(A,B) = max(|6 - 2|, |5 - 2|)=max(4,3)=4$$ 

<p>$n$ 维空间 中切比雪夫距离的距离公式：

<p>$$d(x,y) = max\begin{Bmatrix} |x_1 - y_1|,|x_2 - y_2|,\cdot \cdot \cdot,|x_n - y_n|\end{Bmatrix}$$

$= max\begin{Bmatrix} |x_i - y_i|\end{Bmatrix}(i \in n)$ 

<hr />

<h2>四、（拓展）曼哈顿距离与切比雪夫距离的相互转化</h2>

首先，我们考虑画出平面直角坐标系上所有到原点的 曼哈顿距离 为 $1$ 的点。

通过公式，我们很容易得到方程 $|x| + |y| = 1$ 。

将绝对值展开，得到 $4$ 个 一次函数 ，分别是：

<p>$$y = x + 1(x \geq 0, y \geq 0)$$ 

<p>$$y = -x + 1(x \leq 0, y \geq 0)$$ 

<p>$$y = x - 1(x \geq 0, y \leq 0)$$ 

<p>$$y = -x - 1(x \leq 0, y \leq 0)$$ 

将这 $4$ 个函数画到平面直角坐标系上，得到一个边长为 $\sqrt{2}$ 的正方形，如下图所示：

<p><img src="[https://cdn.luogu.org/upload/pic/47624.png](https://cdn.luogu.org/upload/pic/47624.png)" alt="" /></p>

正方形边界上所有的点到原点的 曼哈顿距离 都是 $1$ 。

同理，我们再考虑画出平面直角坐标系上所有到原点的 切比雪夫距离 为 $1$ 的点。

通过公式，我们知道 $max(|x|,|y|)=1$ 。

我们将式子展开，也同样可以得到可以得到 $4$ 条 线段，分别是：

<p>$$y = 1(-1\leq x \leq 1)$$ 

<p>$$y = -1(-1\leq x \leq 1)$$ 

<p>$$x = 1,(-1\leq y \leq 1)$$ 

<p>$$x = -1,(-1\leq y \leq 1)$$ 

画到平面直角坐标系上，可以得到一个边长为 $2$ 的正方形，如下图所示：

<p><img src="[https://cdn.luogu.org/upload/pic/47626.png](https://cdn.luogu.org/upload/pic/47626.png)" alt="" /></p>

正方形边界上所有的点到原点的 切比雪夫距离 都是 $1$ 。

将这两幅图对比，我们会神奇地发现：

这 $2$ 个正方形是 相似图形 。

所以，曼哈顿距离 与 切比雪夫距离 之间会不会有联系呢？

接下来我们简略证明一下：

假设 $A(x_1,y_1),B(x_2,y_2)$ ，

<p>$A,B$ 两点的 曼哈顿距离 为：

$d(A,B)=|x_1 - x_2| + |y_1 - y_2|$

$=|x_1 - x_2| + |y_1 - y_2|$

$= max\begin{Bmatrix} x_1 - x_2 + y_1 - y_2, x_1 - x_2 + y_2 - y_1,x_2 - x_1 + y_1 - y_2, x_2 - x_1 + y_2 - y_1\end{Bmatrix}$

（ 把绝对值拆开，能够得到四个值，这四个值中的最大值是两个 非负数 之和，即 曼哈顿距离 ）

$= max(|(x_1 + y_1) - (x_2 + y_2)|, |(x_1 - y_2) - (x_2 - y_2)|)$ 

我们很容易发现，这就是 $(x_1 + y_1,x_1 - y_1), (x_2 + y_2,x_2 - y_2)$ 两点之间的 切比雪夫距离。

所以将每一个点 $(x,y)$ 转化为 $(x + y, x - y)$ ，新坐标系下的 切比雪夫距离 即为原坐标系下的 曼哈顿距离。

同理， $A,B$ 两点的 切比雪夫距离 为：

$d(A,B)=max\begin{Bmatrix} |x_1 - x_2|,|y_1 - y_2|\end{Bmatrix}$

$=max\begin{Bmatrix} |\frac{x_1 + y_1}{2}-\frac{x_2 + y_2}{2}|+|\frac{x_1 - y_1}{2}-\frac{x_2 - y_2}{2}|\end{Bmatrix}$ 

而这就是 $(\frac{x_1 + y_1}{2},\frac{x_1 - y_1}{2}), (\frac{x_2 + y_2}{2},\frac{x_2 - y_2}{2})$ 两点之间的 曼哈顿距离。

所以将每一个点 $(x,y)$ 转化为 $(\frac{x + y}{2},\frac{x - y}{2})$ ，新坐标系下的 曼哈顿距离 即为原坐标系下的 切比雪夫距离。

<p><strong>结论：</strong></p>

<ul>

<li>

曼哈顿坐标系是通过切比雪夫坐标系旋转 $45^\circ$ 后，再缩小到原来的一半得到的。

</li>

<li>

将一个点 $(x,y)$ 的坐标变为 $(x + y, x - y)$ 后，

</li>

</ul>

原坐标系中的 曼哈顿距离 $=$ 新坐标系中的 切比雪夫距离</strong></p>

<ul>

<li>将一个点 $(x,y)$ 的坐标变为 $(\frac{x + y}{2},\frac{x - y}{2})$ 后，</li>

</ul>

原坐标系中的 切比雪夫距离 $=$ 新坐标系中的 曼哈顿距离</strong></p>

碰到求 切比雪夫距离 或 曼哈顿距离 的题目时，我们往往可以相互转化来求解。两种距离在不同的题目中有不同的优缺点，应该灵活运用。

<p><strong>例题：</strong></p>

<p><strong><a href="[https://www.luogu.org/problemnew/show/P4648](https://www.luogu.org/problemnew/show/P4648)">P4648</a></strong>（曼哈顿距离转切比雪夫距离）

<p><strong><a href="[https://www.luogu.org/problemnew/show/P3964](https://www.luogu.org/problemnew/show/P3964)">P3964</a></strong>（切比雪夫距离转曼哈顿距离）

最后给出 <strong><a href="[https://www.luogu.org/problemnew/show/P5098](https://www.luogu.org/problemnew/show/P5098)">P5098</a></strong> 的第二种解法：

我们考虑将题目所求的 曼哈顿距离 转化为 切比雪夫距离，即把每个点的坐标 $(x,y)$ 变为 $(x + y, x - y)$ 。

所求的答案就变为 $max_{i,j\in n}\begin{Bmatrix} max\begin{Bmatrix} |x_i - x_j|,|y_i - y_j|\end{Bmatrix}\end{Bmatrix}$ 

现要使得横坐标之差和纵坐标之差最大，只需要预处理出 $x,y$ 的最大值和最小值即可。

<p><strong>Code</strong></p>

<pre><code class="language-cpp">#include &lt;bits/stdc++.h&gt;

using namespace std;

  

template &lt; class T &gt; inline void read(T &amp;x) {

x = 0;

char c = getchar();

bool f = 0;

for (; !isdigit(c); c = getchar()) f ^= c == '-';

for (; isdigit(c); c = getchar()) x = (x &lt;&lt; 3) + (x &lt;&lt; 1) + (c ^ 48);

x = f ? -x : x;

}

  

int n, x, y, a, b, minx = 0x7fffffff, maxx, miny = 0x7fffffff, maxy;

  

int main() {

read(n);

for (int i = 1; i &lt;= n; i++) {

read(a), read(b);

x = a + b, y = a - b;

minx = min(minx, x), maxx = max(maxx, x);

miny = min(miny, y), maxy = max(maxy, y);

}

printf("%d\n", max(maxx - minx, maxy - miny));

return 0;

}</code></pre>

对比两份代码，我们又能够发现，两种不同的思路，写出来的代码却是完全等价的，是不是很神奇呢？当然，更高深的东西需要大家另行研究。

<br>

</div>

搬运自[浅谈三种常见的距离算法](https://www.luogu.org/blog/xuxing/Distance-Algorithm)，感谢作者 [xuxing](https://www.luogu.org/space/show?uid=32139) 的授权。


------
当然，还有其他的一些距离，但是在 OI 中并不常用，有兴趣的话可以了解一下。
