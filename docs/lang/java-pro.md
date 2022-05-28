# java 进阶

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

## BigInteger 与数论

## 数据结构

### List

### Queue

### Set

### Map

## Arrays 与 Collections

## 其他
