import java.util.Arrays;
import java.util.Scanner;

class Edge {
    int u;
    int v;
    int w;

    Edge(int u, int v, int w) {
        this.u = u;
        this.v = v;
        this.w = w;
    }
}

public class Main {
    static int[] parent = new int[1010];  // 定义父亲
    static int m, n, k;  // n 表示点的数量， m 表示边的数量，k 表示需要的棉花糖个数

    static Edge[] edges = new Edge[10010];
    static int l;

    static void addEdge(int u, int v, int w) {
        edges[++l] = new Edge(u, v, w);
    }

    // 标准并查集
    static int findroot(int x) {
        if (parent[x] != x) {
            parent[x] = findroot(parent[x]);
        }
        return parent[x];
    }

    static void Merge(int x, int y) {
        x = findroot(x);
        y = findroot(y);
        parent[x] = y;
    }

    static boolean cmp(Edge A, Edge B) {
        return A.w < B.w;
    }

    // Kruskal 算法
    static void kruskal() {
        int tot = 0;  // 存已选了的边数
        int ans = 0;  // 存总的代价

        for (int i = 1; i <= m; i++) {
            int xr = findroot(edges[i].u);
            int yr = findroot(edges[i].v);
            if (xr != yr) {   // 如果父亲不一样
                Merge(xr, yr); // 合并
                tot++; // 边数增加
                ans += edges[i].w; // 代价增加
            }
            if (tot >= (n - k)) {  // 检查选的边数是否满足 k 个棉花糖
                System.out.println(ans);
                return;
            }
        }
        System.out.println("No Answer");  // 无法连成
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        k = scanner.nextInt();

        // 初始化
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        for (int i = 1; i <= m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            int w = scanner.nextInt();
            addEdge(u, v, w);  // 添加边
        }
        Arrays.sort(edges, 1, m + 1, (a, b) -> Integer.compare(a.w, b.w));  // 先按边权排序
        kruskal();
        scanner.close();
    }
}
