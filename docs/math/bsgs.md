## 大步小步算法

### 1.0 基础篇

大步小步算法英文名：**Baby Step Gaint Step (BSGS)**.

该算法可以在 $O(\sqrt{q})$ 用于求解 $$$a^x \equiv b \bmod p$ 其中 $p$ 是个质数的方程的解 $x$ 满足 $0 \le x < p$ .



令 $x = A \lceil \sqrt p \rceil - B$，其中 $0\le A,B \le \lceil \sqrt p \rceil$，

则有 $a^{A\lceil \sqrt p \rceil -B} \equiv b$，稍加变换，则有 $a^{A\lceil \sqrt p \rceil} \equiv ba^B$.



我们已知的是 $a,b$，所以我们可以先算出等式右边的 $ba^B$ 的所有取值，枚举 $B$，用 hash/map 存下来，然后逐一计算 $a^{A\lceil \sqrt p \rceil}$，枚举 $A$，寻找是否有与之相等的 $ba^B$，从而我们可以得到所有的 $x$，$x=A \lceil \sqrt p \rceil - B$.



注意到 $A,B$ 均小于 $\lceil \sqrt p \rceil$，所以时间复杂度为 $O(\sqrt q)$.



[BZOJ-2480](http://www.lydsy.com/JudgeOnline/problem.php?id=2480) 是一道模板题（可能是权限题），[BZOJ-3122](http://www.lydsy.com/JudgeOnline/problem.php?id=3122) 是一道略微进阶题，代码可以在 [Steaunk的博客](https://blog.csdn.net/Steaunk/article/details/78988376) 中看到。



### 2.0 略微进阶篇

求解 $x^a \equiv b \bmod p$，$p$ 是个质数





