#include <algorithm>
#include <utility>
// author: (ttzytt)[ttzytt.com]
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <tuple>
using namespace std;

struct Node {
  Node *ch[2];
  int val, prio;
  int cnt;
  int siz;

  Node(int _val) : val(_val), cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    prio = rand();
  }

  Node(Node *_node) {
    val = _node->val, prio = _node->prio, cnt = _node->cnt, siz = _node->siz;
  }

  void upd_siz() {
    siz = cnt;
    if (ch[0] != nullptr) siz += ch[0]->siz;
    if (ch[1] != nullptr) siz += ch[1]->siz;
  }
};

struct none_rot_treap {
#define _3 second.second
#define _2 second.first
  Node *root;

  // --8<-- [start:example186]
  pair<Node *, Node *> split(Node *cur, int key) {
    if (cur == nullptr) return {nullptr, nullptr};
    if (cur->val <= key) {
      // cur 以及它的左子树一定属于分裂后的第一个树
      auto temp = split(cur->ch[1], key);
      // 但是它可能有部分右子树也比 key 小
      cur->ch[1] = temp.first;
      // 我们把小于 key 的那部分拿出来，作为 cur 的右子树，这样整个 cur 都是小于
      // key 的 剩下的那部分右子树成为分裂后的第二个 treap
      cur->upd_siz();
      // 分裂过后树的大小会变化，需要更新
      return {cur, temp.second};
    } else {
      // 同上
      auto temp = split(cur->ch[0], key);
      cur->ch[0] = temp.second;
      cur->upd_siz();
      return {temp.first, cur};
    }
  }

  // --8<-- [end:example186]

  // --8<-- [start:example187]
  tuple<Node *, Node *, Node *> split_by_rk(Node *cur, int rk) {
    if (cur == nullptr) return {nullptr, nullptr, nullptr};
    int ls_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    if (rk <= ls_siz) {
      // 排名和 cur 相等的节点在左子树
      Node *l, *mid, *r;
      tie(l, mid, r) = split_by_rk(cur->ch[0], rk);
      cur->ch[0] = r;  // 返回的第三个 treap 中的排名都大于 rk
      // cur 的左子树被设成 r 后，整个 cur 中节点的排名都大于 rk
      cur->upd_siz();
      return {l, mid, cur};
    } else if (rk <= ls_siz + cur->cnt) {
      // 和 cur 相等的就是当前节点
      Node *lt = cur->ch[0];
      Node *rt = cur->ch[1];
      cur->ch[0] = cur->ch[1] = nullptr;
      // 分裂后第二个 treap 只有一个节点，所有要把它的子树设置为空
      return {lt, cur, rt};
    } else {
      // 排名和 cur 相等的节点在右子树
      // 递归过程同上
      Node *l, *mid, *r;
      tie(l, mid, r) = split_by_rk(cur->ch[1], rk - ls_siz - cur->cnt);
      cur->ch[1] = l;
      cur->upd_siz();
      return {cur, mid, r};
    }
  }

  // --8<-- [end:example187]

  // --8<-- [start:example188]
  Node *merge(Node *u, Node *v) {
    // 传进来的两个树的内部已经符合搜索树的性质了
    // 并且 u 内所有节点的值 < v 内所有节点的值
    // 所以在合并的时候需要维护堆的性质
    // 这里用的是小根堆
    if (u == nullptr && v == nullptr) return nullptr;
    if (u != nullptr && v == nullptr) return u;
    if (v != nullptr && u == nullptr) return v;

    if (u->prio < v->prio) {
      // u 的 prio 比较小，u应该作为父节点
      u->ch[1] = merge(u->ch[1], v);
      // 因为 v 比 u 大，所以把 v 作为 u 的右子树
      u->upd_siz();
      return u;
    } else {
      // v 比较小，v应该作为父节点
      v->ch[0] = merge(u, v->ch[0]);
      // u 比 v 小，所以递归时的参数是这样的
      v->upd_siz();
      return v;
    }
  }

