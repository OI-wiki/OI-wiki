author: StudyingFather, Backl1ght, countercurrent-time, Ir1d, greyqz, MicDZ, ouuan

bitset 常用于常规数据结构难以维护的的判定、统计问题，而莫队可以维护常规数据结构难以维护的区间信息。把两者结合起来使用可以同时利用两者的优势。

## 例题 [「Ynoi2016」掉进兔子洞](https://www.luogu.com.cn/problem/P4688)

本题刚好符合上面提到的莫队配合 bitset 的特征。不难想到我们可以分别用 bitset 存储每一个区间内的出现过的所有权值，一组询问的答案即所有区间的长度和减去三者的并集元素个数 $\times 3$。

但是在莫队中使用 bitset 也需要针对 bitset 的特性调整算法：

1.  bitset 不能很好地处理同时出现多个权值的情况。我们可以把当前元素离散化后的权值与当前区间的的出现次数之和作为往 bitset 中插入的对象。
2.  我们平常使用莫队时，可能会不注意 4 种移动指针的方法顺序，所以指针移动的过程中可能会出现区间的左端点在右端点右边，区间长度为负值的情况，导致元素的个数为负数。这在其他情况下并没有什么影响，但是本题中在 bitset 中插入的元素与元素个数有关，所以我们需要注意 4 种移动指针的方法顺序，将左右指针分别往左边和右边移动的语句写在前面，避免往 bitset 中插入负数。
3.  虽然 bitset 用空间小，但是仍然难以承受 $10 ^ 5 \times 10 ^ 5$ 的数据规模。所以我们需要将询问划分成常数块分别处理，保证空间刚好足够的情况下时间复杂度不变。

??? 参考代码
    ```cpp
    --8<-- "docs/misc/code/mo-algo-with-bitset/mo-algo-with-bitset_1.cpp"
    ```

## 习题

-   [小清新人渣的本愿](https://www.luogu.com.cn/problem/P3674)
-   [「Ynoi2017」由乃的玉米田](https://www.luogu.com.cn/problem/P5355)
-   [「Ynoi2011」WBLT](https://www.luogu.com.cn/problem/P5313)
