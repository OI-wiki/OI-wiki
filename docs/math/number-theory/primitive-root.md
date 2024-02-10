## 前置知识

前置：[费马小定理](./fermat.md#费马小定理)，[欧拉定理](./fermat.md#欧拉定理)，[拉格朗日定理](./congruence-equation.md#定理-3lagrange-定理)。

这部分知识与抽象代数相关。如果想要进一步了解文中的「阶」、「原根」名字来源，可以参考群论部分。

## 阶

???+ note "定义"
    由欧拉定理可知，对 $a\in \mathbf{Z}$，$m\in\mathbf{N}^{*}$，若 $(a,m)=1$，则 $a^{\varphi(m)}\equiv 1\pmod m$.
    
    因此满足同余式 $a^n \equiv 1 \pmod m$ 的最小正整数 $n$ 存在，这个 $n$ 称作 $a$ 模 $m$ 的阶，记作 $\delta_m(a)$ 或 $\operatorname{ord}_m(a)$.

???+ note "注"
    在抽象代数中，这里的「阶」就是模 $m$ 缩剩余系关于乘法形成的群中，元素 $a$ 的阶。记号 $\delta$ 表示阶也只用于这个特殊的群。
    
    下面的诸多性质可以直接扩展到抽象代数中阶的性质。
    
    另外还有「半阶」的概念，在数论中会出现 $\delta^-$ 记号，表示同余式 $a^n \equiv -1 \pmod m$ 的最小正整数。半阶不是群论中的概念。阶一定存在，半阶不一定存在。

### 性质

#### 性质 1

$a,a^2,\cdots,a^{\delta_m(a)}$ 模 $m$ 两两不同余。

???+ note "证明"
    考虑反证，假设存在两个数 $i\ne j$，且 $a^i\equiv a^j\pmod m$，则有 $a^{|i-j|}\equiv 1\pmod p$.
    
    但是显然的有：$0<|i-j|<\delta_m(a)$，这与阶的最小性矛盾，故原命题成立。

#### 性质 2

若 $a^n \equiv 1 \pmod m$，则 $\delta_m(a)\mid n$.

???+ note "证明"
    对 $n$ 除以 $\delta_m(a)$ 作带余除法，设 $n=\delta_m(a)q+r,0\leq r<\delta_m(a)$.
    
    若 $r>0$，则
    
    $$
    a^r\equiv a^r(a^{\delta_m(a)})^q\equiv a^n \equiv 1 \pmod m
    $$
    
    这与 $\delta_m(a)$ 的最小性矛盾。故 $r=0$，即 $\delta_m(a)\mid n$.

据此还可推出：

若 $a^p\equiv a^q\pmod m$，则有 $p\equiv q\pmod{\delta_m(a)}$.

还有两个与四则运算有关的重要性质。

#### 性质 3

设 $m\in\mathbf{N}^{*}$，$a,b\in\mathbf{Z}$，$(a,m)=(b,m)=1$，则

$$
\delta_m(ab)=\delta_m(a)\delta_m(b)
$$

的充分必要条件是

$$
\left(\delta_m(a), \delta_m(b)\right)=1
$$

???+ note "证明"
    -   必要性：由 $a^{\delta_m(a)}\equiv 1 \pmod m$ 及 $b^{\delta_m(b)} \equiv 1 \pmod m$，可知
    
        $$
        (ab)^{[\delta_m(a), \delta_m(b)]}\equiv 1 \pmod m
        $$
    
        由前面所述阶的性质，有
    
        $$
        \delta_m(ab)\mid \left[\delta_m(a), \delta_m(b)\right]
        $$
    
        又由于 $\delta_m(ab)=\delta_m(a)\delta_m(b)$，故
    
        $$
        \delta_m(a)\delta_m(b)\mid \left[\delta_m(a), \delta_m(b)\right]
        $$
    
        即 $(\delta_m(a),\delta_m(b))=1$.
    -   充分性：由 $(ab)^{\delta_m(ab)}\equiv 1 \pmod m$ 可知
    
        $$
        1 \equiv (ab)^{\delta_m(ab)\delta_m(b)}\equiv a^{\delta_m(ab)\delta_m(b)} \pmod m
        $$
    
        故 $\delta_m(a)\mid\delta_m(ab)\delta_m(b)$. 结合 $(\delta_m(a),\delta_m(b))=1$ 即得
    
        $$
        \delta_m(a)\mid\delta_m(ab)
        $$
    
        对称地，同理可得
    
        $$
        \delta_m(b)\mid\delta_m(ab)
        $$
    
        所以
    
        $$
        \delta_m(a)\delta_m(b)\mid\delta_m(ab)
        $$
    
        另一方面，有
    
        $$
        (ab)^{\delta_m(a)\delta_m(b)}\equiv(a^{\delta_m(a)})^{\delta_m(b)}\times(b^{\delta_m(b)})^{\delta_m(a)}\equiv 1 \pmod m
        $$
    
        故
    
        $$
        \delta_m(ab)\mid\delta_m(a)\delta_m(b)
        $$
    
        综合以上两点即得
    
        $$
        \delta_m(ab)=\delta_m(a)\delta_m(b)
        $$

#### 性质 4

设 $k \in \mathbf{N}$，$m\in \mathbf{N}^{*}$，$a\in\mathbf{Z}$，$(a,m)=1$，则

$$
\delta_m(a^k)=\dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)}
$$

