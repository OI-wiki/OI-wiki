## 简介 ##

莫比乌斯反演是数论中的重要内容。对于一些函数 $f(n)$，如果很难直接求出它的值，而容易求出其倍数和或约数和 $g(n)$，那么可以通过莫比乌斯反演简化运算，求得 $f(n)$ 的值。

开始学习莫比乌斯反演前，我们需要一些前置知识：**积性函数**、**Dirichlet 卷积**、**莫比乌斯函数**。

---

## 积性函数 ##

### 定义 ###

若 $\gcd(x,y)=1$ 且 $f(xy)=f(x)f(y)$，则 $f(n)$ 为积性函数。

### 性质 ###

若 $f(x)$ 和 $g(x)$ 均为积性函数，则以下函数也为积性函数：


$$

\begin{align*}
h(x)&=f(x^p)\\
h(x)&=f^p(x)\\
h(x)&=f(x)g(x)\\
h(x)&=\sum_{d\mid x}f(d)g(\frac{x}{d})
\end{align*}

$$


### 例子 ###


$$

\qquad\begin{array}
\text{约数个数函数}&d(n)=\displaystyle\sum_{d\mid n}1\\
\text{约数和函数}&\displaystyle\sigma(n)=\sum_{d\mid n}d\\
\text{约数 $k$ 次幂函数}&\displaystyle\sigma_k(n)=\sum_{d\mid n}d^k\\
\text{欧拉函数}&\displaystyle\varphi(n)=\sum_{i=1}^n [\gcd(i,n)=1]\\
\text{莫比乌斯函数}&\displaystyle\mu(n)=
\begin{cases}
1 & n=1\\
(-1)^k &c_{1,2,\cdots,k}=1\quad(n=\displaystyle\prod_{i=1}^k {p_i}^{c_i})\\
0 & c_i>1
\end{cases}
\end{array}

$$


---

## Dirichlet 卷积 ##

### 定义 ###

定义两个数论函数 $f,g$ 的 $\text{Dirichlet}$ 卷积为


$$
(f*g)(n)=\sum_{d\mid n}f(d)g(\frac{n}{d})
$$


### 性质 ###

$\text{Dirichlet}$ 卷积满足交换律和结合律。

其中 $\varepsilon$ 为 $\text{Dirichlet}$ 卷积的单位元（任何函数卷 $\varepsilon$ 都为其本身）

### 例子 ###

$$

\begin{align*}
\varepsilon=\mu*1&\Leftrightarrow\varepsilon(n)=\sum_{d\mid n}\mu(d)\\
d=1*1&\Leftrightarrow d(n)=\sum_{d\mid n}1\\
\sigma=d*1&\Leftrightarrow\varepsilon(n)=\sum_{d\mid n}d\\
\varphi=\mu*\text{ID}&\Leftrightarrow\varphi(n)=\sum_{d\mid n}d\cdot\mu(\frac{n}{d})
\end{align*}

$$


---

## 莫比乌斯函数 ##

### 定义 ###

$\mu$ 为莫比乌斯函数

### 性质 ###

莫比乌斯函数不但是积性函数，还有如下性质：


$$

\mu(n)=
\begin{cases}
1&n=1\\
0&n\text{ 含有平方因子}\\
(-1)^k&k\text{ 为 }n\text{ 的本质不同质因子个数}\\
\end{cases}

$$


### 证明 ###

$$

\varepsilon(n)=
\begin{cases}
1&n=1\\
0&n\neq 1\\
\end{cases}

$$


其中 $\displaystyle\varepsilon(n)=\sum_{d\mid n}\mu(d)$ 即 $\varepsilon=\mu*1$

设 $\displaystyle n=\prod_{i=1}^k{p_i}^{c_i},n'=\prod_{i=1}^k p_i$

