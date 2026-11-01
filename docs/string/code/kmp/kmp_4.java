import java.util.*;

class Main {
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

  // --8<-- [start:core]
  static List<Integer> find_occurrences(String text, String pattern) {
      String cur = pattern + '#' + text;
      int sz1 = text.length(), sz2 = pattern.length();
      List<Integer> v = new ArrayList<>();
      int[] lps = prefix_function(cur);
      for (int i = 2 * sz2; i <= sz1 + sz2; i++) {
          if (lps[i] == sz2) {
              v.add(i - 2 * sz2);
          }
      }
      return v;
  }
  // --8<-- [end:core]

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    String s = input.next(), t = input.next();
    for (int pos : find_occurrences(s, t)) System.out.println(pos);
  }
}
