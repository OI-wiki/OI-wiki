#include <iostream>
#include <queue>
using namespace std;

char a[110][110];    // 存储迷宫地图
bool vis[110][110];  // 记录访问状态
int n, m;            // 迷宫尺寸

struct node {
  int x, y;
};  // 定义坐标结构体

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};  // 方向数组（右左上下）

// 检查坐标是否合法
bool chk(int x, int y) {
  return (x >= 1 && x <= n && y >= 1 && y <= m  // 边界检查
          && !vis[x][y]                         // 未访问过
          && a[x][y] != '#');                   // 不是障碍物
}

bool bfs() {
  queue<node> q;
  q.push({1, 1});  // 起点入队
  vis[1][1] = 1;   // 标记起点已访问
  while (!q.empty()) {
    node p = q.front();  // 取出队首坐标
    q.pop();
    int px = p.x, py = p.y;
    if (px == n && py == m) return true;  // 到达终点立即返回
    // 向四个方向扩展
    for (int i = 0; i < 4; ++i) {
      int nx = px + dx[i], ny = py + dy[i];
      if (chk(nx, ny)) {   // 合法性检查
        q.push({nx, ny});  // 新坐标入队
        vis[nx][ny] = 1;   // 标记已访问
      }
    }
  }
  return false;
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) cin >> a[i][j];
  cout << (bfs() ? "Yes" : "No") << endl;
  return 0;
}
