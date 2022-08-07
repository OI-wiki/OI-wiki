# Java 进阶

???+ warning "注意"
    以下内容均基于 Java JDK 8 版本编写，不排除在更高版本中有部分改动的可能性。

## 更高速的输入输出

`Scanner` 和 `System.out.print` 在最开始会工作得很好，但是在处理更大的输入的时候会降低效率，因此我们会需要使用一些方法来提高 IO 速度。

### 使用 Kattio + StringTokenizer 作为输入

最常用的方法之一是使用来自 Kattis 的 [Kattio.java](https://github.com/Kattis/kattio/blob/master/Kattio.java) 来提高 IO 效率。[^ref1]这个方法会将 `StringTokenizer` 与 `PrintWriter` 包装在一个类中方便使用。而在具体进行解题的时候（假如赛会/组织方允许）可以直接使用这个模板。

下方即为应包含在代码中的 IO 模板，由于 Kattis 的原 Kattio 包含一些并不常用的功能，下方的模板经过了一些调整（原 Kattio 使用 MIT 作为协议）。

```java
class Kattio extends PrintWriter {
    private BufferedReader r;
    private StringTokenizer st;
    // 标准 IO
    public Kattio() { this(System.in, System.out); }
    public Kattio(InputStream i, OutputStream o) {
        super(o);
        r = new BufferedReader(new InputStreamReader(i));
    }
    // 文件 IO
    public Kattio(String intput, String output) throws IOException {
        super(output);
        r = new BufferedReader(new FileReader(intput));
    }
    // 在没有其他输入时返回 null
    public String next() {
        try {
            while (st == null || !st.hasMoreTokens())
                st = new StringTokenizer(r.readLine());
            return st.nextToken();
        } catch (Exception e) {}
        return null;
    }
    public int nextInt() { return Integer.parseInt(next()); }
    public double nextDouble() { return Double.parseDouble(next()); }
    public long nextLong() { return Long.parseLong(next()); }
}
```

而下方代码简单展示了 Kattio 的使用：

```java
class Test {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        // 字符串输入
        String str = io.next();
        // int 输入
        int num = io.nextInt();
        // 输出
        io.println("Result");
        // 请确保关闭 IO 流以确保输出被正确写入
        io.close();
    }
}
```

### 使用 StreamTokenizer 作为输入

在某些情况使用 `StringTokenizer` 会导致 MLE（Memory Limit Exceeded，超过内存上限），此时我们需要使用 `StreamTokenizer` 作为输入。

```java
import java.io.*;
public class Main {
    // IO 代码
    public static StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in), 32768));
    public static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static double nextDouble() throws IOException { in.nextToken(); return in.nval; }
    public static float nextFloat() throws IOException { in.nextToken(); return (float)in.nval; }
    public static int nextInt() throws IOException { in.nextToken(); return (int)in.nval; }
    public static String next() throws IOException { return in.sval; }
    public static long nextLong() throws Exception { in.nextToken(); return (long)in.nval;}
    
    // 使用示例
    public static void main(String[] args) throws Exception {
        int n = nextInt();
        out.println(n);
        out.close();
    }
}
```

### Kattio + StringTokenizer 的方法与 StreamTokenizer 的方法之间的分析与对比

1. `StreamTokenizer` 相较于 `StringTokenizer` 使用的内存较少，当 Java 标程 MLE 时可以尝试使用 `StreamTokenizer`，但是 `StreamTokenizer` 会丢失精度，读入部分数据时会出现问题；
    - `StreamTokenizer` 源码存在 `Type`，该 `Type` 根据你输入内容来决定类型，倘若你输入类似于 `123oi` 以 **数字开头** 的字符串，他会强制认为你的类型是 `double` 类型，因此在读入中以 `double` 类型去读 `String` 类型便会抛出异常；
    - `StreamTokenizer` 在读入 `1e14` 以上大小的数字会丢失精度；
2. 在使用 `PrintWriter` 情况下，需注意在程序结束最后 `close()` 关闭输出流或在需要输出的时候使用 `flush()` 清除缓冲区，否则内容将不会被写入到控制台/文件中。
3. `Kattio` 是继承自 `PrintWriter` 类，自身对象具有了 `PrintWriter` 的功能，因此可以直接调用 `PrintWriter` 类的函数输出，同时将 `StringTokenizer` 作为了自身的成员变量来修改。而第二种 `Main` 是同时将 `StreamTokenizer` 与 `PrintWriter` 作为了自身的成员变量，因此在使用上有些许差距。

综上所述，在大部分情况下，`StringTokenizer` 的使用处境要优越于 `StreamTokenizer`，在极端 MLE 的情况下可以尝试 `StreamTokenizer`，同时 `int` 范围以上的数据 `StreamTokenizer` 处理是无能为力的。


## BigInteger 与数论

`BigInteger` 是 Java 提供的高精度计算类，可以很方便地解决高精度问题。

### 初始化

`BigInteger` 常用创建方式有如下二种：

```java
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) {
        BigInteger a = new BigInteger("12345678910");  // 将字符串以十进制的形式创建 BigInteger 对象
        out.println(a);  // a 的值为 12345678910 
        BigInteger b = new BigInteger("1E", 16);  // 将字符串以指定进制的形式创建 BigInteger 对象
        out.println(b);  // c 的值为 30 
        out.close();
    }
}

```

### 基本运算

以下均用 `this` 代替当前 `BigIntger` :

|          函数名           |                    功能                     |
|:-------------------------:|:-------------------------------------------:|
|           `abs()`           |             返回 this 的绝对值              |
|         `negate()`          |                 返回 - this                 |
|    `add(BigInteger val)`    |              返回 this `+` val              |
| `subtract(BigInteger val)`  |              返回 this `-` val              |
| `multiply(BigInteger val)`  |              返回 this `*` val              |
|  `divide(BigInteger val)`   |              返回 this `/` val              |
| `remainder(BigInteger val)` |              返回 this `%` val              |
|    `mod(BigInteger val)`    |             返回 this `mod` val             |
|        `pow(int e)`         |                返回 $this^e$                |
|    `and(BigInteger val)`    |              返回 this `&` val              |
|    `or(BigInteger val)`     |             返回 this `|` val              |
|           `not()`           |                返回 `~` this                |
|    `xor(BigInteger val)`    |              返回 this `^` val              |
|     `shiftLeft(int n)`      |              返回 this `<<` n               |
|     `shiftRight(int n)`     |              返回 this `>>` n               |
|    `max(BigInteger val)`    |          返回 this 与 val 的较大值          |
|    `min(BigInteger val)`    |          返回 this 与 val 的较小值          |
|        `bitCount()`         | 返回 this 的二进制中不包括符号位的 1 的个数 |
|        `bitLength()`        |   返回 this 的二进制中不包括符号位的长度    |
|     `getLowestSetBit()`     |      返回 this 的二进制中最右边的位置       |
| `compareTo(BigInteger val)` |           比较 this 和 val 值大小           |
|        `toString()`         |     返回 this 的 10 进制字符串表示形式      |
|    `toString(int radix)`。  |    返回 this 的 raidx 进制字符串表示形式    |

使用案例如下：

```java
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static BigInteger a, b;

    static void abs() {
        out.println("abs:");
        a = new BigInteger("-123");
        out.println(a.abs());  // 输出 123 
        a = new BigInteger("123");
        out.println(a.abs());  // 输出 123 
    }

    static void negate() {
        out.println("negate:");
        a = new BigInteger("-123");
        out.println(a.negate());  // 输出 123 
        a = new BigInteger("123");
        out.println(a.negate());  // 输出 -123 
    }

    static void add() {
        out.println("add:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.add(b));  // 输出 246 
    }

    static void subtract() {
        out.println("subtract:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.subtract(b));  // 输出 0 
    }

    static void multiply() {
        out.println("multiply:");
        a = new BigInteger("12");
        b = new BigInteger("12");
        out.println(a.multiply(b));  // 输出 144 
    }

    static void divide() {
        out.println("divide:");
        a = new BigInteger("12");
        b = new BigInteger("11");
        out.println(a.divide(b));  // 输出 1 
    }

    static void remainder() {
        out.println("remainder:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.remainder(b));  // 输出 2 
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.remainder(b));  // 输出 -2 
    }

    static void mod() {
        out.println("mod:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.mod(b));  // 输出 2 
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.mod(b));  // 输出 8 
    }

    static void pow() {
        out.println("pow:");
        a = new BigInteger("2");
        out.println(a.pow(10));  // 输出 1024 
    }

    static void and() {
        out.println("and:");
        a = new BigInteger("3");  // 11 
        b = new BigInteger("5");  // 101 
        out.println(a.and(b));  // 输出 1 
    }

    static void or() {
        out.println("or:");
        a = new BigInteger("2");  // 10 
        b = new BigInteger("5");  // 101 
        out.println(a.or(b));  // 输出 7 
    }

    static void not() {
        out.println("not:");
        a = new BigInteger("2147483647");  // 01111111 11111111 11111111 11111111 
        out.println(a.not());  // 输出 -2147483648 二进制为：10000000 00000000 00000000 00000000 
    }

    static void xor() {
        out.println("xor:");
        a = new BigInteger("6");  // 110 
        b = new BigInteger("5");  // 101 
        out.println(a.xor(b));  // 011 输出 3 
    }

    static void shiftLeft() {
        out.println("shiftLeft:");
        a = new BigInteger("1");
        out.println(a.shiftLeft(10));  // 输出 1024 
    }

    static void shiftRight() {
        out.println("shiftRight:");
        a = new BigInteger("1024");
        out.println(a.shiftRight(8));  // 输出 4 
    }

    static void max() {
        out.println("max:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.max(b));  // 输出 6 
    }

    static void min() {
        out.println("min:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.min(b));  // 输出 5 
    }

    static void bitCount() {
        out.println("bitCount:");
        a = new BigInteger("6");  // 110 
        out.println(a.bitCount());  // 输出 2 
    }

    static void bitLength() {
        out.println("bitLength:");
        a = new BigInteger("6");  // 110 
        out.println(a.bitLength());  // 输出 3 
    }

    static void getLowestSetBit() {
        out.println("getLowestSetBit:");
        a = new BigInteger("8");  // 1000 
        out.println(a.getLowestSetBit());  // 输出 3 
    }

    static void compareTo() {
        out.println("compareTo:");
        a = new BigInteger("8");
        b = new BigInteger("9");
        out.println(a.compareTo(b));  // 输出 -1 
        a = new BigInteger("8");
        b = new BigInteger("8");
        out.println(a.compareTo(b));  // 输出 0 
        a = new BigInteger("8");
        b = new BigInteger("7");
        out.println(a.compareTo(b));  // 输出 1 
    }

    static void toStringTest() {
        out.println("toString:");
        a = new BigInteger("15");
        out.println(a.toString());  // 输出 15 
        out.println(a.toString(16));  // 输出 f 
    }

    public static void main(String[] args) {
        abs();
        negate();
        add();
        subtract();
        multiply();
        divide();
        remainder();
        mod();
        pow();
        and();
        or();
        not();
        xor();
        shiftLeft();
        shiftRight();
        max();
        min();
        bitCount();
        bitLength();
        getLowestSetBit();
        compareTo();
        toStringTest();
        out.close();
    }
}
```

### 数学运算

以下均用 `this` 代替当前 `BigIntger` :

|               函数名               |                   功能                    |
|:----------------------------------:|:-----------------------------------------:|
|        `gcd(BigInteger val)`         | 返回 this 的绝对值与 val 的绝对值的最大公约数 |
|      `isProbablePrime(int val)`      |     返回一个表示 this 是否是素数的布尔值     |
|        `nextProbablePrime()`         |         返回第一个大于 this 的素数          |
| `modPow(BigInteger b, BigInteger p)` |          返回 this `^` b `mod` p           |
|      modInverse(BigInteger p)      |          返回 a `mod` p 的乘法逆元          |

使用案例如下：

```java
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static BigInteger a, b, p;

    static void gcd() {  // 最大公约数 
        a = new BigInteger("120032414321432144212100");
        b = new BigInteger("240231431243123412432140");
        out.println(String.format("gcd(%s,%s)=%s", a.toString(), b.toString(), a.gcd(b).toString()));  // gcd(120032414321432144212100,240231431243123412432140)=20 
    }

    static void isPrime() {  // 基于米勒罗宾判定该数是否是素数，参数越大准确性越高，复杂度越高。准确性为 (1-1/(val*2)) 
        a = new BigInteger("1200324143214321442127");
        out.println("a:" + a.toString());
        out.println(a.isProbablePrime(10) ? "a is prime" : "a is not prime");  // a is not prime 
    }

    static void nextPrime() {  // 找出该数的下一个素数 
        a = new BigInteger("1200324143214321442127");
        out.println("a:" + a.toString());
        out.println(String.format("a nextPrime is %s", a.nextProbablePrime().toString()));  // a nextPrime is 1200324143214321442199 
    }

    static void modPow() {  // 快速幂，比正常版本要快，内部有蒙特卡洛优化 
        a = new BigInteger("2");
        b = new BigInteger("10");
        p = new BigInteger("1000");
        out.println(String.format("a:%s b:%s p:%s", a, b, p));
        out.println(String.format("a^b mod p:%s", a.modPow(b, p).toString()));//  24 
    }

    static void modInverse() {  // 逆元 
        a = new BigInteger("10");
        b = new BigInteger("3");
        out.println(a.modInverse(b));  // a ^ (p-2) mod p = 1 
    }

    public static void main(String[] args) {
        gcd();
        isPrime();
        nextPrime();
        modPow();
        modInverse();
        out.close();
    }
}
```
关于米勒罗宾相关知识可以查阅[miller-rabin 素性测试](https://oi.wiki/math/number-theory/prime/#miller-rabin)。


## 基本数据类型与包装数据类型

### 简介

由于基本类型没有面向对象的特征，为了他们参加到面向对象的开发中，Java 为八个基本类型提供了对应的包装类，分别是 `Byte`、`Double`、`Float`、`Integer`、`Long`、`Short`、`Character` 和 `Boolean`。两者之间的对应关系如下：

|              基本数据类型             |                  包装数据类型                 |
|:------------------------------------:|:-------------------------------------------:|
|               `byte`                 |               `Byte`                        |
|               `short`                |               `Short`                       |
|               `boolean`              |               `Boolean`                     |
|               `char`                 |               `Character`                   |
|               `int`                  |               `Integer`                     |
|               `long`                 |               `Long`                        |
|               `float`                |               `Float`                       |
|               `double`               |               `Double`                      |

### 区别

此处以 `int` 与 `Integer` 举例：

1. `Integer` 是 `int` 的包装类，`int` 则是 Java 的一种基本类型数据。
2. `Integer` 类型实例后才能使用，而 `int` 类型不需要。
3. `Integer` 实际对应的引用，当 `new` 一个 `Integer` 时，实际上生成了一个对象，而 `int` 则是直接存储数据。
4. `Integer` 的默认值是 `null`，可接受 `null` 和 `int` 类型的数据， `int` 默认值是 0，不能接受 `null` 类型的数据。
5. `Integer` 判定二个变量是否相同使用 `==` 可能会导致不正确的结果，只能使用 `equals()`，而 `int` 可以直接使用 `==`。

### 装箱与拆箱

此处以 `int` 与 `Integer` 举例：

`Integer` 的本质是对象，`int` 是基本类型，两个类型之间是不能直接赋值的。需要转换时，应将基础类型转换为包装类型，这种做法称为装箱，反过来则称为拆箱。

```java
// 基本类型
int value1 = 1;
// 装箱转换为包装类型
Integer integer = Integer.valueOf(value1);
// 拆箱转换为基本类型
int value2 = integer.intValue();
```

Java 5 引入了自动装箱拆箱机制：

```java
Integer integer = 1;
int value = integer;
```

???+ warning "注意"
    虽然 JDK 增加了自动装箱拆箱的机制，但在声明变量时请选择合适的类型，因为包装类型 `Integer` 可以接受 `null`，而基本类型 `int` 不能接受 `null`。因此，对使用 `null` 值的包装类型进行拆箱操作时，会抛出异常。

```java
Integer integer = Integer.valueOf(null);
integer.intValue();  // 抛出 java.lang.NumberFormatException 异常

Integer integer = null;
integer.intValue();  // 抛出 java.lang.NullPointerException 异常
```

## 继承

基于已有的设计创造新的设计，就是面向对象程序设计中的继承。在继承中，新的类不是凭空产生的，而是基于一个已经存在的类而定义出来的。通过继承，新的类自动获得了基础类中所有的成员，包括成员变量和方法，包括各种访问属性的成员，无论是 `public` 还是 `private` 。显然，通过继承来定义新的类，远比从头开始写一个新的类要简单快捷和方便。继承是支持代码重用的重要手段之一。

在 Java 中，继承的关键字为 `extends`，且 Java 只支持单继承，但可以实现多接口。

在 Java 中，所有类都是 `Object` 类的子类。

子类继承父类，所有的父类的成员，包括变量和方法，都成为了子类的成员，除了构造方法。构造方法是父类所独有的，因为它们的名字就是类的名字，所以父类的构造方法在子类中不存在。除此之外，子类继承得到了父类所有的成员。

每个成员有不同的访问属性，子类继承得到了父类所有的成员，但是不同的访问属性使得子类在使用这些成员时有所不同：有些父类的成员直接成为子类的对外的界面，有些则被深深地隐藏起来，即使子类自己也不能直接访问。

下表列出了不同访问属性的父类成员在子类中的访问属性：

| 父类成员访问属性 |           在父类中的含义           |                                  在子类中的含义                                   |
|:----------------:|:----------------------------------:|:---------------------------------------------------------------------------------:|
|      `public`      |            对所有类开放            |                                   对所有人类开放                                    |
|    `protected`     | 只有包内其它类、自己和子类可以访问 |                        只有包内其它类、自己和子类可以访问                         |
|  缺省（`default`）   |       只有包内其它类可以访问       | 如果子类与父类在同一个包内，只有包内其它类可以访问；否则相当于 `private`，不能访问 |
|     `private`      |          只有自己可以访问          |                                     不能访问                                      |


## 多态

在 Java 中当把一个对象赋值给一个变量时，对象的类型必须与变量的类型相匹配。但由于 Java 有继承的概念，便可重新定义为 **一个变量可以保存其所声明的类型或该类型的任何子类型**。

如果一个类型实现了接口，也可以称之为该接口的子类型。

Java 中保存对象类型的变量是多态变量。“多态”这个术语（字面意思是许多形态）是指一个变量可以保存不同类型（即其声明的类型或任何子类型）的对象。

多态变量：

1. Java 的对象变量是多态的，它们能保存不止一种类型的对象。
2. 它们可以保存的是声明类型的对象，或声明类型子类的对象。
3. 当把子类的对象赋给父类的变量的时候，就发生了向上转型。


## 泛型

泛型指在类定义时不设置类中的属性或方法参数的具体类型，而是在使用（或创建对象）时再进行类型的定义。泛型本质是参数化类型，即所操作的数据类型被指定为一个参数。

泛型提供了编译时类型安全检测的机制，该机制允许编译时检测非法类型。


## 接口

### 简介

接口（英文：Interface）在 Java 中是一个抽象类型，是抽象方法的集合，通常以 `interface` 来声明。一个类通过实现接口的方式，从而来继承接口的抽象方法。

接口并不是类，编写接口的方式和类很相似，但是它们属于不同的概念。类描述对象的属性和方法。接口则包含类要实现的方法。

除非实现接口的类是抽象类，否则该类要定义接口中的所有方法。

接口无法被实例化，但是可以被实现。一个实现接口的类，必须实现接口内所描述的所有方法，否则就必须声明为抽象类。另外，在 Java 中，接口类型可用来声明一个变量，他们可以成为一个空指针，或是被绑定在一个以此接口实现的对象。

### 与类的区别

1. 接口不能用于实例化对象。
2. 接口没有构造方法。
3. 接口中所有的方法必须是抽象方法，Java 8 之后接口中可以使用 `default` 关键字修饰的非抽象方法。
4. 接口不能包含成员变量，除了 static 和 final 变量。
5. 接口不是被类继承了，而是要被类实现。
6. 接口支持多继承，类不支持多继承。

### 声明

```java
[可见度] interface 接口名称 [extends 其他的接口名] {
        // 声明变量
        // 抽象方法
}
```

### 实现

```java
...implements 接口名称[, 其他接口名称, 其他接口名称..., ...] ...
```

## Lambda 表达式

### 简介

lambda 表达式也可称为闭包，是 Java 8 的最重要的新特性。

lambda 表达式允许把函数作为一个方法的参数（函数作为参数传递进方法中）。

使用 lambda 表达式可以使代码变的更加简洁紧凑。

### 语法

**可选类型声明**：不需要声明参数类型，编译器可以统一识别参数值。

**可选的参数圆括号**：一个参数无需定义圆括号，但多个参数需要定义圆括号。

**可选的大括号**：如果主体包含了一个语句，就不需要使用大括号。

**可选的返回关键字**：如果主体只有一个表达式返回值则编译器会自动返回值，大括号需要指定表达式返回了一个数值。

lambda 表达式声明方式如下：

以字符串数组按长度排序的自定义比较器为例：

1. 参数，箭头，一个表达式。
```java
import java.util.Arrays;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) {
        String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        Arrays.sort(plants, (String first, String second) -> (first.length() - second.length()));
        for (String word : plants) {
            out.print(word + " ");
        }
        out.close();
    }
}
```

2. 参数，箭头，多条语句。
```java
import java.io.PrintWriter;
import java.util.Arrays;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) {
        String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        Arrays.sort(plants, (first, second) ->
        {
            // 形参不写类型，可以从上下文判断出
            int result = first.length() - second.length();
            return result;
        });
        for (String word : plants) {
            out.print(word + " ");
        }
        out.close();
    }
}
```

`->` 是一个推导符号，表示前面的括号接收到参数，推导后面的返回值（其实就是传递了方法）。

3. 常用形式：

```java
// 1. 不需要参数，返回值为 5
() -> 5

// 2. 接收一个参数（数字类型），返回其 2 倍的值
x -> 2 * x

// 3. 接受 2 个参数（数字）并返回他们的差值
(x, y) -> x – y

// 4. 接收 2 个 int 类型整数并返回他们的和
(int x, int y) -> x + y

// 5. 接受一个 String 对象并在控制台打印，不返回任何值（看起来像是返回 void）
(String s) -> System.out.print(s)
```

### 函数式接口

1. 是一个接口，符合 Java 接口定义。
2. 只包含一个抽象方法的接口。
3. 因为只有一个未实现的方法，所以 lambda 表达式可以自动填上去。

函数式接口使用方式如下：
1. 输出长度为 2 的倍数的字符串。

```java
import java.io.PrintWriter;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) {
        String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        Test test = s -> {  // lambda 表达式作为函数式接口的实例
            if (s.length() % 2 == 0) {
                return true;
            }
            return false;
        };
        for (String word : plants) {
            if (test.check(word)) {
                out.print(word + " ");
            }
        }
        out.close();
    }
}

interface Test {
    public boolean check(String s);
}
```
2. 实现加减乘除四则运算。
```java
import java.io.PrintWriter;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    public static double calc(double a, double b, Calculator util) {
        return util.operation(a, b);
    }

    public static void main(String[] args) {
        Calculator util[] = new Calculator[4];  // 定义函数式接口数组
        util[0] = (a, b) -> a + b;
        util[1] = (a, b) -> a - b;
        util[2] = (a, b) -> a * b;
        util[3] = (a, b) -> a / b;
        double a = 20, b = 15;
        for (Calculator c : util) {
            System.out.println(calc(a, b, c));
        }
        out.close();
    }
}

interface Calculator {
    public double operation(double a, double b);
}
```


## Collection

`Collection` 是 Java 中的接口，被多个泛型容器接口所实现。在这里，`Collection` 是指代存放对象类型的数据结构。

Java 中的 `Collection` 元素类型定义时必须为对象，不能为基本数据类型。

以下内容用法均基于 Java 里多态的性质，均是以实现接口的形式出现。

常用的接口包括 `List`、`Queue`、`Set` 和 `Map`。

### 容器定义

1. 当定义泛型容器类时，需要在定义时指定数据类型。

例如：

```java
List<Integer> list1 = new LinkedList<>();
```

2. 倘若不指定数据类型，而当成 `Object` 类型随意添加数据，在 Java 8 中虽能编译通过，但会有很多警告风险。

例如:

```java
List list = new ArrayList<>();
list.add(1);
list.add(true);
list.add(1.01);
list.add(1L);
list.add("I am String");
```

因此，如果没有特殊需求的话不推荐第 2 种行为，编译器无法帮忙检查存入的数据是否安全。`list.get(index)` 取值时无法明确数据的类型（取到的数据类型都为 `Object`），需要手动转回原来的类型，稍有不慎可能出现误转型异常。

如果是明确了类型如 `List<Integer>`，此时编译器会检查放入的数据类型，只能放入整数的数据。声明集合变量时只能使用包装类型 `List<Integer>` 或者自定义的 `Class`，而不能是基本类型如 `List<int>`。

### List

#### ArrayList

`ArrayList` 是支持可以根据需求动态生长的数组，初始长度默认为 10。如果超出当前长度便扩容 $\dfrac{3}{2}$。

##### 初始化

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) {
        List<Integer> list1 = new ArrayList<>();  // 创建一个名字为 list1 的可自增数组，初始长度为默认值（10）
        List<Integer> list2 = new ArrayList<>(30);  // 创建一个名字为list2的可自增数组，初始长度为 30
        List<Integer> list3 = new ArrayList<>(list2);  // 创建一个名字为 list3 的可自增数组，使用 list2 里的元素和 size 作为自己的初始值
    }
}
```

#### LinkedList

`LinkedList` 是双链表。

##### 初始化

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    public static void main(String[] args) {
        List<Integer> list1 = new LinkedList<>();  // 创建一个名字为 list1 的双链表 
        List<Integer> list2 = new LinkedList<>(list1);  // 创建一个名字为 list2 的双链表，将 list1 内所有元素加入进来 
    }
}
```

