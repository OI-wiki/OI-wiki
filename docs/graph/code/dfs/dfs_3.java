import java.util.Scanner;

class Main {
  static class Edge { int t, x; Edge(int t, int x) { this.t=t; this.x=x; } }
  static Edge[] e;
  static int[] head;
  static boolean[] vis;
// --8<-- [start:core]
public static void dfs(int u) {
    vis[u] = true;
    for (int i = head[u]; i != 0; i = e[i].x) {
        if (!vis[e[i].t]) {
            dfs(e[i].t);
        }
    }
}
// --8<-- [end:core]

  public static void main(String[] args) {
    Scanner input = new Scanner(System.in);
    int n = input.nextInt(), m = input.nextInt();
    head = new int[n + 1]; vis = new boolean[n + 1]; e = new Edge[m + 1];
    for (int i = 1; i <= m; ++i) {
      int u = input.nextInt(), v = input.nextInt();
      e[i] = new Edge(v, head[u]); head[u] = i;
    }
    int start = input.nextInt(); input.nextInt();
    dfs(start);
    StringBuilder result = new StringBuilder();
    for (int i = 1; i <= n; ++i) if (vis[i]) {
      if (result.length() > 0) result.append(' ');
      result.append(i);
    }
    System.out.println(result);
  }
}
