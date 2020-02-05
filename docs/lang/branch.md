一个程序默认是按照代码的顺序执行下来的，有时我们需要选择性的执行某些语句，这时候就需要分支的功能来实现。选择合适的分支语句可以提高程序的效率。

## if 语句

### 基本 if 语句

以下是基本 if 语句的结构。

```cpp
if (条件) {
  主体;
}
```

if 语句通过对条件进行求值，若结果为真（非 0），执行语句，否则不执行。

如果主体中只有单个语句的话，花括号可以省略。

### if...else 语句

```cpp
if (条件) {
  主体1;
} else {
  主体2;
}
```

if...else 语句和 if 语句类似，else 不需要再写条件。当 if 语句的条件满足时会执行 if 里的语句，if 语句的条件不满足时会执行 else 里的语句。同样，当主体只有一条语句时，可以省略花括号。

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

else if 语句是 if 和 else 的组合，对多个条件进行判断并选择不同的语句分支。在最后一条的 else 语句不需要再写条件。例如，若条件 1 为真，执行主体 1，条件 3 为真而条件 1 和条件 2 都为假，执行主体 3，所有的条件都为假才执行主体 4。

实际上，这一个语句相当于第一个 if 的 else 分句只有一个 if 语句，就将花括号省略之后放在一起了。如果条件相互之间是并列关系，这样写可以让代码的逻辑更清晰。

在逻辑上，大约相当于这一段话：

> 解一元二次方程的时候，方程的根与判别式的关系：
>
> -   如果 ( $\Delta<0$ )
>     方程无解；
> -   否则，如果 ( $\Delta=0$ )
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

switch 语句执行时，先求出选择句的值，然后根据选择句的值选择相应的标签，从标签处开始执行。其中，选择句必须是一个整数类型表达式，而标签都必须是整数类型的常量。例如：

```cpp
int i = 1;  //这里的 i 的数据类型是整型 ，满足整数类型的表达式的要求
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

switch 语句中还要根据需求加入 break 语句进行中断，否则在对应的 case 被选择之后接下来的所有 case 里的语句和 default 里的语句都会被运行。具体例子可看下面的示例。

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

以上代码运行后输出的结果为 `WIKI` 和 `Hello World` ，如果不想让下面分支的语句被运行就需要 break 了，具体例子可看下面的示例。

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

以上代码运行后输出的结果为 WIKI，因为 break 的存在，接下来的语句就不会继续被执行了。default 语句不需要 break，因为下面没有语句了。

switch 的 case 分句中也可以选择性的加花括号。不过要注意的是，如果需要在 switch 语句中定义变量，花括号是必须要加的。例如：

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

  default: { cout << "Hello World" << endl; }
}
```

??? note "如何理解 switch"
    在上文中，用了大量“case 分句”，“case 子句”等用语，实际上，在底层实现中，switch 相当于一组跳转语句。也因此，有 Duff's Device 这种奇技淫巧，希望了解的人可以自行学习。

    另外还有一种理解 switch 的方式，就是从其逻辑意义去理解。在这种理解里，case 代表的就是一组子句，而 switch 根据选择句的值选择某个 case 分句进行执行。在这种理解中，除了极少数例外，case 是必须要加 break 和花括号的。
