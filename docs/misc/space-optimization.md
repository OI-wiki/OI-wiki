空间优化相关技巧在算法竞赛中不太常见，但仍有讨论价值。

## 信息熵

信息熵描述了存储数据所占用的空间下限，若实际可用的空间低于这个下限则必然损失信息。

???+ note "定义"
    对随机变量 $X$，定义信息熵为
    
    $$
    H(X)=-\sum_{x}P(X=x)\log_2 P(X=x).
    $$

定义中对数底数为 $2$ 是因为计算机中存储的信息每位只有 $2$ 种取值：$0$ 和 $1$。

例如设 $X$ 服从 $\{1,2,\dots,n\}$ 上的均匀分布，则其信息熵为

$$
H(X)=-\sum_{i=1}^n\frac{1}{n}\log_2\frac{1}{n}=\log_2 n,
$$

所以我们至少需要 $\log_2 n$ 位来存储 $1$ 到 $n$ 的整数。

### 例题

???+ note "[\[WC2022\] 猜词](https://www.luogu.com.cn/problem/P8079)"
    交互题，你需要在有限次数内猜一个 5 个字母的单词。每次猜测都需要猜一个词库中存在的单词。如果猜对了，游戏结束；在每次猜错后，交互库会返回哪些字母的位置是正确的，以及哪些字母在待猜单词中出现了但位置是错误的。
    
    ??? note "解法"
        参见 [用信息论解 Wordle 谜题 - 3Blue1Brown](https://www.bilibili.com/video/BV1zZ4y1k7Jw)。
        
        考虑计算信息熵，显然每次猜词时选择信息熵高的词可使得期望猜词次数尽可能小。
        
        由于本题在猜测之前给出了答案首字母，所以我们可以预处理出每种首字母的最优猜测。
        
        另外若剩余的词很少的话，我们可以考虑优先输出可能是答案的词，从而减小次数。

## 常见技巧

### 避免存储不必要的数据

例如：

-   在 [可持久化线段树](../ds/persistent-seg.md) 中，由于单次修改只会产生 $O(\log n)$ 个新结点，所以我们不需要把每个版本的线段树都完整地存储下来，只需要记录新结点即可。
-   考虑 [图的存储](../graph/save.md)，对稀疏图来说，若使用邻接矩阵则会存储大量无用的 $0$，所以一般使用邻接表存稀疏图。
-   `bool` 数组的每个元素均会占用一个字节的空间，必要时可用每个元素只占用一位的 `std::vector<bool>` 或 [bitset](../lang/csl/bitset.md) 代替。
-   在 [背包 DP](../dp/knapsack.md) 中，对 01 背包而言，每次计算 DP 值只会用到上一次计算时的数据，所以我们可以用滚动数组优化空间，只需要记录当前 DP 值即可。

### 利用数据特性

考虑支持路径压缩和启发式合并的 [并查集](../ds/dsu.md)，传统做法需要两个数组，分别记录父结点编号和子树大小。

注意到：

1.  在应用了路径压缩后，对于并查集中的一棵树，我们只需要记录根结点对应的子树大小。
2.  根结点的父亲一定是自己。

我们可以利用有符号整数的特性，用负数表示根结点，正数表示非根结点，所以我们只需一个数组即可实现支持路径压缩和启发式合并的并查集。

???+ note "实现"
    ```cpp
    --8<-- "docs/misc/code/space-optimization/space-optimization_1.cpp"
    ```
### 利用計算機特性

1. 比如在 C++ 中的 `struct` 和 `class` 还是有差异的，在继承的过程中可能会造成额外的指针。那么就应该优先使用 `struct` 来减少额外的内存丢失。
   ```cpp
   // source: https://www.cprogramming.com/tutorial/size_of_class_object.html
   class ABase{ 
        int iMem; 
    }; 
    class BBase : public virtual ABase { 
        int iMem; 
    }; 
   ```
2. 在某些数据结构中，善于用 `union` 语法进行压缩，如常见的 `std::string` 在不同的函数库中有不同的实作。
   ```cpp
   // source: https://stackoverflow.com/questions/76213003/internal-struct-of-std-string-object
   class string {
    ...
    private:
        size_type m_size;
        union {
            class {
                std::unique_ptr<char[]> m_data;
                size_type m_capacity;
            } m_large;
            std::array<char, sizeof(m_large)> m_small;
        };
    };
   ```
3. 指针优化，一般在 64 位平台上需要 8 字节才能完成，所以打 OI 竞赛多半用整数 int 计数索引。
   ```cpp
   // source: https://stackoverflow.com/questions/78338138/using-usecompressedoops
   struct TreeNode {
       TreeNode *lson, *rson;
   }
   struct TreeNode {
       int lson, rson;
   }
   ```
4. 结构体数组与结构体数组，为注意对齐的问题。有时需要改写结构声明。
   ```cpp
   // source: https://en.wikipedia.org/wiki/AoS_and_SoA
   struct Data {
       char c;
       int next;
   } data[10000];

   int next[10000];
   char c[10000];
   ```
5. 预设的初始大小，如 `std::vector` 为 1、`unordered_map` 为 16，这些细节会在唤醒结构中被凸显出来，例如 `map<int, vector<int>>` 或者 `map<int, unordered_map<int, int>>`。必须额外小心索引运算符 `operation[]` 默认建立的问题。
6. 除了常見的 compression (壓縮技術)，還有另一種實作方案 compact (緊壓技術) 經常被忽略。這類技術經常用在作業系統。例如，以 trie 為例，我們可以透過資料排列或者想辦法釋出多餘的空間。
   ```cpp
   struct Node {
       int next[26];
   }
    
   // optimized
   struct OptNode {
       int next*; // new int[<on-demand-size>], cut off the null values on the tailing of next;
       int size;
   }
   ```

## 习题

-   [QOJ 6669 Mapa](https://qoj.ac/problem/6669)
-   [\[SDOI/SXOI2022\] 无处存储](https://www.luogu.com.cn/problem/P8353)

## 参考资料与拓展阅读

1.  陈知轩。《浅谈信息学竞赛中的空间优化问题》。2022 国家集训队论文
2.  [Information theory - Wikipedia](https://en.wikipedia.org/wiki/Information_theory)
3.  [浅谈信息论 - 洛谷专栏](https://www.luogu.com.cn/article/i65ca8i5)
