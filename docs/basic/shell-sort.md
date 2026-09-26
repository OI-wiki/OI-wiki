本页面将简要介绍希尔排序．

## 定义

希尔排序（Shell sort），也称为缩小增量排序法，是 [插入排序](./insertion-sort.md) 的一种改进版本．希尔排序以它的发明者希尔（Donald Shell）命名．

## 过程

排序对不相邻的记录进行比较和移动：

1.  将待排序序列分为若干子序列（每个子序列的元素在原始数组中间距相同）；
2.  对这些子序列进行插入排序；
3.  减小每个子序列中元素之间的间距，重复上述过程直至间距减少为 $1$．

## 性质

### 稳定性

希尔排序是一种不稳定的排序算法．

### 时间复杂度

希尔排序的最好时间依赖间距序列和是否提前退出；下面给出的没有提前退出的 $3h+1$ 实现最好为 $\Theta(n\log n)$．

希尔排序的平均时间复杂度和最坏时间复杂度与间距序列的选取有关．设间距序列为 $H$，下面给出 $H$ 的两种经典选取方式，这两种选取方式均使得排序算法的复杂度降为 $o(n^2)$ 级别．

???+ note "命题 1"
    若间距序列为 $H= \{ 2^k-1\mid k=1,2,\ldots,\lfloor\log_2 n\rfloor \}$（从大到小），则希尔排序算法的时间复杂度为 $O(n^{3/2})$．

???+ note "命题 2"
    若间距序列为 $H= \{ k=2^p\cdot 3^q\mid p,q\in \mathbb N,k\le n \}$（从大到小），则希尔排序算法的时间复杂度为 $O(n\log^2 n)$．

为证明这两个命题，我们先给出一个重要的定理并证明它，这个定理反映了希尔排序的最主要特征．

???+ note "定理 1"
    只要程序执行了一次 $\text{InsertionSort}(h)$，不管之后怎样调用 $\text{InsertionSort}$ 函数，$A$ 数组怎样变换，下列每个子序列均保持有序：
    
    $$
    \begin{array}{c}
    A_1,A_{1+h},A_{1+2h},\ldots \\
    A_2,A_{2+h},A_{2+2h},\ldots \\
    \vdots \\
    A_h,A_{h+h},A_{h+2h},\ldots
    \end{array}
    $$

接下来我们证明定理 1．

我们先证明引理 1．

???+ note "引理 1"
    对于非负整数 $n,m$、正整数 $l$ 与两个数组 $X(x_1,x_2,\ldots,x_{n+l}),Y(y_1,y_2,\ldots,y_{m+l})$，满足如下要求：
    
    $$
    y_1 \le x_{n+1},y_2 \le x_{n+2},\ldots,y_l \le x_{n+l}
    $$
    
    则我们将两个数组分别升序排序后，上述要求依然成立．

??? note "引理 1 证明"
    设数组 $X$ 排序完为数组 $X'(x'_1,\ldots,x'_{n+l})$，数组 $Y$ 排序完为数组 $Y'(y'_1,\ldots,y'_{m+l})$．
    
    对任意 $1\le i\le l$，$X$ 中严格大于 $x'_{n+i}$ 的元素至多有 $l-i$ 个．所以在选定的 $l$ 个元素 $\{x_{n+1},\ldots,x_{n+l}\}$ 中，至少有 $i$ 个不大于 $x'_{n+i}$．记为 $x_{n+k_1},\ldots,x_{n+k_i}$，结合原配对不等式可得：
    
    $$
    y_{k_1}\le x_{n+k_1}\le x'_{n+i},y_{k_2}\le x_{n+k_2}\le x'_{n+i},\ldots,y_{k_i}\le x_{n+k_i}\le x'_{n+i}
    $$
    
    所以 $x'_{n+i}$ 至少大于等于 $Y$ 也即 $Y'$ 中的 $i$ 个元素，那么自然有 $y'_i\le x'_{n+i}\,(1\le i\le l)$．

再回到原命题的证明．设数组长度为 $N$，我们只需证明 $\text{InsertionSort}(k)$ 会保持已有 $h$ 的有序性，再调用次数归纳即可．这里 $h,k$ 为任意正整数．若 $h\ge N$，没有需要检查的相距 $h$ 的元素对，结论显然成立．以下设 $h<N$．

