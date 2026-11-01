#include <algorithm>
#include <functional>
#include <iostream>

// --8<-- [start:declarations]
struct data {
  int a, b;

  bool operator<(const data rhs) const {
    return (a == rhs.a) ? (b < rhs.b) : (a < rhs.a);
  }
} da[1009];

bool cmp(const data u1, const data u2) {
  return (u1.a == u2.a) ? (u1.b > u2.b) : (u1.a > u2.a);
}

// ...
// --8<-- [end:declarations]

int main() {
  for (int i = 1; i <= 10; ++i) std::cin >> da[i].a >> da[i].b;
  // --8<-- [start:sort]
  std::sort(da + 1, da + 1 + 10);  // 使用结构体中定义的 < 运算符，从小到大排序
  std::sort(da + 1, da + 1 + 10, cmp);  // 使用 cmp 函数进行比较，从大到小排序
  // --8<-- [end:sort]
  for (int i = 1; i <= 10; ++i) std::cout << da[i].a << " " << da[i].b << "\n";
}
