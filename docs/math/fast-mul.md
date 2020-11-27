模 N 快速乘法，可以用来解决在模 N 意义下乘法溢出的问题。

## 问题引入

在有时候，我们需要将两个比较大的数相乘再取模（比如说，在[rho 算法](./pollard-rho.md)中，我们给定了一个比较大的数$x$，需要计算$x\times x\bmod b$，如果直接计算乘法时可能会发生溢出）。为了避免溢出的情况，需要引入在模 N 意义下进行快速乘法的算法。

## 基础算法
即使在 `long long` 下进行乘法，也可能会溢出。我们可以模仿二进制乘法：
``` C++
using ll = long long;

ll pmul(ll x, ll y, ll p) {
    ll result=0;
    while (y) {
        if (y & 1) result = (result + x) % p;
        x = (x<<1) % p; y >>= 1;
    }
    return result;
}
```

给定两个数 $x = 2^0 p_0 + 2^1 p_1 + \cdots + 2^n p_n$，$y = 2^0 q_0 + 2^1 p_1 + \cdots + 2^n p_n$。

我们有：$result = x\cdot y\bmod N = (2^0 q_0 x + 2^1 q_1 x + \cdots + 2^n q_n x)\bmod N$。

注意到，`(x<<1)` 是用来给自己乘以二的。因为每一次乘完了就会取模，完全不会溢出了。

## 参考资料

[812-xiao-wen 的快速乘博客](https://www.cnblogs.com/812-xiao-wen/p/10543023.html)
