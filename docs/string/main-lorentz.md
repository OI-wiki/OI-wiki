## 重串

### 定义

给定一个长度为 $n$ 的字符串 $s$。

我们将一个字符串连续写两遍所产生的新字符串称为 **重串 (tandem repetition)**。下文中，为了表述精准，我们将被重复的这个字符串称为原串。换言之，一个重串等价于一对下标 $(i, j)$，其使得 $s[i \dots j]$ 是两个相同字符串拼接而成的。

你的目标是找出给定的字符串 $s$ 中所有的重串。或者，解决一个较为简单的问题：找到字符串 $s$ 中任意重串或者最长的一个重串。

下文的算法由 Michael Main 和 Richard J. Lorentz 在 1982 年提出。

**声明：**

下文所有的字符串下标从 0 开始。

下文中，记 $\overline{s}$ 为 $s$ 的反串。如 $\overline{\tt abc} = \tt cba$。

### 解释

考虑字符串 $\tt acababaee$，这个字符串包括三个重串，分别是：

-   $s[2 \dots 5] = \tt abab$
-   $s[3 \dots 6] = \tt baba$
-   $s[7 \dots 8] = \tt ee$

下面是另一个例子，考虑字符串 $\tt abaaba$，这个字符串只有两个重串：

-   $s[0 \dots 5] = \tt abaaba$
-   $s[2 \dots 3] = \tt aa$

### 重串的个数

一个长度为 $n$ 的字符串可能有高达 $O(n^2)$ 个重串，一个显然的例子就是 $n$ 个字母全部相同的字符串，这种情况下，只要其子串长度为偶数，这个子串就是重串。多数情况下，一个周期比较小的周期字符串会有很多重串。

但这并不影响我们在 $O(n \log n)$ 的时间内计算出重串数量。因为这个算法通过某种压缩形式来表达一个重串，使得我们可以将多个重串压缩为一个。

这里有一些关于重串数量的有趣结论：

-   如果一个重串的原串不是重串，则我们称这个重串为 **本原重串 (primitive repetition)**。可以证明，本原重串最多有 $O(n \log n)$ 个。
-   如果我们把一个重串用 Crochemore 三元组 $(i, p, r)$ 进行压缩，其中 $i$ 是重串的起始位置，$p$ 是该重串某个循环节的长度（注意不是原串长度！），$r$ 为这个循环节重复的次数。则某字符串的所有重串可以被 $O(n \log n)$ 个 Crochemore 三元组表示。
-   Fibonacci 字符串定义如下：

$$
\begin{align} t_0 &= a, \\ t_1 &= b, \\ t_i &= t_{i-1} + t_{i-2}, \end{align}
$$

可以发现 Fibonacci 字符串具有高度的周期性。对于长度为 $f_i$ 的 Fibonacci 字符串 $t_i$，即使用 Crochemore 三元组压缩，也有 $O(f_i \log f_i)$ 个三元组。其本原重串的数量也有 $O(f_i \log f_i)$ 个。

## Main–Lorentz 算法

### 解释

Main–Lorentz 算法的核心思想是 **分治**。

这个算法将字符串分为左、右两部分，首先计算完全处于字符串左部（或右部）的重串数量，然后计算起始位置在左部，终止在右部的重串数量。（下文中，我们将这种重串称为 **交叉重串**）

计算交叉重串的数量是 Main–Lorentz 算法的关键点，我们将在下文详细探讨。

### 过程

#### 寻找交叉重串

我们记某字符串的左部为 $u$，右部为 $v$。则 $s = u + v$，且 $u, v$ 的长度大约等于 $s$ 长度的一半。

对于任意一个重串，我们考虑其中间字符。此处我们将一个重串右半边的第一个字符称为其中间字符，换言之，若 $s[i...j]$ 为重串，则其中间字符为 $s[(i + j + 1)/2]$。如果一个重串的中间字符在 $u$ 中，则称这个重串 **左偏 (left)**，反之则称其 **右偏 (right)**。

接下来，我们将会探讨如何找到所有的左偏重串。

我们记一个左边重串的长度为 $2l$。考虑该重串第一个落入 $v$ 的字符（即 $s[|u|]$），这个字符一定与 $u$ 中的某个字符 $u[\textit{cntr}]$ 一致。

我们考虑固定 $\textit{cntr}$，并找到所有符合条件的重串。举个例子：对于字符串 $\tt c \; \underset{\textit{cntr}}{a} \; c \; | \; a \; d \; a$（这个 $\tt |$ 是用于分辨左右两部分的），固定 $cntr = 1$，则我们可以发现重串 $\tt caca$ 符合要求。

显然，我们一旦固定了 $\textit{cntr}$，那我们同时也固定了 $l$ 的取值。我们一旦知道如何找到所有重串，我们就可以从 $0$ 到 $|u| - 1$ 枚举 $\textit{cntr}$ 的取值，然后找到所有符合条件的重串。

#### 左偏重串的判定

即使固定 $\textit{cntr}$ 后，仍然可能会有多个符合条件的重串，我们怎么找到所有符合条件的重串呢？

我们再来举一个例子，对于字符串 $\tt abcabcac$ 中的重串 $\overbrace{\tt a}^{l_1} \overbrace{\underset{\textit{cntr}}{\tt b} \tt c}^{l_2} \overbrace{\tt a}^{l_1}  \; | \; \overbrace{\tt b \; \tt c}^{l_2}$，我们记 $l_1$ 为该重串的首字符到 $s[\textit{cntr} - 1]$ 所组成的子串的长度，记 $l_2$ 为 $s[\textit{cntr}]$ 到该重串左边原串的末字符所组成的子串的长度。

