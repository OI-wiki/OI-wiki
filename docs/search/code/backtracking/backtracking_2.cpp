// 该代码为回溯法的 BFS 实现
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int n, m, k, x, y, a, b, ans;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};  // 四个方向
bool vis[6][6];

struct oo {
  int x, y, used[6][6];
};

oo sa;

void bfs() {
  queue<oo> q;
  sa.x = x;
  sa.y = y;
  sa.used[x][y] = 1;
  q.push(sa);
  while (!q.empty()) {  // BFS队列
    oo now = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {  // 枚举向四个方向走
      int sx = now.x + dx[i];
      int sy = now.y + dy[i];
      if (now.used[sx][sy] || vis[sx][sy] || sx == 0 || sy == 0 || sx > n ||
          sy > m)
        continue;
      if (sx == a && sy == b) {
        ans++;
        continue;
      }
      sa.x = sx;
      sa.y = sy;
      memcpy(sa.used, now.used, sizeof(now.used));
      sa.used[sx][sy] = 1;
      q.push(sa);  // 假设向此方向走，放入BFS队列
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  scanf("%d%d%d%d", &x, &y, &a, &b);
  for (int i = 1, aa, bb; i <= k; i++) {
    scanf("%d%d", &aa, &bb);
    vis[aa][bb] = 1;  // 障碍位置不可通过
  }
  bfs();
  printf("%d", ans);
  return 0;
}
