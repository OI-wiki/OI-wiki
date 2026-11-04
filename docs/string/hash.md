## 定义

我们定义一个把字符串映射到整数的函数 $f$，这个 $f$ 称为是 Hash 函数．

我们希望这个函数 $f$ 可以方便地帮我们判断两个字符串是否相等．

## Hash 的思想

Hash 的核心思想在于，将输入映射到一个值域较小、可以方便比较的范围．

??? warning "Warning"
    这里的「值域较小」在不同情况下意义不同．
    
    在 [哈希表](../ds/hash.md) 中，值域需要小到能够接受线性的空间与时间复杂度．
    
    在字符串哈希中，值域需要小到能够快速比较（$10^9$、$10^{18}$ 都是可以快速比较的）．
    
    同时，为了降低哈希冲突率，值域也不能太小．

## 性质

具体来说，哈希函数最重要的性质可以概括为下面两条：

1.  在 Hash 函数值不一样的时候，两个字符串一定不一样；

2.  在 Hash 函数值一样的时候，两个字符串不一定一样（但有大概率一样，且我们当然希望它们总是一样的）．

    我们将 Hash 函数值一样但原字符串不一样的现象称为哈希碰撞．

## 解释

我们需要关注的是什么？

时间复杂度和 Hash 的准确率．

通常我们采用的是多项式 Hash 的方法，对于一个长度为 $l$ 的字符串 $s$ 来说，我们可以这样定义多项式 Hash 函数：$f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$．例如，对于字符串 $xyz$，其哈希函数值为 $xb^2+yb+z$．

特别要说明的是，也有很多人使用的是另一种 Hash 函数的定义，即 $f(s) = \sum_{i=1}^{l} s[i] \times b^{i-1} \pmod M$，这种定义下，同样的字符串 $xyz$ 的哈希值就变为了 $x+yb+zb^2$ 了．

显然，上面这两种哈希函数的定义函数都是可行的，但二者在之后会讲到的计算子串哈希值时所用的计算式是不同的，因此千万注意 **不要弄混了这两种不同的 Hash 方式**．

由于前者的 Hash 定义计算更简便、使用人数更多、且可以类比为一个 $b$ 进制数来帮助理解，所以本文下面所将要讨论的都是使用 $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$ 来定义的 Hash 函数．

还有，有时为了方便和扩大模数，我们在 C++ 中我们会使用 `unsigned long long` 来定义 Hash 函数的结果．由于 C++ 的特性，我们相当于把模数 $M$ 定为 $2^{64}$，也是一个不错的选择．

准确率会在后面讨论．

## Hash 的错误率分析

### Hash 冲突

Hash 冲突是指两个不同的字符串映射到相同的 Hash 值．

我们设 Hash 的取值空间（所有可能出现的 Hash 值的数量）为 $d$，计算次数（要计算的字符串数量）为 $n$．

则 Hash 冲突的概率为：

$$
p(n,d) = 1 - \frac{d!}{d^n\left(d-n\right)!} \approx 1 - \exp(-\frac{n(n-1)}{2d} )
$$

??? note "证明"
    当 Hash 中每个值生成概率相同时，Hash 不冲突的概率为：
    
    $$
    \overline{p}(n,d) = 1 \cdot \left (1 - \frac{1}{d} \right) \cdot \left ( 1- \frac{2}{d}\right) \cdots \left ( 1- \frac{n-1}{d}\right)
    $$
    
    化简得到：
    
    $$
    \begin{aligned}
    \overline{p}(n,d) 
    & = \frac{d}{d}\cdot \frac{d-1}{d}\cdot \frac{d-2}{d} \cdots \frac{d-n+1}{d}\\
    & = \frac{d\cdot (d-1)\cdot (d-2)\cdots(d-n+1)}{d^n}\\
    & = \frac{d!}{d^n\left(d-n\right)!}
    \end{aligned}
    $$
    
    则 Hash 冲突的概率为：
    
    $$
    p(n,d) = 1 - \frac{d!}{d^n\left(d-n\right)!}
    $$
    
    这个公式还是太复杂了，我们进一步化简．
    
    根据泰勒公式：
    
    $$
    \exp(x) = \sum_{k=0}^{\infty}\frac{x^k}{k!}=1+x+\frac{x^2}{2}+\frac{x^3}{6}+\frac{x^4}{24}+\cdots
    $$
    
    当 $x$ 为一个极小值时，$\exp(x)$ 趋近于 $1+x$．
    
    将它带入 Hash 不冲突的原始公式：
    
    $$
    \overline{p}(n,d) \approx 1 \cdot \exp(-\frac{1}{d}) \cdot \exp(-\frac{2}{d}) \cdots \exp(-\frac{n-1}{d})
    $$
    
    化简：
    
    $$
    \begin{aligned}
    \overline{p}(n,d) & \approx \exp(-\frac{1}{d} - \frac{2}{d} - \cdots -\frac{n-1}{d})\\
    &=\exp(-\frac{n(n-1)}{2d} )
    \end{aligned}
    $$
    
    则 Hash 冲突的概率为：
    
    $$
    p(n,d) \approx 1 - \exp(-\frac{n(n-1)}{2d})
    $$

