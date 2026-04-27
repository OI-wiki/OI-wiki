## 概述

要想使用随机化技巧，前提条件是能够快速生成随机数．本文将介绍生成随机数的常见方法．

### 随机数与伪随机数

说一个单独的数是「随机数」是无意义的，所以以下我们都默认讨论「随机数列」，即使提到「随机数」，指的也是「随机数列中的一个元素」．

现有的计算机的运算过程都是确定性的，因此，仅凭借算法来生成真正 **不可预测**、**不可重复** 的随机数列是不可能的．

然而在绝大部分情况下，我们都不需要如此强的随机性，而只需要所生成的数列在统计学上具有随机数列的种种特征（比如均匀分布、互相独立等等）．这样的数列即称为 **伪随机数** 序列．

随机数与伪随机数在实际生活和算法中的应用举例：

-   抽样调查时往往只需使用伪随机数．这是因为我们本就只关心统计特征．
-   网络安全中往往要用到（比刚刚提到的伪随机数）更强的随机数．这是因为攻击者可能会利用可预测性做文章．
-   OI/ICPC 中用到的随机算法，基本都只需要伪随机数．这是因为，这些算法往往是通过引入随机数来把概率引入复杂度分析，从而降低复杂度．这本质上依然只利用了随机数的统计特征．
-   某些随机算法（例如 [Moser 算法](https://en.wikipedia.org/wiki/Algorithmic_Lov%C3%A1sz_local_lemma)）用到了随机数的熵相关的性质，因此必须使用真正的随机数．

## 随机数生成方法

### `rand`

用于生成伪随机数，缺点是比较慢，使用时需要 `#include<cstdlib>`．

调用 `rand()` 函数会返回一个 `[0,RAND_MAX]` 中的随机非负整数，其中 `RAND_MAX` 是标准库中的一个宏，在 Linux 系统下 `RAND_MAX` 等于 $2^{31}-1$．可以用取模来限制所生成的数的大小．

使用 `rand()` 需要一个随机数种子，可以使用 `srand(seed)` 函数来将随机种子更改为 `seed`，当然不初始化也是可以的．

同一程序使用相同的 `seed` 两次运行，在同一机器、同一编译器下，随机出的结果将会是相同的．

有一个选择是使用当前系统时间来作为随机种子：`srand(time(nullptr))`．

??? warning "Warning"
    在 `Windows` 系统下 `rand()` 返回值的取值范围为 $\left[0,2^{15}\right)$（即 `RAND_MAX` 等于 $2^{15}-1$），当需要生成的数不小于 $2^{15}$ 时建议使用 `(rand() << 15 | rand())` 来生成更大的随机数．

关于 `rand()` 和 `rand() % n` 的随机性：

-   C/C++ 标准并未关于 `rand()` 所生成随机数的任何方面的质量做任何规定．
-   GCC 编译器对 `rand()` 所采用的实现方式，保证了分布的均匀性等基本性质，但具有低位周期长度短等明显缺陷．（例如在笔者的机器上，`rand()%2` 所生成的序列的周期长约 $2\cdot 10^6$）
-   即使假设 `rand()` 是均匀随机的，`rand()%n` 也不能保证均匀性，因为 `[0,n)` 中的每个数在 `0%n,1%n,...,RAND_MAX%n` 中的出现次数可能不相同．

### 预定义随机数生成器

定义了数个特别的流行算法．如没有特别说明，均定义于头文件 `<random>`．

??? warning "Warning"
    预定义随机数生成器仅在于 C++11 标准[^ref2]中开始使用．

#### mt19937

是一个随机数生成器类，效用同 `rand()`，随机数的范围同 `unsigned int` 类型的取值范围．

其优点是随机数质量高（一个表现为，出现循环的周期更长，具有 $2^{19937} - 1$ 的周期；其他方面也都至少不逊于 `rand()`），且速度比 `rand()` 快很多．使用时需要 `#include<random>`．

`mt19937` 基于 32 位梅森缠绕器，由松本与西村设计于 1998 年[^ref3]，使用时用其定义一个随机数生成器即可：`std::mt19937 myrand(seed)`，`seed` 可不填，不填 `seed` 则会使用默认随机种子．

`mt19937` 重载了 `operator ()`，需要生成随机数时调用 `myrand()` 即可返回一个随机数．

另一个类似的生成器是 `mt19937_64`，基于 64 位梅森缠绕器，由松本与西村设计于 2000 年，使用方式同 `mt19937`，但随机数范围扩大到了 `unsigned long long` 类型的取值范围．

??? note "代码示例"
    ```cpp
    #include <ctime>
    #include <iostream>
    #include <random>
    
    using namespace std;
    
    int main() {
      mt19937 myrand(time(nullptr));
      cout << myrand() << endl;
      return 0;
    }
    ```

#### 线性同余随机数生成器

线性同余随机数生成器（简称 LCG）由 Thomson 和 Rotenberg 于 1958 年发布．其计算公式如下，其中 $A, C, M$ 为预定义常数：

$$
s_i \equiv \begin{cases}
\operatorname{seed} & i = 0 \\
s_{i-1} \times A + C & i \ge 1
\end{cases}\pmod{M}
$$

从 C++11 开始，模板类 `std::linear_congruential_engine` 实现基于如上方法的随机数生成器，模板参数如下：

```cpp
template <class UIntType, UIntType A, UIntType C, UIntType M>
class linear_congruential_engine;
```

这里 `UIntType` 表示 $s$ 的类型，随后是三个常数．

随后 Lewis、Goodman 及 Miller 于 1969 提出，取 $A = 7^{5} = 16807$、$C = 0$、$M = 2^{31} - 1 = 2147483647$ 时，此算法可以达到该模数下近乎最大的周期 $2^{31} - 2$（因为 $16807$ 是该模数下的 [原根](/math/number-theory/primitive-root.md)）且具有相对不错的统计特征．

之后于 1988 年，该参数的 LCG 由 Park 与 Miller 采纳为「最小标准」，只因其实现极其简单、易懂、高效、且质量相对不错．最后于 1993 年，Park、Miller 和 Stockmeyer 将参数 $A$ 改为 $48271$，成为较新的「最小标准」．两个版本的「最小标准」作为 `linear_congruential_engine` 的特化，也都于 C++11 中预定义，分别为 `minstd_rand0` 和 `minstd_rand`．具体而言：

-   对于 `minstd_rand0`，$s_i$ 的类型为 32 位无符号整数，$A$ 取 $16807$，$C$ 取 $0$，$M$ 取 $2147483647$．

-   对于 `minstd_rand`，$s_i$ 的类型为 32 位无符号整数，$A$ 取 $48271$，$C$ 取 $0$，$M$ 取 $2147483647$．

使用方法也很简单，直接定义 `std::minstd_rand myrand(seed);`，其中 `seed` 为种子，不填时默认为 $1$．然后调用 `myrand()` 即可．

如果需要自定义该形式的随机数生成器，且 $A, C, M$ 不是常数，则还可以考虑手写实现．该方法实现难度低，但生成的随机序列周期长度较短（周期最大为 $M$，但大多数情况下都会比 $M$ 短）．

??? note "参考实现"
    ```cpp
    #include <iostream>
    using namespace std;
    
    struct myrand {
      int A, C, M, x;
    
      myrand(int A, int C, int M) {
        this->A = A;
        this->C = C;
        this->M = M;
        this->x = 0;
      }
    
      // 生成随机序列的下一个随机数
      int next() { return x = ((long long)A * x + C) % M; }
    };
    
    myrand rnd(3, 5, 97);  // 初始化一个随机数生成器
    
    int main() {
      int x = rnd.next();
      cout << x << endl;
      return 0;
    }
    ```

#### 非确定随机数的均匀分布整数随机数生成器

`random_device` 是一个基于硬件的均匀分布随机数生成器，**在熵池耗尽** 前可以高速生成随机数．该类在 C++11 定义，需要 `random` 头文件．由于熵池耗尽后性能急剧下降，所以建议用此方法生成 `mt19937` 等伪随机数的种子，而不是直接生成．

`random_device` 是非确定的均匀随机位生成器，尽管若不支持非确定随机数生成，则允许实现用伪随机数引擎实现．目前笔者尚未接到报告称 NOIP 评测机不支持基于硬件的均匀分布随机数生成．但出于保守考虑，建议使用该算法生成随机数种子．

参考代码如下．

```cpp
#include <iostream>
#include <map>
#include <random>
#include <string>

int main() {
  std::random_device rd;
  std::map<int, int> hist;
  std::uniform_int_distribution<int> dist(0, 9);
  for (int n = 0; n < 20000; ++n) {
    ++hist[dist(rd)];  // 注意：仅用于演示：一旦熵池耗尽，
                       // 许多 random_device 实现的性能就急剧下滑
                       // 对于实践使用， random_device 通常仅用于
                       // 播种类似 mt19937 的伪随机数生成器
  }
  for (auto p : hist) {
    std::cout << p.first << " : " << std::string(p.second / 100, '*') << '\n';
  }
}
```

可能的输出如下．

```plain
0 : ********************
1 : *******************
2 : ********************
3 : ********************
4 : ********************
5 : *******************
6 : ********************
7 : ********************
8 : *******************
9 : ********************
```

#### 随机数分布

这里介绍的是要求生成的随机数按照一定的概率出现，如等概率，[伯努利分布](https://en.wikipedia.org/wiki/Bernoulli_distribution)，[二项分布](https://en.wikipedia.org/wiki/Binomial_distribution)，[几何分布](https://en.wikipedia.org/wiki/Geometric_distribution)，[标准正态（高斯）分布](https://en.wikipedia.org/wiki/Normal_distribution)．

具体类名请参见 [伪随机数生成——随机数分布](https://zh.cppreference.com/w/cpp/numeric/random#.E9.9A.8F.E6.9C.BA.E6.95.B0.E5.88.86.E5.B8.83) 的列表．

下面的程序模拟了一个六面体骰子．

```cpp
#include <iostream>
#include <random>

int main() {
  std::random_device rd;   // 将用于为随机数引擎获得种子
  std::mt19937 gen(rd());  // 以播种标准 mersenne_twister_engine
  std::uniform_int_distribution<> dis(1, 6);

  for (int n = 0; n < 10; ++n)
    // 用 dis 变换 gen 所生成的随机 unsigned int 到 [1, 6] 中的 int
    std::cout << dis(gen) << ' ';
  std::cout << '\n';
}
```

### 其他实现方法

有的时候我们需要实现自己的随机数生成器．下面是一些常用的随机数生成方法．

#### Xorshift

Xorshift 系列随机数生成器由 George Marsaglia 于 2003 年提出，其主要基于异或一个数的移位这一种操作．在算法竞赛中常用的版本有 `xorshift32` 和 `xorshift64` 两种：

```cpp
using u32 = unsigned int;
using u64 = unsigned long long;

u32 xorshift32(u32 x) {
  x ^= x << 13;
  x ^= x >> 17;
  x ^= x << 5;
  return x;
}

u64 xorshift32(u64 x) {
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  return x;
}
```

播种方式是直接给 $x$ 赋值为对应的种子，生成方法是将上一次输出的结果作为下一次输入．这两个函数在 $x$ 不为 $0$ 时分别具有 $2^{32} - 1$ 和 $2^{64} - 1$ 的周期，因其实现极其简单，常将其和种子下发给选手生成大范围的数据以减少 I/O 开销．

#### SplitMix

SplitMix 系列随机数生成器由 Stelle，Lee 和 Flood 于 2014 年提出，并应用于 Java 8 的 `java.util.SplittableRandom` 类中．在算法竞赛界最常用的版本为 `splitmix64`：

```cpp
using u64 = unsigned long long;

u64 x;

u64 splitmix64() {
  u64 z = (x += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}
```

其最主要的用途是对一个已经求出的哈希值进行二次哈希，以防止被人通过精心构造的数据卡哈希表卡到超时：

```cpp
struct MyHash {
  u64 mix64(u64 x) {
    // x += 0x9e3779b97f4a7c15; // 这一步实际上失去意义
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(size_t x) {
    static const u64 FIXED_RANDOM =
        std::chrono::steady_clock::now().time_since_epoch().count();
    return mix64(x + FIXED_RANDOM);
  }
}
```

其亦可用于生成随机数，播种方式是直接给 $x$ 赋值为对应的种子，生成方式是直接反复调用 `splitmix64()`．此时较为显然的，该函数具有 $2^{64}$ 的周期（因为所有的大数都是奇数，所以 $x$ 具有 $2^{64}$ 的周期，且后面对 $z$ 的所有操作都是完全可逆的）．这也意味着即使你记不住如上的大参数，你也可以直接随便写几个足够大的奇数结合异或右移来达到相近的效果．

#### 时滞斐波那契随机数生成器

利用下式来生成随机数序列 $\{R_i\}$（其中 $0 < j < k$）：

$$
R_i \equiv R_{i-j} \star R_{i-k} \bmod P
$$

这里的 $P$ 通常取 $2$ 的幂（常用 $2^{32}$ 或 $2^{64}$），$\star$ 表示二元运算符，可以使用加法，减法，乘法，异或．

该方法较传统的线性同余随机数生成器而言，拥有更长的周期，但随机性受初始条件影响较大．

??? note "参考实现"
    ```cpp
    #include <iostream>
    #include <vector>
    using namespace std;
    
    struct myrand {
      vector<unsigned> vec;
      int l, j, k, cur;
    
      myrand(int l, int j, int k) {
        this->l = l;
        this->j = j;
        this->k = k;
        cur = 0;
        for (int i = 0; i < l; i++) {
          vec.push_back(rand());  // 先用其他方法生成随机序列中的前几个元素
        }
      }
    
      unsigned next() {
        vec[cur] = vec[(cur - j + l) % l] * vec[(cur - k + l) % l];
        // 这里用 unsigned 类型是为了实现自动对 2^32 取模
        return vec[cur++];
      }
    };
    
    myrand rnd(11, 4, 7);
    
    int main() {
      unsigned x = rnd.next();
      cout << x << endl;
      return 0;
    }
    ```

## 随机算法

下面介绍在 C++ 标准中定义的一些依赖随机数生成的随机算法．

### `random_shuffle`

`std::random_shuffle` 于 C++98 引入，用于随机打乱指定序列．使用时需要 `#include<algorithm>`，常用实现方法为 [Fisher-Yates 算法](https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle)．

使用时传入指定区间的首尾指针或迭代器（左闭右开）即可：`std::random_shuffle(first, last)` 或 `std::random_shuffle(first, last, myrand)`．

内部使用的随机数生成器默认为 `rand()`．当然也可以传入自定义的随机数生成器．

关于 `random_shuffle` 的随机性：

-   C++ 标准中要求 `random_shuffle` 在所有可能的排列中 **等概率** 随机选取，但 GCC[^note1]编译器 **并未** 严格执行．
-   GCC 中 `random_shuffle` 随机性上的缺陷的原因之一，是因为它使用了 `rand()%n` 这样的写法．如先前所述，这样生成的不是均匀随机的整数．
-   原因之二，是因为 `rand()` 的值域有限．如果所传入的区间长度超过 `RAND_MAX`，将存在某些排列 **不可能** 被产生[^ref1]．

??? warning "Warning"
    `random_shuffle` 已于 C++14 标准中被弃用，于 C++17 标准中被移除．

### `shuffle`

`std::shuffle` 于 C++17 引入，效用同 `random_shuffle`．使用时需要 `#include<algorithm>`．

区别在于必须使用自定义的随机数生成器：`std::shuffle(first, last, myrand)`．

GCC[^note1]实现的 `shuffle` 符合 C++ 标准的要求，即在所有可能的排列中等概率随机选取．

下面是用 `rand()` 及 `random_shuffle()` 编写的一个数据生成器．生成数据为 [「ZJOI2012」灾难](https://www.luogu.com.cn/problem/P2597) 的随机小数据．

```cpp
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

int a[100];

int main() {
  srand(time(nullptr));
  int n = rand() % 99 + 1;
  for (int i = 1; i <= n; i++) a[i] = i;
  std::cout << n << '\n';
  for (int i = 1; i <= n; i++) {
    std::random_shuffle(a + 1, a + i);
    int cnt = rand() % i;
    for (int j = 1; j <= cnt; j++) std::cout << a[j] << ' ';
    std::cout << 0 << '\n';
  }
}
```

下面是用 `mt19937` 及 `shuffle()` 编写的同一个数据生成器．

```cpp
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

int a[100];

int main() {
  std::mt19937 rng(time(nullptr));
  int n = rng() % 99 + 1;
  for (int i = 1; i <= n; i++) a[i] = i;
  std::cout << n << '\n';
  for (int i = 1; i <= n; i++) {
    std::shuffle(a + 1, a + i, rng);
    int cnt = rng() % i;
    for (int j = 1; j <= cnt; j++) std::cout << a[j] << ' ';
    std::cout << 0 << '\n';
  }
}
```

下面是随机排列前十个正整数的一个实现．

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(v.begin(), v.end(), g);

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}
```

### `sample`

`std::sample` 于 C++17 引入，用于从序列里随机选择其中 $n$ 个元素，与 `shuffle` 后提取前 $n$ 个元素的主要区别在于选出来的元素输出后仍保持相对顺序．常用实现方法为 [蓄水池抽样法](https://en.wikipedia.org/wiki/Reservoir_sampling)．

使用方法为 `std::sample(first, last, dest, n, myrand)`，其中 `[first, last)` 表示要采样的范围，`[dest, dest + n)` 表示要输出到的地方，`myrand` 是指定的随机数生成器

下面是从 11 个大写字母里随机抽取 4 个的实现．

```cpp
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>

int main() {
  std::string in{"ABCDEFGHIJK"}, out;
  std::sample(in.begin(), in.end(), std::back_inserter(out), 4,
              std::mt19937{std::random_device{}()});
  std::cout << "Four random letters out of " << in << " : " << out << '\n';
}
```

## 参考资料与注释

[^ref1]: [Don't use rand(): a guide to random number generators in C++](https://codeforces.com/blog/entry/61587)

[^ref2]: [伪随机数生成 - cppreference.com](https://zh.cppreference.com/w/cpp/numeric/random#%E9%A2%84%E5%AE%9A%E4%B9%89%E9%9A%8F%E6%9C%BA%E6%95%B0%E7%94%9F%E6%88%90%E5%99%A8)

[^ref3]: [Mersenne Twister algorithm](https://en.wikipedia.org/wiki/Mersenne_Twister)

[^note1]: 版本号为 GCC 9.2.0