???+ note "证明"
    注意到：
    
    $$
    \begin{aligned}
                & a^{k\delta_m(a^k)}=(a^k)^{\delta_m(a^k)}\equiv 1 \pmod m          \\
        \implies & \delta_m(a)\mid k\delta_m(a^k)                                    \\
        \implies & \dfrac{\delta_m(a)}{\left(\delta_m(a),k\right)}\mid\delta_m(a^k)
    \end{aligned}
    $$
    
    另一方面，由 $a^{\delta_m(a)}\equiv 1 \pmod m$，可知：
    
    $$
    (a^k)^{\frac{\delta_m(a)}{(\delta_m(a),k)}}=(a^{\delta_m(a)})^{\frac{k}{(\delta_m(a),k)}}\equiv 1 \pmod m
    $$
    
    故：
    
    $$
    \delta_m(a^k)\mid\dfrac{\delta_m(a)}{(\delta_m(a),k)}
    $$
    
    综合以上两点，得：
    
    $$
    \delta_m(a^k)=\dfrac{\delta_m(a)}{(\delta_m(a),k)}
    $$

## 原根

???+ note "定义"
    设 $m \in \mathbf{N}^{*}$，$g\in \mathbf{Z}$. 若 $(g,m)=1$，且 $\delta_m(g)=\varphi(m)$，则称 $g$ 为模 $m$ 的原根。
    
    即 $g$ 满足 $\delta_m(g) = \left| \mathbf{Z}_m^* \right| = \varphi(m)$. 当 $m$ 是质数时，我们有 $g^i \bmod m,\,0 \lt i \lt m$ 的结果互不相同。

???+ note "注"
    在抽象代数中，原根就是循环群的生成元。这个概念只在模 $m$ 缩剩余系关于乘法形成的群中有「原根」这个名字，在一般的循环群中都称作「生成元」。
    
    并非每个模 $m$ 缩剩余系关于乘法形成的群都是循环群，存在原根就表明它同构于循环群，如果不存在原根就表明不同构。

### 原根判定定理

设 $m \geqslant 3, (g,m)=1$，则 $g$ 是模 $m$ 的原根的充要条件是，对于 $\varphi(m)$ 的每个素因数 $p$，都有 $g^{\frac{\varphi(m)}{p}}\not\equiv 1\pmod m$.