### 攻击方法总表

不同的 Hash 参数需要用不同的方法攻击．下表汇总了常见攻击方式的适用场景和代价，详细做法见后文各小节．

| 方法                                | 适用场景                  | 复杂度/算法            | 串长                   | 备注                               |
| ----------------------------------- | ------------------------- | ---------------------- | ---------------------- | ---------------------------------- |
| [Thue–Morse 序列](#卡自然溢出-hash) | 自然溢出 $2^{64}$         | $O(1)$                 | $2^{10}$               | 对任意底数同时成立                 |
| [生日攻击](#生日攻击)               | 小模数（$p<2^{32}$）      | $O(\sqrt p)$           | 约 $6$                 | 不依赖多项式结构，异或 Hash 也能卡 |
| [树攻击](#树攻击)                   | 大模数、固定底数          | $2^{O(\sqrt{\log p})}$ | $2^{O(\sqrt{\log p})}$ | 只适用于多项式 Hash                |
| [多树攻击](#多树攻击)               | 大模数、想要短串          | 比树攻击慢             | 可缩短                 | 用运行时间换串长                   |
| [格基约简](#格基约简攻击)           | 中等以上字母表、多重 Hash | LLL/BKZ                | 约 $12$–$108$          | 二进制字母表效果差                 |
| [逐个击破](#逐个击破)               | 多重 Hash                 | 各层之和               | 各层之积               | 通用组合方法                       |

### 卡大模数 Hash

#### 生日攻击

生日攻击通过随机生成大量字符串，利用生日悖论寻找 Hash 碰撞．

注意到这个公式：

$$
p(n,d) \approx 1 - \exp(-\frac{n(n-1)}{2d} )
$$

为了卡掉 Hash，我们要满足以下条件：

1.  可能出现的字符串种数要大于模数．
2.  $1-p(n,d)$ 要尽量小．

举个例子：

若字符集为 **大小写字母和数字**，模数为 $10^9+7$ 时：

$\log_{62}(10^9+7)\approx 5.02$，所以取字符串长度为 $6$．

$p(10^6,10^9+7) \approx 1$

所以对于这个范围，我们随机生成 $10^6$ 个长度为 $6$ 的字符串，其中存在两个字符串 Hash 值相同的概率几乎为 $100\%$．

#### 树攻击

生日攻击需要生成 $O(\sqrt p)$ 个字符串．当模数 $p$ 达到 $10^{18}$ 时，这个代价无法接受；但如果底数 $b$ 固定，可以利用多项式结构在 $2^{O(\sqrt{\log p})}$ 的时间内构造长度同为 $2^{O(\sqrt{\log p})}$ 的碰撞．

设两个等长串为 $S,T$，令 $\alpha_i=S_i-T_i$，则 $|\alpha_i|\le |\Sigma|-1$，且

$$
\sum_{i=1}^{L}\alpha_i b^{L-i}\equiv 0 \pmod p
$$

就是 $S$ 与 $T$ 碰撞的充要条件．树攻击（tree attack）要做的就是找到一组非零的 $\alpha_i$，再把正、负系数分别分配给两个字符串的字符．

??? note "构造细节"
    树攻击维护若干 cluster，每个 cluster 是一个连续区间的系数集合，并记录它在当前区间内的带权和 $S(C)$．初始时有 $2^k$ 个 cluster，每个只含一个系数 $\alpha_i=1$．
    
    合并两个相邻 cluster 时，把其中一个 cluster 的所有系数取负，再与另一个合并；实现上把 cluster 存成二叉树，每个节点记录自己的和，合并时新建一个节点、两个子节点分别是原来的 cluster，和按区间长度乘以相应的 $b$ 的幂后相减．为避免负数，必要时交换两个 cluster．
    
    每一阶段把所有 cluster 按 $S(C)$ 排序，然后合并相邻的两个 cluster，一轮后 cluster 数量减半．如果某个 cluster 的和为 $0$，就把不在该 cluster 中的 $\alpha_i$ 全部置为 $0$，并结束；如果 $k$ 阶段后仍未找到，就增大 $k$ 重试．
    
    在 $S(C)$ 初始近似均匀随机的假设下，期望 $k\approx\sqrt{2\lg p}+1$；串长为 $n=2^k=2^{O(\sqrt{\log p})}$，构造时间为 $\Theta(n)$．

??? note "一个极小的例子"
    取 $p=101$、$b=7$、$L=6$，差值序列 $\alpha=(-1,-1,-1,-1,1,-1)$ 满足
    
    $$
    \sum_{i=1}^{6}\alpha_i 7^{6-i}=-7^5-7^4-7^3-7^2+7-1\equiv 0\pmod{101}
    $$
    
    按 $\alpha_i<0$ 时一个串取 `a`、另一个取 `b`，$\alpha_i>0$ 时相反的规则，可以得到两个串 `aaaaba` 和 `bbbbab`；直接计算可知它们的 Hash 值都等于 $52$．

树攻击只依赖多项式 Hash 的线性结构，因此对二进制字母表也适用；但它对异或 Hash 无效．此外，底数必须是固定的：如果底数在运行时随机选取，攻击者就无法预先构造出碰撞．[^ref1]

如果树攻击产生的串太长，可以用多树攻击（multi-tree attack）换取更短的串，见 [多树攻击](#多树攻击)．

??? note "卡回文串"
    树攻击也可以用于回文串．以偶回文串为例，Sshwy 的中文译述给出了如下化归：把回文串两边的系数对称相减，令 $h_i=d_i-d_{2L-1-i}$，就得到一组普通的树攻击目标；对 $h_i$ 做一次树攻击后，再用字符把正负系数拼成回文串即可．[^ref3]

#### 多树攻击

树攻击的产物可能很长（例如 $p=2^{61}-1$ 时单树攻击的串长可达 $2048$）．多树攻击（multi-tree attack）在每个 cluster 中保留最小的 $m$ 个和，而不是只保留一个；合并两个 cluster 时用堆和 2m-pointer walk 取出最小的 $m$ 个和．这样会把运行时间乘以一个与 $m$ 有关的因子，但能显著缩短最终串长．

在 $p=2^{61}-1$ 时，取 $m\approx 10^5$ 可以在约 $0.4$ 秒内得到长度为 $128$ 的碰撞．多树攻击的期望长度没有简单的严格界，实践数据比渐近分析更有参考价值．[^ref1][^ref3]

#### 格基约简攻击

当同时使用多组固定模数和底数（例如双哈希）时，可以把「寻找差值序列」转化为格上的短向量问题，用 LLL 或 BKZ 算法求解．与树攻击一次只处理一个模数不同，格基约简可以同时卡掉多组 Hash．

给定 $n$ 组模数和底数 $(p_i,q_i)$，串长为 $L$，我们希望找到非零整数数组 $d_0,\dots,d_{L-1}$，使得

$$
\sum_{j=0}^{L-1} d_j q_i^j\equiv 0 \pmod{p_i}\qquad (i=1,\dots,n),
$$

且 $|d_j|<26$．如果找到了这样的 $d$，就可以用 $d_j$ 的正负构造两个只含小写字母的字符串：$d_j>0$ 时一个串取 `'a' + d_j`、另一个取 `'a'`；$d_j<0$ 时反过来；$d_j=0$ 时两个串都取 `'a'`．这样两个串的差恰好是 $d_j$，因而对所有 $i$ 都碰撞．

??? note "格基构造"
    按 CF 129538 的写法，构造 $(n+L)\times(n+L)$ 的矩阵
    
    $$
    M=\begin{bmatrix}
    \lambda Q & I\\
    \lambda P & 0
    \end{bmatrix},
    $$
    
    其中 $Q$ 是 $L\times n$ 矩阵，$Q_{ji}=q_i^j\bmod p_i$；$P=\operatorname{diag}(p_1,\dots,p_n)$；$I$ 是 $L$ 阶单位阵；$\lambda$ 是一个足够大的放大系数．
    
    矩阵的每一行都满足：后 $L$ 个分量按第 $i$ 组参数计算出的 Hash 值，对 $p_i$ 取模后等于前 $n$ 个分量中的第 $i$ 个．对 $M$ 做 LLL 约简后，如果某一行前 $n$ 个分量全为 $0$，后 $L$ 个分量满足 $|d_j|<26$，这一行的后 $L$ 个分量就是我们要的 $d$．放大 $\lambda$ 会惩罚非零的前 $n$ 个分量，使短向量更倾向于满足前 $n$ 个分量为 $0$．

这里按 CF 129538 的下标约定，$j$ 从 $0$ 开始、幂次从左到右递增；与本文前面的定义方向相反，但构造出的碰撞串同样有效．[^ref2]

CF 60442 给出了另一种等价的格基写法，并用 Sage 的 `LLL()`/`BKZ()` 做了实验．在 $p=2^{61}-1$、底数随机的情况下，LLL 对 $n=1,2,3,4,5,6$ 组 Hash 得到的串长分别为 $12,23,34,48,60,77$；$n=7$ 时串长增至 $301$，$n=8$ 时 LLL 在 $1500$ 以内找不到碰撞．BKZ 的近似效果更好但更慢：取 `block_size=10` 时，$n=8$ 的串长为 $108$，耗时约 $5.33$ 秒；取 `block_size=25` 时串长可降到 $96$，但耗时约 $26.7$ 秒．[^ref1]

格基约简的适用条件比树攻击更苛刻：

-   字符必须映射到连续的值，且字母表不能太小；对二进制字母表、$n>1$ 的情况效果很差．
-   如果要在组合攻击中使用，它必须是第一个攻击，因为后续攻击会缩小字母表．
-   它只对固定的模数和底数有效；随机底数或随机模数会使预构造的格失效．

实际卡题时通常不需要自己实现 LLL；CF 129538 提供了一个在浏览器中运行的在线工具，输入模数、底数、串长等参数即可生成碰撞．[^ref2]关于 LLL 算法本身的细节，可以参考论文*An LLL Algorithm with Quadratic Complexity*．[^ref4]

### 卡自然溢出 Hash

自然溢出 Hash 有专门的、更简单的卡法，下面按底数的奇偶性分类讨论．

首先，这种 Hash 是形如 $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i}$，我们根据 $b$ 来分类讨论．

#### b 为偶数

此时 $f(s) = s_1\cdot b^l + s_2\cdot b^{l-1} + \cdots + s_l\cdot b \pmod M$，其中 $M$ 为 $2^{64}$．

容易发现若 $l \ge 64$，$s_i\cdot b^l \equiv 0 \pmod M$．

所以我们只要构造形如：

`aaa...a`

`baa...a`

且长度大于 $64$ 的字符串就能冲突．

#### b 为奇数

定义 $!s_i$ 为把 $s_i$ 中所有字符反转．

例：

$s_i = abaab$

$!s_i = babba$

即把 `a` 变成 `b`，把 `b` 变成 `a`．

再定义 $hash_i$ 为 $s_i$ 的 Hash 值，$!hash_i$ 为 $!s_i$ 的 Hash 值．

不断构造 $s_i = s_{i-1} + !s_{i-1}$．

$s_{12}$ 和 $!s_{12}$ 就是我们要的两个字符串．

??? note "推导"
    首先，有：
    
    $$
    \begin{aligned}
    hash_i = hash_{i-1}\cdot base^{2^{i-2}} + !hash_{i-1}\\
    !hash_{i} = !hash_{i-1}\cdot base^{2^{i-2}}+hash_{i-1}
    \end{aligned}
    $$
    
    尝试相减：
    
    $$
    \begin{aligned}
    &hash_i - !hash_i\\
    =\ &hash_{i-1}\cdot base^{2^{i-2}} + !hash_{i-1}-(!hash_{i-1}\cdot base^{2^{i-2}}+hash_{i-1})\\
    =\ &(hash_{i-1}-!hash_{i-1})\cdot (base^{2^{i-2}}-1)
    \end{aligned}
    $$
    
    发现出现了 $2^i$，但是原式太复杂，尝试换元：
    
    设：
    
    $$
    \begin{aligned}
    f_i = hash_i - !hash_i\\
    g_i = base^{2^{i-2}}-1
    \end{aligned}
    $$
    
    根据原式得：
    
    $$
    \begin{aligned}
    f_i &= f_{i-1} \cdot g_i\\
        &=f_1 \cdot g_2 \cdot g_3 \cdots g_{i}\\
    \end{aligned}
    $$
    
    因为 $base^{2^{i-2}}$ 一定是奇数，所以 $g_i$ 一定是偶数．
    
    所以：
    
    $$
    2^{i-1} | f_i
    $$
    
    但这样太大了，$i-1\ge 64$ 才能卡掉，继续化简：
    
    $$
    g_i = base^{2^{i-2}}-1 = (base^{2^{i-3}}-1)\cdot(base^{2^{i-3}}+1)\\
    $$
    
    即 $g_i$ 为 $g_{i-1} \cdot c\ (c \equiv 0 \pmod 2)$ 的形式．
    
    所以 $2 | g_2$，$4 | g_3$，……，即
    
    $$
    \begin{aligned}
    & 2^{i-1} &| g_i\\
    &2^1\cdot2^2\cdot2^3\cdots2^{i-1} &| f_i\\
    &2^{i(i-1)/2} &| f_i
    \end{aligned}
    $$
    
    即当 $i=12$ 时就可以使 $2^{64} | hash_i - !hash_i$ 达到要求．

### 卡多值 Hash

双哈希通常能挡住直接的生日攻击：两组模数约为 $10^9$ 时，可能的 Hash 值有 $p_1p_2\approx 10^{18}$ 种，生日攻击需要约 $\sqrt{p_1p_2}$ 个串，代价过高．但多值 Hash 仍有两类破法：逐个击破和中国剩余定理．

#### 逐个击破

逐个击破（composition attack）先卡掉第一组 Hash，再把得到的一对碰撞串当作新的字母表，去卡第二组 Hash．

具体地，先找到 $h_1$ 的一对等长碰撞串 $S,T$．所有由 $S,T$ 拼接而成的串在 $h_1$ 下都相同；于是可以把 $S,T$ 看成两个「字符」，对 $h_2$ 再做一次生日攻击或树攻击．得到的串自动也是 $h_1$ 的碰撞．

设各层攻击的串长为 $L_1,L_2,\dots$，则最终串长约为各层串长之积，增长非常快；运行时间约为各层攻击时间之和．$h_2$ 的底数会变成 $b^{|S|}$，字符值变成 $h_2(S),h_2(T)$．如果其中一组是 $2^{64}$ 自然溢出，可以用 Thue–Morse 序列代替该层的生日攻击；如果模数很大，可以用树攻击代替生日攻击．[^ref1]

逐个击破的缺点是字母表会迅速缩小；格基约简在二进制字母表上效果很差，因此如果要在组合攻击中使用 LLL，它必须是第一个攻击．

#### 中国剩余定理

如果各组 Hash 使用相同的底数（或可以化为同一底数），还可以用中国剩余定理（CRT）把多个模数合并成一个：令

$$
M=\operatorname{lcm}(p_1,\dots,p_n),
$$

先用 CRT 把「对所有 $p_i$ 同余」合并成「模 $M$ 同余」，再对 $M$ 做一次树攻击．

CRT 方法要求 $M$ 不能太大，否则树攻击和生日攻击都会变慢；它的优点是可以同时卡掉双哈希的回文串．如果各组的底数不同，CRT 不能直接合并，此时应使用逐个击破或格基约简．

需要说明的是，CRT 这一节来自 Sshwy 的中文译述，CF 60442 原文没有对应的 CRT 小节；回文扩展也是同一来源．[^ref3]

### 例题

???+ note "[例题：BZOJ 3097 Hash Killer I](https://hydro.ac/p/bzoj-P3097)"
    给定一个用 **自然溢出** 实现的 Hash，要求构造一个字符串来卡掉它．

???+ note "[例题：BZOJ 3097 Hash Killer II](https://hydro.ac/p/bzoj-P3098)"
    给定一个用 **大模数** 实现的 Hash，要求构造一个字符串来卡掉它．

???+ note "[例题：洛谷 U461211 字符串 Hash（数据加强）](https://www.luogu.com.cn/problem/U461211)"
    给定 $n$ 个字符串，判断不同的字符串有多少个．

## Hash 的改进

### 多值 Hash

看了上面这么多的卡法，当然也有解决办法．

多值 Hash，就是有多个 Hash 函数，每个 Hash 函数的模数不一样，这样就能解决 Hash 冲突的问题．

判断时只要有其中一个的 Hash 值不同，就认为两个字符串不同，若 Hash 值都相同，则认为两个字符串相同．

一般来说，双值 Hash 就够用了．但前提是各组的模数、底数足够大且相互独立；固定参数的双哈希仍可能被格基约简或 CRT 攻击（见上文）．

### 随机化

面对上面的攻击，最有效的防御是让 Hash 参数在运行时随机化，而不是固定写在代码里．

**随机底数** 固定一个素数模数 $p$，在运行时从 $[0,p-1]$ 中均匀随机选取底数 $b$（实际实现中应取 $b$ 大于字符集大小）．对任意两个不同的等长串 $S,T$，它们的差是一个次数小于串长 $L$ 的多项式 $P(b)$．由于 $S\ne T$，$P$ 不是零多项式；在域 $\mathbb F_p$ 上，$P$ 至多有 $L-1$ 个根，因此

$$
\Pr[h(S)=h(T)]\le \frac{L-1}{p}.
$$

例如 $L=10^5$、$p=10^9+7$ 时，碰撞概率约为 $10^{-4}$．

**多值 Hash** 如果每组 Hash 的随机选择相互独立，总失败概率是各组失败概率之积．两组 $p=10^9+7$ 的随机底数 Hash 失败概率约为 $10^{-8}$，四组约为 $10^{-16}$；取 $p=2^{31}-1$ 时，两组和四组分别约为 $2.1\times 10^{-9}$ 和 $4.7\times 10^{-18}$．[^ref1]

**随机模数** 固定底数，从 $[N,2N-1]$ 中随机选取素数 $p$．这种方案的界略差：$L=10^5$、底数 $a=26$、$N=10^9$ 时，碰撞概率约为 $3\times 10^{-4}$．[^ref1]

**更大的模数** 使用更大的模数可以降低碰撞概率，但乘法和取模也会变慢．$2^{61}-1$ 是梅森素数，乘法和取模可以用移位和掩码完成，只比 30 位模数慢约 $5\%$，是性价比较高的选择．[^ref1]

**自然溢出** 需要特别强调：$2^{64}$ 不是素数，Thue–Morse 攻击对任意底数都成立，因此随机底数也救不了自然溢出 Hash．不要把 `unsigned long long` 溢出当作安全的 Hash．

**多次比较** 如果程序要做 $m$ 次比较，由并集界（union bound），总失败概率不超过 $m$ 倍的单次失败概率．如果要保证 $n$ 个串两两不同，涉及约 $\dbinom{n}{2}$ 对比较，所以实际中通常需要 2 到 4 组 Hash；如果使用 $p=2^{61}-1$，两组可能就足够了．[^ref1]

**错误的随机化** 随机化本身也可能被攻击：

-   固定种子：随机序列完全可复现，攻击者可以直接针对它构造数据．
-   `rand() % 100`：底数只有 100 种可能，可以对每个底数分别构造碰撞再合并．
-   `rand()` 的范围：在 Codeforces 上 `rand()` 只产生 15 位值，最多 $2^{15}$ 种底数．
-   `Time(NULL)`：每秒只变化一次，攻击者可以在相邻时间窗口内预先生成测试数据．
-   `std::random_device`：在 MinGW/Codeforces 上可能是确定性的，等价于固定种子．

正确的做法是用高精度时间（`std::chrono::high_resolution_clock` 或 `steady_clock`）、`__builtin_ia32_rdtsc()`、堆地址或 `rdrand` 作为种子，再用 `std::seed_seq` 组合后喂给 `std::mt19937`．[^ref1]

??? note "安全素数"
    选择安全素数（即 $(p-1)/2$ 也是素数）可以保证 $b^e\bmod p$ 的周期至少为 $(p-1)/2$（$b\ne 0,1,-1$），从而避免某些子串匹配场景下的误判．$10^9+7$ 恰好是安全素数．不过评论区对这种做法有争论：安全素数并不能阻止针对固定参数的构造攻击，随机化仍然更重要．[^ref1]

### 多次询问子串哈希

单次计算一个字符串的哈希值复杂度是 $O(n)$，其中 $n$ 为串长，与暴力匹配没有区别，如果需要多次询问一个字符串的子串的哈希值，每次重新计算效率非常低下．

一般采取的方法是对整个字符串先预处理出每个前缀的哈希值，将哈希值看成一个 $b$ 进制的数对 $M$ 取模的结果，这样的话每次就能快速求出子串的哈希了：

令 $f_i(s)$ 表示 $f(s[1..i])$，即原串长度为 $i$ 的前缀的哈希值，那么按照定义有 $f_i(s)=s[1]\cdot b^{i-1}+s[2]\cdot b^{i-2}+\dots+s[i-1]\cdot b+s[i]$

现在，我们想要用类似前缀和的方式快速求出 $f(s[l..r])$，按照定义有字符串 $s[l..r]$ 的哈希值为 $f(s[l..r])=s[l]\cdot b^{r-l}+s[l+1]\cdot b^{r-l-1}+\dots+s[r-1]\cdot b+s[r]$

对比观察上述两个式子，我们发现 $f(s[l..r])=f_r(s)-f_{l-1}(s) \times b^{r-l+1}$ 成立（可以手动代入验证一下），因此我们用这个式子就可以快速得到子串的哈希值．其中 $b^{r-l+1}$ 可以 $O(n)$ 的预处理出来然后 $O(1)$ 的回答每次询问（当然也可以快速幂 $O(\log n)$ 的回答每次询问）．

## 实现

### 模数 Hash：

注：效率较低，实际使用中不推荐．

=== "C++"
    ```cpp
    using std::string;
    
    constexpr int M = 1e9 + 7;
    constexpr int B = 233;
    
    using ll = long long;
    
    int get_hash(const string& s) {
      int res = 0;
      for (int i = 0; i < s.size(); ++i) {
        res = ((ll)res * B + s[i]) % M;
      }
      return res;
    }
    
    bool cmp(const string& s, const string& t) {
      return get_hash(s) == get_hash(t);
    }
    ```

=== "Python"
    ```python
    M = int(1e9 + 7)
    B = 233
    
    
    def get_hash(s):
        res = 0
        for char in s:
            res = (res * B + ord(char)) % M
        return res
    
    
    def cmp(s, t):
        return get_hash(s) == get_hash(t)
    ```

### 双值 Hash：

=== "C++"
    ```cpp
    using ull = unsigned long long;
    ull base = 131;
    ull mod1 = 212370440130137957, mod2 = 1e9 + 7;
    
    ull get_hash1(std::string s) {
      int len = s.size();
      ull ans = 0;
      for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod1;
      return ans;
    }
    
    ull get_hash2(std::string s) {
      int len = s.size();
      ull ans = 0;
      for (int i = 0; i < len; i++) ans = (ans * base + (ull)s[i]) % mod2;
      return ans;
    }
    
    bool cmp(const std::string s, const std::string t) {
      bool f1 = get_hash1(s) != get_hash1(t);
      bool f2 = get_hash2(s) != get_hash2(t);
      return f1 || f2;
    }
    ```

=== "Python"
    ```python
    def get_hash1(s: str) -> int:
        base = 131
        mod1 = 212370440130137957
        ans = 0
        for char in s:
            ans = (ans * base + ord(char)) % mod1
        return ans
    
    
    def get_hash2(s: str) -> int:
        base = 131
        mod2 = 1000000007
        ans = 0
        for char in s:
            ans = (ans * base + ord(char)) % mod2
        return ans
    
    
    def cmp(s: str, t: str) -> bool:
        f1 = get_hash1(s) != get_hash1(t)
        f2 = get_hash2(s) != get_hash2(t)
        return f1 or f2
    ```

## Hash 的应用

### 字符串匹配

求出模式串的哈希值后，求出文本串每个长度为模式串长度的子串的哈希值，分别与模式串的哈希值比较即可．

### 允许 $k$ 次失配的字符串匹配

问题：给定长为 $n$ 的源串 $s$，以及长度为 $m$ 的模式串 $p$，要求查找源串中有多少子串与模式串匹配．$s'$ 与 $s$ 匹配，当且仅当 $s'$ 与 $s$ 长度相同，且最多有 $k$ 个位置字符不同．其中 $1\leq n,m\leq 10^6$，$0\leq k\leq 5$．

这道题无法使用 KMP 解决，但是可以通过哈希 + 二分来解决．

枚举所有可能匹配的子串，假设现在枚举的子串为 $s'$，通过哈希 + 二分可以快速找到 $s'$ 与 $p$ 第一个不同的位置．之后将 $s'$ 与 $p$ 在这个失配位置及之前的部分删除掉，继续查找下一个失配位置．这样的过程最多发生 $k$ 次．

总的时间复杂度为 $O(m+kn\log_2m)$．

### 最长回文子串

二分答案，判断是否可行时枚举回文中心（对称轴），哈希判断两侧是否相等．需要分别预处理正着和倒着的哈希值．时间复杂度 $O(n\log n)$．

这个问题可以使用 [manacher 算法](./manacher.md) 在 $O(n)$ 的时间内解决．

通过哈希同样可以 $O(n)$ 解决这个问题，具体方法就是记 $R_i$ 表示以 $i$ 作为结尾的最长回文的长度，那么答案就是 $\max_{i=1}^nR_i$．考虑到 $R_i\leq R_{i-1}+2$，因此我们只需要暴力从 $R_{i-1}+2$ 开始递减，直到找到第一个回文即可．记变量 $z$ 表示当前枚举的 $R_i$，初始时为 $0$，则 $z$ 在每次 $i$ 增大的时候都会增大 $2$，之后每次暴力循环都会减少 $1$，故暴力循环最多发生 $2n$ 次，总的时间复杂度为 $O(n)$．

### 最长公共子字符串

问题：给定 $m$ 个总长不超过 $n$ 的非空字符串，查找所有字符串的最长公共子字符串，如果有多个，任意输出其中一个．其中 $1\leq m, n\leq 10^6$．

很显然如果存在长度为 $k$ 的最长公共子字符串，那么 $k-1$ 的公共子字符串也必定存在．因此我们可以二分最长公共子字符串的长度．假设现在的长度为 $k$，`check(k)` 的逻辑为我们将所有字符串的长度为 $k$ 的子串分别进行哈希，将哈希值放入 $n$ 个哈希表中存储．之后求交集即可．

时间复杂度为 $O(m+n\log n)$．

### 确定字符串中不同子字符串的数量

问题：给定长为 $n$ 的字符串，仅由小写英文字母组成，查找该字符串中不同子串的数量．

为了解决这个问题，我们遍历了所有长度为 $l=1,\cdots ,n$ 的子串．对于每个长度为 $l$，我们将其 Hash 值乘以相同的 $b$ 的幂次方，并存入一个数组中．数组中不同元素的数量等于字符串中长度不同的子串的数量，并此数字将添加到最终答案中．

为了方便起见，我们将使用 $h [i]$ 作为 Hash 的前缀字符，并定义 $h[0]=0$．

??? note "参考代码"
    ```cpp
    int count_unique_substrings(string const& s) {
      int n = s.size();
    
      constexpr static int b = 31;
      constexpr static int m = 1e9 + 9;
      vector<long long> b_pow(n);
      b_pow[0] = 1;
      for (int i = 1; i < n; i++) b_pow[i] = (b_pow[i - 1] * b) % m;
    
      vector<long long> h(n + 1, 0);
      for (int i = 0; i < n; i++)
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * b_pow[i]) % m;
    
      int cnt = 0;
      for (int l = 1; l <= n; l++) {
        set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
          long long cur_h = (h[i + l] + m - h[i]) % m;
          cur_h = (cur_h * b_pow[n - i - 1]) % m;
          hs.insert(cur_h);
        }
        cnt += hs.size();
      }
      return cnt;
    }
    ```

### 例题

???+ note "[CF1200E Compress Words](http://codeforces.com/contest/1200/problem/E)"
    给你若干个字符串，答案串初始为空．第 $i$ 步将第 $i$ 个字符串加到答案串的后面，但是尽量地去掉重复部分（即去掉一个最长的、是原答案串的后缀、也是第 $i$ 个串的前缀的字符串），求最后得到的字符串．
    
    字符串个数不超过 $10^5$，总长不超过 $10^6$．
    
    ??? note "题解"
        每次需要求最长的、是原答案串的后缀、也是第 $i$ 个串的前缀的字符串．枚举这个串的长度，哈希比较即可．
        
        当然，这道题也可以使用 [KMP 算法](./kmp.md) 解决．
    
    ??? note "参考代码"
        ```cpp
        --8<-- "docs/string/code/hash/hash_1.cpp"
        ```

## 参考资料与注释

**本页面部分内容译自博文 [строковый хеш](https://github.com/e-maxx-eng/e-maxx-eng/blob/61aff51f658644424c5e1b717f14fb7bf054ae80/src/string/string-hashing.md) 与其英文翻译版 [String Hashing](https://cp-algorithms.com/string/string-hashing.html)．其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0．**

[^ref1]: [On the mathematics behind rolling hashes and anti-hash tests](https://codeforces.com/blog/entry/60442)

[^ref2]: [A tool for hacking rolling hashes with fixed modulos and bases](https://codeforces.com/blog/entry/129538)

[^ref3]: [滚动哈希和卡哈希的数学原理 - Sshwy's Notes](https://notes.sshwy.name/Math/Rolling-Hash-and-Hack/)

[^ref4]: [An LLL Algorithm with Quadratic Complexity](https://epubs.siam.org/doi/10.1137/070705702)
