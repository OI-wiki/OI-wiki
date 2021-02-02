## Hash 的思想

Hash 的核心思想在于，将输入映射到一个值域较小、可以方便比较的范围。

!!! warning

    这里的“值域较小”在不同情况下意义不同。

    在 [哈希表](../ds/hash.md) 中，值域需要小到能够接受线性的空间与时间复杂度。

    在字符串哈希中，值域需要小到能够快速比较（ $10^9$ 、 $10^{18}$ 都是可以快速比较的）。

    同时，为了降低哈希冲突率，值域也不能太小。

我们定义一个把字符串映射到整数的函数 $f$ ，这个 $f$ 称为是 Hash 函数。

我们希望这个函数 $f$ 可以方便地帮我们判断两个字符串是否相等。

具体来说，哈希函数最重要的性质可以概括为下面两条：

1. 在 Hash 函数值不一样的时候，两个字符串一定不一样；

2. 在 Hash 函数值一样的时候，两个字符串不一定一样（但有大概率一样，且我们当然希望它们总是一样的）。

Hash 函数值一样时原字符串却不一样的现象我们成为哈希碰撞。

我们需要关注的是什么？

时间复杂度和 Hash 的准确率。

通常我们采用的是多项式 Hash 的方法，对于一个长度为 $l$ 的字符串 $s$ 来说，我们可以这样定义多项式 Hash 函数： $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$ 。例如，对于字符串 $xyz$ ，其哈希函数值为 $xb^2+yb+z$ 。

特别要说明的是，也有很多人使用的是另一种 Hash 函数的定义，即 $f(s) = \sum_{i=1}^{l} s[i] \times b^{i-1} \pmod M$ ，这种定义下，同样的字符串 $xyz$ 的哈希值就变为了 $x+yb+zb^2$ 了。显然，上面这两种哈希函数的定义函数都是可行的，但二者在之后会讲到的计算子串哈希值时所用的计算式是不同的，因此千万注意 **不要弄混了这两种不同的 Hash 方式** 。由于前者的 Hash 定义计算更简便、使用人数更多、且可以类比为一个 $b$ 进制数来帮助理解，所以本文下面所将要讨论的都是使用 $f(s) = \sum_{i=1}^{l} s[i] \times b^{l-i} \pmod M$ 来定义的 Hash 函数。

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

若进行 $n$ 次比较，每次错误率 $\dfrac 1 M$ ，那么总错误率是 $1-\left(1-\dfrac 1 M\right)^n$ 。在随机数据下，若 $M=10^9 + 7$ , $n=10^6$ ，错误率约为 $\dfrac 1{1000}$ ，并不是能够完全忽略不计的。

所以，进行字符串哈希时，经常会对两个大质数分别取模，这样的话哈希函数的值域就能扩大到两者之积，错误率就非常小了。

### 多次询问子串哈希

单次计算一个字符串的哈希值复杂度是 $O(n)$ ，其中 $n$ 为串长，与暴力匹配没有区别，如果需要多次询问一个字符串的子串的哈希值，每次重新计算效率非常低下。

一般采取的方法是对整个字符串先预处理出每个前缀的哈希值，将哈希值看成一个 $b$ 进制的数对 $M$ 取模的结果，这样的话每次就能快速求出子串的哈希了：

令 $f_i(s)$ 表示 $f(s[1..i])$ ，即原串长度为 $i$ 的前缀的哈希值，那么按照定义有 $f_i(s)=s[1]\cdot b^{i-1}+s[2]\cdot b^{i-2}+...+s[i-1]\cdot b+s[i]$ 

现在，我们想要用类似前缀和的方式快速求出 $f(s[l..r])$ ，按照定义有字符串 $s[l..r]$ 的哈希值为 $f(s[l..r])=s[l]\cdot b^{r-l}+s[l+1]\cdot b^{r-l-1}+...+s[r-1]\cdot b+s[r]$ 

对比观察上述两个式子，我们发现 $f(s[l..r])=f_r(s)-f_{l-1}(s) \times b^{r-l+1}$ 成立（可以手动代入验证一下），因此我们用这个式子就可以快速得到子串的哈希值。其中 $b^{r-l+1}$ 可以 $O(n)$ 的预处理出来然后 $O(1)$ 的回答每次询问（当然也可以快速幂 $O(\log n)$ 的回答每次询问）。

## Hash 的应用

### 字符串匹配

求出模式串的哈希值后，求出文本串每个长度为模式串长度的子串的哈希值，分别与模式串的哈希值比较即可。

### 最长回文子串

二分答案，判断是否可行时枚举回文中心（对称轴），哈希判断两侧是否相等。需要分别预处理正着和倒着的哈希值。时间复杂度 $O(n\log n)$ 。

