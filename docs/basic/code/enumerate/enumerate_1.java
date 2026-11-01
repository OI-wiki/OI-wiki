import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int[] a = new int[n];
        for (int i = 0; i < n; ++i) a[i] = input.nextInt();
        int ans = 0;
        final int MAXN = 100000;
        // --8<-- [start:core]
        for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
            if (a[i] + a[j] == 0) ++ans;
        // --8<-- [end:core]
        System.out.println(ans);
    }
}
