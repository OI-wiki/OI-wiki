#include <cstdio>
#include <iostream>

int p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
unsigned long long n;
unsigned long long ans,
    ans_num;  // ans 为 n 以内的最大反素数（会持续更新），ans_sum 为
              // ans的因子数。

// depth: 当前在枚举第几个素数
// temp: 当前因子数量为 num的时候的数值
// num: 当前因子数
// up：上一个素数的幂，这次应该小于等于这个幂次嘛
void dfs(int depth, unsigned long long temp, unsigned long long num, int up) {
  if (depth >= 16 || temp > n) return;
  if (num > ans_num) {  //更新答案
    ans = temp;
    ans_num = num;
  }
  if (num == ans_num && ans > temp) ans = temp;  //更新答案
  for (int i = 1; i <= up; i++) {
    if (temp * p[depth] > n)
      break;  //剪枝：如果加一个这个乘数的结果比ans要大，则必不是最佳方案
    dfs(depth + 1, temp *= p[depth], num * (i + 1),
        i);  //取一个该乘数，进行对下一个乘数的搜索
  }
  return;
}

int main() {
  while (scanf("%llu", &n) != EOF) {
    ans_num = 0;
    dfs(0, 1, 1, 60);
    printf("%llu\n", ans);
  }
  return 0;
}
