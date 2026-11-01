import java.util.Scanner;

class Main {
// --8<-- [start:core]
  static int m;

  // arr 用于记录方案
  static int[] arr = new int[103];

  public static void dfs(int n, int i, int a) {
      if (n == 0) {
          for (int j = 1; j <= i - 1; j++) System.out.printf("%d ", arr[j]);
          System.out.println();
      }
      if (i <= m) {
          for (int j = a; j <= n; ++j) {
              arr[i] = j;
              dfs(n - j, i + 1, j); // 请仔细思考该行含义．
          }
      }
  }
// --8<-- [end:core]

  public static void main(String[] args) {
// --8<-- [start:main]
    // 主函数
    Scanner input = new Scanner(System.in);
    final int N = input.nextInt();
    m = input.nextInt();
    dfs(N, 1, 1);
// --8<-- [end:main]
  }
}
