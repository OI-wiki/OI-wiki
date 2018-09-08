# Knuth-Morris-Pratt

由 Knuth, Morris, Pratt 共同发明，故得名。简称 KMP。

## 原理

主要思想是暴力的改进。

对于模式串 $b$，定义 $next[]$。


$$
next[i] = \max\{j\}\ \operatorname{s.t.}\ 0 \leq j<i\ \&\&\ b[0 \cdots j-1]=b[i-j \cdots i-1]
$$


!!! warning
    【注意下标从 $0$ 开始】【需要画图】

说好听点，$a$ 的第 $i$ 个前缀的最长的等于同长度的后缀的真前缀的长度。

先不说 $next$ 能干啥，想一想 $next$ 怎么求。

暴力肯定是不行的，每个 $next$ 都要枚举长度（这东西不能二分），再依次比较……

我们换一个思路，从 $next[1]$ 开始，一个一个求。

基础：显然 $next[1]=0$。

归纳：如果已知 $next[0 \cdots i-1]$，那么 $next[i]=next[i-1]+1$ 或 $next[next[i-1]]+1$ 或…

这算法的复杂度是多少？

考虑 $next[i]$ 这个非负值，每次循环最多 $+1$，并且每次应用 $next[]$ 的时候，至少 $-1$，所以是 $O(m)$ 的。

定义势能为 $next[i]$，每次循环势能 $+1$，每次取 $next$ 势能减少得比实际代价多。

均摊代价 $\leq 1$，势能取值范围 $0 \sim 2m$，所以 $O(m)$。

求出了 $next$，对字符串匹配有什么用呢？

在 $a$ 串上进行匹配，当失配时，移到 $next$ 的位置。

时间复杂度是多少呢？（可以证明，是 $O(n+m)$ 的。）

## 实现

```cpp
KMP(char *a, char *b, int n, int m) {
	int *next = new int[m + 1];
	next[1] = 0;
	for (i = 2; i <= m; i++) {
		int t = next[i - 1];
		while (t && b[t] != b[i - 1]) t = next[t];
		next[i] = t + (b[t] == b[i - 1]);
	}
	ans = new vector();
	int p = 0;
	for (i = 0; i < n; i++) {
		while (p && a[i] != b[p]) p = next[p];
		if (a[i] == b[p] && ++p == m) {
			ans.push_back(i - m + 1);
			p = next[p];
		}
	}
	return ans;
}
```

## 优化