那么 $\displaystyle\sum_{d\mid n}\mu(d)=\sum_{d\mid n'}\mu(d)=\sum_{i=0}^k C_k^i\cdot(-1)^k$

根据二项式定理，易知该式子的值在 $k=0$ 即 $n=1$ 时值为 $1$ 否则为 $0$，这也同时证明了 $\displaystyle\sum_{d\mid n}\mu(d)=[n=1]$

### 补充结论 ###

反演结论：$\displaystyle [gcd(i,j)=1] \Leftrightarrow\sum_{d\mid\gcd(i,j)}\mu(d)$

- **直接推导**：如果看懂了上一个结论，这个结论稍加思考便可以推出：如果 $\gcd(i,j)=1$ 的话，那么代表着我们按上个结论中枚举的那个 $n$ 是 $1$，也就是式子的值是 $1$，反之，有一个与 $[\gcd(i,j)=1]$ 相同的值：$0$

- **利用 $\varepsilon$ 函数**：根据上一结论，$[\gcd(i,j)=1]\Rightarrow \varepsilon(\gcd(i,j))$，将 $\varepsilon$ 展开即可。


### 线性筛 ###
由于 $\mu$ 函数为积性函数，因此可以线性筛莫比乌斯函数（线性筛基本可以求所有的积性函数，尽管方法不尽相同）。

**代码**：
```cpp
void getMu() {
	mu[1]=1;
	for(int i=2;i<=n;++i) {
		if(!flg[i]) p[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*p[j]<=n;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) {
				mu[i*p[j]]=0;
				break;
			}
			mu[i*p[j]]=-mu[i];
		}
	}
}
```

### 拓展 ###

证明


$$
\varphi*1=\text{ID}\text{（ID 函数即 } f(x)=x\text{）}
$$


将 $n$ 分解质因数：$\displaystyle n=\prod_{i=1}^k {p_i}^{c_i}$

首先，因为 $\varphi$ 是积性函数，故只要证明当 $n'=p^c$ 时 $\displaystyle\varphi*1=\sum_{d\mid n'}\varphi(\frac{n'}{d})=\text{ID}$ 成立即可。

因为 $p$ 是质数，于是 $d=p^0,p^1,p^2,\cdots,p^c$

易知如下过程：


$$

\begin{align*}
\varphi*1&=\sum_{d\mid n}\varphi(\frac{n}{d})\\
&=\sum_{i=0}^c\varphi(p^i)\\
&=1+p^0\cdot(p-1)+p^1\cdot(p-1)+\cdots+p^{c-1}\cdot(p-1)\\
&=p^c\\
&=\text{ID}\\
\end{align*}

$$


该式子两侧同时卷 $\mu$ 可得 $\displaystyle\varphi(n)=\sum_{d\mid n}d\cdot\mu(\frac{n}{d})$

---

## 莫比乌斯反演 ##

### 公式 ###

设 $f(n),g(n)$ 为两个数论函数。

如果有


$$
f(n)=\sum_{d\mid n}g(d)
$$


那么有


$$
g(n)=\sum_{d\mid n}\mu(d)f(\frac{n}{d})
$$


### 证明 ###

- **暴力计算**：


$$
\sum_{d\mid n}\mu(d)f(\frac{n}{d})=\sum_{d\mid n}\mu(d)\sum_{k\mid \frac{n}{d}}g(k)=\sum_{k\mid n}g(k)\sum_{d\mid \frac{n}{k}}\mu(d)=g(n)
$$


用 $\displaystyle\sum_{d\mid n}g(d)$ 来替换 $f(\dfrac{n}{d})$，再变换求和顺序。最后一步转为的依据：$\displaystyle\sum_{d\mid n}\mu(d)=[n=1]$，因此在 $\dfrac{n}{k}=1$ 时第二个和式的值才为 $1$。此时 $n=k$，故原式等价于 $\displaystyle\sum_{k\mid n}[n=k]\cdot g(k)=g(n)$

- **运用卷积**：

原问题为：已知 $f=g*1$，证明 $g=f*\mu$

易知如下转化：$f*\mu=g*1*\mu\Rightarrow f*\mu=g$（其中 $1*\mu=\varepsilon$）

---

## 问题形式 ##

### [「HAOI 2011」Problem b](https://www.lydsy.com/JudgeOnline/problem.php?id=2301) ###

求值（多组数据）


$$
\sum_{i=x}^{n}\sum_{j=y}^{m}[\gcd(i,j)=k]\qquad (1\leqslant T,x,y,n,m,k\leqslant 5\times 10^4)
$$


根据容斥原理，原式可以分成 $4$ 块来处理，每一块的式子都为


$$
\sum_{i=1}^{n}\sum_{j=1}^{m}[\gcd(i,j)=k]
$$


考虑化简该式子


$$
\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}[\gcd(i,j)=1]
$$


因为 $\gcd(i,j)=1$ 时对答案才用贡献，于是我们可以将其替换为 $\varepsilon(\gcd(i,j))$（$\varepsilon(n)$ 当且仅当 $n=1$ 时值为 $1$ 否则为 $0$ ），故原式化为


$$
\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\varepsilon(\gcd(i,j))
$$


将 $\varepsilon$ 函数展开得到


$$
\displaystyle\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{d\mid  \gcd(i,j)}\mu(d)
$$


变换求和顺序，先枚举 $d\mid gcd(i,j)$ 可得


$$
\displaystyle\sum_{d=1}^{\lfloor\frac{n}{k}\rfloor}\mu(d)\sum_{i=1}^{\lfloor\frac{n}{k}\rfloor}d\mid i\sum_{j=1}^{\lfloor\frac{m}{k}\rfloor}d\mid j
$$


（其中 $d\mid i$ 表示 $i$ 是 $d$ 的倍数时对答案有 $1$ 的贡献）
易知 $1\sim\lfloor\dfrac{n}{k}\rfloor$ 中 $d$ 的倍数有 $\lfloor\dfrac{n}{kd}\rfloor$ 个，故原式化为


$$
\displaystyle\sum_{d=1}^{\lfloor\frac{n}{k}\rfloor}\mu(d) \lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor
$$


很显然，式子可以数论分块求解（注意：过程中默认 $n\leqslant m$）。

**时间复杂度**：$\Theta(N+T\sqrt{n})$

**代码**：
```cpp
#include <cstdio>
#include <algorithm>
const int N=50000;
int mu[N+5],p[N+5];
bool flg[N+5];
void init() {
	int tot=0;
	mu[1]=1;
	for(int i=2;i<=N;++i) {
		if(!flg[i]) {
			p[++tot]=i;
			mu[i]=-1;
		}
		for(int j=1;j<=tot&&i*p[j]<=N;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) {
				mu[i*p[j]]=0;
				break;
			}
			mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=N;++i) mu[i]+=mu[i-1];
}
int solve(int n,int m) {
	int res=0;
	for(int i=1,j;i<=std::min(n,m);i=j+1) {
		j=std::min(n/(n/i),m/(m/i));
		res+=(mu[j]-mu[i-1])*(n/i)*(m/i);
	}
	return res;
}
int main() {
	int T,a,b,c,d,k;
	init();
	for(scanf("%d",&T);T;--T) {
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		printf("%d\n",solve(b/k,d/k)-solve(b/k,(c-1)/k)-solve((a-1)/k,d/k)+solve((a-1)/k,(c-1)/k));
	}
	return 0;
}
```

### [「SPOJ 5971」LCMSUM](https://www.luogu.org/problemnew/show/SP5971) ###

求值（多组数据）


$$
\sum_{i=1}^n \text{lcm}(i,n)\qquad (1\leqslant T\leqslant 3\times 10^5,1\leqslant n\leqslant 10^6)
$$


易得原式即


$$
\sum_{i=1}^n \frac{i\cdot n}{\gcd(i,n)}
$$


根据 $\gcd(a,n)=1$ 时一定有 $\gcd(n-a,n)=1$ ，可将原式化为


$$
\frac{1}{2}\cdot(\sum_{i=1}^{n-1}\frac{i\cdot n}{\gcd(i,n)}+\sum_{i=n-1}^{1}\frac{i\cdot n}{\gcd(i,n)})+n
$$


上述式子中括号内的两个 $\sum$ 对应的项相等，故又可以化为


$$
\frac{1}{2}\cdot \sum_{i=1}^{n-1}\frac{n^2}{\gcd(i,n)}+n
$$


可以将相同的 $\gcd(i,n)$ 合并在一起计算，故只需要统计 $\gcd(i,n)=d$ 的个数。当 $\gcd(i,n)=d$ 时，$\displaystyle\gcd(\frac{i}{d},\frac{n}{d})=1$，所以 $\gcd(i,n)=d$ 的个数有 $\displaystyle\varphi(\frac{n}{d})$ 个。

故答案为


$$
 \frac{1}{2}\cdot\sum_{d\mid n}\frac{n^2\cdot\varphi(\frac{n}{d})}{d}+n
$$


变换求和顺序，设 $\displaystyle d'=\frac{n}{d}$，式子化为


$$
\frac{1}{2}n\cdot\sum_{d'\mid n}d'\cdot\varphi(d')+n
$$


设 $\displaystyle \text{g}(n)=\sum_{d\mid n} d\cdot\varphi(d)$，已知 $\text{g}$ 为积性函数，于是可以 $\Theta(n)$ 预处理。最后枚举 $d$，统计贡献即可。

**时间复杂度**：$\Theta(n\log n)$

**代码**：
```cpp
#include <cstdio>
const int N=1000000;
int tot,p[N+5],phi[N+5];
long long ans[N+5];
bool flg[N+5];

void solve() {
    phi[1]=1;
    for(int i=2;i<=N;++i) {
        if(!flg[i]) p[++tot]=i,phi[i]=i-1;
        for(int j=1;j<=tot&&i*p[j]<=N;++j) {
            flg[i*p[j]]=1;
            if(i%p[j]==0) {
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            phi[i*p[j]]=phi[i]*(p[j]-1);
        }
    }
    for(int i=1;i<=N;++i) {
        for(int j=1;i*j<=N;++j) {
            ans[i*j]+=1LL*j*phi[j]/2;
        }
    }
    for(int i=1;i<=N;++i) ans[i]=1LL*i*ans[i]+i;
}
int main() {
    int T,n;
    solve();
    for(scanf("%d",&T);T;--T) {
        scanf("%d",&n);
        printf("%lld\n",ans[n]);
    }
    return 0;
}
```

### [「BZOJ 2154」Crash的数字表格](https://www.lydsy.com/JudgeOnline/problem.php?id=2154) ###

求值（对 $20101009$ 取模）


$$
\sum_{i=1}^n\sum_{j=1}^m\text{lcm}(i,j)\qquad (n,m\leqslant 10^7)
$$


易知原式等价于


$$
\sum_{i=1}^n\sum_{j=1}^m\frac{i\cdot j}{\gcd(i,j)}
$$


枚举最大公因数 $d$，显然两个数除以 $d$ 得到的数互质


$$
\sum_{i=1}^n\sum_{j=1}^m\sum_{d\mid i,d\mid j,\gcd(\frac{i}{d},\frac{j}{d})=1}\frac{i\cdot j}{d}
$$


非常经典的 $\gcd$ 式子的化法


$$
\sum_{d=1}^n d\cdot\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}[\gcd(i,j)=1]\ i\cdot j
$$


后半段式子中，出现了互质数对之积的和，为了让式子更简洁就把它拿出来单独计算。于是我们记


$$
\text{sum}(n,m)=\sum_{i=1}^n\sum_{j=1}^m [\gcd(i,j)=1]\  i\cdot j
$$


接下来对 $\text{sum}(n,m)$ 进行化简。首先枚举约数，并将 $[\gcd(i,j)=1]$ 表示为 $\varepsilon(\gcd(i,j))$


$$
\sum_{d=1}^n\sum_{d\mid i}^n\sum_{d\mid j}^m\mu(d)\cdot i\cdot j
$$


设 $i=i'\cdot d$，$j=j'\cdot d$，显然式子可以变为


$$
\sum_{d=1}^n\mu(d)\cdot d^2\cdot\sum_{i=1}^{\lfloor\frac{n}{d}\rfloor}\sum_{j=1}^{\lfloor\frac{m}{d}\rfloor}i\cdot j
$$


观察上式，前半段可以预处理前缀和；后半段又是一个范围内数对之和，记


$$
g(n,m)=\sum_{i=1}^n\sum_{j=1}^m i\cdot j=\frac{n\cdot(n+1)}{2}\times\frac{m\cdot(m+1)}{2}
$$


可以 $\Theta(1)$ 求解

至此


$$
\text{sum}(n,m)=\sum_{d=1}^n\mu(d)\cdot d^2\cdot g(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)
$$


我们可以 $\lfloor\frac{n}{\lfloor\frac{n}{d}\rfloor}\rfloor$ 数论分块求解 $\text{sum}(n,m)$ 函数。

在求出 $\text{sum}(n,m)$ 后，回到定义 $\text{sum}$ 的地方，可得原式为


$$
\sum_{d=1}^n d\cdot\text{sum}(\lfloor\frac{n}{d}\rfloor,\lfloor\frac{m}{d}\rfloor)
$$


可见这又是一个可以数论分块求解的式子！

本题除了推式子比较复杂、代码细节较多之外，是一道很好的莫比乌斯反演练习题！（上述过程中，默认 $n\leqslant m$）

**时间复杂度**：$\Theta(n+m)$（两次数论分块）

**代码**：
```cpp
#include <cstdio>
#include <algorithm>
using std::min;

const int N=1e7;
const int mod=20101009;
int n,m,mu[N+5],p[N/10+5],sum[N+5];
bool flg[N+5];

void init() {
	mu[1]=1;
	int tot=0,k=min(n,m);
	for(int i=2;i<=k;++i) {
		if(!flg[i]) p[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*p[j]<=k;++j) {
			flg[i*p[j]]=1;
			if(i%p[j]==0) {mu[i*p[j]]=0;break;}
			mu[i*p[j]]=-mu[i];
		}
	}
	for(int i=1;i<=k;++i) sum[i]=(sum[i-1]+1LL*i*i%mod*(mu[i]+mod))%mod;
}
int Sum(int x,int y) {
	return (1LL*x*(x+1)/2%mod)*(1LL*y*(y+1)/2%mod)%mod;
}
int func(int x,int y) {
	int res=0;
	for(int i=1,j;i<=min(x,y);i=j+1) {
		j=min(x/(x/i),y/(y/i));
		res=(res+1LL*(sum[j]-sum[i-1]+mod)*Sum(x/i,y/i)%mod)%mod;
	}
	return res;
}
int solve(int x,int y) {
	int res=0;
	for(int i=1,j;i<=min(x,y);i=j+1) {
		j=min(x/(x/i),y/(y/i));
		res=(res+1LL*(j-i+1)*(i+j)/2%mod*func(x/i,y/i)%mod)%mod;
	}
	return res;
}
int main() {
	scanf("%d%d",&n,&m);
	init();
	printf("%d\n",solve(n,m));
}
```

> 本文部分内容引用于 [algocode 算法博客](https://algocode.net)，特别鸣谢！
