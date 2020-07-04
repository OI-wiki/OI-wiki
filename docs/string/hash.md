## Hash 的思想

Hash 的核心思想在于，将输入映射到一个值域较小、可以方便比较的范围。

!!! warning
    这里的“值域较小”在不同情况下意义不同。

    在 [哈希表](../ds/hash.md) 中，值域需要小到能够接受线性的空间与时间复杂度。

    在字符串哈希中，值域需要小到能够快速比较（ $10^9$ 、 $10^{18}$ 都是可以快速比较的）。

    同时，为了降低哈希冲突率，值域也不能太小。

我们定义一个把字符串映射到整数的函数 $f$ ，这个 $f$ 称为是 Hash 函数。

我们希望这个函数 $f$ 可以方便地帮我们判断两个字符串是否相等。

具体来说，我们希望在 Hash 函数值不一样的时候，两个字符串一定不一样。

另外，反过来不需要成立。我们把这种条件称为是单侧错误。

我们需要关注的是什么？

时间复杂度和 Hash 的准确率。

通常我们采用的是多项式 Hash 的方法，即 $f(s) = \sum s[i] \times b^i \pmod M$ 。

这里面的 $b$ 和 $M$ 需要选取得足够合适才行，以使得 Hash 函数的值分布尽量均匀。

如果 $b$ 和 $M$ 互质，在输入随机的情况下，这个 Hash 函数在 $[0,M)$ 上每个值概率相等，此时单次比较的错误率为 $\frac 1 M$ 。所以，哈希的模数一般会选用大质数。

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

### 错误率

若进行 $n$ 次比较，每次错误率 $\frac 1 M$ ，那么总错误率是 $1-\left(1-\frac 1 M\right)^n$ 。在随机数据下，若 $M=10^9 + 7$ , $n=10^6$ ，错误率约为 $\frac 1{1000}$ ，并不是能够完全忽略不计的。

所以，进行字符串哈希时，经常会对两个大质数分别取模，这样的话哈希函数的值域就能扩大到两者之积，错误率就非常小了。

### 多次询问子串哈希

单次计算一个字符串的哈希值复杂度是 $O(n)$ ，其中 $n$ 为串长，与暴力匹配没有区别，如果需要多次询问一个字符串的子串的哈希值，每次重新计算效率非常低下。

一般采取的方法是对整个字符串先预处理出每个前缀的哈希值，将哈希值看成一个 $b$ 进制的数对 $M$ 取模的结果，这样的话每次就能快速求出子串的哈希了：

令 $f_i(s)$ 表示 $f(s[1..i])$ ，那么 $f(s[l..r])=\frac{f_r(s)-f_{l-1}(s)}{b^{l-1}}$ ，其中 $\frac{1}{b^{l-1}}$ 也可以预处理出来，用 [乘法逆元](../math/inverse.md) 或者是在比较哈希值时等式两边同时乘上 $b$ 的若干次方化为整式均可。

这样的话，就可以在 $O(n)$ 的预处理后每次 $O(1)$ 地计算子串的哈希值了。

## Hash 的应用

### 字符串匹配

求出模式串的哈希值后，求出文本串每个长度为模式串长度的子串的哈希值，分别与模式串的哈希值比较即可。

### 最长回文子串

二分答案，判断是否可行时枚举回文中心（对称轴），哈希判断两侧是否相等。需要分别预处理正着和倒着的哈希值。时间复杂度 $O(n\log n)$ 。

这个问题可以使用 [manacher 算法](./manacher.md) 在 $O(n)$ 的时间内解决。

### 例题

???+note "[CF1200E Compress Words](http://codeforces.com/contest/1200/problem/E)"
    给你若干个字符串，答案串初始为空。第 $i$ 步将第 $i$ 个字符串加到答案串的后面，但是尽量地去掉重复部分（即去掉一个最长的、是原答案串的后缀、也是第 $i$ 个串的前缀的字符串），求最后得到的字符串。

    字符串个数不超过 $10^5$，总长不超过 $10^6$。

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
