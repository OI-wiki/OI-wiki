## 关于环境

- 不要使用任何以 `ATCODER_` 开头的宏。
- 运行环境需满足特殊要求：
    - 可以使用 `__int128 / unsigned __int128`（对于 g++、clang++）、`_mul128 / _umul128`（对于 msvc）。
    - 可以使用 `__builtin_(ctz/ctzll/clz/clzll/popcount)`（对于 g++、clang++）、`_BitScan(Forward/Reverse)`（对于 msvc）。
    - `char / short / int / ll` 及他们的 `unsigned` 类型（及 `signed char`）是 `8 / 16 / 32 / 64` 位。
    - [有符号整数是二进制补码](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0907r0.html)。

## 如何安装

### g++ / clang++

最简单的方式是，将 `atcoder` 文件夹放在与待编译的文件同一目录下，然后编译 `g++ main.cpp -std=c++14 -I .`。

也有以下其他方式：

- 将编译命令改为 `g++ main.cpp -std=c++14 -I /path/to/ac-library`，其中 `atcoder` 文件夹应在 `/path/to/ac-library` 下。
- 配置环境变量 `CPLUS_INCLUDE_PATH` 为 `ac-library` 所在的路径（在 Windows 下注意使用反斜杠），之后使用 `g++ main.cpp -std=c++14`。

### msvc

只支持 VS 2017+。

将 `atcoder `文件夹放在这个路径中。

`(安装盘符):\Program Files\Microsoft Visual Studio\(2017, 2019 或 2022)\(Community, Professional 或 Enterprise)\VC\Tools\MSVC\(MSVC 版本，如 14.38.33130)\include`

## 提交到其他 OJ

`ac-library` 文件夹下附带了 `expander.py`，可以运行以下命令得到 `combined.cpp` 以提交到其他 OJ：

``` shell
$ # 需要 python 3.5+
$ python3 expander.py main.cpp # main.cpp 是文件名
```

尽管我们进行了测试，我们不保证 expander 的正确性和可用性。

## 常见问题

### 默认构造函数

``` cpp
scc_graph g1; // OK
int main() {
  int n;
  std::cin >> n;
  scc_graph g2(n); // Also OK
  g1 = scc_graph(n); // Also OK
  // 注意这里的 g1 如果在初始化前访问成员变量 / 调用成员函数，则行为未定义。
}
```

### 默认模板参数

卷积文档中有这么一段签名：

``` cpp
vector<T> convolution<int m = 998244353>(vector<T> a, vector<T> b);
```

这里模板参数中的 $m$ 如果不显式指定值，则自动设置为 $998244353$。

``` cpp
auto x = convolution(a, b);            // MOD: 998244353
auto y = convolution<924844033>(a, b); // MOD: 924844033
```

### explicit 说明符

除 `modint` 外，算法库中所有构造函数均带有 `explicit` 说明符。
