# Java 进阶

以下内容均是基于 Jdk8 的版本，不排除在更高版本中有部分的改动可能性

## 排序

关于 Java 中 sort 函数的具体使用方法会在 `Arrays` 部分与 `Collections` 部分给出详细内容，该部分主要是对 `Arrays.sort(int[])` 与 `Arrays.sort(Integer[])` 的探讨。
在 Java 中，`Arrays.sort(int[])` 底层是双端快排，`Arrays.sort(Integer[])` 底层是归并排序。因此 `Arrays.sort(int[])` 的最坏时间复杂度是 $O(n^2)$，可以通过如下例题来验证。

???+note "[[codeforces]Quality vs Quantity](https://www.luogu.com.cn/problem/P1216)"
    题意概要：有 $n$ 个数，你需要将其分为 2 组，是否能存在 1 组的长度小于另 1 组的同时和大于它。

??? 例题代码


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
            out.flush();
        }
    }
}
```

如果你将以上代码的 a 数组类型由 `Integer` 修改为 `int` 则会 TLE

## BigInteger 与数论

`BigInteger` 是 Java 提供的高精度计算类，可以很方便的解决高精度问题。

### 创建对象

BigInteger 常用创建方式有如下二种：

```java
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) {
        BigInteger a = new BigInteger("12345678910");//将字符串以10进制的形式创建BigInteger对象
        out.println(a);//a的值为 12345678910
        BigInteger b = new BigInteger("1E", 16);//将字符串以指定进制的形式创建BigInteger对象
        out.println(b);//c的值为 30
        out.flush();
    }
}

```

### 基本运算

以下均用 this 代替当前 BigIntger :

|            函数名            |             功能             |       |
| :-----------------------: | :------------------------: | ----- |
|           abs()           |        返回 this 的绝对值        |       |
|          negate()         |          返回 - this         |       |
|    add(BigInteger val)    |       返回 this `+` val      |       |
|  subtract(BigInteger val) |       返回 this `-` val      |       |
|  multiply(BigInteger val) |       返回 this `*` val      |       |
|   divide(BigInteger val)  |       返回 this `/` val      |       |
| remainder(BigInteger val) |       返回 this `%` val      |       |
|    mod(BigInteger val)    |   返回 this mod val 总是返回非负数  |       |
|         pow(int e)        |         返回 $this^e$        |       |
|    and(BigInteger val)    |       返回 this `&` val      |       |
|     or(BigInteger val)    |          返回 this\`         | \`val |
|           not()           |         返回 `~` this        |       |
|    xor(BigInteger val)    |       返回 this `^` val      |       |
|      shiftLeft(int n)     |       返回 this `<<` n       |       |
|     shiftRight(int n)     |       返回 this `>>` n       |       |
|    max(BigInteger val)    |     返回 this 与 val 的较大值     |       |
|    min(BigInteger val)    |     返回 this 与 val 的较小值     |       |
|         bitCount()        | 返回 this 的二进制中不包括符号位的 1 的个数 |       |
|        bitLength()        |   返回 this 的二进制中不包括符号位的长度   |       |
|     getLowestSetBit()     |     返回 this 的二进制中最右边的位置    |       |
| compareTo(BigInteger val) |      比较 this 和 val 值大小     |       |
|         toString()        |   返回 this 的 10 进制字符串表示形式   |       |
|    toString(int radix)    |  返回 this 的 raidx 进制字符串表示形式 |       |

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
        out.println(a.abs());//输出 123
        a = new BigInteger("123");
        out.println(a.abs());//输出 123
    }

    static void negate() {
        out.println("negate:");
        a = new BigInteger("-123");
        out.println(a.negate());//输出 123
        a = new BigInteger("123");
        out.println(a.negate());//输出 -123
    }

    static void add() {
        out.println("add:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.add(b));//输出 246
    }

    static void subtract() {
        out.println("subtract:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.subtract(b));//输出 0
    }

    static void multiply() {
        out.println("multiply:");
        a = new BigInteger("12");
        b = new BigInteger("12");
        out.println(a.multiply(b));//输出 144
    }

    static void divide() {
        out.println("divide:");
        a = new BigInteger("12");
        b = new BigInteger("11");
        out.println(a.divide(b));//输出 1
    }

    static void remainder() {
        out.println("remainder:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.remainder(b));//输出 2
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.remainder(b));//输出 -2
    }

    static void mod() {
        out.println("mod:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.mod(b));//输出 2
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.mod(b));//输出 8
    }

    static void pow() {
        out.println("pow:");
        a = new BigInteger("2");
        out.println(a.pow(10));//输出1024
    }

    static void and() {
        out.println("and:");
        a = new BigInteger("3"); // 11
        b = new BigInteger("5"); //101
        out.println(a.and(b));//输出1
    }

    static void or() {
        out.println("or:");
        a = new BigInteger("2"); // 10
        b = new BigInteger("5"); //101
        out.println(a.or(b));//输出7
    }

    static void not() {
        out.println("not:");
        a = new BigInteger("2147483647"); // 01111111 11111111 11111111 11111111
        out.println(a.not());//输出-2147483648 二进制为：10000000 00000000 00000000 00000000
    }

    static void xor() {
        out.println("xor:");
        a = new BigInteger("6");//110
        b = new BigInteger("5");//101
        out.println(a.xor(b));//011 输出3
    }

    static void shiftLeft() {
        out.println("shiftLeft:");
        a = new BigInteger("1");
        out.println(a.shiftLeft(10));// 输出1024
    }

    static void shiftRight() {
        out.println("shiftRight:");
        a = new BigInteger("1024");
        out.println(a.shiftRight(8));//输出4
    }

    static void max() {
        out.println("max:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.max(b));//输出6
    }

    static void min() {
        out.println("min:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.min(b));//输出5
    }

    static void bitCount() {
        out.println("bitCount:");
        a = new BigInteger("6");//110
        out.println(a.bitCount());//输出2
    }

    static void bitLength() {
        out.println("bitLength:");
        a = new BigInteger("6");//110
        out.println(a.bitLength());//输出3
    }

    static void getLowestSetBit() {
        out.println("getLowestSetBit:");
        a = new BigInteger("8");//1000
        out.println(a.getLowestSetBit());//输出3
    }

    static void compareTo() {
        out.println("compareTo:");
        a = new BigInteger("8");
        b = new BigInteger("9");
        out.println(a.compareTo(b)); //输出 -1
        a = new BigInteger("8");
        b = new BigInteger("8");
        out.println(a.compareTo(b)); //输出 0
        a = new BigInteger("8");
        b = new BigInteger("7");
        out.println(a.compareTo(b)); //输出 1
    }

    static void toStringTest() {
        out.println("toString:");
        a = new BigInteger("15");
        out.println(a.toString());//输出15
        out.println(a.toString(16));//输出f
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
        out.flush();
    }
}

```

### 数学运算

以下均用 this 代替当前 BigIntger :

## 数据结构

### List

### Queue

### Set

### Map

## Arrays

## Collections

## 其他
