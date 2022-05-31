# java 进阶

以下内容均是基于 jdk8 的版本，不排除在更高版本中有部分的改动可能性

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
