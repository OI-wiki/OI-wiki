#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

int main() {
  int t, x;
  scanf("%d", &t);
  while (t--) {
    // 大根堆，维护前一半元素（存小值）
    priority_queue<int, vector<int>, less<int> > a;
    // 小根堆，维护后一半元素（存大值）
    priority_queue<int, vector<int>, greater<int> > b;
    while (scanf("%d", &x) && x) {
      // 若为查询并删除操作，输出并删除大根堆堆顶元素
      // 因为这题要求输出中位数中较小者（偶数个数字会存在两个中位数候选）
      // 这个和上面的第k大讲解有稍许出入，但如果理解了上面的，这个稍微变通下便可理清
      if (x == -1) {
        printf("%d\n", a.top());
        a.pop();
      }
      // 若为插入操作，根据大根堆堆顶的元素值，选择合适的堆进行插入
      else {
        if (a.empty() || x <= a.top())
          a.push(x);
        else
          b.push(x);
      }
      // 对对顶堆进行调整
      if (a.size() > (a.size() + b.size() + 1) / 2) {
        b.push(a.top());
        a.pop();
      } else if (a.size() < (a.size() + b.size() + 1) / 2) {
        a.push(b.top());
        b.pop();
      }
    }
  }
  return 0;
}