#### 常用方法

以下均用 `this` 代替当前 `List<Integer>`：

|         函数名          |                   功能                    |
|:-----------------------:|:-----------------------------------------:|
|         `size()`          |             返回 this 的长度              |
|    `add(Integer val)`     |          在 this 尾部插入一个元素           |
| `add(int idx, Integer e)` |        在 this 指定位置插入一个元素         |
|      `get(int idx)`       | 返回 this 中第 idx 位置的值，若越界则抛出异常 |
| `set(int idx, Integer e)` |          修改 this 中第 idx 位置的值          |

使用案例及区别对比：

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static List<Integer> array = new ArrayList<>();
    static List<Integer> linked = new LinkedList<>();

    static void add() {
        array.add(1);  // 时间复杂度为 O(1) 
        linked.add(1);  // 时间复杂度为 O(1) 
    }

    static void get() {
        array.get(10);  // 时间复杂度为 O(1) 
        linked.get(10);  // 时间复杂度为 O(11) 
    }

    static void addIdx() {
        array.add(0, 2);  // 最坏情况下时间复杂度为 O(n)
        linked.add(0, 2);  // 最坏情况下时间复杂度为 O(n)
    }

    static void size() {
        array.size();  // 时间复杂度为 O(1)
        linked.size();  // 时间复杂度为 O(1)
    }

    static void set() {  // 该方法返回值为原本该位置元素的值
        array.set(0, 1);  // 时间复杂度为 O(1)
        linked.set(0, 1);  // 最坏时间复杂度为 O(n)
    }

}
```

#### 遍历

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static List<Integer> array = new ArrayList<>();
    static List<Integer> linked = new LinkedList<>();
    
    static void function1() {  // 朴素遍历
        for (int i = 0; i < array.size(); i++) {
            out.println(array.get(i));  // 遍历自增数组，复杂度为 O(n)
        }
        for (int i = 0; i < linked.size(); i++) {
            out.println(linked.get(i));  // 遍历双链表，复杂度为 O(n^2)，因为 LinkedList 的 get(i) 复杂度是 O(i)
        }
    }

    static void function2() {  // 增强 for 循环遍历 
        for (int e : array) {
            out.println(e);
        }
        for (int e : linked) {
            out.println(e);  // 复杂度均为 O(n) 
        }
    }

    static void function3() {  // 迭代器遍历 
        Iterator<Integer> iterator1 = array.iterator();
        Iterator<Integer> iterator2 = linked.iterator();
        while (iterator1.hasNext()) {
            out.println(iterator1.next());
        }
        while (iterator2.hasNext()) {
            out.println(iterator2.next());
        }  // 复杂度均为 O(n) 
    }

}
```