记调用前后的数组分别为 $A$ 与 $A'$．调用前有 $A_i\le A_{i+h}$，其中 $1\le i\le N-h$．对每个 $1\le w\le\min(k,N-h)$，按带余除法写成

$$
w+h=v+tk,\qquad 1\le v\le k,\quad t\ge0．
$$

考虑从下标 $w$ 和 $v$ 开始、间距为 $k$ 的两个完整子序列：

$$
Y=(A_w,A_{w+k},A_{w+2k},\ldots),\qquad
X=(A_v,A_{v+k},A_{v+2k},\ldots)．
$$

设满足 $w+h+jk\le N$ 的非负整数 $j$ 共有 $l$ 个．于是 $X$ 的长度为 $t+l$，$Y$ 的长度至少为 $l$；由原来的 $h$ 有序性，$Y$ 的前 $l$ 项与 $X$ 的后 $l$ 项满足

$$
y_{j+1}=A_{w+jk}\le A_{w+h+jk}=x_{t+j+1},\qquad 0\le j<l．
$$

$\text{InsertionSort}(k)$ 恰好对每个这样的完整子序列进行升序排序．由引理 1，排序后的对应关系仍成立，即

$$
A'_{w+jk}\le A'_{w+h+jk},\qquad 0\le j<l．
$$

即使 $v=w$、两个子序列实际上相同，上述引理也仍然适用．任意下标 $1\le i\le N-h$ 都能唯一写为 $i=w+jk$，其中 $1\le w\le k$、$j\ge0$，且必有 $w\le N-h$．因此上面的讨论覆盖全部 $i$，得到 $A'_i\le A'_{i+h}$，所以 $h$ 有序性保持不变，定理 1 得证．

这个定理揭示了希尔排序在特定集合 $H$ 下可以优化复杂度的关键，因为在整个过程中，它可以一直保持此前各子序列有序的性质，从而使后面的调用中，指针 $i$ 的移动次数大大减少．

接下来我们单拎出来一个数论引理进行证明．这个定理在 OI 界因 [小凯的疑惑](https://www.luogu.com.cn/problem/P3951) 一题而大为出名．而在希尔排序复杂度的证明中，它也使得定理 $1$ 得到了很大的扩展．

???+ note "引理 2"
    若 $a,b\ge2$ 均为整数且互素，则不在集合 $\{ax+by\mid x,y\in \mathbb N \}$ 中的最大正整数为 $ab-a-b$．

??? note "引理 2 证明"
    分两步证明：
    
    -   先证明方程 $ax+by=ab-a-b$ 没有 $x,y$ 均为非负整数的解：
    
        若无非负整数的限制，容易得到两组解 $(b-1,-1),(-1,a-1)$．
    
        通过其通解形式 $x=x_0+tb,y=y_0-ta$，容易得到上面两组解是「相邻」的（因为 $b-1-b=-1$）．
    
        当 $t$ 递增时，$x$ 递增，$y$ 递减，所以如果方程有非负整数解，必然会夹在这两组解中间，但这两组解「相邻」，中间没有别的解．
    
        故不可能有非负整数解．
    -   再证明对任意整数 $c > ab-a-b$，方程 $ax+by=c$ 有非负整数解：
    
        我们找一组解 $(x_0,y_0)$ 满足 $0\le x_0 < b$（由通解的表达式，这可以做到）．
    
        则有：
    
        $$
        by_0=c-ax_0\ge c-a(b-1)>ab-a-b-ab+a=-b
        $$
    
        所以 $b(y_0+1) > 0$，又因为 $b>0$，所以 $y_0+1>0$，所以 $y_0\ge 0$．
    
        所以 $(x_0,y_0)$ 为一组非负整数解．
    
    综上得证．

而下面这个定理则揭示了引理 $2$ 是如何扩展定理 $1$ 的．

???+ note "定理 2"
    如果 $\gcd(h_{t+1},h_t)=1$，则程序先执行完 $\text{InsertionSort}(h_{t+1})$ 与 $\text{InsertionSort}(h_t)$ 后，执行 $\text{InsertionSort}(h_{t-1})$ 的时间复杂度为 $O\left(\dfrac{nh_{t+1}h_t}{h_{t-1}} \right)$，且对于每个 $j$，其 $i$ 的移动次数是 $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}} \right)$ 级别的．

