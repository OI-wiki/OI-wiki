author: SDLTF, Ethkuil

## 概述

给一个有 $n$ 个元素的数列，保证有一个数 $a$ 出现的次数 **超过** $\dfrac n 2$，求这个数。

## 做法

### 排序做法

显然，若一个数列存在主元素，那么这个主元素在排序后一定位于 $\dfrac{n}{2}$ 的位置。

```cpp
sort(a, a + n);
cout << a[n / 2];
```

时间复杂度是 $O(n\log n)$。

### 桶计数做法

另一个自然的思路是计数数列中各数的出现次数，出现次数大于 $\dfrac n 2$ 的就是主元素。我们创建一个桶来存储出现次数。

```cpp
constexpr int m = 30000;  // 与数的取值范围相对应
int ans[m] = {0};         // 也可选择使用 std::unordered_map<int, int>

for (int i = 0; i < n; i++) {
  cin >> t;
  ans[t]++;
  if (ans[t] > n / 2) {
    cout << t;
    break;
  }
}
```

时间复杂度 $O(n)$，这很好；但空间复杂度较大。能不能把空间复杂度降下来呢？

下面介绍本问题的 $O(n)$ 时间复杂度、$O(1)$ 空间复杂度解法。

### 摩尔投票算法

由于主元素的出现的次数超过 $\dfrac n 2$，那么在不断消掉两个不同的元素之后，最后一定剩下主元素。

由于我们只需要关心元素的值而不关心其位置，故可用 `val` 和 `cnt` 两个变量代替完整存储元素。

```cpp
int val = -1, cnt = 0;
while (n--) {
  cin >> x;
  if (!cnt) val = x;
  (val == x) ? ++cnt : --cnt;
}
cout << val;
```

???+ warning "注意"
    若原数据中并不存在主元素，则摩尔投票算法给出的结果可能是任意值。此时需要再次遍历一遍数组，统计 `val` 出现次数的最大值，判断是否超过 $\dfrac n 2$。
    
    另外，为了保证空间复杂度为 $O(1)$，再次遍历数组时可以选择重置输入位置指示器，可利用 [`std::basic_istream<CharT,Traits>::seekg`](https://en.cppreference.com/w/cpp/io/basic_istream/seekg)（流式输入）或 [`rewind`](https://en.cppreference.com/w/c/io/rewind)、[`fseek`](https://en.cppreference.com/w/c/io/fseek)（C 风格输入）等库函数。

## 习题

-   [洛谷 P2397 yyy loves Maths VI (mode)](https://www.luogu.com.cn/problem/P2397)

进阶：试着基于摩尔投票算法略做调整，找到出现次数严格大于 1/3 的元素？

???+ note "[LeetCode 229. 多数元素 II](https://leetcode.cn/problems/majority-element-ii)"
    给定一个大小为 $n$ 的整数数组，找出其中所有出现超过 $\lfloor n/3\rfloor$ 次的元素。

??? note "实现"
    ```cpp
    class Solution {
     public:
      vector<int> majorityElement(vector<int>& nums) {
        // 将摩尔投票算法的「抵消2个不同元素」变为「抵消3个两两不同的元素」
    
        constexpr int SENTINEL = 1e9 + 1;  // -1e9 <= nums[i] <= 1e9
        int n = nums.size();
    
        int maj1 = SENTINEL, maj2 = SENTINEL;
        int cnt1 = 0, cnt2 = 0;
        for (auto num : nums) {
          if (num == maj1) {
            ++cnt1;
          } else if (num == maj2) {
            ++cnt2;
          } else if (cnt1 == 0) {
            maj1 = num;
            ++cnt1;
          } else if (cnt2 == 0) {
            maj2 = num;
            ++cnt2;
          } else {
            --cnt1;
            --cnt2;
          }
        }
    
        // 由于题目没有保证存在2个超过 ⌊ n/3 ⌋ 次的元素，故需检验
        vector<int> ans;
        cnt1 = 0, cnt2 = 0;
        for (auto num : nums) {
          if (num == maj1)
            ++cnt1;
          else if (num == maj2)
            ++cnt2;
        }
        if (cnt1 > n / 3) ans.push_back(maj1);
        if (cnt2 > n / 3) ans.push_back(maj2);
    
        return ans;
      }
    };
    ```

## 参考

-   [多数投票算法 - 维基百科](https://zh.wikipedia.org/zh-cn/%E5%A4%9A%E6%95%B0%E6%8A%95%E7%A5%A8%E7%AE%97%E6%B3%95)