???+ warning "注意"
    不要在 `for/foreach` 遍历 `List` 的过程中删除其中的元素，否则会抛出异常。
  
    原因也很简单，`list.size()` 改变了，但在循环中已循环的次数却是没有随之变化。原来预计在下一个 `index` 的数据因为删除的操作变成了当前 `index` 的数据，运行下一个循环时操作的会变为原来预计在下下个 `index` 的数据，最终会导致操作的数据不符合预期。

### Queue

#### LinkedList

可以使用 `LinkedList` 实现普通队列。

##### 初始化

```java
Queue<Integer> q = new LinkedList<>();
```

`LinkedList` 底层实现了 `List` 接口与 `Deque` 接口，而 `Deque` 接口继承自 `Queue` 接口，所以 `LinkedList` 可以同时实现 `List` 与 `Queue` 。

#### PriorityQueue

`PriorityQueue` 是优先队列，默认是小根堆。

##### 初始化

```java
Queue<Integer> q1 = new PriorityQueue<>();  // 小根堆
Queue<Integer> q2 = new PriorityQueue<>((x, y) -> {return y - x;});  // 大根堆
```

#### 常用方法

以下均用 `this` 代替当前 `Queue<Integer>` :

|       函数名       |               功能               |
|:------------------:|:--------------------------------:|
|       `size()`      |         返回 this 的长度         |
|  `add(Integer val)`  |               入队               |
| `offer(Integer val)` |               入队               |
|     `isEmpty()`      | 判断队列是否为空，为空则返回 true |
|       `peek()`       |           返回队头元素           |
|       `poll()`       |        返回队头元素并删除        |

