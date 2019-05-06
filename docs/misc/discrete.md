## 简介

离散化本质上也可以看成是[哈希](/string/hash)的过程。同时要保证哈希以后仍然保持原来的全/偏序关系。

通俗的将就是有些数因为本身很大或者类型不支持，自身无法作为数组的下标来方便地处理，而影响最终结果的只有元素之间的相对大小关系时，我们可以将原来的数据按照从大到小重新编号。

用来离散化的可以是大整数、浮点数、字符串……等等。


## 实现

C++ 离散化有现成的 STL 算法：

### 离散化数组

将一个数组离散化，并进行查询是比较常用的应用场景：

```cpp
//a[i]为初始数组,范围为1~n
//len为离散化后数组的有效长度
using namespace std;
sort(a+1,a+1+n);
len=unique(a+1,a+1+n)-a-1;//离散化整个数组的同时求出离散化后数的个数。
```

在完成上述离散化之后可以使用getid函数查找离散化之后的排名（即新编号）：
```cpp
int getid(int x){
  return lower_bound(a+1,a+1+len,x)-a;
}
```

### 离散化vector动态数组

需要对vector进行离散话可以使用：

```cpp
// vector<int> a, b; b 是 a 的一个副本
std::sort(a.begin(), a.end());
V.erase(std::unique(a.begin(), a.end()), a.end());
for (int i = 0; i < n; ++i)
  b[i] = std::lower_bound(a.begin(), a.end(), b[i]) - a.begin();
```
