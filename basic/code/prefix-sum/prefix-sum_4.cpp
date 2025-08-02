#include <iostream>
#include <vector>

int main() {
  // Input.
  int N1, N2, N3;
  std::cin >> N1 >> N2 >> N3;
  std::vector<std::vector<std::vector<int>>> a(
      N1 + 1, std::vector<std::vector<int>>(N2 + 1, std::vector<int>(N3 + 1)));
  for (int i = 1; i <= N1; ++i)
    for (int j = 1; j <= N2; ++j)
      for (int k = 1; k <= N3; ++k) std::cin >> a[i][j][k];

  // Copy.
  auto ps = a;

  // Prefix-sum for 3rd dimension.
  for (int i = 1; i <= N1; ++i)
    for (int j = 1; j <= N2; ++j)
      for (int k = 1; k <= N3; ++k) ps[i][j][k] += ps[i][j][k - 1];

  // Prefix-sum for 2nd dimension.
  for (int i = 1; i <= N1; ++i)
    for (int j = 1; j <= N2; ++j)
      for (int k = 1; k <= N3; ++k) ps[i][j][k] += ps[i][j - 1][k];

  // Prefix-sum for 1st dimension.
  for (int i = 1; i <= N1; ++i)
    for (int j = 1; j <= N2; ++j)
      for (int k = 1; k <= N3; ++k) ps[i][j][k] += ps[i - 1][j][k];

  // Output.
  for (int i = 1; i <= N1; ++i) {
    for (int j = 1; j <= N2; ++j) {
      for (int k = 1; k <= N3; ++k) {
        std::cout << ps[i][j][k] << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }

  return 0;
}