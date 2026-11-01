import java.util.*;

class Main {
  // --8<-- [start:core]
  static class Trie {
      int[][] tree = new int[10000][26];
      int cnt = 0;
      boolean[] end = new boolean[10000];

      public void insert(String word) {
          int p = 0;
          char[] chars = word.toCharArray();
          for (int i = 0; i < chars.length; i++) {
              int c = chars[i] - 'a';
              if (tree[p][c] == 0) {
                  tree[p][c] = ++cnt;
              }
              p = tree[p][c];
          }
          end[p] = true;
      }

      public boolean find(String word) {
          int p = 0;
          char[] chars = word.toCharArray();
          for (int i = 0; i < chars.length; i++) {
              int c = chars[i] - 'a';
              if (tree[p][c] == 0) {
                  return false;
              }
              p = tree[p][c];
          }
          return end[p];
      }
  }
  // --8<-- [end:core]

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    Trie dictionary = new Trie();
    int n = input.nextInt();
    while (n-- > 0) dictionary.insert(input.next());
    Set<String> called = new HashSet<>();
    int m = input.nextInt();
    while (m-- > 0) {
      String s = input.next();
      System.out.println(!dictionary.find(s) ? "WRONG" : !called.add(s) ? "REPEAT" : "OK");
    }
  }
}
