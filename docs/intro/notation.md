author: sshwy, hsfzLZH1, Enter-tainer

本文列举在 OI wiki 中经常使用的符号与符号的行文规范，读者也可以在此查找与学习 LaTeX 的常见符号书写办法。

## 字体

| 名称               | 书写                         | 渲染效果                       | 备注                            |
| ---------------- | -------------------------- | -------------------------- | ----------------------------- |
| 正文中的公式           | `小于 $a$ 的素数`               | 小于 $a$ 的素数                 |                               |
| 正文中的英文           | `SPFA`                     | SPFA                       |                               |
| LaTeX 中的行文、中文与空格 | `$\text{something}$`       | $\text{something}$         | 使用非斜体，语义上应书写为 `\text`         |
| 函数名              | `\operatorname{something}` | $\operatorname{something}$ | 使用罗马体，语义上应书写为 `\operatorname` |
| 变量               | `x`                        | $x$                        | 使用意大利体，是 LaTeX 默认字体           |
| 多字母的变量           | `\textit{something}`       | $\textit{something}$       | 显示上和默认字体没有区别                  |
| 斜体               | `\mathit{something}`       | $\mathit{something}$       | 这是 LaTeX 默认字体                 |
| 常量               | `\mathrm{something}`       | $\mathrm{something}$       | 使用罗马体，支持大小写英文字母和数字            |
| 黑板粗体             | `\mathbb{something}`       | $\mathbb{something}$       | 仅支持大写英文字母。用于特殊集合的书写           |
| Roman 粗体         | `\mathbf{something}`       | $\mathbf{something}$       | 支持大小写英文字母、数字和大写希腊字母。用于特殊集合的书写 |

- 还有一些字体尚未有应用，仅列在这里，表示网站 OI wiki 的架构支持下列 LaTeX 字体。

| 名称        | 书写                               | 渲染效果                           | 备注                  |
| --------- | -------------------------------- | ------------------------------ | ------------------- |
| 打印机体      | `\mathtt{something}`             | $\mathtt{something}$           | 支持大小写英文字母、大写希腊字母和数字 |
| 无衬线体      | `\mathsf{something}`             | $\mathsf{something}$           | 支持大小写英文字母、大写希腊字母和数字 |
| Fraktur 体 | `\mathfrak{something}`           | $\mathfrak{something}$         | 支持大小写英文字母和数字        |
| Italic 粗体 | `\boldsymbol{something}`         | $\boldsymbol{something}$       |                     |
| 小型非斜体     | `$\scriptstyle\text{something}$` | $\scriptstyle\text{something}$ | 支持大小写英文字母和数字        |

## 字母

| 名称        | 书写                                                                                                                               | 渲染效果                                                                                                                           | 备注                     |
| --------- | -------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------ | ---------------------- |
| 大写希腊字母    | `$\Gamma \Delta \Theta \Lambda \Xi \Pi \Sigma \Upsilon \Phi \Psi \Omega$`                                                        | $\Gamma \Delta \Theta \Lambda \Xi \Pi \Sigma \Upsilon \Phi \Psi \Omega$                                                        | 共 $11$ 个，其他可以用形近拉丁字母替代 |
| 相似的小写希腊字母 | `$\gamma \digamma \epsilon \varepsilon \theta \vartheta \kappa \varkappa \pi \varpi \rho \varrho \sigma \varsigma \phi \varphi$` | $\gamma \digamma \epsilon \varepsilon \theta \vartheta \kappa \varkappa \pi \varpi \rho \varrho \sigma \varsigma \phi \varphi$ | 共 $8$ 对，不可混用           |
| 其他小写希腊字母  | `$\alpha \beta \delta \zeta \eta \iota \lambda \mu \nu \xi \omicron \tau \upsilon \chi \psi \omega$`                             | $\alpha \beta \delta \zeta \eta \iota \lambda \mu \nu \xi \omicron \tau \upsilon \chi \psi \omega$                             | 共 $16$ 个               |
| 希伯来符号     | `$\aleph \beth \gimel \daleth$`                                                                                                  | $\aleph \beth \gimel \daleth$                                                                                                  | 共 $4$ 个                |
| LaTeX 符号  | `$\rm{\LaTeX}$`                                                                                                                  | $\rm{\LaTeX}$                                                                                                                  | 在非必要的情形下写作 LaTeX 即可    |

## 一元函数

