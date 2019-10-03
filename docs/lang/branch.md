一个程序默认是按照代码的顺序执行下来的，有时我们需要选择性的执行某些语句，这时候就需要分支的功能来实现。对于分支的选择应该使用恰当的语句，这样可以提升程序效率。

## if 语句

### 基本 if 语句

以下是基本 if 语句的结构。

```cpp
if (表达式) {
  语句;
}
```

if 语句通过对表达式进行判断，若表达式为真（非 0）则执行语句，否则不执行。

### if...else 语句

```cpp
if (表达式) {
  语句;
} else {
  语句;
}
```

if...else 语句和 if 语句类似，else 不需要再写判断表达式。两者区别在于当 if 语句的判断表达式为假时，直接执行 else 里的语句。

### else if 语句

```cpp
if (表达式1) {
  语句1;
} else if (表达式2) {
  语句2;
} else if (表达式3) {
  语句3;
} else {
  语句4;
}
```

else if 语句是 if 和 else 的组合，对多个条件进行判断并选择不同的语句分支。在最后一条的 else 语句则不需要再写判断表达式。

## switch 语句

```cpp
switch (整数类型的表达式) {
  case 常量表达式1: {
    语句1;
  }
  case 常量表达式2: {
    语句2;
  }
  default: { 语句3; }
}
```

switch 语句的括号中的表达式就是要判断的条件必须是整数类型的表达式（如 int/char/bool 以及它们的修饰类型），case 检验条件是否等于该表达式，若等于则执行其后的语句直到 switch 块末尾；若不等于所有 case 的表达式则执行 default 之后的语句。如果不需要默认执行的操作，那么 switch 中也可以没有 default 语句。

```cpp
int i = 1;  //这里的 i 的数据类型是整型 ，满足整数类型的表达式的要求
switch (i) {
  case 1: {
    cout << "OI WIKI" << endl;
  }
}
```

```cpp
char i = 'A';
// 这里的 i 的数据类型是字符型 ，但 char
// 也是属于整数的类型，满足整数类型的表达式的要求
switch (i) {
  case 'A': {
    cout << "OI WIKI" << endl;
  }
}
```

switch 语句中还要根据需求加入 break 语句进行中断，否则检验条件满足后接下来的所有 case 里的语句和 default 里的语句都会被运行。具体例子可看下面的示例。

```cpp
char i = 'B';
switch (i) {
  case 'A': {
    cout << "OI" << endl;
    break;
  }
  case 'B': {
    cout << "WIKI" << endl;
  }
  default: { cout << "Hello World" << endl; }
}
```

以上代码运行后输出的结果为 WIKI 和 Hello World，如果不想让 default 分支的内容被输出就需要 break 了，具体例子可看下面的示例。

```cpp
char i = 'B';
switch (i) {
  case 'A': {
    cout << "OI" << endl;
    break;
  }
  case 'B': {
    cout << "WIKI" << endl;
    break;
  }
  default: { cout << "Hello World" << endl; }
}
```

以上代码运行后输出的结果为 WIKI，因为 break 的存在接下来的语句就不会继续被执行了。
