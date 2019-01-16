本页面主要分享一下在竞赛中的小技巧。

1. 利用局部性
    局部性是指程序倾向于引用邻近于其他最近引用过的数据项的数据项，或者最近引用过的数据项本身。局部性分为时间局部性和空间局部性。
    - 消除循环中的低效率，比如遍历字符串的时候：
        ```c++
        for (int i = 0; i < strlen(s); ++i);
        // 不如
        int len = strlen(s);
        for (int i = 0; i < len; ++i);
        ```
    - 循环展开。通过适当的循环展开可以减少整个计算中关键路径上的操作数量
        ```c++
        for (int i = 0; i < n; ++i) {
            res = res OP a[i];
        }
        // 不如
        int i;
        for (i = 0; i < n; i += 2) {
            res = res OP a[i];
            res = res OP a[i + 1];
        }
        for (; i < n; ++i) {
            res = res OP a[i];
        }
        ```
    - 重新结合变换
        增加了可以并行执行的运算数量
        ```c++
        for (int i = 0; i < n; ++i) res = (res OP a[i]) OP a[i + 1];
        // 不如
        for (int i = 0; i < n; ++i) res = res OP (a[i] OP a[i + 1]);
        ```
    

