#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> w(n + 1), stk(n + 1), ls(n + 1), rs(n + 1);
  for (int i = 1; i <= n; ++i) cin >> w[i];
  int top = 0;
  // --8<-- [start:example26]
  // stk 维护笛卡尔树中节点对应到序列中的下标
  for (int i = 1; i <= n; i++) {
    int k = top;  // top 表示操作前的栈顶，k 表示当前栈顶
    while (k > 0 && w[stk[k]] > w[i]) k--;  // 维护右链上的节点
    if (k) rs[stk[k]] = i;  // 栈顶元素.右儿子 := 当前元素
    if (k < top) ls[i] = stk[k + 1];  // 当前元素.左儿子 := 上一个被弹出的元素
    stk[++k] = i;                     // 当前元素入栈
    top = k;
  }
  // --8<-- [end:example26]
  for (int i = 1; i <= n; ++i) cout << ls[i] << " " << rs[i] << "\n";
}
