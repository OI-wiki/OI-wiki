#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

#define Wall 0
#define Unknown 1
#define Space 2
#define Gate 3
#define Path 4

const int N = 20;
const int dir[8][2] = {{0, 1},  {1, 0}, {0, -1}, {-1, 0},
                       {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
const char dirs[5] = "ESWN";
int n, m, k;
int a[N][N], id[N][N];

struct point {
  int x, y;

  point(int x = 0, int y = 0) : x(x), y(y) {}

  bool operator==(const point& tmp) const { return x == tmp.x && y == tmp.y; }

  bool operator!=(const point& tmp) const { return !(*this == tmp); }

  point side(int d) const { return point(x + dir[d][0], y + dir[d][1]); }

  int check(int d) { return a[x + dir[d][0]][y + dir[d][1]]; }

  int id() { return ::id[x][y]; }
} start;

std::vector<std::pair<point, int>> path;
std::pair<point, point> ans[N];
std::pair<point, bool> vis[N];

bool walk(int d) {
  printf("MoveRobot %c\n", dirs[d]);
  fflush(stdout);
  int ret;
  scanf("%d", &ret);
  return ret;
}

bool walk(int d, std::stack<int>& st) {
  if (walk(d)) {
    st.push(d);
    return true;
  }
  return false;
}

bool read() {
  if (scanf("%d%d%d", &n, &m, &k) != 3) return false;
  if (n == 0) return false;
  memset(a, 0, sizeof(a));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      char c;
      std::cin >> c;
      if (c == 'S') start = point(i, j);
      if (c == '*')
        a[i][j] = Wall;
      else
        a[i][j] = Unknown;
    }
  return true;
}

void answer() {
  for (int i = 0; i < k; i++)
    printf("Answer %d %d\n", ans[i].first.id(), ans[i].second.id());
  fflush(stdout);
}

// 单手扶墙法，因为靠墙的 Path 是极大闭合环，所以只需要在沿着 Path
// 走的过程中没有碰到障碍就可以了
void wall_follower_init(point x, int last, int wallside, point s) {
  if (x == s && !path.empty()) return;
  if (x.check(wallside) == Path) {
    path.push_back(std::make_pair(x, wallside));
    wall_follower_init(x.side(wallside), wallside, last ^ 2, s);
  } else if (x.check(last) == Wall) {
    for (int i = 0; i < 4; i++)
      if (i != (last ^ 2) && x.check(i) != Wall) {
        path.push_back(std::make_pair(x, i));
        wall_follower_init(x.side(i), i, last, s);
        return;
      }
  } else {
    path.push_back(std::make_pair(x, last));
    wall_follower_init(x.side(last), last, wallside, s);
  }
}

void init() {
  int cnt = 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      if (a[i][j] == Unknown) {
        id[i][j] = cnt++;
        for (int k = 0; k < 8; k++)
          if (point(i, j).check(k) == Wall) {
            a[i][j] = Path;
            break;
          }
      } else
        id[i][j] = 0;
    }
  path.clear();
  int wallside = 0, last = 0;
  for (int i = 0; i < 4; i++)
    if (start.check(i) == Wall) {
      wallside = i;
      break;
    }
  for (int i = 0; i < 4; i++)
    if (start.check(i) == Path && i != (wallside ^ 2)) {
      last = i;
      break;
    }
  wall_follower_init(start, last, wallside, start);
}

void undo(std::stack<int>& st) {
  while (!st.empty()) walk(st.top() ^ 2), st.pop();
}

bool wall_follower(point x) {
  std::stack<int> st;
  bool ok = true;
  int i = 0;
  while (i < path.size() && path[i].first != x) i++;
  for (int j = i; ok && j < path.size(); j++) {
    if (walk(path[j].second))
      st.push(path[j].second);
    else
      ok = false;
  }
  for (int j = 0; ok && j < i; j++) {
    if (walk(path[j].second))
      st.push(path[j].second);
    else
      ok = false;
  }
  if (!ok) undo(st);
  return ok;
}

// 确定自己当前在
// x，使用「摸着石头过河」的方法，只需要沿着可以避开障碍、未知格子和传送门的方向走到
// Path 就行． 在找传送门和配对传送门时使用
void bfs(point s, point t, std::vector<int>& v) {
  static int map[N][N] = {};
  memset(map, -1, sizeof(map));
  std::queue<point> q;
  map[s.x][s.y] = 4;
  q.push(s);
  while (!q.empty()) {
    point x = q.front();
    q.pop();
    if (x == t) break;
    for (int i = 0; i < 4; i++) {
      point y = x.side(i);
      if ((x.check(i) == Path || x.check(i) == Space) && map[y.x][y.y] == -1) {
        map[y.x][y.y] = i;
        q.push(y);
      }
    }
  }
  for (point x = t; x != s; x = x.side(map[x.x][x.y] ^ 2)) {
    v.push_back(map[x.x][x.y]);
  }
  std::reverse(v.begin(), v.end());
}

bool move(point s, point t, std::stack<int>& st) {  // 在靠近传送门时使用
  static std::vector<int> v;
  v.clear();
  bfs(s, t, v);
  for (int i : v)
    if (!walk(i, st)) return false;
  return true;
}

// 尽可能快地向墙边移动
bool make_sure(point x, int last) {
  if (a[x.x][x.y] == Path) return wall_follower(x);
  for (int i = 0; i < 4; i++)
    if ((x.check(i) == Path || x.check(i) == Space) && i != (last ^ 2)) {
      if (!walk(i)) return false;
      bool ret = make_sure(x.side(i), i);
      walk(i ^ 2);
      return ret;
    }
  return false;
}

void find_gate() {
  int cnt = 0;
  std::stack<int> st;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (cnt == k * 2 && a[i][j] == Unknown)
        a[i][j] = Space;
      else if (a[i][j] == Unknown) {
        bool ok = true;
        if (!move(start, point(i - 1, j), st))
          ok = false;
        else if (!walk(1, st))
          ok = false;
        else if (!walk(2, st))
          ok = false;
        else if (!make_sure(point(i, j - 1), -1))
          ok = false;
        if (!ok) {
          vis[cnt++] = std::make_pair(point(i, j), false);
          a[i][j] = Gate;
          for (int k = 0; k < 8; k++) {
            point y = point(i, j).side(k);
            if (point(i, j).check(k) == Unknown) a[y.x][y.y] = Space;
          }
        } else
          a[i][j] = Space;
        undo(st);
      }
}

void make_gate_pair() {
  int cnt = 0;
  std::stack<int> st;
  for (int i = 0; i < k * 2; i++)
    if (!vis[i].second)
      for (int j = 0; !vis[i].second && j < k * 2; j++)
        if (j != i && !vis[j].second) {
          bool ok = true;
          if (!move(start, vis[i].first.side(2), st))
            ok = false;
          else if (!walk(0, st))
            ok = false;
          else if (!make_sure(vis[j].first.side(0), -1))
            ok = false;
          if (ok) {
            ans[cnt++] = std::make_pair(vis[i].first, vis[j].first);
            vis[i].second = vis[j].second = true;
          }
          undo(st);
        }
}

int main() {
  while (read()) {
    init();
    find_gate();
    make_gate_pair();
    answer();
  }
  return 0;
}
