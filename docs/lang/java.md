## 关于 Java

 `Java` 是一种广泛使用的计算机编程语言，拥有 **跨平台** 、 **面向对象** 、 **泛型编程** 的特性，广泛应用于企业级 Web 应用开发和移动应用开发。

## 环境安装

### Windows

> 待加

### macOS/Linux

> 待加

## 基本语法

 **_注意_**  `Java` 类似 `C/C++` 语言，有一个主类作为程序执行的起始点，所有的程序只有一个主类，每次执行的时候都会从主类开始

### 注释

和 `C/C++` 一样， `Java` 使用 `//` 和 `/* */` 分别注释单行和多行

### 数据类型

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

### 申明变量

```java
int a = 12;//设置a为整数类型,并给a赋值12
String str = "Hello,OI-wiki"; //申明字符串变量str
char ch = "W";
double PI = 3.1415926;  
```

### final 关键字

 `final` 含义是这是最终的、不可更改的结果，被 final 修饰的变量只能被赋值一次，赋值后不再改变

```java
final double PI  = 3.1415926; 
```

### 数组

```java
int[] ary = new int[10];
//有十个元素的整数类型数组
//其语法格式为 数据类型[] 变量名 = new 数据类型[数组大小]
```

### 字符串

-   字符串是 `Java` 一个内置的类。

```java
//最为简单的构造一个字符串变量的方法如下
String a = "Hello";
//还可以使用字符数组构造一个字符串变量
char[] stringArray = {'H','e','l','l','o'};
String s = new String(stringArray);
```

### 输出

可以对变量进行格式化输出

|   符号   |   意义  |
| :----: | :---: |
|  `%f`  | 浮点类型 |
|  `%s`  | 字符串类型 |
|  `%d`  |  整数类型  |
|  `%c`  |  字符类型 |

```java
class test{
    public static void main(String[] args) {
        int a =12;
        char b = 'A';
        double s = 3.14;
        String str = "Hello world";
        System.out.println("%f",s);
        System.out.println("%d",a);
        system.out.println("%c",b);
        system.out.println("%s",str);
    }
}
```

### 控制语句

#### 选择

#### 循环
