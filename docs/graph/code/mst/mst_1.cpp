#include <algorithm>
#include <cstdio>

struct Edge {
  int x, y, z;
};

int f[100001];
Edge a[100001];

int cmp(const Edge& a, const Edge& b) { return a.z < b.z; }

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) f[i] = i;
    for (int i = 1; i <= m; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
    std::sort(a + 1, a + m + 1, cmp);  // 先排序
    int num = 0, ans = 0, tail = 0, sum1 = 0, sum2 = 0;
    bool flag = 1;
    for (int i = 1; i <= m + 1; i++) {  // 再并查集加边
      if (i > tail) {
        if (sum1 != sum2) {
          flag = 0;
          break;
        }
        sum1 = 0;
        for (int j = i; j <= m + 1; j++) {
          if (a[j].z != a[i].z) {
            tail = j - 1;
            break;
          }
          if (find(a[j].x) != find(a[j].y)) ++sum1;
        }
        sum2 = 0;
      }
      if (i > m) break;
      int x = find(a[i].x);
      int y = find(a[i].y);
      if (x != y && num != n - 1) {
        sum2++;
        num++;
        f[x] = f[y];
        ans += a[i].z;
      }
    }
    if (flag)
      printf("%d\n", ans);
    else
      printf("Not Unique!\n");
  }
  return 0;
}