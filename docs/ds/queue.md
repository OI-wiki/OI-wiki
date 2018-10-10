队列，英文名是 queue，在 C++ STL 中有 [std::queue](https://en.cppreference.com/w/cpp/container/queue) 和 [std::priority_queue](https://en.cppreference.com/w/cpp/container/priority_queue)。

先进入队列的元素一定先出队列，因此队列通常也被称为先进先出（first in first out）表，简称 FIFO 表。

注：`std::stack` 和 `std::queue` 都是容器适配器，默认底层容器为 `std::deque`（双端队列）。

通常用一个数组模拟一个队列，用两个指针：front 和 rear 分别表示队列头部和尾部。

在入队的时候将 rear 后移，在出队的时候将 front 后移。

这样会导致一个问题：随着时间的推移，整个队列会向数组的尾部移动，一旦到达数组的最末端，即使数组的前端还有空闲位置，再进行入队操作也会导致溢出。（这种数组上实际有空闲位置而发生了上溢的现象称为是 “假溢出”。

解决假溢出的办法是采用循环的方式来组织存放队列元素的数组，即将数组下标为 0 的位置看做是最后一个位置的后继。（`x` 的后继为 `(x + 1) % Size`）。这样就形成了循环队列。
