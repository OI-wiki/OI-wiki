#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int n, a[5005], mem[5005];

// --8<-- [start:core]
int dfs(int i) {
  if (mem[i] != -1) return mem[i];
  int ret = 1;
  for (int j = 1; j < i; j++)
    if (a[j] < a[i]) ret = max(ret, dfs(j) + 1);
  return mem[i] = ret;
}

int main() {
  memset(mem, -1, sizeof(mem));
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  int ret = 0;
  for (int j = 1; j <= n; j++) {
    ret = max(ret, dfs(j));
  }
  cout << ret << endl;
}

// --8<-- [end:core]
