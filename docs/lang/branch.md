一个程序默认是按照代码的顺序执行下来的，有时我们需要选择性的执行某些语句，这时候就需要分支的功能来实现。选择合适的分支语句可以提高程序的效率。

## if 语句

### 基本 if 语句

以下是基本 if 语句的结构。

```cpp
if (布尔表达式) {
  主体;
}
```

if 语句通过对布尔表达式进行求值，若结果为真（非 0）则执行语句，否则不执行。

如果主体中只有单个语句的话，花括号可以省略。

### if...else 语句

```cpp
if (布尔表达式) {
  主体1;
} else {
  主体2;
}
```

if...else 语句和 if 语句类似，else 不需要再写判断式。两者区别在于当 if 语句的判断表达式为假时，会直接执行 else 里的语句。同样，当主体只有一条语句的话，可以省略花括号。

### else if 语句

```cpp
if (布尔表达式1) {
  主体1;
} else if (布尔表达式2) {
  主体2;
} else if (布尔表达式3) {
  主体3;
} else {
  主体4;
}
```

else if 语句是 if 和 else 的组合，对多个条件进行判断并选择不同的语句分支。在最后一条的 else 语句则不需要再写判断表达式。例如，若布尔表达式 1 为真，执行主体 1，布尔表达式 3 为真而前面的都为假，执行主体 2，所有的布尔表达式都为假才执行主体 4。

实际上，这一个语句相当于第一个 if 的 else 分句只有一个 if 表达式，就将花括号省略之后放在一起了。如果判断式相互之间是并列关系，这样写可以让代码的逻辑更清晰。

在逻辑上，大约相当于这一段话：

> 解一元二次方程的时候，方程的根与判别式的关系：
>
> -   如果 ( $\delta<0$ )
>     方程无解；
> -   否则，如果 ( $\delta=0$ )
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

switch 语句求值选择句，然后根据选择句的值选择相应的标签处开始执行。其中，选择句必须是一个整数类型，而标签都必须是整数类型的常量。例如：

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

switch 语句中还要根据需求加入 break 语句进行中断，否则检验条件满足后接下来的所有 case 里的语句和 default 里的语句都会被运行。具体例子可看下面的示例。

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

以上代码运行后输出的结果为 WIKI 和 Hello World，如果不想让下面分支的语句被运行就需要 break 了，具体例子可看下面的示例。

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
