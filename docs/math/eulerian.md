在计算组合中，**欧拉数**（Eulerian Number）是从1到n中正好满足m个元素大于前一个元素（具有 $m$ 个“上升”的排列）条件的排列 **个数** 。定义为：

$$
A(n, m) = 
\langle 
\begin{aligned}
& n \\
& m - 1 \\
\end{aligned}
\rangle
$$

例如，从数字1到3一共有4种排列能满足刚好有1个元素比前面的数字大：

| 排列  | 详例  | 个数  |
| ---------- | --------------- | -------------- |
| 1 2 3 | 1, 2 & 2, 3 | 2 |
| 1 3 2 | 1, 3 | 1 |
| 2 1 3 | 1, 3 | 1 |
| 2 3 1 | 2, 3 | 1 | 
| 3 1 2 | 1, 2 | 1 |
| 3 2 1 |      | 0 |

所以按照 $A(n, m)$ 定义： 如果 $n$ 等于 $3$ , $m$ 等于 $1$ ，欧拉数值为 $4$ ， 表示共有 $4$ 个有 $1$ 个元素大于前一个元素的排列。

对于 $n$ 和 $m$ 值比较小的欧拉数来说，我们可以直接得到结果：

| $A(n, m)$  | 排列 | 个数 | 
| ---------- | --------------- | --------------- | 
| $A(1, 0)$ | $(1)$ | 1 |
| $A(2, 0)$ | $(2, 1)$ | 1 |
| $A(2, 1)$  | $(1, 2)$ | 1 |
| $A(3, 0)$ | $(3, 2, 1)$ | 1 | 
| $A(3, 1)$ | $(1, 3, 2), (2, 1, 3), (2, 3, 1), (3, 1, 2)$ | 4 |
| $A(3, 2)$ | $(1, 2, 3)$ | 1 |

## 公式

$$
\begin{aligned}
&A(n, m) = 0, if m > n or n = 0 \\
&A(n, m) = 1, if m = 0  \\
&A(n, m) = (n-m)*A(n-1, m-1) + (m+1) * A(n-1, m)\\
\end{aligned}
$$

## 实现

```c++
int eulerianNumber(int n, int m)
{
    if (m >= n || n == 0)
        return 0;
    if (m == 0)
        return 1;
    return (((n - m) * eulerianNumber(n - 1, m - 1)) + ((m + 1) * eulerianNumber(n - 1, m)));
}
```

## 习题

-  [CF1349F1 Slime and Sequences (Easy Version)](https://www.luogu.com.cn/problem/CF1349F1) 
-  [CF1349F2 Slime and Sequences (Hard Version)](https://www.luogu.com.cn/problem/CF1349F2) 
-  [UOJ 593. 新年的军队](https://uoj.ac/problem/593) 
-  [P7511 三到六](https://www.luogu.com.cn/problem/P7511) 
