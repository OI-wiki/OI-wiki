## hash的思想

哈希的核心思想在于，将输入映射到一个值域较小、可以方便比较的范围。

!!! warning
    这里的“值域较小”在不同情况下意义不同。
    
    在 [哈希表](../ds/hash.md) 中，值域需要小到能够接受线性的空间与时间复杂度。
    
    在字符串哈希中，值域需要小到能够快速比较（ $10^9$ 、 $10^{18}$ 都是可以快速比较的）。
    
    同时，为了降低哈希冲突率，值域也不能太小。

我们需要有效地解决比较字符串的问题，而暴力破解的方法只是比较两个字符串的字母，时间复杂度为$O(\min(n_1,n_2))$（$n_1,n_2$是两个字符串的长度）。而哈希算法比较字符串的背后想法如下：我们将每个字符串转换为整数，然后比较他们而不是字符串，于是比较字符串是复杂度只有$O(1)$的操作。

于是为了进行转换，我们需要定义一个把字符串映射到整数的函数 $f$ ，这个 $f$ 称为是**哈希函数**。这个函数满足以下条件：如果两个字符串$s$和$t$相等，即$s=t$，那么他们的哈希值也一定相等：
$$
\operatorname{hash}(s)=\operatorname{hash}(t)
$$
否则这两个字符串无法比较。

注意，反之不一定成立。如果哈希值相等，字符串也不一定相等。我们把这种条件称为是单侧错误，这是因为两个完全不同的字符串可能具有相同的哈希值。

那么我们需要关注的是什么？

时间复杂度和哈希的冲突率。

通常我们采用的是多项式哈希的方法，即：
$$
\begin{align} \text{hash}(s) &= s[0] + s[1] \cdot b + s[2] \cdot b^2 + ... + s[n-1] \cdot b^{n-1} \bmod m \\ &= \sum_{i=0}^{n-1} s[i] \cdot b^i \bmod m, \end{align}
$$
这里面的 $b$和 $M$ 需要选取得足够合适才行，以使得哈希函数的值分布尽量均匀。

如果 $b$ 和 $M$ 互质，在输入随机的情况下，这个哈希函数在 $[0,M)$ 上每个值概率相等，此时单次比较的冲突率为 $\frac 1 M$ 。所以，哈希的模数一般会选用大质数。

## Hash 的实现

参考代码：（效率低下的版本，实际使用时一般不会这么写）

```cpp
using std::string;

const int M = 1e9 + 7;
const int B = 233;

typedef long long ll;

int get_hash(const string& s) {
  int res = 0;
  for (int i = 0; i < s.size(); ++i) {
    res = (ll)(res * B + s[i]) % M;
  }
  return res;
}

bool cmp(const string& s, const string& t) {
  return get_hash(s) == get_hash(t);
}
```

## Hash 的分析与改进

### 哈希冲突与降低

若进行 $n$ 次比较，每次冲突率 $\dfrac 1 M$ ，那么总冲突率是 $1-\left(1-\dfrac 1 M\right)^n$ 。在随机数据下，若 $M=10^9 + 7$ , $n=10^6$ ，冲突率约为 $\dfrac 1{1000}$ ，并不是能够完全忽略不计的。

于是我们有一个非常简单的技巧来减小冲突率：我们可以为每个字符串计算两个不同的哈希（通过使用两个不同的$b$或者$M$，然后比较两次获得的哈希对 。）如果两个哈希函数的$M\approx 10^9$，那么就几乎等同于一个哈希函数的$M\approx 10^{18}$，这样哈希冲突的概率就能大大降低。



### 多次询问子串哈希

单次计算一个字符串的哈希值复杂度是 $O(n)$ ，其中 $n$ 为串长，与暴力匹配没有区别，如果需要多次询问一个字符串的子串的哈希值，每次重新计算效率非常低下。

一般采取的方法是对整个字符串先预处理出每个前缀的哈希值，将哈希值看成一个 $b$ 进制的数对 $M$ 取模的结果，这样的话每次就能快速求出子串的哈希了。

通过定义，我们有：
$$
\text{f}(s[i \dots j]) = \sum_{k = i}^j s[k] \cdot b^{k-i} \bmod M
$$
两边同时乘以$b^i$得：
$$
\begin{align} \text{f}(s[i \dots j]) \cdot b^i &= \sum_{k = i}^j s[k] \cdot b^k \bmod M\\ &= \text{f}(s[0 \dots j]) - \text{f}(s[0 \dots i-1]) \bmod  M \end{align}
$$


令 $ f_i(s)$ 表示 $f(s[1..i])$ ，那么 $f(s[l..r])=\frac{f_r(s)-f_{l-1}(s)}{b^{l-1}}$ ，其中 $\frac{1}{b^{l-1}}$ 也可以预处理出来，用 [乘法逆元](../math/inverse.md) 或者是在比较哈希值时等式两边同时乘上 $b$ 的若干次方化为整式均可。

这样的话，就可以在 $O(n)$ 的预处理后每次 $O(1)$ 地计算子串的哈希值了。

