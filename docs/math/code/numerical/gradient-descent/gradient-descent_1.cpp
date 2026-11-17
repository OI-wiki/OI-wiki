#include <cstdio>

// 目标函数 f(x, y) = x^2 + 4y^2
double f(double x, double y) { return x * x + 4 * y * y; }

// 从 (x, y) 出发，以步长 eta 迭代 k 次，输出每一步的位置和函数值
void gradient_descent(double x, double y, double eta, int k) {
  printf("eta = %.2f\n", eta);
  for (int i = 0; i <= k; ++i) {
    printf("%d %.4f %.4f %.4f\n", i, x, y, f(x, y));
    double gx = 2 * x, gy = 8 * y;  // 梯度
    x -= eta * gx;
    y -= eta * gy;
  }
}

int main() {
  double x0, y0;
  int k, m;
  scanf("%lf%lf%d%d", &x0, &y0, &k, &m);
  for (int i = 0; i < m; ++i) {
    double eta;
    scanf("%lf", &eta);
    gradient_descent(x0, y0, eta, k);
  }
  return 0;
}
