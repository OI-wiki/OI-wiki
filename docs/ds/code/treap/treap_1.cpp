#include <algorithm>
#include <utility>
// author: (ttzytt)[ttzytt.com]
#include <cstdint>
#include <cstdio>
#include <cstdlib>
using namespace std;

// --8<-- [start:example178]
struct Node {
  Node *ch[2];  // 两个子节点的地址
  int val, rank;
  int rep_cnt;  // 当前这个值（val）重复出现的次数
  int siz;      // 以当前节点为根的子树大小

  Node(int val) : val(val), rep_cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    rank = rand();
    // 注意初始化的时候，rank 是随机给出的
  }

  void upd_siz() {
    // 用于旋转和删除过后，重新计算 siz 的值
    siz = rep_cnt;
    if (ch[0] != nullptr) siz += ch[0]->siz;
    if (ch[1] != nullptr) siz += ch[1]->siz;
  }
};

// --8<-- [end:example178]

class Treap {
 private:
  Node *root;

  constexpr static int NIL = -1;  // 用于表示查询的值不存在

  int q_prev_tmp = 0, q_nex_tmp = 0;

  // --8<-- [start:example179]
  enum rot_type { LF = 1, RT = 0 };

  void _rotate(Node *&cur,
               rot_type dir) {  // dir参数代表旋转的方向 0为右旋，1为左旋
    // 注意传进来的 cur 是指针的引用，也就是改了这个
    // cur，变量是跟着一起改的，如果这个 cur 是别的 树的子节点，根据 ch
    // 找过来的时候，也是会找到这里的

    // 以下的代码解释的均是左旋时的情况
    Node *tmp = cur->ch[dir];  // 让 C 变成根节点，
                               // 这里的 tmp
                               // 是一个临时的节点指针，指向成为新的根节点的节点

    /* 左旋：也就是让右子节点变成根节点
     *         A                 C
     *        / \               / \
     *       B  C    ---->     A   E
     *         / \            / \
     *        D   E          B   D
     */
    cur->ch[dir] = tmp->ch[!dir];    // 让 A 的右子节点变成 D
    tmp->ch[!dir] = cur;             // 让 C 的左子节点变成 A
    cur->upd_siz(), tmp->upd_siz();  // 更新大小信息
    cur =
        tmp;  // 最后把临时储存 C 树的变量赋值到当前根节点上（注意 cur 是引用）
  }

  // --8<-- [end:example179]

  // --8<-- [start:example180]
  void _insert(Node *&cur, int val) {
    if (cur == nullptr) {
      // 没这个节点直接新建
      cur = new Node(val);
      return;
    } else if (val == cur->val) {
      // 如果有这个值相同的节点，就把重复数量加一
      cur->rep_cnt++;
      cur->siz++;
    } else if (val < cur->val) {
      // 维护搜索树性质，val 比当前节点小就插到左边，反之亦然
      _insert(cur->ch[0], val);
      if (cur->ch[0]->rank < cur->rank) {
        // 小根堆中，上面节点的优先级一定更小
        // 因为新插的左子节点比父节点小，现在需要让左子节点变成父节点
        _rotate(cur, RT);  // 注意前面的旋转性质，要把左子节点转上来，需要右旋
      }
      cur->upd_siz();  // 插入之后大小会变化，需要更新
    } else {
      _insert(cur->ch[1], val);
      if (cur->ch[1]->rank < cur->rank) {
        _rotate(cur, LF);
      }
      cur->upd_siz();
    }
  }

  // --8<-- [end:example180]