使用案例及区别对比：

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Queue<Integer> q1 = new LinkedList<>();
    static Queue<Integer> q2 = new PriorityQueue<>();

    static void add() {  // add 和 offer 功能上没有差距，区别是是否会抛出异常 
        q1.add(1);  // 时间复杂度为 O(1) 
        q2.add(1);  // 时间复杂度为 O(logn) 
    }

    static void isEmpty() {
        q1.isEmpty();  // 时间复杂度为 O(1) 
        q2.isEmpty();  // 空间复杂度为 O(1) 
    }

    static void size() {
        q1.size();  // 时间复杂度为 O(1) 
        q2.size();  // 返回 q2 的长度 
    }

    static void peek() {
        q1.peek();  // 时间复杂度为 O(1) 
        q2.peek();  // 时间复杂度为 O(logn) 
    }

    static void poll() {
        q1.poll();  // 时间复杂度为 O(1) 
        q2.poll();  // 时间复杂度为 O(logn) 
    }
}
```

#### 遍历

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Queue<Integer> q1 = new LinkedList<>();
    static Queue<Integer> q2 = new PriorityQueue<>();

    static void test() {
        while (!q1.isEmpty()) {  // 复杂度为 O(n) 
            out.println(q1.poll());
        }
        while (!q2.isEmpty()) {  // 复杂度为 O(nlogn) 
            out.println(q2.poll());
        }
    }

}
```