??? note "定理 2 证明"
    对于 $j\le h_{t+1}h_t$ 的部分，$i$ 的移动次数显然是 $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}} \right)$ 级别的．
    
    故以下假设 $j>h_{t+1}h_t$．
    
    对于任意的正整数 $k$ 满足 $1\le k\le j-h_{t+1}h_t$，注意到：$h_{t+1}h_t-h_{t+1}-h_t<h_{t+1}h_t\le j-k\le j-1$．
    
    又因为 $\gcd(h_{t+1},h_t)=1$，故由引理 $2$，得存在非负整数 $a,b$，使得：$ah_{t+1}+bh_t=j-k$．
    
    即得：
    
    $$
    k=j-ah_{t+1}-bh_t
    $$
    
    由定理 $1$，得：
    
    $$
    A_{j-bh_t}\le A_{j-(b-1)h_t}\le \ldots\le A_{j-h_t}\le A_j
    $$
    
    与
    
    $$
    A_{j-bh_t-ah_{t+1}}\le A_{j-bh_t-(a-1)h_{t+1}}\le \ldots\le A_{j-bh_t-h_{t+1}}\le A_{j-bh_t}
    $$
    
    综合以上即有：$A_k=A_{j-ah_{t+1}-bh_t}\le A_j$．
    
    所以对于任何 $1\le k\le j-h_{t+1}h_t$，有 $A_k\le A_j$．
    
    在 Shell-Sort 伪代码中 $i$ 指针每次减 $h_{t-1}$，减 $O\left(\dfrac{h_{t+1}h_t}{h_{t-1}} \right)$ 次，即可使得 $i\le j-h_{t+1}h_t$，进而有 $A_i\le A_j$，不满足 while 循环的条件退出．
    
    证明完对于每个 $j$ 的移动复杂度后，即可得到总的时间复杂度：
    
    $$
    \sum_{j=h_{t-1}+1}^n{O\left(\frac{h_{t+1}h_t}{h_{t-1}} \right)}=O\left(\frac{nh_{t+1}h_t}{h_{t-1}}\right)
    $$
    
    得证．

认真观察定理 $2$ 的证明过程，可以发现：定理 1 可以进行「线性组合」，即 $A$ 以 $h$ 为间隔有序，以 $k$ 为间隔亦有序，则以 $h$ 和 $k$ 的非负系数线性组合仍是有序的．而这种「线性性」即是由引理 $2$ 保证的．

有了这两个定理，我们可以证明命题 $1$ 与 $2$．

??? note "命题 1 证明"
    将 $H$ 写为序列的形式：
    
    $$
    H(h_1=1,h_2=3,h_3=7,\ldots,h_{\lfloor \log_2 n\rfloor}=2^{\lfloor \log_2 n\rfloor}-1)
    $$
    
    Shell-Sort 执行顺序为：$\text{InsertionSort}(h_{\lfloor \log_2 n\rfloor}),\text{InsertionSort}(h_{\lfloor \log_2 n\rfloor-1}),\ldots,\text{InsertionSort}(h_2),\text{InsertionSort}(h_1)$．
    
    分两部分去分析复杂度：
    
    -   对于前面的若干个满足 $h_t\ge \sqrt{n}$ 的 $h_t$，显然有 $\text{InsertionSort}(h_t)$ 的时间复杂度为 $O\left(\dfrac{n^2}{h_t} \right)$．
    
        考虑对最接近 $\sqrt{n}$ 的项 $h_k$，有：
    
        $$
        O\left(\frac{n^2}{h_t} \right)=O(n^{3/2})
        $$
    
        而对于 $i> k$ 的 $h_i$，因为有 $2h_i< h_{i+1}$，所以可得：
    
        $$
        O\left(\frac{n^2}{h_i} \right)=O(n^{3/2}/2^{i-k})\,(i>k)
        $$
    
        所以大于等于 $\sqrt n$ 部分的总时间复杂度为：
    
        $$
        \sum_{i=k}^{\lfloor \log_2 n\rfloor}{O(n^{3/2}/2^{i-k})}=O(n^{3/2})
        $$
    -   对于后面剩下的满足 $h_t< \sqrt{n}$ 的项，前两项的复杂度还是 $O(n^{3/2})$，而对于后面的项 $h_t$，由定理 $2$ 可得时间复杂度为：
    
        $$
        O\left(\frac{nh_{t+2}h_{t+1}}{h_t} \right)=O\left(\frac{nh_{t+2}\cdot h_{t+2}/2}{h_{t+2}/4} \right)=O(nh_{t+2})
        $$
    
        再次利用 $2h_i < h_{i+1}$ 性质可得此部分总时间复杂度为（下式中 $k$ 沿用了上一种情况中的含义）：
    
        $$
        2O(n^{3/2})+\sum_{i=1}^{k-3}{O(nh_{i+1})}=O(n^{3/2})+\sum_{i=1}^{k-3}{O(nh_{k-1}/2^{k-i-3})}=O(n^{3/2})+O(nh_{k-1})=O(n^{3/2})
        $$
    
    综上可得总时间复杂度即为 $O(n^{3/2})$．

