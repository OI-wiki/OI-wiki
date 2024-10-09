当序列是一个 01 序列时，如何实现简洁数据结构的操作？

大概 2000 年左右一系列被称为 Succinct Indexable Dictionaries 的数据结构被提出，它们可以通过 $\mathcal O(n)$ 时间预处理，$\mathcal o(n)$ 的额外空间，在常数时间内静态实现 01 序列上的 $\operatorname{access},\operatorname{rank},\operatorname{select}$ 操作。对于这三种操作的定义，请参阅[简洁数据结构简介](./succinct-data-structure.md)。

由于在国内不常见，没有统一的译名。可以翻译为「简洁索引字典」或「简洁位向量」。

???+ info " 不常用的 $\operatorname{select}$ 操作 "
    $\operatorname{select}$ 操作在算法竞赛中不常见，但是实现很复杂。读者可以先阅读有关 $\operatorname{rank}$ 的内容，完全理解后再考虑 $\operatorname{select}$。

## $\operatorname{access}$

Succinct Indexable Dictionaries 直接维护 $n$ 个原始 bit。

## $\operatorname{rank}$

为了完成 $\operatorname{rank}$ 操作，Succinct Indexable Dictionaries 把 01 序列分成长为 $L$ 的块。我们可以处理出每一块内 1 的数量，得到长为 $\left\lceil \dfrac{n}{L}\right\rceil$ 的数列 $c$；再做 $c$ 的前缀和，得到一个长为 $\left\lceil \dfrac{n}{L}\right\rceil$ 的数列 $S$，$S_i$ 表示前 $i$ 块中 1 的出现次数。

对于一个长为 $L$，含有 $p_i$ 个 1 的块，本质不同的块的个数是 $\dbinom{L}{p_i}$。我们可以预处理出每一种块的前缀和，这样，块内的前缀 01 个数也可以 $\mathcal O(1)$ 查询。

但是很可惜，这样占用的总空间是 $\left\lceil \dfrac{n}{L} \right\rceil + L 2^L$ 个数。由于一个数需要 $\mathcal O(\log n)$ 个 bit, 这样还无法做到 $o(n)$ 的额外空间。

Succinct Indexable Dictionaries 的做法是首先把序列先分为长度为 $L_s$ 的超级块，再对于每个超级块进行上述分块。同样维护超级块的前缀和。查询时，先查超级块的和，再查块和，最后查表得到块内前缀和。这样有 $\left\lceil \dfrac{n}{L_s} \right\rceil$ 个 $\log n$ 位的超级块前缀和，$\left\lceil \dfrac{n}{L} \right\rceil$ 个 $\log L_s$ 位的块前缀和，$L 2^L$ 个 $\log L$ 位数字组成的表。取 $L_s = \dfrac{\log^2 n}{2}$,$L = \dfrac{\log n}{2}$，总空间占用是 $\mathcal O\left(\dfrac{n}{\log n} + \dfrac{n}{\log n}\log \log n +  \sqrt n \log n \log \log n\right) = o(n)$ 位。

## $\operatorname{select}$

一个简单的做法是在超级块和块内进行二分查找，时间复杂度为 $\mathcal O(\log n)$。下面介绍 $\mathcal O(1)$ 的做法。我们解决 $w=1$ 的询问。0 的情况是对称的。

将每 $L$ 个 1 分成一块，取 $L = \left\lfloor \log n\log\log n\right\rfloor$。

维护 $p_i$ 表示第 $iL$ 个 1 所在的位置。存储 $p_i$ 需要 $\mathcal O\left(\dfrac{n}{L} \log n\right) = \mathcal O\left(\dfrac{n}{\log \log n}\right)$ 个二进制位。

假设第 $k$ 个 1 在 $p_i$ 与 $p_{i+1}$ 之间。设 $r = p_{i+1} - p_i$，直接存储这一段内的 1 的位置需要 $L\log n$ 个位。

如果 $L \log n \le \left\lfloor\dfrac{r}{\log \log n}\right\rfloor$，也即 $r \ge L^2$，我们直接存储这些 1 的位置。因为 $\sum r = n$，这样不会使得总空间超过 $\mathcal O\left(\dfrac{n}{\log \log n}\right)$。

否则 $r < L^2$。那么我们递归存储这一结构，即将这一块每 $L'$ 个 1 分成一个小块。取 $L' = \left\lfloor\log r \log \log n\right\rfloor$。

维护 $p'_i$ 表示这一段中第 $iL'$ 个 1 的相对位置（从 $1 \sim r$），存储 $p'$ 需要 $\mathcal O\left(\dfrac{r}{L'}\log r\right) = \mathcal O\left(\dfrac{r}{\log \log n}\right)$ 个位。

同样知道 $k$ 在 $p'_i$ 与 $p'_{i+1}$ 之间。设 $r' = p'_{i+1} - p'_i$。直接存储这一段需要 $L'\log r$ 个二进制位。

