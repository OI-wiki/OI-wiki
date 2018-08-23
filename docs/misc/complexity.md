复杂度是我们衡量一个算法好坏的重要的标准。在算法竞赛中，我们通常关注于算法的时间复杂和空间复杂度。 

一般的来说，复杂度是一个关于输入长度的一个函数。对于某些算法来说，相同的输入的不同输入依然会造成算法的运行时间/空间的不同，因此我们通常使用算法的最坏时间复杂度，记为 $T(n)$ 。对于一些特殊的情况，我们可能会关心它的平均情况复杂复杂度（特别是对于随机算法 (randomized algorithm) ），这个时候我们通过使用随机分析 (probabilistic analysis)来得到期望的复杂度。


##渐进符号
我们通常使用渐进符号来描述一个算法的复杂度。

### $\Theta$ 符号
对于给定的一个函数 $g(n)$, 函数集合 $\Theta(g(n))$ 定义为

$$\Theta(g(n)) = \{f(n) : 存在常数 c_1,c_2,n_0 \in \mathbb{R^{+}}使得 0 \leq c_1g(n) \leq f(n) \leq c_2g(n), \qquad \forall n \geq n_0\}$$

也就是说，如果函数 $f(n)$ 属于 $\Theta(g(n))$，那么我们能找到两个正常数 $c_1, c_2$ 使得 $f(n)$ 被 $c_1g(n)$ 和 $c_2g(n)$ 夹在中间。 因为 $\Theta(g(n))$ 是一个函数集合，我们可以用 $f(n) \in \Theta(g(n))$ 表达 $f(n)$ 属于 $\Theta(g(n))$， 但是我们通常使用 $f(n) = \Theta(g(n))$。

### $O$ 符号
$\Theta$ 符号同时给了我们一个函数的上下界，如果我们只有一个函数的渐进上界的时候，我们使用$O$ 符号。 对于一个给定的函数 $g(n)$, 我们把它记作 $O(g(n))$。

$$O(g(n)) = \{f(n):存在常数 c,n_0 使得 0\leq f(n) \leq cg(n), \qquad \forall n \geq n_0\}$$

### $\Omega$ 符号
同样的，我们使用$\Omega$符号来描述一个函数的渐进下界。
$$\Omega(g(n)) = \{f(n):存在常数 c,n_0 使得 0 \leq cg(n) \leq f(n) , \qquad \forall n \geq n_0\}$$

![](images/order.png)

## 主定理 (Master Theorem)
我们可以使用Master Theorem来快速的求得关于递归算法的复杂度。
假设我们有递推关系式

$$T(n) = AT\left(\frac{n}{b}\right)＋cn^k, \qquad \forall n > b$$ 

那么

$$
T(n) = \begin{cases}\Theta(n^{\log_b a}) & a > b^k \\ \Theta(n^k) & a< b^k \\ \Theta(n^k\log n ) & a = b^k \end{cases}
$$ 