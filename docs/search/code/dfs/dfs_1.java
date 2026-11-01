import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    int n = new Scanner(System.in).nextInt();
// --8<-- [start:core]
    for (int i = 1; i < n + 1; i++) {
        for (int j = i; j < n + 1; j++) {
            for (int k = j; k < n + 1; k++) {
                if (i + j + k == n) System.out.printf("%d = %d + %d + %d%n", n, i, j, k);
            }
        }
    }
// --8<-- [end:core]
  }
}
