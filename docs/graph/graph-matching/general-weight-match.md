author: accelsao, Henry-ZHR, yuhuoji

本页从一般图最大全完美匹配到一般图最大权匹配。

## 预备知识

一般图匹配和二分图匹配不同的是，图可能存在奇环。可以将偶环视为二分图解决。

带花树算法（Blossom Algorithm）的处理方式时是遇到奇环就把它缩成一个**花（Blossom ）**。

这也可以变成线性规划和对偶问题，但是要对花进行一些处理。

### 等边



## 定义

设$S\subseteq V$
$\gamma(S)=\{(u,v)\in E:u\in S,v\in S\}$
$O=\{B\subseteq V:|B|\text{是奇数且}|B|\geq3\}$

## 一般图最大权完美匹配的线性规划

???+ note "原问题"
    $max\sum_{e\in E}w(e)x_e$
    限制：
    $x(\delta(u))=1:\forall u\in V$ 
    $x(\gamma(B))\leq\lfloor\frac{|B|}2\rfloor:\forall B\in O$ 
    $x_e\geq0:\forall e\in E$

???+ note "对偶问题"
    $min\sum_{u\in V}z_u+\sum_{B\in O}\lfloor\frac{|B|}2\rfloor z_B$ 
    限制:
    $z_B\geq0:\forall B\in O$
    $z_e\geq0:\forall e\in E$
    设$e=(u,v)$，这里
$$
z_e&=z_u+z_v-w(e)+\sum_{\begin{array}{c}B\in O\\u,v\in\gamma(B)\end{array}}z_B
$$
和二分图一样，我们必须满足$x_e\in\{0,1\}:\forall e\in E$。因此必须在最大权完美匹配的时候，让所有匹配边都是等边的。这里等边的定义为$z_e=0$的边。

和二分图不同的是，一般图多了$z_B$要处理。下面考虑$z_B$什么时候大于$0$。

可以看出，尽量使$z_B=0$是最好的做法，但在不得已时还是要让$z_B>0$。

在$x(\gamma(B))=\lfloor\frac{|B|}2\rfloor\text{且}x(\delta(B))=1$时，让$z_B>0$即可。因为除了在这种情况下，$z_B>0$是无意义的。

所以有以下的对应关系：
$$
\begin{array}{rcl}x_e>0&\longrightarrow&z_e=0&\forall e\in E
\\
z_B>0&\longrightarrow&x(\gamma(B))=\lfloor\frac{|B|}2\rfloor,&x(\delta(B))=1&\forall B\in O
\end{array}
$$
可以发现在$z_B>0$时，B就会是一朵花。

以「等边」的概念，结合之前的带花树算法:

用「等边」构成的增广路不断进行扩充，由于用来扩充的边全是「等边」，最后得到的最大权完美匹配仍然全是「等边」。

### 处理花的问题

当遇到花的时候，要将它缩成一个偶点。将花中所有点都设为偶点，并让它的$z_B=0$。

由于缩花后会把花保存起来，直到满足某些条件才会拆开，所以不能用之前的方法记录花。

如果没有特殊说明，之前提到的点，都包含缩花形成的偶点。

由于花也有可能缩成点被加入队列中，并且花的数量是不固定的，因此不能像之前一样枚举每个点来检查是否有增广路。因此，在进行广度优先搜索（BFS）时，必须将所有未匹配的点都放入队列中。

这样会同时产生很多棵交错树。

### 四个步骤

这个算法可以分成四个步骤。

1. GROW（等边）：用"等边"构成交错树。
2. AUGMENT（增广）：找出增广路并扩充匹配。
3. SHRINK（缩花）：把花缩成一个点。
4. EXPAND（展开）：把花拆开。

![general-weight-match-1](images/general-weight-match-1.png)

在AUGMENT阶段时，因为所有未匹配点都会在不同的交错树上，所以当增广时两棵交错树的偶点连在一起，就表示找到了一条增广路。

### 找不到等边

和二分圖一樣，也會有找不到「等邊」擴充的問題
必須要調整vertex labeling

### 調整 VERTEX LABELING

vertex labeling 仍要維持大於等於的性質
而且既有的「等邊」不能被改變
還要讓zB��盡量的小

## 一般图最大權匹配

vertex labeling 額外增加一個限制：
對於所有匹配點u�，zu>0��>0

一開始先設所有zu=max({w(e):e∈E})/2��=���({�(�):�∈�})/2
vertex labeling為 0 的點最後將成為未匹配點

## Code

这里为了方便实现，使用边权乘2来计算$z_e$的值，这样就不会出现浮点数误差了。



## 复杂度分析

每朵花在一次BFS中只会被缩花或拆花一次。每次缩花或拆花的时间复杂度为$O(|V|)$。最多总共有$O(|V|)$朵花，所以花的处理花费$O(|V|^2)$的时间。 而BFS花费$O(|V| + |E|)$的时间复杂度。 因此，找增广路花费$O(|V| + |E|) + O(|V|^2) = O(|V|^2)$的时间复杂度。

最多做$|V|$次BFS。所以，总时间复杂度为$O(|V|^3)$。

## 习题

-   [UOJ #81. 一般图最大权匹配](https://uoj.ac/problem/81)

## 参考资料

[Kolmogorov, Vladimir (2009), "Blossom V: A new implementation of a minimum cost perfect matching algorithm"](http://pub.ist.ac.at/~vnk/papers/BLOSSOM5.html)