### Set

`Set` 是保持容器中的元素不重复的一种数据结构。

#### HashSet

随机位置插入的 `Set`。

##### 初始化

```java
Set<Integer> s1 = new HashSet<>();
```

#### LinkedHashSet

保持插入顺序的 `Set`。

##### 初始化

```java
Set<Integer> s2 = new LinkedHashSet<>();
```

#### TreeSet

保持容器中元素有序的 `Set`，默认为升序。

##### 初始化

```java
Set<Integer> s3 = new TreeSet<>();
Set<Integer> s4 = new TreeSet<>((x, y) -> {return y - x;});  // 降序 
```

#### 常用方法

以下均用 `this` 代替当前 `Set<Integer>` :

|         函数名          |               功能               |
|:-----------------------:|:--------------------------------:|
|         `size()`          |         返回 this 的长度         |
|    `add(Integer val)`     |        插入一个元素进 this        |
|  `contains(Integer val)`  |     判断 this 中是否有元素 val      |
|  `addAll(Collection e)`   | 将一个容器里的所有元素添加进 this |
| `retainAll(Collection e)` |  将 this 改为两个容器内相同的元素  |
| `removeAll(Collection e)` |    将 this 中与 e 相同的元素删除     |

使用案例：求并集、交集、差集。

```java
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Set<Integer> s1 = new HashSet<>();
    static Set<Integer> s2 = new LinkedHashSet<>();

    static void add() {
        s1.add(1);
    }

    static void contains() {  // 判断 set 中是否有元素值为 2，有则返回 true，否则返回 false 
        s1.contains(2);
    }

    static void test1() {  // s1 与 s2 的并集 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.addAll(s2);
    }

    static void test2() {  // s1 与 s2 的交集 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.retainAll(s2);
    }

    static void test3() {  // 差集：s1 - s2 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.removeAll(s2);
    }
}
```

