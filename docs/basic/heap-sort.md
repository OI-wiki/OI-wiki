本页面将简要介绍堆排序。

## 简介

堆排序（英语：Heapsort）是指利用 [二叉堆](../ds/binary-heap.md) 这种数据结构所设计的一种排序算法。堆排序的适用数据结构为数组。

## 工作原理

本质是建立在堆上的选择排序。

### 排序过程

首先建立大顶堆，然后将堆顶的元素取出，作为最大值，与数组尾部的元素交换，并维持残余堆的性质；

之后将堆顶的元素取出，作为次大值，与数组倒数第二位元素交换，并维持残余堆的性质；

以此类推，在第 $n-1$ 次操作后，整个数组就完成了排序。

### 在数组上建立二叉堆

从根节点开始，依次将每一层的节点排列在数组里。

于是有数组中下标为 `i` 的节点，对应的父结点、左子结点和右子结点如下：

```cpp
iParent(i) = (i - 1) / 2;
iLeftChild(i) = 2 * i + 1;
iRightChild(i) = 2 * i + 2;
```

## 性质

### 稳定性

同选择排序一样，由于其中交换位置的操作，所以是不稳定的排序算法。

### 时间复杂度

堆排序的最优时间复杂度、平均时间复杂度、最坏时间复杂度均为 $O(n\log n)$。

### 空间复杂度

而由于可以在输入数组上建立堆，所以这又是一个原地算法。

## 代码实现

### C++

```cpp
// C++ Version
void sift_down(int arr[], int start, int end) {
  // 建立父结点指标和子结点指标
  int dad = start;
  int son = dad * 2 + 1;
  while (son <= end) {  // 子结点指标在范围内才做比较
    if (son + 1 <= end &&
        arr[son] < arr[son + 1])  // 先比较两个子结点大小，选择最大的
      son++;
    if (arr[dad] >=
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
  // 从最后一个节点的父节点开始sift down以完成堆化(heapify)
  for (int i = (len - 1 - 1) / 2; i >= 0; i--) sift_down(arr, i, len - 1);
  // 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    sift_down(arr, 0, i - 1);
  }
}
```

### Python

```python
# Python Version
def sift_down(arr, start, end):
    # 建立父结点指标和子结点指标
    dad = int(start)
    son = int(dad * 2 + 1)
    while son <= end: # 子结点指标在范围内才做比较
        if son + 1 <= end and arr[son] < arr[son + 1]:
            son += 1 # 先比较两个子结点大小，选择最大的
        if arr[dad] >= arr[son]:
            return # 如果父结点比子结点大，代表调整完毕，直接跳出函数
        else: # 否则交换父子内容，子结点再和孙结点比较
            arr[dad], arr[son] = arr[son], arr[dad]
            dad = son
            son = int(dad * 2 + 1)

def heap_sort(arr, len):
  # 从最后一个节点的父节点开始sift down以完成堆化(heapify)
    i = (len - 1 - 1) / 2
    while(i >= 0):
        sift_down(arr, i, len - 1)
        i -= 1
  # 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
    i = len - 1
    while(i > 0):
        arr[0], arr[i] = arr[i], arr[0]
        sift_down(arr, 0, i - 1)
        i -= 1
```

## 外部链接

- [堆排序 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%A0%86%E6%8E%92%E5%BA%8F)