| 名称          | 书写                                | 渲染效果                            | 备注                                                              |
| ----------- | --------------------------------- | ------------------------------- | --------------------------------------------------------------- |
| 对数函数        | `$\log \ln \lg$`                  | $\log \ln \lg$                  |                                                                 |
| 指数函数        | `$\exp \mathrm{e}^x$`             | $\exp \mathrm{e}^x$             | 在指数结构较简单且没有歧义的情况下推荐使用 $\mathrm{e}^x$                            |
| 三角函数        | `$\sin \cos \tan \cot \sec \csc$` | $\sin \cos \tan \cot \sec \csc$ |                                                                 |
| 最大和最小       | `$\max \min$`                     | $\max \min$                     |                                                                 |
| 上确界和下确界     | `$\sup \inf$`                     | $\sup \inf$                     | 来源是 supremum 与 infimum 的简写                                      |
| 极限          | `$\lim$`                          | $\lim$                          | 当位于行间时，下标会自动记在极限记号下方                                            |
| 单位函数        | `$\varepsilon(n)$`                | $\varepsilon(n)$                |                                                                 |
| 恒等函数        | `$\operatorname{id}_k(n)$`        | $\operatorname{id}_k(n)$        | $\operatorname{id}_{1}(n)$ 有时记作 $\operatorname{id}(n)$          |
| 常数函数        | `$1(n)$`                          | $1(n)$                          |                                                                 |
| 除数函数        | `$\sigma_{k}(n)$`                 | $\sigma_{k}(n)$                 | $\sigma_{0}(n)$ 有时记作 $\tau(n)$，$\sigma_{1}(n)$ 有时记作 $\sigma(n)$ |
| 欧拉函数        | `$\varphi(n)$`                    | $\varphi(n)$                    |                                                                 |
| 莫比乌斯函数      | `$\mu(n)$`                        | $\mu(n)$                        |                                                                 |
| $n$ 的阶乘     | `$n!$`                            | $n!$                            | 当自变量不是单独一个数或一个量的时候应当加括号                                         |
| 括号          | `$\left(\right)$`                 | $\left(\right)$                 | 左右的 left 和 right 用于适配内容大小                                       |
| 小数部分        | `$\{x\}$`                         | $\{x\}$                         | 在数学类的书上用大括号表示实数的小数部分                                            |
| 向下取整或整数部分   | `$\lfloor x\rfloor [x]$`          | $\lfloor x\rfloor [x]$          | 在数学类的书上用中括号表示实数的整数部分，但在本站建议使用向下取整标记                             |
| 向上取整        | `$\lceil x\rceil$`                | $\lceil x\rceil$                |                                                                 |
| 对 $t$ 求微分   | `$\mathrm{d}t$`                   | $\mathrm{d}t$                   | 使用罗马体                                                           |
| 对 $t$ 求偏微分  | `$\partial t$`                    | $\partial t$                    |                                                                 |
| $\Theta$ 符号 | `$\Theta(n)$`                     | $\Theta(n)$                     |                                                                 |
| 大 O 符号      | `$O(n)$`                          | $O(n)$                          | 来源于希腊字母 Omicron，由于字形相同，写为拉丁字母 O                                 |
| 小 O 符号      | `$o(n)$`                          | $o(n)$                          | 来源于希腊字母 omicron，由于字形相同，写为拉丁字母 o                                 |
| $\Omega$ 符号 | `$\Omega(n)$`                     | $\Omega(n)$                     |                                                                 |
| $\omega$ 符号 | `$\omega(n)$`                     | $\omega(n)$                     |                                                                 |

## 二元函数与二元关系

| 名称         | 书写                           | 渲染效果                       | 备注                                                          |
| ---------- | ---------------------------- | -------------------------- | ----------------------------------------------------------- |
| 等价关系       | `$\iff$`                     | $\iff$                     |                                                             |
| 叉乘和点乘      | `$a\times b a\cdot b$`       | $a\times b a\cdot b$       |                                                             |
| 最大公约数      | `$\gcd$`                     | $\gcd$                     | 在一些书上用小括号 `()` 表示最大公约数，本站使用 gcd 函数写法                        |
| 最小公倍数      | `$\operatorname{lcm}$`       | $\operatorname{lcm}$       | 在 LaTeX 默认内置中没有 lcm 函数。在一些书上用中括号 `[]` 表示最小公倍数，本站使用 lcm 函数写法 |
| 两数互素       | `$\gcd(x,y)=1$`              | $\gcd(x,y)=1$              | 不建议写成垂直记号，容易费解                                              |
| 两数大小关系     | `$= > < \geq \leq \neq$`     | $= > < \geq \leq \neq$     | `\ne` 和 `\neq` 显示效果完全相同                                     |
| 整除和不整除     | `$\mid \not\mid$`            | $\mid \not\mid$            | 不建议使用 `\|`，两侧的空间会偏窄                                         |
| 余数         | `$x\bmod y$`                 | $x\bmod y$                 |                                                             |
| 同余和不同余     | `$\equiv \not\equiv$`        | $\equiv \not\equiv$        |                                                             |
| 模 $n$ 的同余式 | `$\pmod{n}$`                 | $\pmod{n}$                 |                                                             |
| 分数         | `$\dfrac{1}{2}$`             | $\dfrac{1}{2}$             |                                                             |
| 组合数        | `$\dbinom{n}{m}$`            | $\dbinom{n}{m}$            | 在本站不建议使用符号 $C$ 表示组合数                                        |
| 第一类斯特林数    | `$x\brack y$`                | $x\brack y$                | 在一些书上用小写 $s$ 表示第一类斯特林数                                      |
| 第二类斯特林数    | `$x\brace y$`                | $x\brace y$                | 在一些书上用大写 $S$ 表示第二类斯特林数                                      |
| 二次剩余符号     | `$\left(\frac{a}{p}\right)$` | $\left(\frac{a}{p}\right)$ |                                                             |

