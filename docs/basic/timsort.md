timsort是归并排序和插入排序的结合，是一个稳定的排序算法，由Tim Peters于2002年用Python实现。现在，timsort是Python的标准排序算法，且被Java SE7用于对非原始类型的数组排序。

timsort在最好情况下的时间复杂度为$O(n)$，最差情况下的时间复杂度为$O(n \log n)$，期望时间复杂度为$O(n \log n)$。timsort在最坏情况下的空间复杂度为$O(n)$。

## 算法过程

## 复杂度证明

## 参考资料

1.  [Timsort](https://en.wikipedia.org/wiki/Timsort)
2.  [On the Worst-Case Complexity of TimSort](https://drops.dagstuhl.de/opus/volltexte/2018/9467/pdf/LIPIcs-ESA-2018-4.pdf)
3.  [original explanation by Tim Peters](https://bugs.python.org/file4451/timsort.txt)