#### 遍历

```java
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Set<Integer> s1 = new HashSet<>();
    static Set<Integer> s2 = new LinkedHashSet<>();

    static void test() {
        for (int key : s1) {
            out.println(key);
        }
        out.close();
    }
}
```

### Map

`Map` 是维护键值对 `<Key, Value>` 的一种数据结构，其中 `Key` 唯一。

#### HashMap

随机位置插入的 `Map`。

##### 初始化

```java
Map<Integer, Integer> map1 = new HashMap<>();
```

#### LinkedHashMap

保持插入顺序的 `Map`。

##### 初始化

```java
Map<Integer, Integer> map2 = new LinkedHashMap<>();
```

#### TreeMap

保持 `key` 有序的 `Map`，默认升序。

##### 初始化

```java
Map<Integer, Integer> map3 = new TreeMap<>();
Map<Integer, Integer> map4 = new TreeMap<>((x, y) -> {return y - x;});  // 降序
```

#### 常用方法

以下均用 `this` 代替当前 `Map<Integer, Integer>`：

|             函数名             |               功能                |
|:------------------------------:|:---------------------------------:|
| `put(Integer key, Integer value)` |        插入一个元素进 this         |
|             `size()`             |          返回 this 的长度           |
|    `containsKey(Integer val)`    |   判断 this 中是否有元素 key 为 val    |
|        `get(Integer key)`        |   将 this 中对应的 key 的 value 返回    |
|             `keySet`             | 将 this 中所有元素的 key 作为集合返回 |