如果 $L'\log r \le \left\lfloor\dfrac{r'}{\log \log n}\right\rfloor$，即 $r' \ge L'^2$，则还是直接存储 1 的位置。因为 $\sum r' \le n$，这样不会使得总空间超过 $\mathcal O\left(\dfrac{n}{\log \log n}\right)$。

最后的情况是 $r' < L'^2 < (\log r \log \log n)^2$，由于 $r < L < (\log n \log \log n)^2$，则 $\log r < 2(\log \log n + \log \log \log n) < 4 \log \log n$。那么 $r' < 16 (\log \log n)^4$。

由于 $(\log \log n)^4$ 渐进小于 $\log n$，所以 $r' = \mathcal O(\log n)$。换句话说，此时答案所在的区间长度已经是 $\log n$ 级别的。那直接对所有长为 $\dfrac{\log n}{2}$ 的区间的 $\operatorname{select}$ 结果进行预处理，所需的空间是 $\mathcal O(\sqrt n \log \log n)$。

总共的额外空间是 $\mathcal O\left(\dfrac{n}{\log \log n}+\sqrt n \log \log n\right) = o(n)$。时间复杂度 $\mathcal O(1)$。

## 实现

竞赛中实现 Succinct Indexable Dictionaries 需要更多考虑常数和代码复杂度。对于 $\operatorname{rank}$ 操作，可以设定 $L = 64$，然后简单地调用 `__builtin_popcountll` 直接计算块内的 $\operatorname{rank}$。对于 $\operatorname{access}$ 操作，复用之前的分块即可。

对于 $\operatorname{select}$ 操作，理论 $\mathcal O(1)$ 所需的常数和编码复杂度是难以接受的。可以退一步采用二分法实现。当然，如果空间允许，直接预处理答案也是完全可以接受的。不过，这就不算是什么简洁数据结构了。

??? note "Succinct Indexable Dictionaries 模板"
    ```cpp
    #ifdef _MSC_VER
    #include <intrin.h>
    #define __builtin_popcountll __popcnt64
    #endif
    
    struct Bits {
      vector<unsigned long long> b;
      vector<int> sum;
      int len;
    
      Bits(int n) {
        len = n >> 6;
        b.resize(len + 1, 0);
        sum.resize(len + 1, 0);
      }
    
      // 第 k 位（从 1 开始编号）设为 1
      void set(int k) {
        k--;  // 内部从 0 开始存储
        b[k >> 6] |= (1ull << (k & 0x3f));
      }
    
      // 设定完毕后调用
      void prepare() {
        for (int i = 0; i < b.size(); i++) {
          if (i) sum[i] = sum[i - 1];
          sum[i] += __builtin_popcountll(b[i]);
        }
      }
    
      int access(int k) {
        k--;
        return (b[k >> 6] >> (k & 0x3f)) & 1;
      }
    
      int rank1(int k) {
        int res = 0;
        int hi = (k >> 6), lo = (k & 0x3f);
        if (hi) res += sum[hi - 1];
        // (1 << lo) - 1 取了小于 lo 的位，正好符合从 0 开始存储
        res += __builtin_popcountll(b[hi] & ((1ull << lo) - 1ull));
        return res;
      }
    
      int rank0(int k) { return k - rank1(k); }
    
      int select1(int k) {
        int hi_l = 0, hi_r = len, mid;
        while (hi_l < hi_r) {
          mid = (hi_l + hi_r) >> 1;
          if (sum[mid] < k)
            hi_l = mid + 1;
          else
            hi_r = mid;
        }
        int lo_l = 1, lo_r = 64;
        while (lo_l < lo_r) {
          mid = (lo_l + lo_r) >> 1;
          int cnt = __builtin_popcountll(b[hi_l] & ((1ull << mid) - 1ull));
          if (cnt < k)
            lo_l = mid + 1;
          else
            lo_r = mid;
        }
        return 64 * hi_l + lo_l;
      }
    
      int select0(int k) {
        int hi_l = 0, hi_r = len, mid;
        while (hi_l < hi_r) {
          mid = (hi_l + hi_r) >> 1;
          if (64 * (mid + 1) - sum[mid] < k)
            hi_l = mid + 1;
          else
            hi_r = mid;
        }
        int lo_l = 1, lo_r = 64;
        while (lo_l < lo_r) {
          mid = (lo_l + lo_r) >> 1;
          int cnt = __builtin_popcountll((~b[hi_l]) & ((1ull << mid) - 1ull));
          if (cnt < k)
            lo_l = mid + 1;
          else
            lo_r = mid;
        }
        return 64 * hi_l + lo_l;
      }
    };
    ```

大部分的时候用不到 $\operatorname{select}$，编码复杂度和时空复杂度都会很优秀。

## 参考资料

-   David Richard Clark. 1998. Compact pat trees(p28-p35). Ph.D. Dissertation. University of Waterloo, CAN. Order Number: UMI Order No. GAXNQ-21335.