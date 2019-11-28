Interactor，即交互器，用于交互题与选手程序交互。交互题的介绍见 [非传统题](../non-trad.md#_3) 。

???+note
    Testlib 仅支持 Codeforces 形式交互题，即两程序交互。不支持 NOI 形式的选手编写函数与其他函数交互。

请在阅读下文前先阅读 [通用](./general.md) 。

Testlib 为 interactor 提供了一个特殊的流 `std::fstream tout` ，它是一个 log 流，你可以在 interactor 中向它写入，并在 checker 中用 `ouf` 读取。

在 interactor 中，我们从 `inf` 读取题目测试数据，将选手程序（和标程）的标准输入写入 `stdout` （在线），从 `ouf` 读选手输出（在线），从 `ans` 读标准输出（在线）。

如果 interactor 返回了 ok 状态，checker（如果有的话）将接管工作，检查答案合法性。

## 用法

Windows:

```bat
interactor.exe <Input_File> <Output_File> [<Answer_File> [<Result_File> [-appes]]],
```

Linux:

```bash
./interactor.out <Input_File> <Output_File> [<Answer_File> [<Result_File> [-appes]]],
```

## 简单的例子

???+note 题目
    interactor 随机选择一个 $[1,10^9]$ 范围内的整数，你要写一个程序来猜它，你最多可以询问 $50$ 次一个 $[1,10^9]$ 范围内的整数。

    interactor 将返回：

     `1` ：询问与答案相同，你的程序应当停止询问。

     `0` ：询问比答案小。

     `2` ：询问比答案大。

注意在此题中我们不需要 `ans` ，因为我们不需要将标准输出与其比较；而在其他题中可能需要这么做。

```cpp
int main(int argc, char** argv) {
  registerInteraction(argc, argv);
  int n = inf.readInt();  // 选数
  cout.flush();           // 刷新缓冲区
  int left = 50;
  bool found = false;
  while (left > 0 && !found) {
    left--;
    int a = ouf.readInt(1, 1000000000);  // 询问
    if (a < n)
      cout << 0 << endl;
    else if (a > n)
      cout << 2 << endl;
    else
      cout << 1 << endl, found = true;
    cout.flush();
  }
  if (!found) quitf(_wa, "couldn't guess the number with 50 questions");
  ouf.readEof();
  quitf(_ok, "guessed the number with %d questions!", 50 - left);
}
```
