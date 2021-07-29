#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
#define MAXN (30 + 5)
#define MAXV (500 + 5)
int d[MAXN][3];
int x[MAXN], y[MAXN], z[MAXN];
int babylon_sub(int c, int rot, int n) {
  if (d[c][rot] != -1) {
    return d[c][rot];
  }
  d[c][rot] = 0;
  int base1, base2;
  if (rot == 0) {  //处理三个方向
    base1 = x[c];
    base2 = y[c];
  }
  if (rot == 1) {
    base1 = y[c];
    base2 = z[c];
  }
  if (rot == 2) {
    base1 = x[c];
    base2 = z[c];
  }
  for (int i = 0; i < n; i++) {  //根据不同条件，分别调用不同的递归
    if ((x[i] < base1 && y[i] < base2) || (y[i] < base1 && x[i] < base2))
      d[c][rot] = max(d[c][rot], babylon_sub(i, 0, n) + z[i]);
    if ((y[i] < base1 && z[i] < base2) || (z[i] < base1 && y[i] < base2))
      d[c][rot] = max(d[c][rot], babylon_sub(i, 1, n) + x[i]);
    if ((x[i] < base1 && z[i] < base2) || (z[i] < base1 && x[i] < base2))
      d[c][rot] = max(d[c][rot], babylon_sub(i, 2, n) + y[i]);
  }
  return d[c][rot];
}
int babylon(int n) {
  for (int i = 0; i < n; i++) {
    d[i][0] = -1;
    d[i][1] = -1;
    d[i][2] = -1;
  }
  int r = 0;
  for (int i = 0; i < n; i++) {  //三种建法
    r = max(r, babylon_sub(i, 0, n) + z[i]);
    r = max(r, babylon_sub(i, 1, n) + x[i]);
    r = max(r, babylon_sub(i, 2, n) + y[i]);
  }
  return r;
}
int main() {
  int t = 0;
  while (true) {  //死循环求答案
    int n;
    cin >> n;
    if (n == 0) break;  //没有砖头了就停止
    t++;
    for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i] >> z[i];
    }
    cout << "Case " << t << ":"
         << " maximum height = " << babylon(n);  //递归
    cout << endl;
  }
  return 0;
}
