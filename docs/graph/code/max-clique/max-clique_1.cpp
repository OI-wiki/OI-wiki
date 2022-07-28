#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

int n, m;
bool G[N][N];
int cnt[N];    // cnt[i]为>=i的最大团点数
int group[N];  // 最大团的点
int vis[N];    // 记录点的位置
int res;       // 最大团的数目

bool dfs(int pos, int num) {  // num为当前独立集中的点数
  for (int i = pos + 1; i <= n; i++) {
    if (cnt[i] + num <= res)  // 剪枝，若取i但cnt[i]+已经取了的点数仍<ans
      return false;

    if (G[pos][i]) {  // 与当前团中元素比较，取Non-N(i)
      int j;
      for (j = 0; j < num; j++)
        if (!G[i][vis[j]]) break;
      if (j == num) {  // 若为空，则皆与i相邻，则此时将i加入到最大团中
        vis[num] = i;
        if (dfs(i, num + 1)) return true;
      }
    }
  }

  if (num > res) {  // 每添加一个点最多使最大团数+1,后面的搜索就没有意义了
    for (int i = 0; i < num; i++)  // 最大团的元素
      group[i] = vis[i];
    res = num;  // 最大团中点的数目
    return true;
  }
  return false;
}

void maxClique() {
  res = -1;
  for (int i = n; i > 0; i--) {  // 枚举所有点
    vis[0] = i;
    dfs(i, 1);
    cnt[i] = res;
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    memset(G, 0, sizeof(G));

    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      G[x][y] = 1;
      G[y][x] = 1;
    }

    // 建立反图
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (i == j)
          G[i][j] = 0;
        else
          G[i][j] ^= 1;
      }
    }
    maxClique();

    if (res < 0) res = 0;
    printf("%d\n", res);           // 最大团的个数
    for (int i = 0; i < res; i++)  // 最大团中的顶点
      printf("%d ", group[i]);
    printf("\n");
  }
  return 0;
}
