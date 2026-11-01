#include <iostream>

int main() {
  constexpr int N = 8;
  int var1;
  std::cin >> var1;
  // --8<-- [start:example160]
  int st[N] = {};
  // 这里使用 st[0] (即 *st) 代表栈中元素数量，同时也是栈顶下标

  // 压栈 ：
  st[++*st] = var1;
  // 取栈顶 ：
  int u = st[*st];
  // 弹栈 ：注意越界问题, *st == 0 时不能继续弹出
  if (*st) --*st;
  // 清空栈
  *st = 0;
  // --8<-- [end:example160]
  std::cout << u << " " << st[0] << "\n";
}