??? note "命题 2 证明"
    注意到一个事实：如果已经执行过了 $\text{InsertionSort}(2)$ 与 $\text{InsertionSort}(3)$，那么因为 $2\cdot 3-2-3=1$，所以由定理 $2$，每个元素只有与它相邻的前一个元素可能大于它，之前的元素全部都小于它．于是 $i$ 指针只需要最多两次就可以退出 while 循环．也就是说，此时再执行 $\text{InsertionSort}(1)$，复杂度降为 $O(n)$．
    
    更进一步：如果已经执行过了 $\text{InsertionSort}(4)$ 与 $\text{InsertionSort}(6)$，我们考虑所有的下标为奇数的元素组成的子列与下标为偶数的元素组成的子列．则这相当于把这两个子列分别执行 $\text{InsertionSort}(2)$ 与 $\text{InsertionSort}(3)$．那么也是一样，这时候再执行 $\text{InsertionSort}(2)$，相当于对两个子列分别执行 $\text{InsertionSort}(1)$，也只需要两个序列和的级别，即 $O(n)$ 的复杂度就可以将数组变为 $2$ 间隔有序．
    
    不断归纳，就可以得到：如果已经执行过了 $\text{InsertionSort}(2h)$ 与 $\text{InsertionSort}(3h)$，则执行 $\text{InsertionSort}(h)$ 的复杂度也只有 $O(n)$．
    
    接下来分为两部分分析复杂度：
    
    -   对于 $h_t>n/3$ 的部分，则执行每个 $\text{InsertionSort}(h_t)$ 的复杂度为 $O(n^2/h_t)$．
    
        而 $n^2/h_t<3n$，所以单次插入排序复杂度为 $O(n)$．
    
        而这一部分元素个数是 $O(\log^2 n)$ 级别的，所以这一部分时间复杂度为 $O(n\log^2 n)$．
    -   对于 $h_t\le n/3$ 的部分，因为 $3h_t\le n$，所以这之前已经执行了 $\text{InsertionSort}(2h_t)$ 与 $\text{InsertionSort}(3h_t)$，于是执行 $\text{InsertionSort}(h_t)$ 的时间复杂度是 $O(n)$．
    
        还是一样的，这一部分元素个数也是 $O(\log^2 n)$ 级别的，所以这一部分时间复杂度为 $O(n\log^2 n)$．
    
    综上可得总时间复杂度即为 $O(n\log^2 n)$．

### 空间复杂度

希尔排序的空间复杂度为 $O(1)$．

## 实现

=== "C++[^ref1]"
    ```cpp
    template <typename T>
    void shell_sort(T array[], int length) {
      int h = 1;
      while (h < length / 3) {
        h = 3 * h + 1;
      }
      while (h >= 1) {
        for (int i = h; i < length; i++) {
          for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
            std::swap(array[j], array[j - h]);
          }
        }
        h = h / 3;
      }
    }
    ```

=== "Python"
    ```python
    def shell_sort(array, length):
        h = 1
        while h < length / 3:
            h = int(3 * h + 1)
        while h >= 1:
            for i in range(h, length):
                j = i
                while j >= h and array[j] < array[j - h]:
                    array[j], array[j - h] = array[j - h], array[j]
                    j -= h
            h = int(h / 3)
    ```

## 参考资料与注释

[^ref1]: [希尔排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%B8%8C%E5%B0%94%E6%8E%92%E5%BA%8F)
