#include <algorithm>
#include <utility>
// author: (ttzytt)[ttzytt.com]
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// 参考：https://www.cnblogs.com/Equinox-Flower/p/10785292.html
struct Node {
  Node* ch[2];
  int val, prio;
  int cnt;
  int siz;
  bool to_rev = false;  // 需要把这个子树下的每一个节点都翻转过来

  Node(int _val) : val(_val), cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    prio = rand();
  }

  int upd_siz() {
    siz = cnt;
    if (ch[0] != nullptr) siz += ch[0]->siz;
    if (ch[1] != nullptr) siz += ch[1]->siz;
    return siz;
  }

  // --8<-- [start:example195]
  // 这里这个 pushdown 是 Node 类的成员函数，其中 to_rev 是懒标记
  void pushdown() {
    swap(ch[0], ch[1]);
    if (ch[0] != nullptr) ch[0]->to_rev ^= 1;
    if (ch[1] != nullptr) ch[1]->to_rev ^= 1;
    to_rev = false;
  }

  void check_tag() {
    if (to_rev) pushdown();
  }

  // --8<-- [end:example195]
};

struct Seg_treap {
  Node* root;
// --8<-- [start:example196]
#define siz(_) (_ == nullptr ? 0 : _->siz)

  pair<Node*, Node*> split(Node* cur, int sz) {
    // 按照树的大小判断
    if (cur == nullptr) return {nullptr, nullptr};
    cur->check_tag();
    // 分裂前先下传
    if (sz <= siz(cur->ch[0])) {
      auto temp = split(cur->ch[0], sz);
      cur->ch[0] = temp.second;
      cur->upd_siz();
      return {temp.first, cur};
    } else {
      auto temp =
          split(cur->ch[1],
                sz - siz(cur->ch[0]) -
                    1);  // 这里的转换在有旋 treap 的 「根据排名查询值有讲」
      cur->ch[1] = temp.first;
      cur->upd_siz();
      return {cur, temp.second};
    }
  }

  // --8<-- [end:example196]

  // --8<-- [start:example197]
  Node* merge(Node* sm, Node* bg) {
    // small, big
    if (sm == nullptr && bg == nullptr) return nullptr;
    if (sm != nullptr && bg == nullptr) return sm;
    if (sm == nullptr && bg != nullptr) return bg;
    sm->check_tag(), bg->check_tag();
    if (sm->prio < bg->prio) {
      sm->ch[1] = merge(sm->ch[1], bg);
      sm->upd_siz();
      return sm;
    } else {
      bg->ch[0] = merge(sm, bg->ch[0]);
      bg->upd_siz();
      return bg;
    }
  }

  // --8<-- [end:example197]

  void insert(int val) {
    auto temp = split(root, val);
    auto l_tr = split(temp.first, val - 1);
    Node* new_node;
    if (l_tr.second == nullptr) new_node = new Node(val);
    Node* l_tr_combined =
        merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
    root = merge(l_tr_combined, temp.second);
  }

  // --8<-- [start:example198]
  void seg_rev(int l, int r) {
    // 这里的 less 和 more 是相对于 l 的
    auto less = split(root, l - 1);
    // 所有小于等于 l - 1 的会在 less 的左子树
    auto more = split(less.second, r - l + 1);
    // 从 l 开始的前 r - l + 1 个元素的区间
    more.first->to_rev = true;
    root = merge(less.first, merge(more.first, more.second));
  }

  // --8<-- [end:example198]

  // --8<-- [start:example199]
  void print(Node* cur) {
    if (cur == nullptr) return;
    cur->check_tag();
    // 中序遍历 -> 先左子树，再自己，最后右子树
    print(cur->ch[0]);
    cout << cur->val << " ";
    print(cur->ch[1]);
  }

  // --8<-- [end:example199]
};

Seg_treap tr;

int main() {
  srand(time(nullptr));
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) tr.insert(i);
  while (m--) {
    int l, r;
    cin >> l >> r;
    tr.seg_rev(l, r);
  }
  tr.print(tr.root);
}
