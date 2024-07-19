#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
#define MAXN (30 + 5)
#define MAXV (500 + 5)
extern int d[MAXN][3];
extern int x[MAXN], y[MAXN], z[MAXN];

extern int babylon(int n);

int main() {
  int t = 0;
  while (true) {  // 死循环求答案
    int n;
    cin >> n;
    if (n == 0) break;  // 没有砖头了就停止
    t++;
    for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i] >> z[i];
    }
    cout << "Case " << t << ":"
         << " maximum height = " << babylon(n);  // 递归
    cout << endl;
  }
  return 0;
}
