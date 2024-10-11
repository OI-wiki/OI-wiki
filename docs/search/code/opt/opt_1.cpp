#include <iostream>
constexpr int N = 16;
int is_working[N] = {0};  // 某项工作是否被分配
int tm[N][N];             // 完成某项工作所需的时间
int cost_time_total_min;  // 完成 n 份工作的最小时间总和

// i 表示第几个人，count 表示工作费用总和
void work(int i, int count, int n) {
  // 如果 i 超出了所能分配的最大工作件数，表示分配完成，并且 count 比原来
  // cost_time_total_min 花费少，则更新 cost_time_total_min 的值
  if (i > n && count < cost_time_total_min) {
    cost_time_total_min = count;
    return;
  }
  // 回溯思想
  if (count < cost_time_total_min) {
    // j 表示第几件工作
    for (int j = 1; j <= n; j++) {
      // 如果工作未被分配 is_working = 0
      if (is_working[j] == 0) {
        // 分配工作 is_working = 1
        is_working[j] = 1;
        // 工作交给第 i + 1 个人
        work(i + 1, count + tm[i][j], n);
        // 在一轮迭代完成之后，返回到上一个人，要对此次的工作进行重新分配
        // 将 is_working[j] 重设为 0
        is_working[j] = 0;
      }
    }
  }
}

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> tm[i][j];
    }
    cost_time_total_min += tm[i][i];
  }
  work(1, 0, n);
  cout << cost_time_total_min << '\n';
  return 0;
}