使用案例:

```java
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    static Map<Integer, Integer> map1 = new HashMap<>();
    static Map<Integer, Integer> map2 = new LinkedHashMap<>();
    static Map<Integer, Integer> map3 = new TreeMap<>();
    static Map<Integer, Integer> map4 = new TreeMap<>((x,y)->{return y-x;});

    static void put(){  // 将 key 为 1、value 为 1 的元素返回
        map1.put(1, 1);
    }
    static void get(){  // 将 key 为 1 的 value 返回
        map1.get(1);
    }
    static void containsKey(){  // 判断是否有 key 为 1 的键值对
        map1.containsKey(1);
    }
    static void KeySet(){
        map1.keySet();
    }
}
```

#### 遍历

```java
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    static Map<Integer, Integer> map1 = new HashMap<>();

    static void print() {
        for (int key : map1.keySet()) {
            out.println(key + " " + map1.get(key));
        }
    }
}
```

当然，在面向对象的世界里，你的参数是什么都可以，包括 `Collection` 与自定义类型。

例如 `Map` 也可以定义为：

```java
Map<String, Set<Integer>> map = new HashMap<>();
```

## Arrays

`Arrays` 是 `java.util` 中对数组操作的一个工具类。方法均为静态方法，可使用类名直接调用。

### Arrays.sort()

`Arrays.sort()` 是对数组进行的排序的方法，主要重载方法如下：

```java
import java.util.Arrays;
import java.util.Comparator;

public class Main {
    static int a[] = new int[10];
    static Integer b[] = new Integer[10];
    static int firstIdx, lastIdx;

    public static void main(String[] args) {
        Arrays.sort(a);  // 1 
        Arrays.sort(a, firstIdx, lastIdx);  // 2 
        Arrays.sort(b, new Comparator<Integer>() {  // 3 
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        Arrays.sort(b, firstIdx, lastIdx, new Comparator<Integer>() {  // 4 
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        // 由于 Java 8 后有 Lambda 表达式，第三个重载及第四个重载亦可写为 
        Arrays.sort(b, (x, y) -> {  // 5 
            return y - x;
        });
        Arrays.sort(b, (x, y) -> {  // 6 
            return y - x;
        });
    }
}
```

**序号所对应的重载方法含义：**

1. 对数组 a 进行排序，默认升序。
2. 对数组 a 的指定位置进行排序，默认升序，排序区间为左闭右开 `[firstIdx, lastIdx)`。
3. 对数组 a 以自定义的形式排序，第二个参数 `-` 第一个参数为降序,第一个参数 `-` 第二个参数为升序，当自定义排序比较器时，数组元素类型必须为对象类型。
4. 对数组 a 的指定位置进行自定义排序，排序区间为左闭右开 `[firstIdx, lastIdx)`，当自定义排序比较器时，数组元素类型必须为对象类型。
5. 和 3 同理，用 Lambda 表达式优化了代码长度。
6. 和 4 同理，用 Lambda 表达式优化了代码长度。

**`Arrays.sort()` 底层函数：**

