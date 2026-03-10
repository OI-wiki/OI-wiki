#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int n, m, u, v, ag[100010], as;
int dfn[200020], low[200020], bel[200020], dcnt, scnt;
vector<int> to[200020], stk;

bool ix(int x) {return ag[x] * n >= as;} // 是否为老资历
int N(int x) {return x > n? x - n : x + n;} // 取反

void DFS(int x) { // Tarjan SCC 缩点
  dfn[x] = low[x] = ++dcnt, stk.push_back(x);
  for(auto i : to[x]) {
    if(!dfn[i]) {
      DFS(i);
      low[x] = min(low[x], low[i]);
    }else if(!bel[i]) low[x] = min(low[x], dfn[i]);
  }
  if(dfn[x] == low[x]) {
    scnt++;
    for(; stk.size() && dfn[stk.back()] >= dfn[x]; stk.pop_back()) bel[stk.back()] = scnt;
  }
}

void solve() {
  for(int i = 1; i <= n; i++) cin >> ag[i];
  as = accumulate(ag + 1, ag + n + 1, 0);
  for(; m--; ) {
    cin >> u >> v;
    if(ix(u) ^ ix(v)) {
      to[N(u)].push_back(v);
      to[N(v)].push_back(u);
    }else { // 注意这里正向反向都需要连
      to[u].push_back(N(v));
      to[N(u)].push_back(v);
      to[v].push_back(N(u));
      to[N(v)].push_back(u);
    }
  }
  for(int i = 1; i <= 2 * n; i++) {
    if(!dfn[i]) DFS(i);
  }
  for(int i = 1; i <= n; i++) {
    if(bel[i] == bel[N(i)]) {
      cout << "No solution." << '\n';
      return ;
    }
  }
  for(int i = 1; i <= n; i++) {
    if(bel[i] < bel[N(i)]) cout << (ix(i)? 'A' : 'B') << '\n';
    else cout << 'C' << '\n';
  }
}

int main() {
  for(cin >> n >> m; n && m; cin >> n >> m) {
    solve();
    for(int i = 1; i <= n + n; i++) dfn[i] = low[i] = bel[i] = 0, to[i].clear();
    dcnt = scnt = 0;
  }
  return 0;
}