## Hash 的应用

### 字符串匹配

求出模式串的哈希值后，求出文本串每个长度为模式串长度的子串的哈希值，分别与模式串的哈希值比较即可。

### 最长回文子串

二分答案，判断是否可行时枚举回文中心（对称轴），哈希判断两侧是否相等。需要分别预处理正着和倒着的哈希值。时间复杂度 $O(n\log n)$ 。

这个问题可以使用 [manacher 算法](./manacher.md) 在 $O(n)$ 的时间内解决。

### 确定字符串中不同子字符串的数量

问题：给定长为$n$的字符串 ，仅由小写英文字母组成，查找该字符串中不同子串的数量。

为了解决这个问题，我们遍历了所有子串的长度 $l=1,\cdots ,n$。对于每个长度为$l$，我们将其哈希值乘以相同的幂$b$，并存入一个数组中。数组中不同元素的数量等于字符串中长度不同的子串的数量，并此数字将添加到最终答案中。

为了方便起见，我们将使用 $h [i] $ 作为哈希的前缀字符，并定义$h[o]=0$ 。

```c++
int count_unique_substrings(string const& s) {
    int n = s.size();

    const int b = 31;
    const int m = 1e9 + 9;
    vector<long long> b_pow(n);
    b_pow[0] = 1;
    for (int i = 1; i < n; i++)
        b_pow[i] = (b_pow[i-1] * b) % m;

    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * b_pow[i]) % m;

    int cnt = 0;
    for (int l = 1; l <= n; l++) {
        set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
            long long cur_h = (h[i + l] + m - h[i]) % m;
            cur_h = (cur_h * b_pow[n-i-1]) % m;
            hs.insert(cur_h);
        }
        cnt += hs.size();
    }
    return cnt;
}
```

### 例题

???+note "[CF1200E Compress Words](http://codeforces.com/contest/1200/problem/E)"
    给你若干个字符串，答案串初始为空。第 $i$ 步将第 $i$ 个字符串加到答案串的后面，但是尽量地去掉重复部分（即去掉一个最长的、是原答案串的后缀、也是第 $i$ 个串的前缀的字符串），求最后得到的字符串。


~~~
字符串个数不超过 $10^5$ ，总长不超过 $10^6$ 。

??? mdui-shadow-6 "题解"
    每次需要求最长的、是原答案串的后缀、也是第 $i$ 个串的前缀的字符串。枚举这个串的长度，哈希比较即可。

    当然，这道题也可以使用 [KMP 算法](./kmp.md) 解决。

??? mdui-shadow-6 "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>

    const int N = 1000010;
    const int m1 = 998244353;
    const int m2 = 1000001011;
    const int K = 233;

    typedef long long ll;

    int m, h1[N], h2[N], len, i1[N], i2[N];
    char s[N];

    void add(char x) {
      h1[len + 1] = ((ll)h1[len] * K + x) % m1;
      h2[len + 1] = ((ll)h2[len] * K + x) % m2;
      ++len;
    }

    int get1(int l, int r) { return (ll)(h1[r] - h1[l - 1] + m1) * i1[l - 1] % m1; }
    int get2(int l, int r) { return (ll)(h2[r] - h2[l - 1] + m2) * i2[l - 1] % m2; }

    bool cmp(int l1, int r1, int l2, int r2) {
      return get1(l1, r1) == get1(l2, r2) && get2(l1, r1) == get2(l2, r2);
    }

    int qpow(int x, int y, int mod) {
      int out = 1;
      while (y) {
        if (y & 1) out = (ll)out * x % mod;
        x = (ll)x * x % mod;
        y >>= 1;
      }
      return out;
    }

    int main() {
      i1[0] = i2[0] = 1;
      int k1 = qpow(K, m1 - 2, m1);  // 求逆元
      int k2 = qpow(K, m2 - 2, m2);
      for (int i = 1; i < N; ++i) {
        i1[i] = (ll)i1[i - 1] * k1 % m1;
        i2[i] = (ll)i2[i - 1] * k2 % m2;
      }

      scanf("%d", &m);

      while (m--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) add(s[i]);
        // 先把当前串加到答案串的后面，可以方便地求哈希
        for (int i = std::min(n, len - n); i >= 0; --i) {
          if (cmp(len - n - i + 1, len - n, len - n + 1, len - n + i)) {
            len -= n;  // 确定了要加多长再真正地加进去
            for (int j = i + 1; j <= n; ++j) add(s[j]);
            printf("%s", s + i + 1);
            break;
          }
        }
      }

      return 0;
    }
    ```
~~~

******



[Topcoder SRM 604, Div1-250](https://community.topcoder.com/stat?c=problem_statement&pm=12917&rd=15837)

 **本页面部分内容译自博文 [строковый хеш](https://github.com/e-maxx-eng/e-maxx-eng/blob/61aff51f658644424c5e1b717f14fb7bf054ae80/src/string/string-hashing.md)与其英文翻译版[String Hashing](https://cp-algorithms.com/string/string-hashing.html)。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。**
