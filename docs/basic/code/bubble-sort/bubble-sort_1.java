import java.util.Scanner;

class Main {
    // --8<-- [start:core]
    // 假设数组的大小是 n + 1，冒泡排序从数组下标 1 开始
    static void bubble_sort(int[] a, int n) {
        boolean flag = true;
        while (flag) {
            flag = false;
            for (int i = 1; i < n; i++) {
                if (a[i] > a[i + 1]) {
                    flag = true;
                    int t = a[i];
                    a[i] = a[i + 1];
                    a[i + 1] = t;
                }
            }
        }
    }
    // --8<-- [end:core]

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int[] a = new int[n + 1];
        for (int j = 1; j <= n; ++j) a[j] = input.nextInt();
        bubble_sort(a, n);
        for (int j = 1; j <= n; ++j) {
            if (j > 1) System.out.print(" ");
            System.out.print(a[j]);
        }
        System.out.println();
    }
}