于是，我们可以给出某个长度为 $2l = 2(l_1 + l_2) = 2(|u| - \textit{cntr})$ 的子串是重串的 **充分必要条件**：

记 $k_1$ 为满足 $u[\textit{cntr} - k_1 \dots \textit{cntr} - 1] = u[|u| - k_1 \dots |u| - 1]$ 的最大整数，记 $k_2$ 为满足 $u[\textit{cntr} \dots \textit{cntr} + k_2 - 1] = v[0 \dots k_2 - 1]$ 的最大整数。则对于任意满足 $l_1 \leq k_1$，$l_2 \leq k_2$ 的二元组 $(l_1, l_2)$，我们都能恰好找到一个与之对应的重串。

总结一下，即有：

-   固定一个 $\textit{cntr}$。
-   那么我们此时要找的重串长度均为 $2l = 2(|u| - \textit{cntr})$。此时可能仍有多个符合条件的重串，取决于 $l_1$ 与 $l_2$ 的取值。
-   计算上文提到的 $k_1$，$k_2$。
-   则所有符合条件的重串符合条件：

$$
\begin{align} l_1 + l_2 &= l = |u| - \textit{cntr} \\ l_1 &\le k_1, \\ l_2 &\le k_2. \\ \end{align}
$$

接下来，只需要考虑如何快速算出 $k_1$ 与 $k_2$ 了。借助 [Z 函数](./z-func.md)，我们可以 $O(1)$ 计算它们：

-   计算 $k_1$：只需计算 $\overline{u}$ 的 Z 函数即可。
-   计算 $k_2$：只需计算 $v + \# + u$ 的 Z 函数即可，其中 $\#$ 是一个 $u$，$v$ 中均没有的字符。

#### 右偏重串

计算右偏重串的方法与计算左偏重串的方法几乎一致。考虑该重串第一个落入 $u$ 的字符（即 $s[|u| - 1]$），则其一定与 $v$ 中的某个字符一致，记这个字符在 $v$ 中的位置为 $\textit{cntr}$。

令 $k_1$ 为满足 $v[\textit{cntr} - k_1 + 1 \dots \textit{cntr}] = u[|u| - k_1 \dots |u| - 1]$ 的最大整数，$k_2$ 为满足 $v[\textit{cntr} + 1 \dots \textit{cntr} + k_2] = v[0 \dots k_2 - 1]$ 的最大整数。则我们可以分别通过计算 $\overline{u} + \# + \overline{v}$ 和 $v$ 的 Z 函数来得出 $k_1$ 与 $k_2$。

枚举 $\textit{cntr}$，用相仿的方法寻找右偏重串即可。

### 实现

Main–Lorentz 算法以四元组 $(\textit{cntr}, l, k_1, k_2)$ 的形式给出所有重串。如果你只需要计算重串的数量，或者只需要找到最长的一个重串，这个四元组给的信息是足够的。由 [主定理](../basic/complexity.md#主定理-master-theorem) 可得，Main–Lorentz 算法的时间复杂度为 $O(n \log n)$。

请注意，如果你想通过这些四元组来找到所有重串的起始位置与终止位置，则最坏时间复杂度会达到 $O(n^2)$。我们在下面的程序中实现了这一点，将所有重串的起始位置与终止位置存于 `repetitions` 中。

```cpp
vector<int> z_function(string const& s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

int get_z(vector<int> const& z, int i) {
  if (0 <= i && i < (int)z.size())
    return z[i];
  else
    return 0;
}

vector<pair<int, int>> repetitions;

void convert_to_repetitions(int shift, bool left, int cntr, int l, int k1,
                            int k2) {
  for (int l1 = max(1, l - k2); l1 <= min(l, k1); l1++) {
    if (left && l1 == l) break;
    int l2 = l - l1;
    int pos = shift + (left ? cntr - l1 : cntr - l - l1 + 1);
    repetitions.emplace_back(pos, pos + 2 * l - 1);
  }
}

void find_repetitions(string s, int shift = 0) {
  int n = s.size();
  if (n == 1) return;

  int nu = n / 2;
  int nv = n - nu;
  string u = s.substr(0, nu);
  string v = s.substr(nu);
  string ru(u.rbegin(), u.rend());
  string rv(v.rbegin(), v.rend());

  find_repetitions(u, shift);
  find_repetitions(v, shift + nu);

  vector<int> z1 = z_function(ru);
  vector<int> z2 = z_function(v + '#' + u);
  vector<int> z3 = z_function(ru + '#' + rv);
  vector<int> z4 = z_function(v);

  for (int cntr = 0; cntr < n; cntr++) {
    int l, k1, k2;
    if (cntr < nu) {
      l = nu - cntr;
      k1 = get_z(z1, nu - cntr);
      k2 = get_z(z2, nv + 1 + cntr);
    } else {
      l = cntr - nu + 1;
      k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
      k2 = get_z(z4, (cntr - nu) + 1);
    }
    if (k1 + k2 >= l) convert_to_repetitions(shift, cntr < nu, cntr, l, k1, k2);
  }
}
```

**本页面主要译自博文 [Поиск всех тандемных повторов в строке. Алгоритм Мейна-Лоренца](http://e-maxx.ru/algo/string_tandems) 与其英文翻译版 [Finding repetitions](https://cp-algorithms.com/string/main_lorentz.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