这个问题可以使用 [manacher 算法](./manacher.md) 在 $O(n)$ 的时间内解决。

### 确定字符串中不同子字符串的数量

问题：给定长为 $n$ 的字符串，仅由小写英文字母组成，查找该字符串中不同子串的数量。

为了解决这个问题，我们遍历了所有长度为 $l=1,\cdots ,n$ 的子串。对于每个长度为 $l$ ，我们将其 Hash 值乘以相同的 $b$ 的幂次方，并存入一个数组中。数组中不同元素的数量等于字符串中长度不同的子串的数量，并此数字将添加到最终答案中。

为了方便起见，我们将使用 $h [i]$ 作为 Hash 的前缀字符，并定义 $h[0]=0$ 。

??? note "参考代码"
    ```cpp
    int count_unique_substrings(string const& s) {
      int n = s.size();
    
      const int b = 31;
      const int m = 1e9 + 9;
      vector<long long> b_pow(n);
      b_pow[0] = 1;
      for (int i = 1; i < n; i++) b_pow[i] = (b_pow[i - 1] * b) % m;
    
      vector<long long> h(n + 1, 0);
      for (int i = 0; i < n; i++)
        h[i + 1] = (h[i] + (s[i] - 'a' + 1) * b_pow[i]) % m;
    
      int cnt = 0;
      for (int l = 1; l <= n; l++) {
        set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
          long long cur_h = (h[i + l] + m - h[i]) % m;
          cur_h = (cur_h * b_pow[n - i - 1]) % m;
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
    
    字符串个数不超过 $10^5$ ，总长不超过 $10^6$ 。
    
    ??? mdui-shadow-6 "题解"
        每次需要求最长的、是原答案串的后缀、也是第 $i$ 个串的前缀的字符串。枚举这个串的长度，哈希比较即可。
        
        当然，这道题也可以使用 [KMP 算法](./kmp.md) 解决。
    
    ??? mdui-shadow-6 "参考代码"
        ```cpp
        #include <cstdio>
        #include <cstring>
        #include <iostream>
        #include <string>
        using namespace std;
        const int CN = 1e6 + 6;
        const int M1 = 11431471;
        const int B1 = 231;
        const int M2 = 37101101;
        const int B2 = 312;
        int read() {
          int s = 0, ne = 1;
          char c = getchar();
          while (c < '0' || c > '9') ne = c == '-' ? -1 : 1, c = getchar();
          while (c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
          return s * ne;
        }
        int qp(int a, int b, int P) {
          int r = 1;
          while (b) {
            if (b & 1) r = 1ll * r * a % P;
            a = 1ll * a * a % P;
            b >>= 1;
          }
          return r;
        }
        int H1[CN], H2[CN], l1 = 0;
        void add1(int x) {
          H1[l1 + 1] = (1ll * H1[l1] * B1 % M1 + x) % M1,
                  H2[l1 + 1] = (1ll * H2[l1] * B2 % M2 + x) % M2;
          l1++;
        }
        int h1[CN], h2[CN], l2 = 0;
        void add2(int x) {
          h1[l2 + 1] = (1ll * h1[l2] * B1 % M1 + x) % M1,
                  h2[l2 + 1] = (1ll * h2[l2] * B2 % M2 + x) % M2;
          l2++;
        }
        int get(int* h, int l, int r, int b, int m) {
          return 1ll * (h[r] - 1ll * h[l - 1] * qp(b, r - l + 1, m) % m + m) % m;
        }
        int n, len;
        char cur[CN], nxt[CN];
        int main() {
          n = read() - 1;
          cin >> cur;
          len = strlen(cur);
          for (int i = 0; i < len; i++) add1(cur[i] - '0');
          while (n--) {
            cin >> nxt;
            int l = strlen(nxt);
            for (int i = 0; i < l; i++) add2(nxt[i] - '0');
            int p = 0;
            for (int i = 0; i < l && i < len; i++) {
              int G1 = get(H1, len - i, len, B1, M1),
                  G2 = get(H2, len - i, len, B2, M2);
              int g1 = get(h1, 1, i + 1, B1, M1), g2 = get(h2, 1, i + 1, B2, M2);
              if (G1 == g1 && G2 == g2) p = i + 1;
            }
        
            for (int i = len; i < len - p + l; i++)
              cur[i] = nxt[i - len + p], add1(cur[i] - '0');
            len = len - p + l, cur[len] = '\0';
            l2 = 0;
          }
          cout << cur;
        }
        ```

 **本页面部分内容译自博文 [строковый хеш](https://github.com/e-maxx-eng/e-maxx-eng/blob/61aff51f658644424c5e1b717f14fb7bf054ae80/src/string/string-hashing.md) 与其英文翻译版 [String Hashing](https://cp-algorithms.com/string/string-hashing.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
