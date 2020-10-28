本页面将简要介绍堆排序。

## 简介

堆排序（英语：Heapsort）是指利用 [堆](../ds/heap.md) 这种数据结构所设计的一种排序算法。堆排序的适用数据结构为数组。

## 工作原理

它的工作原理为对所有待排序元素建堆，然后依次取出堆顶元素，就可以得到排好序的序列。

当当前的结点下标为 `i` 时，父结点、左子结点和右子结点的选择方式如下：

```cpp
//这里 floor 函数将实数映射到最小的前导整数。
iParent(i) = floor((i - 1) / 2);
iLeftChild(i) = 2 * i + 1;
iRightChild(i) = 2 * i + 2;
```

## 性质

### 稳定性

堆排序是一种不稳定的排序算法。

### 时间复杂度

堆排序的最优时间复杂度、平均时间复杂度、最坏时间复杂度均为 $O(n\log n)$ 。

## 代码实现

### C++

```cpp
void max_heapify(int arr[], int start, int end) {
  // 建立父结点指标和子结点指标
  int dad = start;
  int son = dad * 2 + 1;
  while (son <= end) {  // 子结点指标在范围内才做比较
    if (son + 1 <= end &&
        arr[son] < arr[son + 1])  // 先比较两个子结点大小，选择最大的
      son++;
    if (arr[dad] >
        arr[son])  // 如果父结点比子结点大，代表调整完毕，直接跳出函数
      return;
    else {  // 否则交换父子内容，子结点再和孙结点比较
      swap(arr[dad], arr[son]);
      dad = son;
      son = dad * 2 + 1;
    }
  }
}

void heap_sort(int arr[], int len) {
  // 初始化，i 从最后一个父结点开始调整
  for (int i = len / 2 - 1; i >= 0; i--) max_heapify(arr, i, len - 1);
  // 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    max_heapify(arr, 0, i - 1);
  }
}
```

## 外部链接

-  [堆排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%A0%86%E6%8E%92%E5%BA%8F) 
