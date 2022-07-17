author: frank-xjh

本页面将简要介绍枚举算法。

## 简介

枚举（英语：Enumerate）是基于已有知识来猜测答案的一种问题求解策略。

枚举的思想是不断地猜测，从可能的集合中一一尝试，然后再判断题目的条件是否成立。

## 要点

### 给出解空间

建立简洁的数学模型。

枚举的时候要想清楚：可能的情况是什么？要枚举哪些要素？

### 减少枚举的空间

枚举的范围是什么？是所有的内容都需要枚举吗？

在用枚举法解决问题的时候，一定要想清楚这两件事，否则会带来不必要的时间开销。

### 选择合适的枚举顺序

根据题目判断。比如例题中要求的是最大的符合条件的素数，那自然是从大到小枚举比较合适。

## 例题

以下是一个使用枚举解题与优化枚举范围的例子。

!!! 例题
    一个数组中的数互不相同，求其中和为 $0$ 的数对的个数。

??? note "解题思路"
    枚举两个数的代码很容易就可以写出来。
    
    ```cpp
    // C++ Version
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        if (a[i] + a[j] == 0) ++ans;
    ```
    
    ```python
    # Python Version
    for i in range(0, n):
      for j in range(0, n):
          if(a[i] + a[j] == 0):
              ans = ans + 1
    ```
    
    来看看枚举的范围如何优化。由于题中没要求数对是有序的，答案就是有序的情况的两倍（考虑如果 `(a, b)` 是答案，那么 `(b, a)` 也是答案）。对于这种情况，只需统计人为要求有顺序之后的答案，最后再乘上 $2$ 就好了。
    
    不妨要求第一个数要出现在靠前的位置。代码如下：
    
    ```cpp
    // C++ Version
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < i; ++j)
        if (a[i] + a[j] == 0) ++ans;
    ```
    
    ```python
    # Python Version
    for i in range(0, n):
      for j in range(0, i):
          if(a[i] + a[j] == 0):
              ans = ans + 1
    ```
    
    不难发现这里已经减少了 $j$ 的枚举范围，减少了这段代码的时间开销。
    
    我们可以在此之上进一步优化。
    
    两个数是否都一定要枚举出来呢？枚举其中一个数之后，题目的条件已经确定了其他的要素（另一个数）的条件，如果能找到一种方法直接判断题目要求的那个数是否存在，就可以省掉枚举后一个数的时间了。较为进阶地，在数据范围允许的情况下，我们可以使用桶[^1]记录遍历过的数。
    
    ```cpp
    // C++ Version
    bool met[MAXN * 2];
    memset(met, 0, sizeof(met));
    for (int i = 0; i < n; ++i) {
      if (met[MAXN - a[i]]) ans += 1;
      met[MAXN + a[i]] = true;
    }
    ```
    
    ```python
    # Python Version
    met = [False] * MAXN * 2
    for i in range(0, n):
        if met[MAXN - a[i]]:
            ans = ans + 1
        met[a[i] + MAXN] = True
    ```

## 习题

- [2811: 熄灯问题 - OpenJudge](http://bailian.openjudge.cn/practice/2811/)

## 脚注

[^1]: [桶排序](../basic/bucket-sort.md) 以及 [主元素问题](../misc/main-element.md#_3) 以及 [Stack Overflow 上对桶数据结构的讲解](https://stackoverflow.com/questions/42399355/what-is-a-bucket-or-double-bucket-data-structure)（英文）
