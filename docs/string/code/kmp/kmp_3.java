import java.util.*;

class Main {
  // --8<-- [start:core]
  static int[] prefix_function(String s) {
      int n = s.length();
      int[] pi = new int[n];
      for (int i = 1; i < n; i++) {
          int j = pi[i - 1];
          while (j > 0 && s.charAt(i) != s.charAt(j)) {
              j = pi[j - 1];
          }
          if (s.charAt(i) == s.charAt(j)) {
              j++;
          }
          pi[i] = j;
      }
      return pi;
  }
  // --8<-- [end:core]

  public static void main(String[] args) {
    String s = new Scanner(System.in).next();
    int[] pi = prefix_function(s);
    for (int i = 0; i < pi.length; ++i) System.out.print((i == 0 ? "" : " ") + pi[i]);
    System.out.println();
  }
}
