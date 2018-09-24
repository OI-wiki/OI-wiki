[【模板】乘法逆元](https://www.luogu.org/problemnew/show/P3811)

## 逆元简介

如果一个线性同余方程 $ax \\equiv 1 \\pmod b$，则 $x$ 称为 $a$ 的逆元，记作 $a^{-1}$。

## 如何求逆元

### 扩展欧几里得法：

```cpp
void exgcd(int a,int b,int c,int &x,int &y){
    if(a==0){
        x=0;
        y=0;
        return;
    }
    else{
        int tx,ty;
        exgcd(b%a,a,tx,ty);
        x=ty-(b/a)*tx;
        y=tx;
        return;
    }
}
```

扩展欧几里得法和求解 [线性同余方程](/math/linear-equation/) 是一个原理，在这里不展开解释。

### 快速幂法：

这个要运用 [费马小定理](https://oi-wiki.org/math/fermat/)：

> 若 $p$ 为质数，$a$ 为正整数，且 $a$、$p$ 互质，则 $a^{p-1} \\equiv 1 \\pmod p$。

因为 $ax \\equiv 1 \\pmod b$；

所以 $ax \\equiv a^{b-1} \\pmod b$（根据费马小定理）；

所以 $x \\equiv a^{b-2} \\pmod b$；

然后我们就可以用快速幂来求了。

代码：

```cpp
#define ll long long
inline ll poW(ll a,ll b){
    long long ans=1;
    a%=p;
    while (b){
        if (b&1) ans=((ans*a)%p+p)%p;
        a=(a*a)%p; b>>=1;
    }
    return ans%p;
}
```

### 线性求逆元

但是如果要求的很多，以上两种方法就显得慢了，很有可能超时，所以下面来讲一下如何线性求逆元。

首先，很显然的 $1^{-1} \\equiv 1 \\pmod p$；

然后，设 $p=ki+j,j&lt;i,1&lt;i&lt;p$，再放到 $\\mod p$ 意义下就会得到：$ki+j \\equiv 0 \\pmod p$；

两边同时乘 $i^{-1},j^{-1}$：

$kj^{-1}+i^{-1} \\equiv 0 \\pmod p$；

$i^{-1} \\equiv -kj^{-1}+ \\pmod p$；

$i^{-1} \\equiv -(\\frac{p}{i}) (p \\mod i)^{-1}$；

然后我们就可以推出逆元了，代码只有一行：

```cpp
a[i]=-(p/i)*a[p%i];
```

但是，有些情况下要避免出现负数，所以我们要改改代码，让它只求正整数：

```cpp
a[i]=(p-p/i)*a[p%i]%p;
```

这就是线性求逆元

## 逆元练习题

[\[AHOI2005\]洗牌](https://www.lydsy.com/JudgeOnline/problem.php?id=1965)

[\[SDOI2016\]排列计数](https://www.luogu.org/problemnew/show/P4071)