  // --8<-- [end:example188]

  // --8<-- [start:example189]
  void insert(int val) {
    auto temp = split(root, val);
    // 根据 val 的值把整个树分成两个
    // 注意 split 的实现，等于 val 的子树是在左子树的
    auto l_tr = split(temp.first, val - 1);
    // l_tr 的左子树 <= val - 1，如果有 = val 的节点，那一定在右子树
    Node *new_node;
    if (l_tr.second == nullptr) {
      // 没有这个节点就新开，否则直接增加重复次数．
      new_node = new Node(val);
    } else {
      l_tr.second->cnt++;
      l_tr.second->upd_siz();
    }
    Node *l_tr_combined =
        merge(l_tr.first, l_tr.second == nullptr ? new_node : l_tr.second);
    // 合并 T_1 left 和 T_1 right
    root = merge(l_tr_combined, temp.second);
    // 合并 T_1 和 T_2
  }

  // --8<-- [end:example189]

  // --8<-- [start:example190]
  void del(int val) {
    auto temp = split(root, val);
    auto l_tr = split(temp.first, val - 1);
    if (l_tr.second->cnt > 1) {
      // 如果这个节点的重复次数大于 1，减小即可
      l_tr.second->cnt--;
      l_tr.second->upd_siz();
      l_tr.first = merge(l_tr.first, l_tr.second);
    } else {
      if (temp.first == l_tr.second) {
        // 有可能整个 T_1 只有这个节点，所以也需要把这个点设成 null
        // 来标注已经删除
        temp.first = nullptr;
      }
      delete l_tr.second;
      l_tr.second = nullptr;
    }
    root = merge(l_tr.first, temp.second);
  }

  // --8<-- [end:example190]

  // --8<-- [start:example191]
  int qrank_by_val(Node *cur, int val) {
    auto temp = split(cur, val - 1);
    int ret =
        (temp.first == nullptr ? 0 : temp.first->siz) + 1;  // 根据定义 + 1
    root = merge(temp.first, temp.second);  // 拆好了再粘回去
    return ret;
  }

  // --8<-- [end:example191]

  // --8<-- [start:example192]
  int qval_by_rank(Node *cur, int rk) {
    Node *l, *mid, *r;
    tie(l, mid, r) = split_by_rk(cur, rk);
    int ret = mid->val;
    root = merge(merge(l, mid), r);
    return ret;
  }

  // --8<-- [end:example192]

  // --8<-- [start:example193]
  int qprev(int val) {
    auto temp = split(root, val - 1);
    // temp.first 就是值小于 val 的子树
    int ret = qval_by_rank(temp.first, temp.first->siz);
    // 这里查询的是，所有小于 val 的节点里面，最大的那个的值
    root = merge(temp.first, temp.second);
    return ret;
  }

  // --8<-- [end:example193]

  // --8<-- [start:example194]
  int qnex(int val) {
    auto temp = split(root, val);
    int ret = qval_by_rank(temp.second, 1);
    // 查询所有大于 val 的子树里面，值最小的那个
    root = merge(temp.first, temp.second);
    return ret;
  }

  // --8<-- [end:example194]
};

none_rot_treap tr;

int main() {
  srand(time(nullptr));
  int t;
  scanf("%d", &t);
  while (t--) {
    int mode;
    int num;
    scanf("%d%d", &mode, &num);
    switch (mode) {
      case 1:
        tr.insert(num);
        break;
      case 2:
        tr.del(num);
        break;
      case 3:
        printf("%d\n", tr.qrank_by_val(tr.root, num));
        break;
      case 4:
        printf("%d\n", tr.qval_by_rank(tr.root, num));
        break;
      case 5:
        printf("%d\n", tr.qprev(num));
        break;
      case 6:
        printf("%d\n", tr.qnex(num));
        break;
    }
  }
}
