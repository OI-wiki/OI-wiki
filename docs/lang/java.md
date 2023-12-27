## 关于 Java

Java 是一种广泛使用的计算机编程语言，拥有 **跨平台**、**面向对象**、**泛型编程** 的特性，广泛应用于企业级 Web 应用开发和移动应用开发。

## 环境安装

参见 [JDK](../tools/compiler.md#jdk)。

## 基本语法

### 主函数

Java 类似 C/C++ 语言，需要一个函数（在面向对象中，这被称为方法）作为程序执行的入口点。

Java 的主函数的格式是固定的，形如：

```java
class Test {
    public static void main(String[] args) {
        // 程序的代码
    }
}
```

一个打包的 Java 程序（名称一般是 `*.jar`）中可以有很多个类似的函数，但是当运行这个程序的时候，只有其中一个函数会被运行，这是定义在 `Jar` 的 `Manifest` 文件中的，在 OI 比赛中一般用不到关于它的知识。

### 注释

和 C/C++ 一样，Java 使用 `//` 和 `/* */` 分别注释单行和多行。

### 基本数据类型

|   类型名   |   意义  |
| :-----: | :---: |
| boolean |  布尔类型 |
|   byte  |  字节类型 |
|   char  |  字符型  |
|  double | 双精度浮点 |
|  float  | 单精度浮点 |
|   int   |   整型  |
|   long  |  长整型  |
|  short  |  短整型  |
|   null  |   空   |

### 声明变量

```java
int a = 12; // 设置 a 为整数类型,并给 a 赋值为 12
String str = "Hello, OI-wiki"; // 声明字符串变量 str
char ch = 'W';
double PI = 3.1415926;
```

### final 关键字

`final` 含义是这是最终的、不可更改的结果，被 `final` 修饰的变量只能被赋值一次，赋值后不再改变。

```java
final double PI = 3.1415926;
```

### 数组

```java
// 有十个元素的整数类型数组
// 其语法格式为 数据类型[] 变量名 = new 数据类型[数组大小]
int[] ary = new int[10];
```

### 字符串

-   字符串是 Java 一个内置的类。

```java
// 最为简单的构造一个字符串变量的方法如下
String a = "Hello";

// 还可以使用字符数组构造一个字符串变量
char[] stringArray = { 'H', 'e', 'l', 'l', 'o' };
String s = new String(stringArray);
```

### 包和导入包

Java 中的类（`Class`）都被放在一个个包（`package`）里面。在一个包里面不允许有同名的类。在类的第一行通常要说明这个类是属于哪个包的。例如：

```java
package org.oi-wiki.tutorial;
```

包的命名规范一般是：`项目所有者的顶级域.项目所有者的二级域.项目名称`。

通过 `import` 关键字来导入不在本类所属的包下面的类。例如下面要用到的 `Scanner`：

```java
import java.util.Scanner;
```

如果想要导入某包下面所有的类，只需要把这个语句最后的分号前的类名换成 `*`。

### 输入

可以通过 `Scanner` 类来处理命令行输入。

```java
package org.oiwiki.tutorial;

import java.util.Scanner;

class Test {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in); // System.in 是输入流
        int a = scan.nextInt();
        double b = scan.nextDouble();
        String c = scan.nextLine();
    }
}
```

### 输出

可以对变量进行格式化输出。

|  符号  |   意义  |
| :--: | :---: |
| `%f` |  浮点类型 |
| `%s` | 字符串类型 |
| `%d` |  整数类型 |
| `%c` |  字符类型 |

```java
class Test {
    public static void main(String[] args) {
        int a = 12;
        char b = 'A';
        double s = 3.14;
        String str = "Hello world";
        System.out.printf("%f\n", s);
        System.out.printf("%d\n", a);
        System.out.printf("%c\n", b);
        System.out.printf("%s\n", str);
    }
}
```

### 控制语句

Java 的流程控制语句与 C++ 是基本相同的。

#### 选择

-   if

```java
class Test {
    public static void main(String[] args) {
        if ( /* 判断条件 */ ){
            // 条件成立时执行这里面的代码
        }
    }
}
```

-   if...else

```java
class Test {
    public static void main(String[] args) {
        if ( /* 判断条件 */ ) {
            // 条件成立时执行这里面的代码
        } else {
            // 条件不成立时执行这里面的代码
        }
    }
}
```

-   if...else if...else

```java
class Test {
    public static void main(String[] args) {
        if ( /* 判断条件 */ ) {
            //判断条件成立执行这里面的代码
        } else if ( /* 判断条件2 */ ) {
            // 判断条件2成立执行这里面的代码
        } else {
          // 上述条件都不成立执行这里面的代码
        }
    }
}
```

-   switch...case

```java
class Test {
    public static void main(String[] args) {
        switch ( /* 表达式 */ ){
          case /* 值 1 */:
              // 当表达式取得的值符合值 1 执行此段代码
              break; // 如果不加上 break 语句,会让程序按顺序往下执行直到 break
          case /* 值 2 */:
              // 当表达式取得的值符合值 2 执行此段代码
              break;
          default:
              // 当表达式不符合上面列举的值的时候执行这里面的代码
        }
    }
}
```

#### 循环

-   for

`for` 关键字有两种使用方法，其中第一种是普通的 `for` 循环，形式如下：

```java
class Test {
    public static void main(String[] args) {
        for ( /* 初始化 */; /* 循环的判断条件 */; /* 每次循环后执行的步骤 */ ) {
            // 当循环的条件成立执行循环体内代码
        }
    }
}
```

第二种是类似 C++ 的 `foreach` 使用方法，用于循环数组或者集合中的数据，相当于把上一种方式中的循环变量隐藏起来了，形式如下：

```java
class Test {
    public static void main(String[] args) {
        for	( /* 元素类型X */ /* 元素名Y */ : /* 集合Z */ ) {
            // 这个语句块的每一次循环时，元素Y分别是集合Z中的一个元素。
        }
    }
}
```

-   while

```java
class Test {
    public static void main(String[] args) {
        while ( /* 判定条件 */ ) {
            // 条件成立时执行循环体内代码
        }
    }
}
```

-   do...while

```java
class Test {
    public static void main(String[] args) {
        do {
          // 需要执行的代码
        } while ( /* 循环判断条件 */ );
    }
}
```

## 注意事项

### 类名与文件名一致

创建  Java 源程序需要类名和文件名一致才能编译通过，否则编译器会提示找不到类。通常该文件名会在具体 OJ 中指定。

例：

`Add.java`

```java
class Add {
    public static void main(String[] args) {
        // ...
    }
}
```

在该文件中需使用 `Add` 为类名方可编译通过。
