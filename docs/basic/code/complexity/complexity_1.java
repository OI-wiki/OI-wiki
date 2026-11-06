import java.util.Scanner;
import java.io.OutputStream;
import java.io.PrintStream;

class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        // --8<-- [start:core]
        int n, m;
        n = input.nextInt();
        m = input.nextInt();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < m; ++k) {
                    System.out.println("hello world");
                }
            }
        }
        // --8<-- [end:core]
    }
}
