#include <iostream>
#include <vector>
using namespace std;

// --8<-- [start:core]
pair<bool, vector<int>> findCycle(
    vector<int>
        nxt)  // nxt[i]表示i在单向链表中指向的节点（0-indexed），-1表示没有指向任何节点
{
  int fast = 0, slow = 0;
  do  // 先判断有没有环
  {
    if (nxt[fast] == -1 || nxt[nxt[fast]] == -1) {
      return make_pair(false, vector<int>());  // 没有环
    }
    fast = nxt[nxt[fast]];
    slow = nxt[slow];
  } while (fast != slow);
  slow = 0;
  while (slow != fast)  // 再找入环位置
  {
    slow = nxt[slow];
    fast = nxt[fast];
  }
  vector<int> cycle;
  do  // 最后找出整个环
  {
    cycle.push_back(slow);
    slow = nxt[slow];
  } while (slow != fast);
  return make_pair(true, cycle);
}

// --8<-- [end:core]
int main() {
  int n;
  while (cin >> n) {
    vector<int> nxt;
    nxt.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> nxt[i];
    }
    pair<bool, vector<int>> cycle = findCycle(nxt);
    if (cycle.first) {
      cout << "Cycle:";
      for (int i = 0; i < cycle.second.size(); i++) {
        cout << " " << cycle.second[i];
      }
      cout << endl;
    } else {
      cout << "No cycle.\n";
    }
  }
}
