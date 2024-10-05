#include <cstdio>
#include <cstring>
#include <iostream>

const int LEN = 1000;
extern void mul_short(int a[], int b, int c[]);

int main() {
  int a[LEN] = {0}, b, c[LEN];
  char temp[LEN];
  std::cin >> temp;
  for (int i = 0; i < strlen(temp); ++i) a[i] = temp[i] - '0';
  std::cin >> b;
  mul_short(a, b, c);

  int i = LEN - 1;
  for (; i >= 0; --i)
    if (c[i] != 0) break;
  for (; i >= 0; --i) std::cout << c[i];
  std::cout << std::endl;
  return 0;
}
