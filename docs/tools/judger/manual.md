在赛场上，面对可能较多的大样例，除了一个一个地手动测试以外，手写一个简易的评测程序是明智的选择。

以下假设我们的题目名字是 `tree`，当前文件夹下有待测代码 `tree.cpp` 和 $100$ 个大样例，文件名为 `tree1.in``tree1.ans`\~`tree100.in``tree100.ans`。

假设 `tree.cpp` 使用文件输入输出，即从 `tree.in` 读入，输出到 `tree.out`。否则，参考 [这个](/tools/cmd/#重定向机制) 进行输入输出重定向。

先展示测试一组数据的评测机写法。

```cpp
#include <stdio.h>
#include<stdlib.h>
main() {
  system("g++ tree.cpp -o tree -O2 -lm");  // 编译
  system("echo tree1.in > tree.in");  // 把 tree1.in 中的内容复制到 tree.in 中
  if (system("./tree"))               // 运行
  {
    printf("RE");  // 返回值不为 0，出现运行时错误
    return 0;
  }
  if(system("diff -sb tree.out tree1.ans"))//比较输出与答案，其中 -b 选项意为忽略空白字符
    printf("WA");//返回值不为 0，两个文件不同
  else printf("AC");
}
```
