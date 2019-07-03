（本文转载自[桃酱的算法笔记](https://zhuanlan.zhihu.com/c_1005817911142838272)，原文戳[链接](https://zhuanlan.zhihu.com/p/41867199)，已获得作者授权）

## 简介

NTT 解决的是多项式乘法带模数的情况，可以说有些受模数的限制，数也比较大，

但是它比较方便呀毕竟没有复数部分

## 学习 NTT 之前……

### 生成子群

子群：群 $(S,⊕), (S′,⊕)$ ， 满足 $S′⊂S$ ，则 $(S′,⊕)$ 是 $(S,⊕)$ 的子群

拉格朗日定理： $|S′|∣|S |$ 证明需要用到陪集，得到陪集大小等于子群大小，每个陪集要么不想交要么相等，所有陪集的并是集合 $S$ ，那么显然成立。

生成子群： $a \in S$ ​的生成子群 $\left<a\right> = \{a^{(k)}, k \geq 1 \}$ ​， $a$ 是 $\left< a \right>$ 的生成元

阶：群 $S$ 中 $a$ 的阶是满足 $a^r=e$ 的最小的 $r$ ， 符号 $\operatorname{ord}(a)$ ， 有 $\operatorname{ord}(a)=\left|\left<a\right>\right|$ ，显然成立。

考虑群 $Z_n^ \times =\{[a], n \in Z_n : \gcd(a, n) = 1\}, |Z_n^ \times | = \phi(n)$

阶就是满足 $a^r \equiv 1 (\bmod n)$ ​的最小的 $r$ ， $\operatorname{ord}(a)=r$

### [原根](/math/primitive-root)

 $g$ 满足 $\operatorname{ord}_n(g)=\left|Z_n^\times\right|=\phi(n)$ ，对于质数 $p$ ，也就是说 $g^i \bmod p, 0 \leq i < p$ 结果互不相同。

模 $n$ 有原根的充要条件 : $n = 2, 4, p^e, 2 \times p^e$

离散对数： $g^t \equiv a (\bmod n)，ind_{n,g}{(a)}=t$

​因为 $g$ 是原根，所以 $gt$ 每 $\phi(n)$ 是一个周期，可以取到 $| Z \times n |$ 的所有元素
对于 $n$ 是质数时，就是得到 $[1,n−1]$ 的所有数，就是 $[0,n−2]$ 到 $[1,n−1]$ 的映射
离散对数满足对数的相关性质，如

求原根可以证明满足 $g^r \equiv 1(\bmod p)$

​的最小的 $r$ 一定是 $p−1$ 的约数
对于质数 $p$ ，质因子分解 $p−1$ ，若 $g^{(p-1)/pi} \neq 1 (\bmod p)$

​恒成立， $g$ 为 $p$ 的原根

## NTT

对于质数 $p=qn+1, (n=2^m)$ ​, 原根 $g$ 满足 $g^{qn} \equiv 1 (\bmod p)$ ​, 将 $g_n=g^p(\bmod q)$ 看做 $\omega_n$ 的等价，择其满足相似的性质，比如 $g_n^n \equiv 1 (\bmod p), g_n^{n/2} \equiv -1 (\bmod p)$

然后因为这里涉及到数论变化，所以这里的 $N$ （为了区分 FFT 中的 n，我们把这里的 n 称为 $N$ ）可以比 FFT 中的 n 大，但是只要把 $\frac{qN}{n}$ 看做这里的 $q$ 就行了，能够避免大小问题……

常见的有

$$
p = 1004535809 = 479 \times 2^{21}+1, g=3
$$

$$
p=998244353=2 \times 17 \times 2^{23}+1, g=3
$$

就是 $g^{qn}$ 的等价 $e^{2\pi n}$

迭代到长度 $l$ 时 $g_l = g^{\frac{p-1}{l}}$ ， 或者 $\omega_n = g_l = g_N^{\frac{N}{l}} = g_N^{\frac{p-1}{l}}$

接下来放一个大数相乘的模板

参考网址如下<https://blog.csdn.net/blackjack_/article/details/79346433>

```cpp
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch <= '9' && ch >= '0') {
    x = 10 * x + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void print(int x) {
  if (x < 0) putchar('-'), x = -x;
  if (x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}

const int N = 300100, P = 998244353;

inline int qpow(int x, int y) {
  int res(1);
  while (y) {
    if (y & 1) res = 1ll * res * x % P;
    x = 1ll * x * x % P;
    y >>= 1;
  }
  return res;
}

int r[N];

void ntt(int *x, int lim, int opt) {
  register int i, j, k, m, gn, g, tmp;
  for (i = 0; i < lim; ++i)
    if (r[i] < i) swap(x[i], x[r[i]]);
  for (m = 2; m <= lim; m <<= 1) {
    k = m >> 1;
    gn = qpow(3, (P - 1) / m);
    for (i = 0; i < lim; i += m) {
      g = 1;
      for (j = 0; j < k; ++j, g = 1ll * g * gn % P) {
        tmp = 1ll * x[i + j + k] * g % P;
        x[i + j + k] = (x[i + j] - tmp + P) % P;
        x[i + j] = (x[i + j] + tmp) % P;
      }
    }
  }
  if (opt == -1) {
    reverse(x + 1, x + lim);
    register int inv = qpow(lim, P - 2);
    for (i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % P;
  }
}

int A[N], B[N], C[N];

char a[N], b[N];

int main() {
  register int i, lim(1), n;
  scanf("%s", &a);
  n = strlen(a);
  for (i = 0; i < n; ++i) A[i] = a[n - i - 1] - '0';
  while (lim < (n << 1)) lim <<= 1;
  scanf("%s", &b);
  n = strlen(b);
  for (i = 0; i < n; ++i) B[i] = b[n - i - 1] - '0';
  while (lim < (n << 1)) lim <<= 1;
  for (i = 0; i < lim; ++i) r[i] = (i & 1) * (lim >> 1) + (r[i >> 1] >> 1);
  ntt(A, lim, 1);
  ntt(B, lim, 1);
  for (i = 0; i < lim; ++i) C[i] = 1ll * A[i] * B[i] % P;
  ntt(C, lim, -1);
  int len(0);
  for (i = 0; i < lim; ++i) {
    if (C[i] >= 10) len = i + 1, C[i + 1] += C[i] / 10, C[i] %= 10;
    if (C[i]) len = max(len, i);
  }
  while (C[len] >= 10) C[len + 1] += C[len] / 10, C[len] %= 10, len++;
  for (i = len; ~i; --i) putchar(C[i] + '0');
  puts("");
  return 0;
}
```