???+ note "证明"
    必要性显然，下面用反证法证明充分性。
    
    当对于 $\varphi(m)$ 的每个素因数 $p$，都有 $g^{\frac{\varphi(m)}{p}}\not\equiv 1\pmod m$ 成立时，我们假设存在一个 $g$，其不是模 $m$ 的原根。
    
    因为 $g$ 不是 $m$ 的原根，则存在一个 $t<\varphi(m)$ 使得 $g^t\equiv 1\pmod{m}$.
    
    由 [裴蜀定理](./bezouts.md) 得，一定存在一组 $k,x$ 满足 $kt=x\varphi(m)+(t,\varphi(m))$.
    
    又由 [欧拉定理](./fermat.md#欧拉定理) 得 $g^{\varphi(m)}\equiv 1\pmod{m}$，故有：
    
    $$
    1\equiv g^{kt}\equiv g^{x\varphi(m)+(t,\varphi(m))}\equiv g^{(t,\varphi(m))}\pmod{m}
    $$
    
    由于 $(t, \varphi(m)) \mid \varphi(m)$ 且 $(t, \varphi(m))\leqslant t < \varphi(m)$.
    
    故存在 $\varphi(m)$ 的素因数 $p$ 使得 $(t, \varphi(m)) \mid \frac{\varphi(m)}{p}$.
    
    则 $g^{\frac{\varphi(m)}{p}}\equiv g^{(t, \varphi(m))}\equiv 1\pmod{m}$，与条件矛盾。
    
    故假设不成立，原命题成立。

### 原根个数

若一个数 $m$ 有原根，则它原根的个数为 $\varphi(\varphi(m))$.

???+ note "证明"
    若 $m$ 有原根 $g$，则：
    
    $$
    \delta_m(g^k)=\dfrac{\delta_m(g)}{\left(\delta_m(g),k\right)}=\dfrac{\varphi(m)}{\left(\varphi(m),k\right)}
    $$
    
    所以若 $\left(k,\varphi(m)\right)=1$，则有：$\delta_m(g^k)=\varphi(m)$，即 $g^k$ 也是模 $m$ 的原根。
    
    而满足 $\left(\varphi(m),k\right)=1$ 且 $1\leq k \leq \varphi(m)$ 的 $k$ 有 $\varphi(\varphi(m))$ 个。所以原根就有 $\varphi(\varphi(m))$ 个。

### 原根存在定理

???+ note "原根存在定理"
    一个数 $m$ 存在原根当且仅当 $m=2,4,p^{\alpha},2p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in \mathbf{N}^{*}$.

我们来证明它，分成 $m=2,4$、$m=p^{\alpha}$、$m=2p^{\alpha}$ 与 $m\ne 2,4,p,p^{\alpha}$，四个部分。

1.  $m=2,4$，原根显然存在。

2.  $m=p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in \mathbf{N}^*$.

    ???+ note "定理 1"
        对于奇素数 $p$，$p$ 有原根。
        
        ???+ note "证明"
            先证一个引理：
            
            设 $a$ 与 $b$ 是与 $p$ 互素的两个整数，则存在 $c\in\mathbf{Z}$ 使得 $\delta_p(c)=\left[\delta_p(a),\delta_p(b)\right]$.
            
            ???+ note "证明"
                我们先将 $\delta_m(a),\delta_m(b)$ 表示成质因数分解的形式：
                
                $$
                \left(\delta_m(a)=\prod_{i=1}^k{p_i^{\alpha_i}},\delta_m(b)=\prod_{i=1}^k{p_i^{\beta_i}} \right)
                $$
                
                接着将它们表示成如下形式：
                
                $$
                \delta_m(a)=XY,\delta_m(b)=ZW
                $$
                
                其中：
                
                -   $Y=\prod_{i=1}^k{p_i^{[\alpha_i>\beta_i]\alpha_i}}$
                -   $X=\dfrac {\delta_m(a)}Y$
                -   $W=\prod_{i=1}^k{p_i^{[\alpha_i\le\beta_i]\beta_i}}$
                -   $Z=\dfrac {\delta_m(b)}W$
                
                则由阶的 [性质 4](#性质-4)，可得：
                
                $$
                \begin{aligned}
                    \delta_m\left(a^X\right)&=\dfrac{\delta_m(a)}{\left(\delta_m(a),X\right)}\\
                    &=\dfrac{XY}{X}\\
                    &=Y
                \end{aligned}
                $$
                
                同理：
                
                $$
                \delta_m\left(b^Z\right)=W
                $$
                
                又因为显然有 $(Y,W)=1$，$YW=\left[\delta_p(a),\delta_p(b)\right]$，则再由阶的 [性质 3](#性质-3)，可得：
                
                $$
                \begin{aligned}
                    \delta_m\left(a^Xb^Z\right)&=\delta_m\left(a^X\right)\delta_m\left(b^Z\right)\\
                    &=YW\\
                    &=\left[\delta_p(a),\delta_p(b)\right]
                \end{aligned}
                $$
                
                于是令 $c=a^Xb^Z$ 则原命题得证。
            
            回到原命题，对 $1 \sim (p-1)$ 依次两两使用引理，可知存在 $g\in \mathbf{Z}$ 使得
            
            $$
            \delta_p(g)=\left[\delta_p(1),\delta_p(2),\cdots,\delta_p(p-1)\right]
            $$
            
            这表明 $\delta_p(j)\mid\delta_p(g)(j=1,2,\cdots,p-1)$，所以 $j=1,2,\cdots,p-1$ 都是同余方程
            
            $$
            x^{\delta_p(g)}\equiv 1\pmod p
            $$
            
            的根。由拉格朗日定理，可知方程的次数 $\delta_p(g) \geq p-1$.
            
            又由费马小定理，易知 $\delta_p(g) \leq p-1$，故 $\delta_p(g)=p-1=\varphi(p)$.
            
            综上可知 $g$ 为模 $p$ 的原根。

    ???+ note "定理 2"
        对于奇素数 $p$，$\alpha \in \mathbf{N}^{*}$，$p^\alpha$ 有原根。
        
        ???+ note "证明"
            一个基本的想法是将模 $p$ 的原根平移。
            
            先证明一个引理：
            
            存在模 $p$ 的原根 $g$，使得 $g^{p-1}\not\equiv 1 \pmod {p^2}$.
            
            ???+ note "证明"
                事实上，任取模 $p$ 的原根 $g$，若 $g$ 不满足条件，我们认定 $g+p$ 满足条件。
                
                易知 $g+p$ 也是模 $p$ 的原根。
                
                我们有
                
                $$
                \begin{aligned}
                    (g+p)^{p-1}&\equiv \binom{p-1}{0}g^{p-1}+\binom{p-1}{1}pg^{p-2} \pmod {p^2}\\
                    &\equiv g^{p-1}+p(p-1)g^{p-2} \pmod {p^2}\\
                    &\equiv 1-pg^{p-2} \pmod {p^2}\\
                    &\not\equiv 1 \pmod {p^2}
                \end{aligned}
                $$
            
            回到原题，我们证明若 $g$ 是一个满足引理条件的原根，则对任意 $\alpha\in\mathbf{N}^{*}$，$g$ 是模 $p^{\alpha}$ 的原根。
            
            首先，证明下面的结论：对任意 $\beta\in\mathbf{N}^{*}$，都可设
            
            $$
            g^{\varphi(p^\beta)}=1+p^{\beta} k_{\beta}
            $$
            
            这里 $p\nmid k_{\beta}$。事实上，$\beta=1$ 时，由 $g$ 的选取可知结论成立。现设上式对 $\beta$ 时成立，则
            
            $$
            \begin{aligned}
                g^{\varphi(p^{\beta+1})}&=\left(g^{\varphi\left(p^{\beta}\right)}\right)^p\\
                &=\left(1+p^{\beta}k_{\beta}\right)^p\\
                &\equiv 1+p^{\beta+1}k_{\beta} \pmod {p^{\beta+2}}
            \end{aligned}
            $$
            
            结合 $p\nmid k_{\beta}$ 可知命题对 $\beta+1$ 成立。
            
            所以命题对任意 $\beta\in\mathbf{N}^{*}$ 都成立。
            
            其次，记 $\delta=\delta_{p^\alpha}(g)$，则由欧拉定理，可知 $\delta\mid p^{\alpha-1}(p-1)$.
            
            而由 $g$ 为模 $p$ 的原根，及 $g^{\delta}\equiv 1\pmod {p^\alpha}$.
            
            所以可设 $\delta=p^{\beta-1}(p-1)$，这里 $1\leq \beta\leq \alpha$.
            
            现在利用之前的结论，可知：
            
            $$
            g^{\varphi(p^{\beta})}\not\equiv 1\pmod {p^{\beta+1}}\implies g^{\delta}\not\equiv 1\pmod {p^{\beta+1}}
            $$
            
            结合 $g^{\delta}\equiv 1\pmod {p^\alpha}$ 可知 $\beta \geq \alpha$.
            
            综上可知，$\beta=\alpha$，即：
            
            $$
            \delta_{p^{\alpha}}(g)=p^{\alpha-1}(p-1)=\varphi(p^\alpha)
            $$
            
            从而，$g$ 是模 $p^{\alpha}$ 的原根。

3.  $m=2p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in\mathbf{N}^*$.

    ???+ note "定理 3"
        对于奇素数 $p$，$\alpha\in\mathbf{N}^{*}$，$2p^{\alpha}$ 的原根存在。
        
        ???+ note "证明"
            设 $g$ 是模 $p^{\alpha}$ 的原根，则 $g+p^{\alpha}$ 也是模 $p^{\alpha}$ 的原根。
            
            在 $g$ 和 $g+p^{\alpha}$ 中有一个是奇数，设这个奇数是 $G$，则 $(G,2p^{\alpha})=1$.
            
            由欧拉定理，$\delta_{2p^{\alpha}}(G)\mid\varphi(2p^{\alpha})$.
            
            而 $G^{\delta_{2p^{\alpha}}(G)}\equiv 1\pmod {2p^{\alpha}}$，故：
            
            $$
            G^{\delta_{2p^{\alpha}}(G)}\equiv 1 \pmod {p^{\alpha}}
            $$
            
            利用 $G$ 为模 $p^{\alpha}$ 的原根可知 $\varphi(p^{\alpha})\mid\delta_{2p^{\alpha}}(G)$.
            
            结合 $\varphi(p^{\alpha})=\varphi(2p^{\alpha})$ 可知 $G$ 为模 $2p^{\alpha}$ 的原根。

4.  $m\ne 2,4,p^{\alpha},p^{\alpha}$，其中 $p$ 为奇素数，$\alpha\in\mathbf{N}^*$.

    ???+ note "定理 4"
        对于 $m\ne 2,4$，且不存在奇素数 $p$ 及 $\alpha \in \mathbf{N}^{*}$ 使得 $m=p^{\alpha},2p^{\alpha}$，模 $m$ 的原根不存在。
        
        ???+ note "证明"
            对于 $m=2^{\alpha}$，$\alpha\in\mathbf{N}^{*},\alpha\geq 3$，则对任意奇数 $a=2k+1$ 均有：
            
            $$
            \begin{aligned}
                a^{2^{\alpha-2}}&=(2k+1)^{2^{\alpha-2}}\\
                &\equiv 1+\binom{2^{\alpha-2}}{1}(2k)+\binom{2^{\alpha-2}}{2}(2k)^{2} \pmod {2^{\alpha}}\\
                &\equiv1+2^{\alpha-1}k+2^{\alpha-1}(2^{\alpha-2}-1)k^2 \pmod {2^{\alpha}}\\
                &\equiv 1+2^{\alpha-1}(k+(2^{\alpha-2}-1)k^2) \pmod {2^{\alpha}}\\
                &\equiv 1 \pmod {2^{\alpha}}
            \end{aligned}
            $$
            
            其中最后一步用到 $k$ 与 $(2^{\alpha-2}-1)k^2$ 同奇偶，故其和为偶数。
            
            若 $m$ 不是 $2$ 的幂，且 $m$ 为符合题目条件的数，则可设 $m=rt$，这里 $2<r<t$ 且 $(r,t)=1$.
            
            此时，若 $(a,m)=1$，由欧拉定理可知：
            
            $$
            a^{\varphi(r)}\equiv 1 \pmod r\;,\quad a^{\varphi(t)}\equiv1\pmod t
            $$
            
            注意到 $n>2$ 时，$\varphi(n)$ 为偶数，所以：
            
            $$
            a^{\frac{1}{2}\varphi(r)\varphi(t)}\equiv 1\pmod {rt}
            $$
            
            进而：
            
            $$
            \delta_m(a)\leq\dfrac{1}{2}\varphi(r)\varphi(t)=\dfrac{1}{2}\varphi(rt)=\dfrac{1}{2}\varphi(m)<\varphi(m)
            $$
            
            由原根定义可得：模 $m$ 的原根不存在。

综合以上 $4$ 个定理，我们便给出了一个数存在原根的充要条件。

### 最小原根的范围估计

王元[^yuan1959note]和 Burgess[^burgess1962character]证明了素数 $p$ 的最小原根 $g_p=O\left(p^{0.25+\epsilon}\right)$，其中 $\epsilon>0$.

Fridlander[^fridlender1949least]和 Salié[^salie1949kleinsten]证明了素数 $p$ 的最小原根 $g_p=\Omega(\log p)$.

这保证了我们暴力找一个数的最小原根，复杂度是可以接受的。

## 参考资料与注释

1.  [Primitive root modulo n - Wikipedia](https://en.wikipedia.org/wiki/Primitive_root_modulo_n)

[^burgess1962character]: BURGESS, David A. On character sums and primitive roots.*Proceedings of the London Mathematical Society*, 1962, 3.1: 179-192.

[^yuan1959note]: Wang Y. On the least primitive root of a prime (in Chinese).*Acta Math Sinica*, 1959, 4: 432–441; English transl. in*Sci. Sinica*, 1961, 10: 1–14

[^fridlender1949least]: FRIDLENDER, V. R. On the least n-th power non-residue. In:*Dokl. Akad. Nauk SSSR*. 1949. p. 351-352.

[^salie1949kleinsten]: SALIÉ, Hans. Über den kleinsten positiven quadratischen Nichtrest nach einer Primzahl.*Mathematische Nachrichten*, 1949, 3.1: 7-8.
