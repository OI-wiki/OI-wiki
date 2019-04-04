## 算法

归并排序是一种采用了[分治](/basic/divide-and-conquer)思想的排序算法，其本质是一种 [CDQ 分治](/misc/cdq-divide)。

归并排序分为三个过程：

1. 将数列随意划分为两部分（在均匀划分时时间复杂度为 $O\left(n\log{n}\right)$ ）
2. 递归地分别对两个子序列进行归并排序
3. 合并两个子序列

不难发现，归并排序的核心是如何合并两个子序列，前两步都很好实现。

其实合并的时候也不难操作。注意到两个子序列在第二步中已经保证了都是有序的了，第三步中实际上是想要把两个 **有序** 的序列合并起来。

```cpp
void merge(int ll, int rr) {
  // 用来把 a[ll.. rr - 1] 这一区间的数排序。 t 数组是临时存放有序的版本用的。
  if (rr - ll <= 1) return;
  int mid = ll + (rr - ll >> 1);
  merge(ll, mid);
  merge(mid, rr);
  int p = ll, q = mid, s = ll;
  while (s < rr) {
    if (p >= mid || (q < rr && a[p] > a[q])) {
      t[s++] = a[q++];
      // ans += mid - p;
    } else
      t[s++] = a[p++];
  }
  for (int i = ll; i < rr; ++i) a[i] = t[i];
}
```

下面参考《算法4》的 Java 完整代码，很漂亮，建议背住，学习一下代码风格。

```java
public class Merge {
    private static Comparable[] aux;

     public static void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        sort(a, 0, a.length - 1);
    }

    private static void sort(Comparable[] a, int lo, int hi) {
        if (lo >= hi) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, lo, mid);
        sort(a, mid + 1, hi);
        merge(a, lo, mid, hi);
    }

    private static void merge(Comparable[] a, int lo, int mid, int hi) {
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k];
        }
        for (int k = lo; k <= hi; k++) {
            if      (i > mid)               { a[k] = aux[j++]; }
            else if (j > hi)                { a[k] = aux[i++]; }
            else if (less(aux[j], aux[i]))  { a[k] = aux[j++]; }
            else                            { a[k] = aux[i++]; }
        }
    }

    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }
}
```

关键点在于一次性创建数组，避免在每次递归调用时创建，避免了对象的无谓构造和析构。



## 逆序对

归并排序还可以用来求逆序对的个数。

所谓逆序对，就是满足 $a_{i} > a_{j}$ 且 $i < j$ 的数对 $(i, j)$ 。

可以用[树状数组](/ds/bit)、[线段树](/ds/segment/)等数据结构来求，也可以用归并排序来求。

具体来说，上面归并排序中间注释掉的 `ans += mid - p` 就是在统计逆序对个数。

是因为，那里把靠后的数放到前面了（较小的数放在前面），所以在这个数的原来位置之前的、比它大的数都会和它形成逆序对，而这个个数就是还没有合并进去的数的个数，即为 `mid - p` 。

使用归并排序求逆序对的时间复杂度也是 $O(n \log n)​$ 。

## 参考

<https://www.geeksforgeeks.org/merge-sort/>
