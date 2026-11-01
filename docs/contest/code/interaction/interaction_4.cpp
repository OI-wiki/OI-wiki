#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 256 + 5;
int T, h, chance;
bool ok;
vector<int> to[N], path;

bool read(int x) {
  if (to[x].empty()) {
    printf("? %d\n", x), fflush(stdout);
    int k, t;
    scanf("%d", &k);
    if (k == 0) exit(0);
    for (int i = 0; i < k; i++) {
      scanf("%d", &t);
      to[x].push_back(t);
    }
    if (k == 2) {
      printf("! %d\n", x), fflush(stdout);
      return ok = true;
    }
    chance--;
  }
  return false;
}

bool dfs(int x) {
  if (to[x].empty()) path.push_back(x);
  if (read(x)) return true;
  for (int i : to[x])
    if (to[i].empty()) return dfs(i);
  return false;
}

void bfs(int s, int k) {
  queue<int> q;
  for (int i : to[s])
    if (to[i].empty()) q.push(i);
  for (int i = 1; i < k; i++) {
    int x = q.front();
    q.pop();
    if (read(x)) return;
    for (int j : to[x])
      if (to[j].empty()) q.push(j);
  }
  for (int i = 1; i < k; i++) {
    int x = q.front();
    q.pop();
    if (read(x)) return;
  }
  printf("! %d\n", q.front()), fflush(stdout);
}

int main() {
  for (scanf("%d", &T); T--;) {
    ok = false;
    for (int i = 0; i < N; i++) to[i].clear();
    chance = 16;
    scanf("%d", &h);
    if (h == 0) exit(0);
    vector<int> long_path;
    if (read(1)) continue;
    int root, dep;
    if (to[1].size() == 1)
      root = 1, dep = h;
    else {
      for (int i : to[1]) {
        path.clear();
        if (dfs(i)) break;
        if (path.size() > long_path.size()) swap(path, long_path);
      }
      if (ok) continue;
      dep = h - (path.size() + long_path.size()) / 2;
      root = long_path.at((long_path.size() - (h - dep)) - 1);
    }
    while ((1 << (dep - 1)) - 2 > chance) {
      path.clear();
      if (dfs(root)) break;
      dep = h - (h - dep + path.size()) / 2;
      root = path.at((path.size() - (h - dep)) - 1);
    }
    if (!ok) bfs(root, 1 << (dep - 2));
  }
  return 0;
}
