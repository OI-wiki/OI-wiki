## 简介

所谓离散化，一般是指数据范围很大，但是它的实际大小并不是很重要，我们只需要用到它们的相对大小关系。

或者是有些数本身很大，自身无法作为数组的下标来方便地处理。

用来离散化的可以是大整数、浮点数、字符串……等等。

离散化本质上也可以看成是[哈希](/string/hash)的过程。

## 实现

C++ 离散化有现成的 STL 算法：

```cpp
// vector<int> a, b; b 是 a 的一个副本
std::sort(a.begin(), a.end());
V.erase(std::unique(a.begin(), a.end()), a.end());
for (int i = 0; i < n; ++i)
  b[i] = std::lower_bound(a.begin(), a.end(), b[i]) - a.begin();
```
