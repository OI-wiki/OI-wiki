#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 150000 + 10;
const int maxm = 300 + 10;

ll f[2][maxn];
ll a[maxm], b[maxm], t[maxm];
int n, m, d;

int que[maxn];

int fl = 1;
void init() {
  memset(f, 207, sizeof(f));
  memset(que, 0, sizeof(que));
  for (int i = 1; i <= n; i++) f[0][i] = 0;
  fl = 1;
}

void dp() {
  init();
  for (int i = 1; i <= m; i++) {
    int l = 1, r = 0, k = 1;
    for (int j = 1; j <= n; j++) {  //在这里使用了单调队列的优化，推式子详见上面
      for (; k <= min(1ll * n, j + d * (t[i] - t[i - 1])); k++) {
        while (l <= r && f[fl ^ 1][que[r]] <= f[fl ^ 1][k]) r--;
        que[++r] = k;
      }

      while (l <= r && que[l] < max(1ll, j - d * (t[i] - t[i - 1]))) l++;
      f[fl][j] = f[fl ^ 1][que[l]] - abs(a[i] - j) + b[i];
    }

    fl ^= 1;
  }
}

int main() {
  cin >> n >> m >> d;
  for (int i = 1; i <= m; i++) cin >> a[i] >> b[i] >> t[i];

  // then dp
  dp();
  ll ans = -1e18;
  for (int i = 1; i <= n; i++) ans = max(ans, f[fl ^ 1][i]);
  cout << ans << endl;
  return 0;
}