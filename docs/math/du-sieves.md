在数论题目中，常常需要根据一些**积性函数**的性质，求出一些式子的值。

**积性函数**：对于所有互质的$a$和$b$，总有$f(ab)=f(a)f(b)$，则称$f(x)$为积性函数。

常见的积性函数有：

$d(x)=\sum_{i|n} 1$

$\sigma(x)=\sum_{i|n} i$

$\varphi(x)=\sum_{i=1}^x 1[gcd(x,i)=1]$

$\mu(x)=\begin{cases}1&\text{n=1}\\(-1)^k& \ \prod_{i=1}^k q_i=1\\0 &\ \max\{q_i\}>1\end{cases}$

积性函数有如下性质：

若$f(x)$，$g(x)$为积性函数，则

$h(x)=f(x^p)$

$h(x)=f^p(x)$

$h(x)=f(x)g(x)$

$h(x)=\sum_{d|x} f(d)g(\frac x d)$

中的$h(x)$也为积性函数。

在莫比乌斯反演的题目中，往往要求出一些数论函数的前缀和，利用**杜教筛**可以快速求出这些前缀和。

??? note " 例题[P4213【模板】杜教筛（Sum）](https://www.luogu.org/problemnew/show/P4213)"

题目大意：求$S_1(n)= \sum_{i=1}^n \mu(i)$和$S_2(n)= \sum_{i=1}^n \varphi(i)$的值，$n\le 2^{31} -1$。

由**狄利克雷卷积**，我们知道：

$\because \epsilon =\mu * 1$（$\epsilon(n)=~[n=1]$）

$\therefore \epsilon (n)=\sum_{d|n} \mu(d)$

$S_1(n)=\sum_{i=1}^n \epsilon (i)-\sum_{i=2}^n S_1(\lfloor \frac n i \rfloor)$

$= 1-\sum_{i=2}^n S_1(\lfloor \frac n i \rfloor)$

观察到$\lfloor \frac n i \rfloor$最多只有$O(\sqrt n)$种取值，我们就可以应用**整除分块**（或称数论分块）来计算每一项的值了。

直接计算的时间复杂度为$O(n^{\frac 3 4})$。考虑先线性筛预处理出前$n^{\frac 2 3}$项，剩余部分的时间复杂度为

$O(\int_{0}^{n^{\frac 1 3}} \sqrt{\frac{n}{x}} ~ dx)=O(n^{\frac 2 3})$

对于较大的值，需要用`map`存下其对应的值，方便以后使用时直接使用之前计算的结果。

当然也可以用杜教筛求出$\varphi (x)$的前缀和，但是更好的方法是应用莫比乌斯反演：

$\sum_{i=1}^n \sum_{j=1}^n 1[gcd(i,j)=1]=\sum_{i=1}^n \sum_{j=1}^n \sum_{d|i,d|j} \mu(d)$

$=\sum_{d=1}^n \mu(d) {\lfloor \frac n d \rfloor}^2$

由于题目所求的是$\sum_{i=1}^n \sum_{j=1}^i 1[gcd(i,j)=1]$，所以我们排除掉$i=1,j=1$的情况，并将结果除以$2$即可。

观察到，只需求出莫比乌斯函数的前缀和，就可以快速计算出欧拉函数的前缀和了。时间复杂度$O(n^{\frac 2 3})$。

给出一种代码实现：

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
const int maxn = 2000010;
typedef long long ll;
ll T, n, pri[maxn], cur, mu[maxn], sum_mu[maxn];
bool vis[maxn];
map<ll, ll> mp_mu;
ll S_mu(ll x) {
  if (x < maxn) return sum_mu[x];
  if (mp_mu[x]) return mp_mu[x];
  ll ret = 1ll;
  for (ll i = 2, j; i <= x; i = j + 1) {
    j = x / (x / i);
    ret -= S_mu(x / i) * (j - i + 1);
  }
  return mp_mu[x] = ret;
}
ll S_phi(ll x) {
  ll ret = 0ll;
  for (ll i = 1, j; i <= x; i = j + 1) {
    j = x / (x / i);
    ret += (S_mu(j) - S_mu(i - 1)) * (x / i) * (x / i);
  }
  return ((ret - 1) >> 1) + 1;
}
int main() {
  scanf("%lld", &T);
  mu[1] = 1;
  for (int i = 2; i < maxn; i++) {
    if (!vis[i]) {
      pri[++cur] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cur && i * pri[j] < maxn; j++) {
      vis[i * pri[j]] = true;
      if (i % pri[j])
        mu[i * pri[j]] = -mu[i];
      else {
        mu[i * pri[j]] = 0;
        break;
      }
    }
  }
  for (int i = 1; i < maxn; i++) sum_mu[i] = sum_mu[i - 1] + mu[i];
  while (T--) {
    scanf("%lld", &n);
    printf("%lld %lld\n", S_phi(n), S_mu(n));
  }
  return 0;
}
```
