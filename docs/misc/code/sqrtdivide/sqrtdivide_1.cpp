#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
ll sum[755][755], a[500005];  // 阈值取了 700

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  for (; q--;) {
    int tp, x, y;
    cin >> tp >> x >> y;
    if (tp == 1) {
      for (int i = 1; i < 700; ++i) sum[i][x % i] += y;  //枚举模数
      a[x] += y;
    } else {
      if (x < 700) {
        cout << sum[x][y] << endl;
      } else {
        ll rt = 0;
        for (int i = y; i <= 500000; i += x) rt += a[i];  //暴力统计
        cout << rt << endl;
      }
    }
  }
}
