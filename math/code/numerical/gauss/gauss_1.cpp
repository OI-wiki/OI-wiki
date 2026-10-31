#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

// --8<-- [start:core]
constexpr double EPS = 1E-9;

double determinant(std::vector<std::vector<double>> a) {
  int n = a.size();
  double det = 1;
  for (int i = 0; i < n; ++i) {
    int k = i;
    for (int j = i + 1; j < n; ++j)
      if (std::abs(a[j][i]) > std::abs(a[k][i])) k = j;
    if (std::abs(a[k][i]) < EPS) {
      det = 0;
      break;
    }
    std::swap(a[i], a[k]);
    if (i != k) det = -det;
    det *= a[i][i];
    for (int j = i + 1; j < n; ++j) {
      double factor = a[j][i] / a[i][i];
      a[j][i] = 0;
      for (int k = i + 1; k < n; ++k) a[j][k] -= factor * a[i][k];
    }
  }
  return det;
}

// --8<-- [end:core]

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<double>> a(n, std::vector<double>(n));
  for (auto& row : a)
    for (double& value : row) std::cin >> value;
  std::cout << std::setprecision(10) << determinant(a) << '\n';
}
