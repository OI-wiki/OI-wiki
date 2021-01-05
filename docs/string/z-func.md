author: LeoJacob, TrisolarisHD, minghu6

假设我们有一个长度为 $n$ 的字符串 $s$ 。该字符串的 **Z 函数** 为一个长度为 $n$ 的数组，其中第 $i$ 个元素为满足从位置 $i$ 开始且为 $s$ 前缀的字符串的最大长度。

换句话说， $z[i]$ 是 $s$ 和从 $i$ 开始的 $s$ 的后缀的最大公共前缀长度。

 **注意** ：为了避免歧义，在这篇文章中下标从 $0$ 开始，即 $s$ 的第一个字符下标为 $0$ ，最后一个字符下标为 $n - 1$ 。

Z 函数的第一个元素， $z[0]$ ，通常不是良定义的。在这篇文章中我们假定它是 $0$ （虽然在算法实现中这没有任何影响）。

国外一般将计算该数组的算法称为 **Z Algorithm** ，而国内则称其为 **扩展 KMP** 。

这篇文章包含在 $O(n)$ 时间复杂度内计算 Z 函数的算法以及其各种应用。

## 样例

下面若干样例展示了对于不同字符串的 Z 函数：

-  $Z(\mathtt{aaaaa}) = [0, 4, 3, 2, 1]$ 
-  $Z(\mathtt{aaabaab}) = [0, 2, 1, 0, 2, 1, 0]$ 
-  $Z(\mathtt{abacaba}) = [0, 0, 1, 0, 3, 0, 1]$ 

## 朴素算法

Z 函数的形式化定义可被表述为下列基础的 $O(n^2)$ 实现。

```cpp
vector<int> z_function_trivial(string s) {
  int n = (int)s.length();
  vector<int> z(n);
  for (int i = 1; i < n; ++i)
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
  return z;
}
```

其中 $z[i]$ 可以被认为是字符串 $s$ 的 $z$ 函数前缀即 $s[0\dots z[i]]$ 的右边界。

诚然，这并不是一个高效的实现。我们接下来将展示一个高效实现的构造过程。

## 计算 Z 函数的高效算法

如同大多数字符串主题所介绍的算法，其关键在于，运用自动机的思想寻找限制条件下的状态转移函数，使得可以借助之前的状态来加速计算新的状态。

*这句话可以 Write once paste anywhere, 简称 WOPA*

我们把符合 $z$ 函数定义的那些子串的前缀称为 **匹配段**，其中我们关注的是最靠右的那一个匹配段，假定它为: $s[l\dots r]$ 。

根据 $z$ 函数定义，有 $s[0\dots r-l] = s[l\dots r]$ 。于是当 $i \leqslant r$ 时，有 $s[i-l\dots r-l] = s[i\dots r]$。

显然，在这个长度为 $r-i+1$ 的范围内，计算 $z[i]$ 可以直接从 $z[i-l]$ 开始。

如果 $z[i-l] \leqslant r-i+1$ ，那么 $z[i] = z[i-l]$ ；

否则继续按照朴素算法在 $z[i-l]$ 的值的基础上求解 $z[i]$ 。

最后记得当新的 $z[i]$ 匹配段的右边界超出了 $r$ ，计算得到 $z[i]$ 后需要更新 $l,\ r$ 为 $i,\ i+z[i]-1$ 。

## 实现

```cpp
vector<int> z_function(string s) {
  int n = (int)s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}
```

## 算法的渐进行为

由于 `while` 每次循环都会使得最右边匹配段的右边界 $r$ 向后移 $1$ 位，而 $r\lt n-1$ ，所以时间复杂度是线性的。

## 应用

我们现在来考虑在若干具体情况下 Z 函数的应用。

这些应用在很大程度上同 [前缀函数](./kmp.md) 的应用类似。

### 查找子串

为了避免混淆，我们将 $t$ 称作 **文本** ，将 $p$ 称作 **模式** 。所给出的问题是：寻找在文本 $t$ 中模式 $p$ 的所有出现（occurrence）。

