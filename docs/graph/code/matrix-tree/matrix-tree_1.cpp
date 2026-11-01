#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
constexpr double eps = 1e-7;

struct matrix {
  static constexpr int MAXN = 20;
  int n, m;
  double mat[MAXN][MAXN];

  matrix() { memset(mat, 0, sizeof(mat)); }

  void print() {
    cout << "MATRIX " << n << " " << m << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << mat[i][j] << "\t";
      }
      cout << endl;
    }
  }

  void random(int n) {
    this->n = n;
    this->m = n;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) mat[i][j] = rand() % 100;
  }

  void initSquare() {
    this->n = 4;
    this->m = 4;
    memset(mat, 0, sizeof(mat));
    mat[0][1] = mat[0][3] = -1;
    mat[1][0] = mat[1][2] = -1;
    mat[2][1] = mat[2][3] = -1;
    mat[3][0] = mat[3][2] = -1;
    mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = 2;
    this->n--;  // 去一行
    this->m--;  // 去一列
  }

  double gauss() {
    double ans = 1;
    for (int i = 0; i < n; i++) {
      int sid = i;
      for (int j = i + 1; j < n; j++)
        if (abs(mat[j][i]) > abs(mat[sid][i])) sid = j;
      if (abs(mat[sid][i]) <= eps) return 0;
      if (sid != i) {
        for (int j = 0; j < n; j++) swap(mat[sid][j], mat[i][j]);
        ans = -ans;
      }
      for (int j = i + 1; j < n; j++) {
        double ratio = mat[j][i] / mat[i][i];
        for (int k = 0; k < n; k++) {
          mat[j][k] -= mat[i][k] * ratio;
        }
      }
    }
    for (int i = 0; i < n; i++) ans *= mat[i][i];
    return ans;
  }
};

int main() {
  srand(1);
  matrix T;
  // T.random(2);
  T.initSquare();
  T.print();
  double ans = T.gauss();
  T.print();
  cout << ans << endl;
}