1. 当你 `Arrays.sort` 的参数数组元素类型为基本数据类型（`byte`、`short`、`char`、`int`、`long`、`double`、`float`）时，默认为 `DualPivotQuicksort`（双轴快排），复杂度最坏可以达到 $O(n^2)$。
2. 当你 `Arrays.sort` 的参数数组元素类型为非基本数据类型时），则默认为 `legacyMergeSort` 和 `TimSort` (归并排序），复杂度为$O(nlog_n)$。

可以通过如下代码验证：

???+note "[Codeforces 1646B - Quality vs Quantity](https://codeforces.com/problemset/problem/1646/B)"
    题意概要：有 $n$ 个数，你需要将其分为 2 组，是否能存在 1 组的长度小于另 1 组的同时和大于它。

??? note "例题代码"
    ```java
    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.io.PrintWriter;
    import java.util.Arrays;
    import java.util.StringTokenizer;
    
    public class Main {
        static class FastReader {
            StringTokenizer st;
            BufferedReader br;
    
            public FastReader() {
                br = new BufferedReader(new InputStreamReader(System.in));
            }
    
            String next() {
                while (st == null || !st.hasMoreElements()) {
                    try {
                        st = new StringTokenizer(br.readLine());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                return st.nextToken();
            }
    
            int nextInt() {
                return Integer.parseInt(next());
            }
    
            long nextLong() {
                return Long.parseLong(next());
            }
    
            double nextDouble() {
                return Double.parseDouble(next());
            }
    
            String nextLine() {
                String str = "";
                try {
                    str = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return str;
            }
        }
    
        static PrintWriter out = new PrintWriter(System.out);
        static FastReader in = new FastReader();
    
        static void solve() {
            int n = in.nextInt();
            Integer a[] = new Integer[n + 10];
            for (int i = 1; i <= n; i++) {
                a[i] = in.nextInt();
            }
            Arrays.sort(a, 1, n + 1);
            long left = a[1];
            long right = 0;
            int x = n;
            for (int i = 2; i < x; i++, x--) {
                left = left + a[i];
                right = right + a[x];
                if (right > left) {
                    out.println("YES");
                    return;
                }
            }
            out.println("NO");
        }
    
        public static void main(String[] args) {
            int t = in.nextInt();
            while (t-- > 0) {
                solve();
            }
            out.close();
        }
    }
    ```

如果你将以上代码的 a 数组类型由 `Integer` 修改为 `int`，会导致 TLE。

### Arrays.binarySearch()

`Arrays.binarySearch()` 是对数组连续区间进行二分搜索的方法，前提是数组必须有序，时间复杂度为 $O(\log_n)$，主要重载方法如下：

```java
import java.util.Arrays;

public class Main {
    static int a[] = new int[10];
    static Integer b[] = new Integer[10];
    static int firstIdx, lastIdx;
    static int key;

    public static void main(String[] args) {
        Arrays.binarySearch(a, key);  // 1 
        Arrays.binarySearch(a, firstIdx, lastIdx, key);  // 2 
    }
}
```

源码如下：

```java
 private static int binarySearch0(int[] a, int fromIndex, int toIndex, int key) {
        int low = fromIndex;
        int high = toIndex - 1;

        while (low <= high) {
            int mid = (low + high) >>> 1;
            int midVal = a[mid];

            if (midVal < key)
                low = mid + 1;
            else if (midVal > key)
                high = mid - 1;
            else
                return mid; // key found
        }
        return -(low + 1);  // key not found.
    }
```

**序号所对应的重载方法含义：**

1. 从数组 a 中二分查找是否存在 `key`，如果存在，便返回其下标。若不存在，则返回一个负数。
2. 从数组 a 中二分查找是否存在 `key`，如果存在，便返回其下标,搜索区间为左闭右开 `[firstIdx,lastIdx)`。若不存在，则返回一个负数。

### Arrays.fill()

`Arrays.fill()` 方法将数组中连续位置的元素赋值为统一元素。其接受的参数为数组、`fromIndex`、`toIndex` 和需要填充的数。方法执行后，数组左闭右开区间 `[firstIdx,lastIdx)` 内的所有元素的值均为需要填充的数。

## Collections

`Collections` 是 `java.util` 中对集合操作的一个工具类。方法均为静态方法，可使用类名直接调用。

### Collections.sort()

`Collections.sort()` 底层原理为将其中所有元素转化为数组调用 `Arrays.sort()`，完成排序后再赋值给原本的集合。又因为 Java 中 `Collection` 的元素类型均为对象类型，所以始终是归并排序去处理。

该方法无法对集合指定区间排序。

底层源码：

```java
  default void sort(Comparator<? super E> c) {
        Object[] a = this.toArray();
        Arrays.sort(a, (Comparator) c);
        ListIterator<E> i = this.listIterator();
        for (Object e : a) {
            i.next();
            i.set((E) e);
        }
    }
```

### Collections.binarySearch()

`Collections.binarySearch()` 是对集合中指定区间进行二分搜索,功能与 `Arrays.binarySearch()` 相同。

```java
Collections.binarySearch(list, key);
```

该方法无法对指定区间进行搜索。

### Collections.swap()

`Collections.swap()` 的功能是交换集合中指定二个位置的元素。

```java
 Collections.swap(list, i, j);
```

## 其他

### 1. -0.0 != 0.0

在 Java 中，如果单纯是数值类型，-0.0 = 0.0 。若是对象类型，则 -0.0 != 0.0 。倘若你尝试用 `Set` 统计斜率数量时，这个问题就会带来麻烦。
提供的解决方式是在所有的斜率加入 `Set` 前将值增加 0.0。

```java
import java.io.PrintWriter;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);

    static void A() {
        Double a = 0.0;
        Double b = -0.0;
        out.println(a.equals(b));  // false 
    }

    static void B() {
        Double a = 0.0;
        Double b = -0.0 + 0.0;
        out.println(a.equals(b));  // true 
    }

    static void C() {
        double a = 0.0;
        double b = -0.0;
        out.println(a == b);  // true 
    }


    public static void main(String[] args) {
        A();
        B();
        C();
        out.close();
    }
}
```
## 参考资料

[^ref1]: [Input & Output - USACO Guide](https://usaco.guide/general/input-output?lang=java#method-3---io-template)
