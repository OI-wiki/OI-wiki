author: SDLTF, Ethkuil

## 问题介绍

给一个有 $n$ 个元素的序列，保证有一个元素 $a$ 出现的次数 **严格大于**  $n/2$，求这个元素。

## 做法

### 离线算法

若一开始就可以知道整个序列，一个自然的思路是统计序列中各元素的出现次数，出现次数大于 $n/2$ 的就是主元素。可以创建一个桶来统计每种元素的出现次数，输出出现次数大于 $n/2$ 的元素即可。

但上述方案引入了桶进行统计，空间效率并不优。显然，若序列存在主元素，那么在排序后，序列的第 $\lfloor n/2\rfloor+1$ 个元素一定是主元素，利用 [`nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element.html) 就可以找到这个元素。这样我们就在不引入额外空间的情况下，以线性时间复杂度求得主元素了。

### 在线算法

在一些情况下，我们需要在线处理流式数据，此时我们需要一种不需要预知全体数据，而是只利用当前给出的数据逐步求得答案的算法。**多数投票算法** [^ref1]就是一种可以在线解决主元素问题的算法。

由于主元素的出现的次数超过 $n/2$，那么对于一个完整的序列，在不断消掉一个主元素和一个与主元素不同的元素之后，最后一定剩下主元素。借助这个观察，我们可以设计一个在线算法进行这样的消除操作。设 `val` 和 `cnt` 两个变量分别代表当前的主元素候选和目前如果进行了这样的消除操作后主元素候选会剩多少个。初始时 `cnt` 置为 $0$。每次从数据流中取出一个元素，如果当前 `cnt` 为 $0$，则代表主元素候选已经被消除完了，当前记录的 `val` 一定不是主元素，因此设置当前元素为主元素候补。之后检查当前元素是否是主元素候补，如果是，则 `cnt` 增加 $1$，如果不是，则该元素应与一个主元素候补一起消除，`cnt` 减少 $1$。重复上述操作直到数据流读取完成，`val` 即为主元素。

???+ warning "注意"
    当原数据中不存在主元素时，此算法给出的结果是错误的。如要判断序列中是否存在主元素，需要再次读入数据流，统计 `val` 出现次数，判断其是否超过 $n/2$。
    
    为了再次读入数据流，可以选择重置输入位置指示器，可利用 [`std::basic_istream<CharT,Traits>::seekg`](https://en.cppreference.com/w/cpp/io/basic_istream/seekg)（流式输入）或 [`rewind`](https://en.cppreference.com/w/c/io/rewind)、[`fseek`](https://en.cppreference.com/w/c/io/fseek)（C 风格输入）等库函数。

## 例题

???+ example "[洛谷 P2397 yyy loves Maths VI (mode)](https://www.luogu.com.cn/problem/P2397)"
    求给定序列的主元素。

??? note "参考代码"
    ```cpp
    --8<-- "docs/misc/code/main-element/main-element_1.cpp"
    ```

???+ example "[LeetCode 229. 多数元素 II](https://leetcode.cn/problems/majority-element-ii)"
    给定一个大小为 $n$ 的整数数组，找出其中所有出现超过 $\lfloor n/3\rfloor$ 次的元素。

??? note "参考代码"
    ```cpp
    --8<-- "docs/misc/code/main-element/main-element_2.cpp:core"
    ```

## 参考资料

[^ref1]: [多数投票算法 - 维基百科](https://zh.wikipedia.org/zh-cn/%E5%A4%9A%E6%95%B0%E6%8A%95%E7%A5%A8%E7%AE%97%E6%B3%95)
