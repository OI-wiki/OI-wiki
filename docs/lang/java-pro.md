# java 进阶

以下内容均是基于 jdk8 的版本，不排除在更高版本中有部分的改动可能性

## 详解快速读入与写入

`Scanner` 与 `System.out.print` 在读入大量数据的情况下效率很低，因此引入 `StringTokenizer` 与 `StreamTokenizer` 来提高输入效率，引入 `PrintWriter` 来提高输出效率。
关于基础知识可以参考 java 速成部分

### StringTokenizer 与 StreamTokenizer

如果你不想深究背后的原理，初学时可以直接将这个“框架”背下来

#### 代码框架 StringTokenizer

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;
class Main{
    static class FastReader{
        StringTokenizer st;
        BufferedReader br;
        public FastReader(){
            br=new BufferedReader(new InputStreamReader(System.in));
        }
        String next(){
            while (st==null||!st.hasMoreElements()){
                try {
                    st=new StringTokenizer(br.readLine());
                }catch (IOException e){
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
    static void solve(){
       //do something
       int x=in.nextInt();
       out.println(x);
    }
    public static void main(String[] args) {
        int t=1;
        while (t-->0){
            solve();
        }
        out.flush();
    }
    static PrintWriter out = new PrintWriter(System.out);
    static FastReader in = new FastReader();
}
```

#### 代码框架 StreamTokenizer

```java
import java.io.*;
public class Main {
    public static StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in),32768));
    public static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static double nextDouble() throws IOException{ in.nextToken(); return in.nval; }
    public static float nextFloat() throws IOException{ in.nextToken(); return (float)in.nval; }
    public static int nextInt() throws IOException { in.nextToken(); return (int)in.nval; }
    public static String next() throws IOException{
        return in.sval;
    }
    public static long nextLong() throws Exception{ in.nextToken();return (long)in.nval;}
    public static void main(String[] args) throws Exception{
        //do something
        int n=nextInt();
        out.println(n);
        out.flush();
    }
}
```

#### StringTokenizer 与 StreamTokenizer 和 PrintWriter 的分析与对比

1.  `StreamTokenizer` 相较于 `StringTokenizer` 内存较小，速度较快，可忽略不计，但是 `StreamTokenizer` 会丢精度，读入部分数据会出现问题；
    - `StreamTokenizer` 源码存在 Type，该 Type 根据你输入内容来决定类型，倘若你输入类似于 `123oi` 以 **数字开头** 的字符串，他会强制认为你的类型是 double 类型，因此在读入中以 double 类型去读 String 类型便会抛出异常；
    - `StreamTokenizer` 在读入 1e14 以上大小的数字会丢失精度；
2. 在使用 `PrintWriter` 情况下，需注意在程序结束最后 flush 清除缓冲区，否则控制台将会没有输出。

## 排序

关于 java 中 sort 函数的具体使用方法会在 `Arrays` 部分与 `Collections` 部分给出详细内容，该部分主要是对 `Arrays.sort(int[])` 与 `Arrays.sort(Integer[])` 的探讨。
在 java 中，`Arrays.sort(int[])` 底层是双端快排，`Arrays.sort(Integer[])` 底层是归并排序。因此 `Arrays.sort(int[])` 的最坏时间复杂度是 $O(n^2)$，可以通过如下例题来验证。

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

public class Main{
    static class FastReader{
        StringTokenizer st;
        BufferedReader br;
        public FastReader(){
            br=new BufferedReader(new InputStreamReader(System.in));
        }

        String next(){
            while (st==null||!st.hasMoreElements()){
                try {
                    st=new StringTokenizer(br.readLine());
                }catch (IOException e){
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
    static void solve(){
        int n=in.nextInt();
        Integer a[]=new Integer[n+10];
        for(int i=1;i<=n;i++){
            a[i]=in.nextInt();
        }
        Arrays.sort(a,1,n+1);
        long left=a[1];
        long right=0;
        int x=n;
        for(int i=2;i<x;i++,x--){
            left=left+a[i];
            right=right+a[x];
            if(right>left) {
                out.println("YES");
                return;
            }
        }out.println("NO");
    }
    public static void main(String[] args) {
        int t=in.nextInt();
        while (t-->0){
            solve();
            out.flush();
        }
    }
}
```

如果你将以上代码的 a 数组类型由 `Integer` 修改为 `int` 则会 TLE

## BigInteger 与数论

## 数据结构

### List

### Queue

### Set

### Map

## Arrays

## Collections

## 其他
