本页面将简要介绍希尔排序。

## 简介

希尔排序（英语：Shell sort），也称为缩小增量排序法，是 [插入排序](insertion-sort.md) 的一种改进版本。希尔排序以它的发明者希尔（英语：Donald Shell）命名。

## 工作原理

排序对不相邻的记录进行比较和移动：

1. 将待排序序列分为若干子序列（每个子序列的元素在原始数组中间距相同）；
2. 对这些子序列进行插入排序；
3. 减小每个子序列中元素之间的间距，重复上述过程直至间距减少为 1。

## 性质

### 稳定性

希尔排序是一种不稳定的排序算法。

### 时间复杂度

希尔排序的最优时间复杂度为 $O(n)$。

希尔排序的平均时间复杂度和最坏时间复杂度与间距序列的选取（就是间距如何减小到 1）有关，比如「间距每次除以 3」的希尔排序的时间复杂度是 $O(n^{3/2})$。已知最好的最坏时间复杂度为 $O(n \log^2n)$。

### 空间复杂度

希尔排序的空间复杂度为 $O(n)$。

## 实现

### C++[^ref1]

```cpp
// C++ Version
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

### Python

```python
# Python Version
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
