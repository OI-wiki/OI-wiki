程序默认按代码顺序执行，需要选择性地执行某些语句时，就要使用分支．选择合适的分支语句可以提高程序的效率．

## if 语句

### 基本 if 语句

以下是基本 if 语句的结构．

```cpp
if (条件) {
  主体;
}
```

if 语句对条件求值，若结果为真（非 0），则执行语句，否则不执行．

如果主体只有一条语句，可以省略花括号．

### if...else 语句

```cpp
if (条件) {
  主体1;
} else {
  主体2;
}
```

if...else 语句和 if 语句类似，else 不需要再写条件．当 if 语句的条件满足时会执行 if 里的语句，if 语句的条件不满足时会执行 else 里的语句．同样，当主体只有一条语句时，可以省略花括号．

### else if 语句

```cpp
if (条件1) {
  主体1;
} else if (条件2) {
  主体2;
} else if (条件3) {
  主体3;
} else {
  主体4;
}
```

else if 语句是 if 和 else 的组合，判断多个条件并选择不同的语句分支．最后的 else 语句无需再写条件．例如，若条件 1 为真，执行主体 1，条件 3 为真而条件 1 和条件 2 都为假，执行主体 3，所有的条件都为假才执行主体 4．

实际上，这相当于第一个 if 的 else 分句仅含一条 if 语句，省略花括号后便连写在一起．如果各个条件并列，这样写能让代码逻辑更清晰．

在逻辑上，大约相当于这一段话：

> 解一元二次方程的时候，方程的根与判别式的关系：
>
> -   如果 ($\Delta<0$)
>     方程无解；
> -   否则，如果 ($\Delta=0$)
>     方程有两个相同的实数解；
> -   否则
>     方程有两个不相同的实数解；

## switch 语句

```cpp
switch (选择句) {
  case 标签1:
    主体1;
  case 标签2:
    主体2;
  default:
    主体3;
}
```

switch 语句执行时，先求出选择句的值，然后根据选择句的值选择相应的标签，从标签处开始执行．其中，选择句必须是一个整数类型表达式，而标签都必须是整数类型的常量．例如：

```cpp
int i = 1;  // 这里的 i 的数据类型是整型 ，满足整数类型的表达式的要求

switch (i) {
  case 1:
    cout << "OI WIKI" << endl;
}
```

```cpp
char i = 'A';

// 这里的 i 的数据类型是字符型 ，但 char
// 也是属于整数的类型，满足整数类型的表达式的要求
switch (i) {
  case 'A':
    cout << "OI WIKI" << endl;
}
```

switch 语句还需按需求加入 break 语句以中断执行，否则在选中对应的 case 之后，还会运行接下来的所有 case 里的语句和 default 里的语句．具体例子可看下面的示例．

```cpp
char i = 'B';

switch (i) {
  case 'A':
    cout << "OI" << endl;
    break;

  case 'B':
    cout << "WIKI" << endl;

  default:
    cout << "Hello World" << endl;
}
```

以上代码输出 `WIKI` 和 `Hello World`．如果不想运行下面分支的语句，就需要使用 break，示例如下．

```cpp
char i = 'B';

switch (i) {
  case 'A':
    cout << "OI" << endl;
    break;

  case 'B':
    cout << "WIKI" << endl;
    break;

  default:
    cout << "Hello World" << endl;
}
```

以上代码输出 WIKI，因为 break 中断了执行，程序不会继续执行接下来的语句．最后一个语句不需要 break，因为下面没有语句了．

处理入口编号不能重复，但顺序任意，各个 case（包括 default）的出现次序也任意．例如：

```cpp
char i = 'B';

switch (i) {
  case 'B':
    cout << "WIKI" << endl;
    break;

  default:
    cout << "Hello World" << endl;
    break;

  case 'A':
    cout << "OI" << endl;
}
```

switch 的 case 分句中也可以选择性地加花括号．但如果需要在 switch 语句中定义变量，就必须加花括号．例如：

```cpp
char i = 'B';

switch (i) {
  case 'A': {
    int i = 1, j = 2;
    cout << "OI" << endl;
    ans = i + j;
    break;
  }

  case 'B': {
    int qwq = 3;
    cout << "WIKI" << endl;
    ans = qwq * qwq;
    break;
  }

  default: {
    cout << "Hello World" << endl;
  }
}
```

??? note "如何理解 switch"
    在上文中，用了大量「case 分句」，「case 子句」等用语，实际上，在底层实现中，switch 相当于一组跳转语句．也因此，有 Duff's Device 这种奇技淫巧，希望了解的人可以自行学习．
