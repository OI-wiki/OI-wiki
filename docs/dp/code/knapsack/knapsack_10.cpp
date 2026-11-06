#include <algorithm>
#include <vector>

// --8<-- [start:program]
#include <iostream>
using namespace std;
constexpr int MAXN = 13010;
int n, W, w[MAXN], v[MAXN], f[MAXN];

int main() {
  cin >> n >> W;
  for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];  // 读入数据
  // --8<-- [start:core]
  for (int i = 1; i <= n; i++)
    for (int l = W; l >= w[i]; l--) f[l] = max(f[l], f[l - w[i]] + v[i]);
  // --8<-- [end:core]
  cout << f[W];
  return 0;
}

// --8<-- [end:program]
