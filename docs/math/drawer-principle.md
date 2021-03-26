抽屉原理，亦可称之为鸽巢原理。

先考虑一种简单的情况：有 $n+1$ 个苹果，想要放到 $n$ 个抽屉里，那么必然会有至少一个抽屉里有两个（或以上）的苹果。

这个定理看起来比较显然，证明方法考虑反证法：假如所有抽屉都至多放了一个苹果，那么 $n$ 个抽屉至多只能放 $n$ 个苹果，矛盾。

进一步的，若有 $n$ 个苹果，想要放到 $k$ 个抽屉里，那么必然至少一个抽屉里有不少于 $\left \lfloor \dfrac{n}{k} \right \rfloor$ 个的苹果。

证明亦为反证法，若所有抽屉都有不超过 $\left \lfloor \dfrac{n}{k} \right \rfloor$ 个苹果，则其总和不超过 $(\left \lfloor \dfrac{n}{k} \right \rfloor -1 ) \times k$。因为 $\left \lfloor \dfrac{n}{k} \right \rfloor \times k \le n$，所以 $(\left \lfloor \dfrac{n}{k} \right \rfloor -1 ) \times k < n$，矛盾。

抽屉原理经常被使用在证明存在性和最坏情况下的解。
