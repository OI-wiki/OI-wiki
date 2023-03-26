author: Ir1d, HeRaNO, NachtgeistW, i-Yirannn, bear-good, ranwen, CoelacanthusHex, billchenchina, Tiger3018, Xeonacid

## Lemon

???+ warning
    macOS 下 Lemon 可能会出现内存测试不准确的情况，因为 macOS 缺少部分 Linux 的监测工具，且 Lemon-Linux 也没有针对 macOS 进行优化。

**Lemon** 是 zhipeng-jia 编写的开源评测工具，源代码托管于 [zhipeng-jia/project-lemon](https://github.com/zhipeng-jia/project-lemon)。

### 可直接运行的版本

-   Ir1d 提供了一份 Linux 下编译好的版本，源代码托管于 [FreestyleOJ/Project\_lemon](https://github.com/FreestyleOJ/Project_lemon/tree/Built)。
-   （已停止维护）Menci 提供了一份更新的版本，源代码托管于 [Menci/Lemon](https://github.com/Menci/Lemon/)。
-   （已停止维护）Dust1404 维护了一份支持子文件夹和单题测试等功能的版本，源代码托管于 [Dust1404/Project\_LemonPlus](https://github.com/Dust1404/Project_LemonPlus)。
-   iotang 和 Coelacanthus 维护了一份支持子文件夹和单题测试等功能的版本，源代码托管于 [Project-LemonLime/Project\_LemonLime](https://github.com/Project-LemonLime/Project_LemonLime)。

### 自行编译

Ubuntu：

```bash
sudo apt update
sudo apt install qt5-default build-essential git -y
git clone --depth=1 https://github.com/Menci/Lemon.git
cd lemon
# 可以修改 -j 后面的数字来调整 make job 的线程数
./make -j2
sudo install -Dm755 -t /usr/bin/ Lemon
```

如要编译 LemonLime，请参阅 LemonLime 的 [编译手册](https://github.com/Project-LemonLime/Project_LemonLime/blob/master/BUILD.md)。

### 数据格式

首先打开 lemon 选择「新建试题」，然后打开新建试题的文件夹。

题目和数据应该如以下格式所示：

```text
├── data
│   ├── gendata.py
│   ├── product
│   │   ├── product100.in
│   │   ├── product100.out
│   │   ├── product10.in
│   │   ├── product10.out
│   │   ├── product11.in
...
```

当所有试题添加完成后，回到 lemon 选择「自动添加试题」。此时题目和数据点将显示在 lemon 当中。
