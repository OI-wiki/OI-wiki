本页面将简要介绍锦标赛排序。

## 简介

锦标赛排序（英文：Tournament sort），又被称为树形选择排序，是 [选择排序](/selection-sort.md) 的优化版本，[堆排序](heap-sort.md) 的一种变体（均采用完全二叉树）。它在选择排序的基础上使用优先队列查找下一个该选择的元素。

该算法的名字来源于单败淘汰制的竞赛形式。在这种赛制中有许多选手参与比赛，他们两两比较，胜者进入下一轮比赛。这种淘汰方式能够决定最好的选手，但是在最后一轮比赛中被淘汰的选手不一定是第二好的——他可能不如先前被淘汰的选手。

## 工作原理

以 **最小锦标赛排序树** 为例：

![tournament-sort1](./images/tournament-sort1.png)

待排序元素是叶子节点显示的元素。红色边显示的是每一轮比较中较小的元素的胜出路径。显然，完成一次＂锦标赛＂可以选出一组元素中最小的那一个。

每一轮对 $n$ 个元素进行比较后可以得到 $\frac{n}{2}$ 个“优胜者”，每一对中较小的元素进入下一轮比较。如果无法凑齐一对元素，那么这个元素直接进入下一轮的比较。

![tournament-sort2](./images/tournament-sort2.png)

完成一次“锦标赛”后需要将被选出的元素去除。直接将其设置为 $\infty$（这个操作类似 [堆排序](/heap-sort.md)），然后再次举行“锦标赛”选出次小的元素。

之后一直重复这个操作，直至所有元素有序。

## 性质

### 稳定性

锦标赛排序是一种不稳定的排序算法。

### 时间复杂度

锦标赛排序的最优时间复杂度、平均时间复杂度和最坏时间复杂度均为 $O(n\log n)$。它用 $O(n)$ 的时间初始化“锦标赛”，然后用 $O(\log n)$ 的时间从 $n$ 个元素中选取一个元素。

### 空间复杂度

锦标赛排序的空间复杂度为 $O(n)$。

## 代码实现

### C++

```cpp
// C++ Version
int n, a[maxn], tmp[maxn << 1];

int winner(int pos1, int pos2) {
  int u = pos1 >= n ? pos1 : tmp[pos1];
  int v = pos2 >= n ? pos2 : tmp[pos2];
  if (tmp[u] <= tmp[v]) return u;
  return v;
}

void creat_tree(int &value) {
  for (int i = 0; i < n; i++) tmp[n + i] = a[i];
  for (int i = 2 * n - 1; i > 1; i -= 2) {
    int k = i / 2;
    int j = i - 1;
    tmp[k] = winner(i, j);
  }
  value = tmp[tmp[1]];
  tmp[tmp[1]] = INF;
}

void recreat(int &value) {
  int i = tmp[1];
  while (i > 1) {
    int j, k = i / 2;
    if (i % 2 == 0 && i < 2 * n - 1)
      j = i + 1;
    else
      j = i - 1;
    tmp[k] = winner(i, j);
    i = k;
  }
  value = tmp[tmp[1]];
  tmp[tmp[1]] = INF;
}

void tournament_sort() {
  int value;
  creat_tree(value);
  for (int i = 0; i < n; i++) {
    a[i] = value;
    recreat(value);
  }
}
```

### Python

```python
# Python Version
n = 0
a = [0] * maxn
tmp = [0] * maxn * 2

def winner(pos1, pos2):
    u = pos1 if pos1 >= n else tmp[pos1]
    v = pos2 if pos2 >= n else tmp[pos2]
    if tmp[u] <= tmp[v]:
        return u
    return v

def creat_tree(value):
    for i in range(0, n):
        tmp[n + 1] = a[i]
    for i in range(2 * n -1, 1, -2):
        k = int(i / 2)
        j = i - 1
        tmp[k] = winner(i, j)
    value = tmp[tmp[i]]
    tmp[tmp[i]] = INF

def recreat(value):
    i = tmp[1]
    while i > 1:
        j = k = int(i / 2)
        if i % 2 == 0 and i < 2 * n - 1:
            j = i + 1
        else:
            j = i - 1
        tmp[k] = winner(i, j)
        i = k
    value = tmp[tmp[1]]
    tmp[tmp[1]] = INF

def tournament_sort():
    value = 0
    creat_tree(value)
    for i in range(0, n):
        a[i] = value
        recreat(value)
```

## 外部链接

- [Tournament sort - Wikipedia](https://en.wikipedia.org/wiki/Tournament_sort)
