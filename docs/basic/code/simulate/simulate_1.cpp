#include <cstdio>
int main(void) {
  int n = 0, u = 0, d = 0;
  while (scanf("%d %d %d", &n, &u, &d) && n != 0) {
    int time = 0, dist = 0;
    while (true) {  //用死循环来枚举
      dist += u;
      time++;
      if (dist >= n) break;  //满足条件则退出死循环
      dist -= d;
      time++;
    }
    printf("%d\n", time);  //输出得到的结果
  }
  return 0;
}