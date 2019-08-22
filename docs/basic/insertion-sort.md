插入排序依次处理待排序的记录，每个记录和之前处理过的序列中的记录进行比较，然后插入到其中适当的位置。

时间复杂度是 $O(n^2)$ 。

```cpp
void insertion_sort() {
  for (int i = 1; i <= n; i++) {
    for (int j = n - 1; j > 0; j--) {
      if (a[j] > a[j + 1]) {
        int t = a[j];
        a[j] = a[j + 1];
        a[j + 1] = t;
      } else
        break;  //如果没有进行交换，则说明已经插入到正确位置
    }
  }
}
```
