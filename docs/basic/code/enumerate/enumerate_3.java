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
        boolean[] met = new boolean[MAXN * 2 + 1];
        for (int i = 0; i < n; ++i) {
            if (met[MAXN - a[i]]) ++ans;
            met[MAXN + a[i]] = true;
        }
        ans *= 2;
        // --8<-- [end:core]
        System.out.println(ans);
    }
}
