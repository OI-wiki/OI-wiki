#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
using namespace std;

// Sample source: https://www.luogu.com.cn/problem/P1840
// Maintain black (1) and white (0) intervals.
int remaining;

// --8<-- [start:node]
using i64 = std::int64_t;

struct Block {
  Block *next;  // 链表下一节点
  int l, r;     // 区间范围
  i64 val;      // 区间上的值

  Block(Block *next, int l, int r, i64 val)
      : next(next), l(l), r(r), val(val) {}

  bool operator<(const Block &b) const { return val < b.val; }
} *root;

// --8<-- [end:node]
// --8<-- [start:split]
// 返回左端点为 mid+1 的区间
Block *split(int mid) {
  for (Block *b = root; b; b = b->next) {  // 遍历链表
    if (b->l == mid + 1) {                 // 左端点为 mid+1
      return b;
    }
    // 寻找能包含 mid 和 mid+1 的区间 [l, r]，将其被拆分成 [l, mid] 和 [mid+1,
    // r]
    if (b->l <= mid && mid + 1 <= b->r) {
      b->next = new Block(b->next, mid + 1, b->r, b->val);
      b->r = mid;
      return b->next;
    }
  }
  return nullptr;  // 未找到，返回空
}

// --8<-- [end:split]
// --8<-- [start:prepare]
Block *lb, *rb;

// 预分裂，保证后续操作在 [l, r] 内部
void prepare(int l, int r) {
  lb = split(l - 1);
  rb = split(r);
}

// --8<-- [end:prepare]
// --8<-- [start:assign]
void assign(int l, int r, i64 val) {
  prepare(l, r);
  Block *current = lb->next;
  while (current != rb) {
    Block *next = current->next;
    delete current;
    current = next;
  }
  lb->r = r;  // 将区间 [lb.l, lb.r] 修改成 [lb.l, r]
  lb->val = val;
  lb->next = rb;  // 将 [lb.l, r] 链至其右侧相邻区间
}

// 被覆盖区间中不再使用的节点已经释放．
// --8<-- [end:assign]
// --8<-- [start:perform]
void perform(int l, int r) {
  prepare(l, r);
  for (Block *b = lb; b != rb; b = b->next) {
    remaining -= static_cast<int>((b->r - b->l + 1) * b->val);
  }
}

// --8<-- [end:perform]

int main() {
  int n, m;
  if (!(cin >> n >> m)) return 0;
  remaining = n;
  root = new Block(nullptr, 1, n, 1);
  while (m--) {
    int l, r;
    cin >> l >> r;
    perform(l, r);
    assign(l, r, 0);
    cout << remaining << '\n';
  }
  while (root) {
    Block *next = root->next;
    delete root;
    root = next;
  }
}
