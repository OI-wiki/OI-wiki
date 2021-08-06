#include <iomanip>
#include <iostream>
using namespace std;
int n;
bool vis[50];  // 访问标记数组
int a[50];     // 排列数组，按顺序储存当前搜索结果

void dfs(int step) {
  if (step == n + 1) {  // 边界
    for (int i = 1; i <= n; i++) {
      cout << setw(5) << a[i];  //保留5个场宽
    }
    cout << endl;
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i] == 0) {  //判断数字i是否在正在进行的全排列中
      vis[i] = 1;
      a[step] = i;
      dfs(step + 1);
      vis[i] = 0;  //这一步不使用该数 置0后允许下一步使用
    }
  }
  return;
}

int main() {
  cin >> n;
  dfs(1);
  return 0;
}
