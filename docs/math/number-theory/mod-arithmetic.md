author: 383494, buuzzing, c-forrest, cr4c1an, Emp7iness, Enter-tainer, Great-designer, HeRaNO, jifbt, Kaiser-Yang, Koishilll, ksyx, Marcythm, Qiu-Quanzhi, Saisyc, sshwy, StarryReverie, StudyingFather, Tiphereth-A, Xeonacid, xyf007

算法竞赛中，数论部分的一个重要组成部分就是 **模算术**（modular arithmetic），也就是在某一模数下进行各种整数运算。除了基础的四则运算和求幂外，还可以方便地进行取对数、开各次方、求阶乘和组合数等运算。

模算术常见于各类问题中，而不仅仅局限于数论部分。很多问题的实际答案可能非常大，超过了常见的整型变量的存储范围。此时，为了避免引入大整数运算和输出长数字，题目常常要求对答案取模后输出。这就要求熟练掌握各类模算术技巧。

## C/C++ 的整数除法和取模运算

在 C/C++ 中，整数除法和取模运算，与数学上习惯的取模和除法不一致。

对于所有标准版本的 C/C++，规定在整数除法中：

1.  当除数为 0 时，行为未定义；
2.  否则 `(a / b) * b + a % b` 的运算结果与 `a` 相等。

也就是说，取模运算的符号取决于除法如何取整；而除法如何取整，这是实现定义的（由编译器决定）。

从 [C99](https://en.cppreference.com/w/c/language/operator_arithmetic) 和 [C++11](https://en.cppreference.com/w/cpp/language/operator_arithmetic) 标准版本起，规定 **商向零取整**（舍弃小数部分）；取模的符号就与被除数相同。从此，以下运算结果保证为真：

```c
5 % 3 == 2;
5 % -3 == 2;
-5 % 3 == -2;
-5 % -3 == -2;
```

## 模整数类

除了上述基础运算外，还可以在各种模数下做如下运算：

-   [除法运算](./linear-equation.md)
-   [阶乘](./factorial.md)
-   [组合数](./lucas.md)
-   [开平方](./quad-residue.md)
-   [取对数](./discrete-logarithm.md)
-   [开各次方](./residue.md)

模意义下的运算大多可以看作求解某种同余方程。对于求解同余方程（组）的一般方法，可以参考 [同余方程](./congruence-equation.md) 页面。

### 快速乘

在素性测试与质因数分解中，经常会遇到模数在 `long long` 范围内的乘法取模运算。为了避免运算中的整型溢出问题，本节介绍一种可以处理模数在 `long long` 范围内，不需要使用 `__int128` 且复杂度为 $O(1)$ 的「快速乘」。

我们发现：

$$
a\times b\bmod m=a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m
$$

我们巧妙运用 `unsigned long long` 的自然溢出：

$$
a\times b\bmod m=a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m=\left(a\times b-\left\lfloor \dfrac{ab}m \right\rfloor\times m\right)\bmod 2^{64}
$$

于是在算出 $\left\lfloor\dfrac{ab}m\right\rfloor$ 后，两边的乘法和中间的减法部分都可以使用 `unsigned long long` 直接计算，现在我们只需要解决如何计算 $\left\lfloor\dfrac {ab}m\right\rfloor$。

我们考虑先使用 `long double` 算出 $\dfrac am$ 再乘上 $b$。

既然使用了 `long double`，就无疑会有精度误差。极端情况就是第一个有效数字（二进制下）在小数点后一位。在 64 位系统中，`long double` 通常表示为 $80$ 位扩展精度浮点数（即符号为 $1$ 位，指数为 $15$ 位，尾数为 $64$ 位），所以 `long double` 最多能精确表示的有效位数为 $64$[^note1]。所以 $\dfrac am$ 最差从第 $65$ 位开始出错，误差范围为 $\left(-2^{-64},2^{-64}\right)$。乘上 $b$ 这个 $64$ 位整数，误差范围为 $(-0.5,0.5)$，再加上 $0.5$ 误差范围为 $(0,1)$，取整后误差范围位 $\{0,1\}$。于是乘上 $-m$ 后，误差范围变成 $\{0,-m\}$，我们需要判断这两种情况。

因为 $m$ 在 `long long` 范围内，所以如果计算结果 $r$ 在 $[0,m)$ 时，直接返回 $r$，否则返回 $r+m$，当然你也可以直接返回 $(r+m)\bmod m$。

代码实现如下：

```cpp
long long binmul(long long a, long long b, long long m) {
  unsigned long long c =
      (unsigned long long)a * b -
      (unsigned long long)((long double)a / m * b + 0.5L) * m;
  if (c < m) return c;
  return c + m;
}
```

如今，绝大多数测评系统所配备的 C/C++ 编译器已支持 `__int128` 类型，因此也可以利用 [Barrett Reduction](https://en.wikipedia.org/wiki/Barrett_reduction) 进行快速乘。之所以不直接将乘数类型提升至 `__int128` 后取模计算是因为此方法仍然可以节省一次时间可观的 `__int128` 类型取模。

## 进阶算法

## 参考资料与注释

[^note1]: 参见 [Double-precision floating-point format - Wikipedia](https://en.wikipedia.org/wiki/Double-precision_floating-point_format)。