  // --8<-- [start:example181]
  void _del(Node *&cur, int val) {
    if (val > cur->val) {
      _del(cur->ch[1], val);
      // 值更大就在右子树，反之亦然
      cur->upd_siz();
    } else if (val < cur->val) {
      _del(cur->ch[0], val);
      cur->upd_siz();
    } else {
      if (cur->rep_cnt > 1) {
        // 如果要删除的节点是重复的，可以直接把重复值减小
        cur->rep_cnt--, cur->siz--;
        return;
      }
      uint8_t state = 0;
      state |= (cur->ch[0] != nullptr);
      state |= ((cur->ch[1] != nullptr) << 1);
      // 00都无，01有左无右，10，无左有右，11都有
      Node *tmp = cur;
      switch (state) {
        case 0:
          delete cur;
          cur = nullptr;
          // 没有任何子节点，就直接把这个节点删了
          break;
        case 1:  // 有左无右
          cur = tmp->ch[0];
          // 把根变成左儿子，然后把原来的根节删了，注意这里的 tmp 是从 cur
          // 复制的，而 cur 是引用
          delete tmp;
          break;
        case 2:  // 有右无左
          cur = tmp->ch[1];
          delete tmp;
          break;
        case 3:
          rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank
                             ? RT
                             : LF;  // dir 是 rank 更小的那个儿子
          _rotate(cur, dir);  // 这里的旋转可以把优先级更小的儿子转上去，rt 是
                              // 0， 而 lf 是 1，刚好跟实际的子树下标反过来
          _del(
              cur->ch[!dir],
              val);  // 旋转完成后原来的根节点就在旋方向那边，所以需要
                     // 继续把这个原来的根节点删掉
                     // 如果说要删的这个节点是在整个树的「上层的」，那我们会一直通过这
                     // 这里的旋转操作，把它转到没有子树了（或者只有一个），再删掉它．
          cur->upd_siz();
          // 删除会造成大小改变
          break;
      }
    }
  }

  // --8<-- [end:example181]

  // --8<-- [start:example182]
  int _query_rank(Node *cur, int val) {
    int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    // 这个树中小于 val 的节点的数量
    if (val == cur->val)
      // 如果这个节点就是要查的节点
      return less_siz + 1;
    else if (val < cur->val) {
      if (cur->ch[0] != nullptr)
        return _query_rank(cur->ch[0], val);
      else
        return 1;  // 如果左子树是空的，说比最小的节点还要小，那这个数字就是最小的
    } else {
      if (cur->ch[1] != nullptr)
        // 如果要查的值比这个节点大，那这个节点的左子树以及这个节点自身肯定都比要查的值小
        // 所以要加上这两个值，再加上往右边找的结果
        // （以右子树为根的子树中，val 这个值的大小的排名）
        return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
      else
        return cur->siz + 1;
      // 没有右子树的话直接整个树 + 1 相当于 less_siz + cur->rep_cnt + 1
    }
  }

  // --8<-- [end:example182]

  // --8<-- [start:example183]
  int _query_val(Node *cur, int rank) {
    // 查询树中第 rank 大的节点的值
    int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    // less siz 是左子树的大小
    if (rank <= less_siz)
      return _query_val(cur->ch[0], rank);
    else if (rank <= less_siz + cur->rep_cnt)
      return cur->val;
    else
      return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);  // 见前文
  }

  // --8<-- [end:example183]

  // --8<-- [start:example184]
  int _query_prev(Node *cur, int val) {
    if (val <= cur->val) {
      // 还是比 val 大，所以往左子树找
      if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
    } else {
      // 只有能进到这个 else 里，才会更新 q_prev_tmp 的值
      q_prev_tmp = cur->val;
      // 当前节点已经比 val，小了，但是不确定是否是最大的，所以要到右子树继续找
      if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
      // 接下来的递归可能不会更改 q_prev_tmp
      // 了，那就直接返回这个值，总之返回的就是最后一次进到 这个 else 中的
      // cur->val
      return q_prev_tmp;
    }
    return NIL;
  }

  // --8<-- [end:example184]

  // --8<-- [start:example185]
  int _query_nex(Node *cur, int val) {
    if (val >= cur->val) {
      if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
    } else {
      q_nex_tmp = cur->val;
      if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
      return q_nex_tmp;
    }
    return NIL;
  }

  // --8<-- [end:example185]

 public:
  void insert(int val) { _insert(root, val); }

  void del(int val) { _del(root, val); }

  int query_rank(int val) { return _query_rank(root, val); }

  int query_val(int rank) { return _query_val(root, rank); }

  int query_prev(int val) { return _query_prev(root, val); }

  int query_nex(int val) { return _query_nex(root, val); }
};

Treap tr;

int main() {
  srand(0);
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
        printf("%d\n", tr.query_rank(num));
        break;
      case 4:
        printf("%d\n", tr.query_val(num));
        break;
      case 5:
        printf("%d\n", tr.query_prev(num));
        break;
      case 6:
        printf("%d\n", tr.query_nex(num));
        break;
    }
  }
}
