import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // 读取N的值
        int N = scanner.nextInt();
        int[] A = new int[N]; // 原数组
        int[] B = new int[N]; // 前缀和数组

        // 读取数组A的值
        for (int i = 0; i < N; i++) {
            A[i] = scanner.nextInt();
        }

        // 前缀和数组的第一项和原数组的第一项是相等的。
        B[0] = A[0];

        // 计算前缀和数组
        for (int i = 1; i < N; i++) {
            // 前缀和数组的第i项 = 原数组的0到i-1项的和 + 原数组的第i项。
            B[i] = B[i - 1] + A[i];
        }

        // 输出前缀和数组
        for (int i = 0; i < N; i++) {
            System.out.print(B[i] + " ");
        }

        scanner.close();
    }
}
