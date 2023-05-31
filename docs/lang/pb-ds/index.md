author: HeRaNO, Xeonacid, saffahyjp

pb\_ds 库全称 Policy-Based Data Structures。

pb\_ds 库封装了很多数据结构，比如哈希（Hash）表，平衡二叉树，字典树（Trie 树），堆（优先队列）等。

就像 `vector`、`set`、`map` 一样，其组件均符合 STL 的相关接口规范。部分（如优先队列）包含 STL 内对应组件的所有功能，但比 STL 功能更多。

pb\_ds 只在使用 libstdc++ 为标准库的编译器下可以用。

可以使用 `begin()` 和 `end()` 来获取 `iterator` 从而遍历

可以 `increase_key`,`decrease_key` 以及删除单个元素

由于 pb\_ds 库的主要内容在以下划线开头的 `__gnu_pbds` 命名空间中，在 NOI 系列活动中的合规性一直没有确定。2021 年 9 月 1 日，根据 [《关于 NOI 系列活动中编程语言使用限制的补充说明》](https://www.noi.cn/xw/2021-09-01/735729.shtml)，允许使用以下划线开头的库函数或宏（但具有明确禁止操作的库函数和宏除外），在 NOI 系列活动中使用 pb\_ds 库的合规性有了文件上的依据。

**参考资料：[《C++ 的 pb\_ds 库在 OI 中的应用》](https://github.com/OI-Wiki/libs/blob/master/lang/pb-ds/C%2B%2B的pb_ds库在OI中的应用.pdf)**
