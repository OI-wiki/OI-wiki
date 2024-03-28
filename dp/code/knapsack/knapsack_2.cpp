#include <iostream>
using namespace std;
const int maxn = 1e4 + 5;
const int maxW = 1e7 + 5;
int n, W, w[maxn], v[maxn];
long long f[maxW];

int main() {
  cin >> W >> n;
  for (int i = 1; i <= n; i++) cin >> w[i] >> v[i];
  for (int i = 1; i <= n; i++)
    for (int l = w[i]; l <= W; l++)
      if (f[l - w[i]] + v[i] > f[l]) f[l] = f[l - w[i]] + v[i];  // 核心状态方程
  cout << f[W];
  return 0;
}