## 常数

| 名称   | 书写           | 渲染效果         | 备注                                                                       |
| ---- | ------------ | ------------ | ------------------------------------------------------------------------ |
| 自然常数 | `\mathrm{e}` | $\mathrm{e}$ |                                                                          |
| 虚数单位 | `\mathrm{i}` | $\mathrm{i}$ |                                                                          |
| 圆周率  | `\pi`        | $\pi$        |                                                                          |
| 黄金分割 | `$\Phi$`     | $\Phi$       | 为 [cppreference](https://zh.cppreference.com/w/cpp/numeric/constants) 写法 |
| 欧拉常数 | `$\gamma$`   | $\gamma$     |                                                                          |

## 大型运算符

大型运算符主要有求和与求积两个符号，其他还有各种积分符号等。

| 名称 | 书写        | 渲染效果    | 备注                          |
| -- | --------- | ------- | --------------------------- |
| 求和 | `$\sum$`  | $\sum$  | 大型运算符应该行间使用，此时上下标位于运算符顶部和底部 |
| 求积 | `$\prod$` | $\prod$ | 大型运算符应该行间使用，此时上下标位于运算符顶部和底部 |

求和符号：$\sum$ 符号，表示满足特定条件的数的和。举几个例子：

- $\sum_{i=1}^n i$ 表示 $1+2+\dotsb+n$ 的和。其中 $i$ 是一个变量，在求和符号的意义下 $i$ 通常是 **正整数或者非负整数**（除非特殊说明）。这个式子的含义可以理解为，$i$ 从 $1$ 循环到 $n$，所有 $i$ 的和。这个式子用代码的形式很容易表达。当然，学过简单的组合数学的同学都知道 $\sum_{i=1}^n i=\dfrac{n(n+1)}{2}$。
- $\sum_{S\subseteq T}|S|$ 表示所有被 $T$ 包含的集合的大小的和。
- $\sum_{p\le n,p\perp n}1$ 表示的是 $n$ 以内有多少个与 $n$ 互质的数，即 $\varphi(n)$，$\varphi$ 是欧拉函数。

求积符号：$\prod$ 符号，表示满足特定条件的数的积。举几个例子：

- $\prod_{i=1}^ni$ 表示 $n$ 的阶乘，即 $n!$。在组合数学常见符号中会讲到。
- $\prod_{i=1}^na_i$ 表示 $a_1\times a_2\times a_3\times \dotsb\times a_n$。
- $\prod_{x|d}x$ 表示 $d$ 的所有因数的乘积。

求和与求积两个符号也可能有其他的界限描述方式，视具体情况而定，不再一一列举。在行间公式中，求和符号与求积符号的上下条件会放到符号的上面和下面，所以求和与求积两个符号必须写作 $\sum$ 和 $\prod$，不能写作 $\Sigma$ 和 $\Pi$。

## 特殊记号

| 名称              | 书写                     | 渲染效果                 | 备注                              |
| --------------- | ---------------------- | -------------------- | ------------------------------- |
| 无穷              | `$\infty$`             | $\infty$             |                                 |
| 居中省略号           | `$\cdots$`             | $\cdots$             |                                 |
| 下对齐省略号          | `$\ldots$`             | $\ldots$             | `$\ldots$` 与 `$\dots$` 显示效果完全相同 |
| 竖直省略号           | `$\vdots$`             | $\vdots$             |                                 |
| 斜向省略号           | `$\ddots$`             | $\ddots$             |                                 |
| 三下标数组           | `$f_{i,j,k} f(i,j,k)$` | $f_{i,j,k} f(i,j,k)$ |                                 |
| 多项式展开中 $n$ 项的系数 | `$[n]f(z)$`            | $[n]f(z)$            |                                 |
| 空集              | `$\varnothing$`        | $\varnothing$        |                                 |
| 实数集             | `$\mathbf{R}$`         | $\mathbf{R}$         | 该写法来源于人民教育出版社普通高中数学教材 A 版       |
| 正整数集            | `$\mathbf{N}^*$`       | $\mathbf{N}^*$       | 该写法来源于人民教育出版社普通高中数学教材 A 版       |

## 参考资料

- [LaTeX 数学公式大全 - Iowa_BattleShip 的博客 - 洛谷博客](https://www.luogu.com.cn/blog/IowaBattleship/latex-gong-shi-tai-quan?tdsourcetag=s_pctim_aiomsg)
