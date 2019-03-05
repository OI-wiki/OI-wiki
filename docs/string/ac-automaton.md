## KMP 自动机

为了介绍 AC 自动机这种神奇的算法，先介绍自动机和 KMP 自动机。

有限状态自动机 (DFA)：字符集，有限状态控制，初始状态，接受状态。

KMP 自动机：一个不断读入待匹配串，每次匹配时走到接受状态的 DFA。

共有 $m$ 个状态，第 $i$ 个状态表示已经匹配了前 $i$ 个字符。

定义 $trans_{i,c}$ 表示状态 $i$ 读入字符 $c$ 后到达的状态，$next_{i}$ 表示 [prefix function](../prefix-function)，则有:

$$
trans_{i,c} =
\begin{cases}
i + 1,  & \text{if $b_{i} = c$} \\[2ex]
trans_{next_{i},c}, & \text{else}
\end{cases}
$$

（约定 $next_{0}=0$ ）

我们发现 $trans_{i}$ 只依赖于之前的值，所以可以跟 [KMP](../prefix-function/#knuth-morris-pratt) 一起求出来。

时间和空间复杂度： $O(m|\Sigma|)$ 

一些细节：走到接受状态之后立即转移到该状态的 $next$ 。

## AC 算法就是 Trie 上的自动机

注意在 [BFS](/search/bfs) 的同时求出 $trans$ 数组即可。

可以解决多串匹配问题。

注意细节： $O(n+m)$ 还是 $O(n)$，其中 $m$ 表示匹配次数。

前者能找到每次匹配，后者只能求出匹配次数（通过合并接受状态）。

## AC 自动机的实现