为了解决该问题，我们构造一个新的字符串 $s = p + \diamond + t$ ，也即我们将 $p$ 和 $t$ 连接在一起，但是在中间放置了一个分割字符 $\diamond$ （我们将如此选取 $\diamond$ 使得其必定不出现在 $p$ 和 $t$ 中）。

首先计算 $s$ 的 Z 函数。接下来，对于在区间 $[0; \operatorname{length}(t) - 1]$ 中的任意 $i$ ，我们考虑其对应的值 $k = z[i + \operatorname{length}(p) + 1]$ 。如果 $k$ 等于 $\operatorname{length}(p)$ ，那么我们知道有一个 $p$ 的出现位于 $t$ 的第 $i$ 个位置，否则没有 $p$ 的出现位于 $t$ 的第 $i$ 个位置。

其时间复杂度（同时也是其空间复杂度）为 $O(\operatorname{length}(t) + \operatorname{length}(p))$ 。

### 一个字符串中本质不同子串的数目

给定一个长度为 $n$ 的字符串 $s$ ，计算 $s$ 的本质不同子串的数目。

我们将迭代的解决该问题。也即：在知道了当前的本质不同子串的数目的情况下，在 $s$ 末尾添加一个字符后重新计算该数目。

令 $k$ 为当前 $s$ 的本质不同子串数量。我们添加一个新的字符 $c$ 至 $s$ 。显然，会有一些新的子串以新的字符 $c$ 结尾（换句话说，那些以该字符结尾且我们之前未曾遇到的子串）。

构造字符串 $t = s + c$ 并将其反转（以相反顺序书写其字符）。我们现在的任务是计算有多少 $t$ 的前缀未在 $t$ 的其余任何地方出现。让我们计算 $t$ 的 Z 函数并找到其最大值 $z_{\max}$ 。显然， $t$ 的长度为 $z_{\max}$ 的前缀出现在 $t$ 中间的某个位置。自然的，更短的前缀也出现了。

所以，我们已经找到了当将字符 $c$ 添加至 $s$ 后新出现的子串数目为 $\operatorname{length}(t) - z_{\max}$ 。

作为其结果，该解法对于一个长度为 $n$ 的字符串的时间复杂度为 $O(n^2)$ 。

值得注意的是，我们可以用同样的方法在 $O(n)$ 时间内，重新计算在头部添加一个字符，或者移除一个字符（从尾或者头）时的本质不同子串数目。

### 字符串压缩

给定一个长度为 $n$ 的字符串 $s$ ，找到其最短的“压缩”表示，即：寻找一个最短的字符串 $t$ ，使得 $s$ 可以被 $t$ 的一份或多份拷贝的拼接表示。

其中一种解法为：计算 $s$ 的 Z 函数，从小到大循环所有满足 $i$ 整除 $n$ 的 $i$ 。在找到第一个满足 $i + z[i] = n$ 的 $i$ 时终止。那么该字符串 $s$ 可被压缩为长度 $i$ 的字符串。

该事实的证明同应用 [前缀函数](./kmp.md) 的解法证明一样。

## 练习题目

-  [CF126B Password](http://codeforces.com/problemset/problem/126/B) 
-  [UVA # 455 Periodic Strings](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=396) 
-  [UVA # 11022 String Factoring](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1963) 
-  [UVa 11475 - Extend to Palindrome](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2470) 
-  [LA 6439 - Pasti Pas!](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=588&page=show_problem&problem=4450) 
-  [Codechef - Chef and Strings](https://www.codechef.com/problems/CHSTR) 
-  [Codeforces - Prefixes and Suffixes](http://codeforces.com/problemset/problem/432/D) 

* * *

 **本页面主要译自博文 [Z-функция строки и её вычисление](http://e-maxx.ru/algo/z_function) 与其英文翻译版 [Z-function and its calculation](https://cp-algorithms.com/string/z-function.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
