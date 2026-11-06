import java.util.Scanner;

class Main {
    // --8<-- [start:core]
    // arr 数组的下标从 1 开始
    static void selection_sort(int[] arr, int n) {
        for (int i = 1; i < n; i++) {
            int ith = i;
            for (int j = i + 1; j <= n; j++) {
                if (arr[j] < arr[ith]) {
                    ith = j;
                }
            }
            // swap
            int temp = arr[i];
            arr[i] = arr[ith];
            arr[ith] = temp;
        }
    }
    // --8<-- [end:core]

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int[] a = new int[n + 1];
        for (int j = 1; j <= n; ++j) a[j] = input.nextInt();
        selection_sort(a, n);
        for (int j = 1; j <= n; ++j) {
            if (j > 1) System.out.print(" ");
            System.out.print(a[j]);
        }
        System.out.println();
    }
}
