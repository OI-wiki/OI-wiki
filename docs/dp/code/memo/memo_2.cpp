#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

constexpr int INF = 1000000000;
// --8<-- [start:core]
int n, t;
int tcost[103], mget[103];
int mem[103][1003];

int dfs(int pos, int tleft) {
  if (mem[pos][tleft] != -1)
    return mem[pos][tleft];  // 已经访问过的状态，直接返回之前记录的值
  if (pos == n + 1) return mem[pos][tleft] = 0;
  int dfs1, dfs2 = -INF;
  dfs1 = dfs(pos + 1, tleft);
  if (tleft >= tcost[pos])
    dfs2 = dfs(pos + 1, tleft - tcost[pos]) + mget[pos];  // 状态转移
  return mem[pos][tleft] = max(dfs1, dfs2);  // 最后将当前状态的值存下来
}

int main() {
  memset(mem, -1, sizeof(mem));
  cin >> t >> n;
  for (int i = 1; i <= n; i++) cin >> tcost[i] >> mget[i];
  cout << dfs(1, t) << endl;
  return 0;
}

// --8<-- [end:core]
