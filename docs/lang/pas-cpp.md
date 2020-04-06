author: kexplorning, Ir1d

> 用来急救，不多废话。

## C++ 快速安装与环境配置

> 注意：这里假设使用的系统是 Windows。

### 方式一：使用 IDE

以下 IDE 选择一个即可：

-    [Dev-C++](https://sourceforge.net/projects/orwelldevcpp/) 
-    [Code::Blocks](https://sourceforge.net/projects/codeblocks/) 
-    [Visual Studio](https://visualstudio.microsoft.com/) （Community 版本够用）

### 方式二：使用 代码编辑器 + 编译器 + 调试器

如果愿意折腾就去配吧，此处略，需要注意配置环境变量。

## C++ 语法快速提要 Start Here

C++ 程序都是从 `main` 这个部分开始运行的。

大括号表示块语句的开始与结束： `{` 就相当于 Pascal 里面的 `begin` ，而 `}` 就相当于 `end` 。

注意，和 Pascal 一样，C++ 每句话结束要加分号 `;` ，不过大括号结尾不需要有分号，而且程序结束末尾不用打句号 `.` 。

 `//` 表示行内注释， `/* */` 表示块注释。

按照惯例，看看 Hello World 吧。

### Hello World：第一个 C++ 程序

```cpp
#include <iostream>  // 导入 iostream 库

int main(int argc, char const *argv[])  // main 部分
{
  std::cout << "Hello World!" << std::endl;

  return 0;
}
```

然后编译运行一下，看看结果。

#### 简要解释

第一行， `#include <iostream>` 的意思是，导入 `iostream` 这个库。

??? note "Pascal 的库文件"
    Pascal 其实是有库文件的，只不过，很多同学从来都没有用过……

看到第三行的 `main` 吗？程序从 `main` 开始执行。

接下来最重要的一句话是

```cpp
std::cout << "Hello World!" << std::endl;
```

 `std::cout` 是输出（ `cout` 即 C-out）的命令。你可能看过有些 C++ 程序中直接写的是 `cout` 。

??? note "有关 std:: 前缀"
    有关 `std::` 这个前缀的问题，请见 [这节](../basic/#cin-cout) 底下的注释「什么是 std？」。

中间的 `<<` 很形象地表示流动，其实它就是表示输出怎么「流动」的。这句代码的意思就是， `"Hello World!"` 会先被推到输出流，之后 `std::endl` 再被推到输出流。

而 `std::endl` 是 **输出** 换行（ `endl` 即 end-line）命令，这与 Pascal 的 `writeln` 类似，不过 C++ 里面可没有 `coutln` 。Pascal 与 C++ 的区别在于， `write('Hello World!')` 等价于 `std::cout << "Hello World!"` ，而 `writeln('Hello World!')` 等价于 `std::cout << "Hello World!" << std::endl` 。

此处 `"Hello World!"` 是字符串，Pascal 中字符串都是用单引号 `'` 不能用双引号，而 C++ 的字符串必须用双引号。C++ 中单引号包围的字符会有别的含义，后面会再提及的。

好了，到这里 Hello World 应该解释的差不多了。

可能有同学会问，后面那个 `return 0` 是什么意思？那个 `int main(int argc, char const *argv[])` 是啥意思？ **先别管它** ，一开始写程序的时候先把它当作模板来写吧（这里也是用模板写的）。不过，入门时并不会用到 `main` 中参数，所以写成 `int main()` 也是没有关系的。

#### 简单练习

1.  试着换个字符串输出。
2.  试着了解转义字符。

### A+B Problem：第二个 C++ 程序

经典的 A+B Problem。

```cpp
#include <iostream>

int main(int argc, char const *argv[]) {
  int a, b, c;

  std::cin >> a >> b;

  c = a + b;

  std::cout << c << std::endl;

  return 0;
}
```

注：代码空行较多，若不习惯可去掉空行。

#### 简要解释

 `std::cin` 是读入（ `cin` 即 C-in）， `>>` 也与输出语法的类似。

这里多出来的语句中最重要的是两个，一个是变量声明语句

```cpp
int a, b, c;
```

你可能习惯于 Pascal 里面的声明变量

```pas
var
a, b, c: integer;
```

C++ 的声明是直接以数据类型名开头的，在这里， `int` （整型）开头表示接下来要声明变量。

接着一个最重要的语句就是赋值语句

```cpp
c = a + b;
```

这是 Pascal 与 C++ 语法较大的不同， **这是个坑** ：Pascal 是 `:=` ，C++ 是 `=` ；而 C++ 判断相等是 `==` 。

C++ 也可直接在声明时进行变量初始化赋值

```cpp
int a = 0, b = 0, c = 0;
```

#### 简单练习

1.  重写一遍代码，提交到 OJ 上，并且 AC。
2.  更多的输入输出语法参考 [这节内容](../basic/#scanf-printf) ，并试着了解 C++ 的格式化输出。

### 结束语与下一步

好了，到现在为止，你已经掌握了一些最基本的东西了，剩下就是找 Pascal 和 C++ 里面对应的语法和不同的特征。

不过在此之前，强烈建议先看 [变量作用域：全局变量与局部变量](#scope) ，也可使用 [附 B：文章检索](#index) 查阅阅读。

请善用<kbd>Alt</kbd>+<kbd>←</kbd>与<kbd>Alt</kbd>+<kbd>→</kbd>返回跳转。

## 对应语法

### 变量 Variable

#### 基本数据类型 Fundamental types

C++ 与 Pascal 基本上差不多，常见的有

-    `bool` Boolean 类型
-    `int` 整型
-   浮点型
    -    `float` 
    -    `double` 
-    `char` 字符型
-    `void` 无类型

C++ 的单引号是专门用于表示单个字符的（字符型），比如 `'a'` ，而字符串（字符型数组）必须要用双引号。

C++ 还要很多额外的数据类型，请参考更多资料。

扩展阅读：

-    [基础类型 - cppreference.com](https://zh.cppreference.com/w/cpp/language/types) 

#### 常量声明 Constant

```cpp
const double PI = 3.1415926;
```

若不清楚有关宏展开的问题，建议使用常量，而不用宏定义。

### 运算符 Operator

请直接参考

-    [附：Pascal 与 C++ 语法对比表](#apascal-c-pascal-vs-c-syntax-table) 
-    [运算 - OI Wiki](../op/) 

### 条件

####  `if` 语句

```pas
if (a = b) and (a > 0) and (b > 0) then
    begin
        b := a;
    end
else
    begin
        a := b;
    end;
```

```cpp
if (a == b && a > 0 && b > 0) {
  b = a;
} else {
  a = b;
}
```

布尔运算与比较

-    `and` -> `&&` 
-    `or` -> `||` 
-    `not` -> `!` 
-    `=` -> `==` 
-    `<>` -> `!=` 

注释：

1.  Pascal 中 `and` 与 C++ 中 `&&` 优先级不同，C++ 不需要给判断条件加括号。
2.  Pascal 中判断相等是 `=` ，赋值是 `:=` ；C++ 中判断相等是 `==` ，赋值是 `=` 。
3.  如果在 `if` 语句的括号内写了 `a = b` 而不是 `a == b` ，程序不会报错，而且会把 `b` 赋值给 `a` ， `a = b` 这个语句的返回结果是 `true` 。
4.  C++ 不需要思考到底要不要在 `end` 后面加分号。
5.  C++ 布尔运算中，非布尔值可以自动转化为布尔值。

???+note "易错提醒"
    特别注意： **不要把 `==` 写成 `=` ！** 

    由于 C/C++ 比 Pascal 语法灵活，如果在判断语句中写了 `if (a=b) {`，那么程序会顺利运行下去，因为 C++ 中 `a=b` 是有返回值的。

####  `case` 与 `switch` 

用到得不多，此处不详细展开。

需要注意：C++ 没有 `1..n` ，也没有连续不等式（比如 `1 < x < 2` ）。

### 循环 Loop

以下三种循环、六份代码实现的功能是一样的。

####  `while` 循环

 `while` 很相似。（C++ 此处并非完整程序，省略一些框架模板，后同）

```pas
var i: integer;

begin
    i := 1;
    while i <= 10 do
        begin
            write(i,' ');
            inc(i); // 或者 i := i + 1;
        end;
end.
```

```cpp
int i = 1;
while (i <= 10) {
  std::cout << i << " ";
  i++;
}
```

####  `for` 循环

C++ 的 `for` 语句非常不同。

```pas
var i: integer;

begin
    for i:= 1 to 10 do
        begin
            write(i, ' ');
        end;
end.
```

```cpp
for (int i = 1; i <= 10; i++) {
  std::cout << i << " ";
}
```

注释：

1.   `for (int i = 1; i <= 10; i++){` 这一行语句很多， `for` 中有三个语句。
2.  第一个语句 `int i = 1;` 此时声明一局部变量 `i` 并初始化。（这个设计比 Pascal 要合理得多。）
3.  第二个语句 `i <= 10;` 作为判断循环是否继续的标准。
4.  第三个语句 `i++` ，在每次循环结尾执行，意思大约就是 Pascal 中的 `inc(i)` ，此处写成 `++i` 也是一样的。 `i++` 与 `++i` 的区别请参考其他资料。

####  `repeat until` 与 `do while` 循环

注意， `repeat unitl` 与 `do while` 是不同的，请对比以下代码

```pas
var i: integer;

begin
    i := 1;
    repeat
        write(i, ' ');
        inc(i);
    until i = 11;
end.
```

```cpp
int i = 1;
do {
  std::cout << i << " ";
  i++;
} while (i <= 10);
```

#### 循环控制 Loop Control

C++ 中 `break` 的作用与 Pascal 是一样的，退出循环。

而 `continue` 也是一样的，跳过当前循环，进入下一次循环（回到开头）。

### 数组与字符串 Array and String

#### 不定长数组：标准库类型 Vector

C++ 标准库中提供了 `vector` ，相当于不定长数组，调用前需导入库文件。

```cpp
#include <iostream>
#include <vector>  // 导入 vector 库

int main(int argc, char const *argv[]) {
  std::vector<int> a;  // 声明 vector a 并定义 a 为空 vector 对象
  int n;

  std::cin >> n;
  // 读取 a
  for (int i = 0; i < n; i++) {
    int t;
    std::cin >> t;
    a.push_back(t);  // 将读入的数字 t，放到 vector a 的末尾；该操作复杂度 O(1)
    /* 这里不能使用下标访问来赋值，因为声明时，a 大小依然为空，
    此处使用 `a[i] = t;` 是错误做法。
    */
  }

  // 将读入到 a 中的所有数打印出
  for (int i = 0; i < n; i++) {
    std::cout << a[i] << ", ";  // !注意，a 中第一个数是 a[0]；
    // 如果下标越界，它会返回一个未知的值（溢出），而不会报错
  }
  std::cout << std::endl;

  return 0;
}
```

C++ 访问数组成员，与 Pascal 类似，不过有很重要的区别：数组的第一项是 `a[0]` ，而 Pascal 中是可以自行指定的。

扩展阅读：

-    [序列式容器 - OI Wiki](../csl/sequence-container/) 

#### 字符串：标准库类型 String

C++ 标准库中提供了 `string` ，与 `vector` 可以进行的操作有些相同，同样需要导入库文件。

```cpp
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  std::string s;  // 声明 string s

  std::cin >> s;  // 读入 s；
  // 读入时会忽略开头所有空格符（空格、换行符、制表符），读入的字串直到下一个空格符为止。

  std::cout << s << std::endl;

  return 0;
}
```

扩展阅读：

-    [string - OI Wiki](../csl/string/) 

#### C 风格数组 Array

如果要用不定长的数组请用 Vector，不要用 C 风格的数组。

C 风格的数组与指针有密切关系，所以此处不多展开。

扩展阅读：

-    [数组 - OI Wiki](../array/) 

## 重要不同之处

### 变量作用域 Scope：全局变量与局部变量

C++ 几乎可以在 **任何地方** 声明变量。

以下对于 C++ 的变量作用域的介绍摘自 [变量作用域 - OI Wiki](../var/#_3) ：

> 作用域是变量可以发挥作用的代码块。
>
> 变量分为全局变量和局部变量。在所有函数外部声明的变量，称为全局变量。在函数或一个代码块内部声明的变量，称为局部变量。
>
> 全局变量的作用域是整个文件，全局变量一旦声明，在整个程序中都是可用的。
>
> 局部变量的作用域是声明语句所在的代码块，局部变量只能被函数内部或者代码块内部的语句使用。
>
> 由一对大括号括起来的若干语句构成一个代码块。
>
> ```cpp
> int g = 20;  // 声明全局变量
> int main() {
>   int g = 10;         // 声明局部变量
>   printf("%d\n", g);  // 输出 g
>   return 0;
> }
> ```
>
> 在一个代码块中，局部变量会覆盖掉同名的全局变量，比如上面的代码输出的 `g` 就是 `10` 而不是 `20` 。为了防止出现意料之外的错误，请尽量避免局部变量与全局变量重名的情况。

在写 Pascal 过程/函数时，容易忘记声明局部变量 `i` 或者 `j` ，而一般主程序里会有循环，于是大部分情况下 `i` 与 `j` 都是全局变量，于是，在这种情况下，过程/函数中对 `i` 操作极易出错。更要命的是，如果忘记声明这种局部变量，编译器编译不报错，程序可以运行。（有很多难找的 bug 就是这么来的。）

所以，在使用 C++ 时，声明变量，比如循环中使用的 `i` ， **不要用全局变量，能用局部变量就用局部变量** 。如果这么做，不用担心函数中变量名（比如 `i` ）冲突。

??? note "额外注"
    Pascal 可在某种程度上避免这个问题，仿照 C++ 的方法，主程序只有调用过程/函数，不声明 `i`  `j` 这类极易名称冲突的全局变量，如果需要循环，另写一个过程进行调用。

### C++ 可以自动转换类型

```cpp
int i = 2;
if (i) {  // i = 0 会返回 false，其余返回 true
  std::cout << "true";
} else {
  std::cout << "false";
}
```

不光是 `int` 转成 `bool` ，还有 `int` 与 `float` 相互转换

```cpp
int a;
a = 3.2;      // 此时 a = 3
float b = a;  // 此时 b = 3.0
```

区分 `/` 是整除还是浮点除法，是通过除数与被除数的类型判断的

```cpp
float a = 32 / 10;    // 32/10 的结果是 3（整除）；a = 3.0
float b = 32.0 / 10;  // 32.0/10 的结果是 3.2；b = 3.2
```

还有 `char` 与 `int` 之间相互转换。

### C++ 很多语句有返回值：以如何实现读取数量不定数据为例

有些时候需要读取到数据结束，比如，求一组不定数量的数之和（数据可以多行），直到文件末尾，实现方式是

??? note "文件末尾 EOF"
    EOF，文件末尾标识符，在命令行中 Windows 上以<kbd>Ctrl</kbd>+<kbd>Z</kbd>输入（还需按<kbd>Enter</kbd>），\*unix 系统以<kbd>Ctrl</kbd>+<kbd>D</kbd>输入。

```cpp
#include <iostream>

int main(int argc, char const *argv[]) {
  int sum = 0, a = 0;

  while (std::cin >> a) {
    sum += a;
  }
  std::cout << sum << std::endl;

  return 0;
}
```

实现原理： `while (std::cin >> a)` 中 `std::cin >> a` 若在输入有问题或遇到文件结尾时，会返回 false，使得循环中断。

### 函数 Function：C++ 只有函数没有过程但有 `void` ，没有函数值变量但有 `return` 。

Pascal 函数与 C++ 函数对比示例：

```pas
function abs(x:integer):integer;
begin
    if x < 0 then
        begin
            abs := -x;
        end
    else
        begin
            abs := x;
        end;
end;
```

```cpp
int abs(int x) {
  if (x < 0) {
    return -x;
  } else {
    return x;
  }
}
```

C++ 中函数声明 `int abs` ，就定义了 `abs()` 函数且返回值为 `int` 型（整型），函数的返回值就是 `return` 语句给出的值。

如果不想有返回值（即 Pascal 的「过程」），就用 `void` 。 `void` 即「空」，什么都不返回。

```pas
var ans: integer;

procedure printAns(ans:integer);
begin
    writeln(ans);
end;

begin
    ans := 10;
    printAns(ans);
end.
```

```cpp
#include <iostream>

void printAns(int ans) { std::cout << ans << std::endl; }

int main(int argc, char const *argv[]) {
  int ans = 10;
  printAns(ans);

  return 0;
}
```

C++ 把函数和过程统统视作函数，连 `main` 都不放过，比如写 `int main` ，C++ 视 `main` 为一个整型的函数，这里返回值是 `0` 。它是一种习惯约定，返回 `0` 代表程序正常退出。

也许你已经猜到了， `main(int argc, char const *argv[])` 中的参数就是 `int argc` 与 `char const *argv[]` ，不过意义请参考其他资料。

### 在函数中传递参数 Passing Parameters to Functions

C++ 中没有 Pascal 的 `var` 关键字可以改变传递的参数

```pas
var a, b: integer;

procedure swap(var x,y:integer);
var temp:integer;
begin
    temp := x;
    x := y;
    y := temp;
end;

begin
    a := 10; b:= 20;    
    swap(a, b);
    writeln(a, ' ', b);
end.
```

```cpp
#include <iostream>

void swap(int* x, int* y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

int main(int argc, char const* argv[]) {
  int a = 10, b = 20;
  swap(&a, &b);
  std::cout << a << " " << b;

  return 0;
}
```

注意，此处 C++ 代码涉及指针问题。指针问题还是很麻烦的，建议去阅读相关资料。

C++ 中函数传递参数还有其他方法，其中一种是 **直接使用全局变量传递参数** ，如果不会用指针，可以先用这种方法。

## C++ 标准库与参考资料 Reference

千万不要重复造轮子（除非为了练习），想要自己动手写一个功能出来之前，先去看看有没有这个函数或者数据结构。

### C++ 标准库

C++ 标准库中 `<algorithm>` 有很多有用的函数比如快排、二分查找等，可以直接调用。请参考这个页面： [STL 算法 - OI Wiki](../csl/algorithm/) 。

还有 STL 容器，比如数组、向量（可变大小的数组）、队列、栈等，附带很多函数。请参考这个页面： [STL 容器简介 - OI Wiki](../csl/container/) 。

如果要找关于字符串操作的函数见

-    [std::basic_string - cppreference.com](https://zh.cppreference.com/w/cpp/string/basic_string) 
-    [ `<string>` - C++ Reference](https://www.cplusplus.com/reference/string/) 

C/C++ 的指针是很灵活的东西，如果想要彻底理解指针，建议找本书或者参考手册仔细阅读。

### 错误排查与技巧

-    [常见错误 - OI Wiki](../../intro/common-mistakes/) 
-    [常见技巧 - OI Wiki](../../intro/common-tricks/) 

### C++ 语言资料

-    [学习资源 - OI Wiki](../../intro/resources/) 
-    [cppreference.com](https://zh.cppreference.com/) - 最重要的 C/C++ 参考资料
-    [C++ Language - C++ Tutorials](https://www.cplusplus.com/doc/tutorial/) 
-    [Reference - C++ Reference](https://www.cplusplus.com/reference/) 
-    [C++ Standard Library - Wikipedia](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) 
-    [The Ultimate Question of Programming, Refactoring, and Everything](https://www.gitbook.com/book/alexastva/the-ultimate-question-of-programming-refactoring-/details) 
-    [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) 

## 后记

写到这里，很多同学会觉得这一点都不急救啊，有很多东西没有提到啊。那也是没办法的事情。

虽然是为了急救，但很多东西像怎么把字符串转化为数字，怎么搜索字符串中的字符，这些东西也不适合一篇精悍短小的急救帖，如果把这些都写出来，那就是 C++ 入门教程，所以请充分利用本 Wiki、参考手册与搜索引擎。

需要指出的一点是，上面说 C++ 的语法，其实有很多语法是从 C 语言来的，标题这么写比较好——《Pascal 转 C/C++ 急救帖》。

Pascal 在上个世纪后半叶是门很流行的语言，它早于 C 语言，不过随着 UNIX 系统的普及，微软使用 C 语言，现在 Pascal 已经成为历史了。Pascal 后期发展也是有的，比如 Free Pascal 这个开源编译器项目，增加面向对象的特性（Delphi 语言）。Pascal 目前的用处除了在信息竞赛外，有一个特点是其他语言没有的——编译支持非常非常多老旧机器，比如 Gameboy 这种上个世纪的任天堂游戏机。

最后，Pascal 的圈子其实很小，C/C++ 的圈子很大，帮助手册与教程很多很全，一定要掌握好英语。世界上还有很多很多编程语言，而计算机这门学科与技术不光是信息竞赛和编程语言。

## 附 A：Pascal 与 C++ 语法对比表 Pascal vs C++ Syntax Table

### 基本算术

|      | Pascal      | C++       |
| ---- | ----------- | --------- |
| 加法   |  `a + b`    |  `a + b`  |
| 减法   |  `a - b`    |  `a - b`  |
| 乘法   |  `a * b`    |  `a * b`  |
| 整除   |  `a div b`  |  `a / b`  |
| 浮点除法 |  `a / b`    |  `a / b`  |
| 取模   |  `a mod b`  |  `a % b`  |

### 逻辑

|     | Pascal      | C++        |
| --- | ----------- | ---------- |
| 非   |  `not(a)`   |  `!a`      |
| 且   |  `a and b`  |  `a && b`  |
| 或   |  `a or b`   |  `a || b`  |

### 比较

|      | Pascal     | C++        |
| ---- | ---------- | ---------- |
| 相等   |  `a = b`   |  `a == b`  |
| 不等   |  `a <> b`  |  `a != b`  |
| 大于   |  `a > b`   |  `a > b`   |
| 小于   |  `a < b`   |  `a < b`   |
| 大于等于 |  `a >= b`  |  `a >= b`  |
| 小于等于 |  `a <= b`  |  `a <= b`  |

### 赋值

|     | Pascal                          | C++        |
| --- | ------------------------------- | ---------- |
|     |  `a := b`                       |  `a = b`   |
|     |  `a := a + b`                   |  `a += b`  |
|     |  `a := a - b`                   |  `a -= b`  |
|     |  `a := a * b`                   |  `a *= b`  |
|     |  `a := a div b` 或 `a := a / b`  |  `a /= b`  |
|     |  `a := a mod b`                 |  `a &= b`  |

### 自增/自减

|     | Pascal     | C++     |
| --- | ---------- | ------- |
| 自增  |  `inc(a)`  |  `a++`  |
| 自增  |  `inc(a)`  |  `++a`  |
| 自减  |  `dec(a)`  |  `a--`  |
| 自减  |  `dec(a)`  |  `--a`  |

## 附 B：文章检索 Index

-    [基本语法](#c-start-here) 
-    [变量](#variable) 
    -    [数据类型](#fundamental-types) 
    -    [常量声明](#constant) 
    -    [作用域](#scope) 
-    [运算符](#operator) 
-    [if 语句](#if) 
    -   if
    -   else
-    [循环语句](#loop) 
    -    [for 语句](#for) 
    -    [while 语句](#while) 
    -    [do while 语句](#repeat-until-do-while) 
    -    [break, continue](#loop-control) 
-    [函数](#functionc-void-return) 
    -    [函数定义](#functionc-void-return) 
    -    [函数传参](#passing-parameters-to-functions) 
-    [数组与字符串](#array-and-string) 
    -    [不定长数组 Vector](#vector) 
    -    [C 风格数组](#c-array) 
    -    [字符串 String](#string) 
-    [资料](#c-reference) 
