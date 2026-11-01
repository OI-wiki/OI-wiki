#include <algorithm>
#include <utility>
// --8<-- [start:display]
// author: (ttzytt)[ttzytt.com]
#include <cstdint>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct Node {
  Node *ch[2];
  int val, rank;
  int rep_cnt;
  int siz;

  Node(int val) : val(val), rep_cnt(1), siz(1) {
    ch[0] = ch[1] = nullptr;
    rank = rand();
  }

  void upd_siz() {
    siz = rep_cnt;
    if (ch[0] != nullptr) siz += ch[0]->siz;
    if (ch[1] != nullptr) siz += ch[1]->siz;
  }
};

class Treap {
 private:
  Node *root;

  constexpr static int NIL = -1;  // 用于表示查询的值不存在

  enum rot_type { LF = 1, RT = 0 };

  int q_prev_tmp = 0, q_nex_tmp = 0;

  void _rotate(Node *&cur, rot_type dir) {  // 0为右旋，1为左旋
    Node *tmp = cur->ch[dir];
    cur->ch[dir] = tmp->ch[!dir];
    tmp->ch[!dir] = cur;
    cur->upd_siz(), tmp->upd_siz();
    cur = tmp;
  }

  void _insert(Node *&cur, int val) {
    if (cur == nullptr) {
      cur = new Node(val);
      return;
    } else if (val == cur->val) {
      cur->rep_cnt++;
      cur->siz++;
    } else if (val < cur->val) {
      _insert(cur->ch[0], val);
      if (cur->ch[0]->rank < cur->rank) {
        _rotate(cur, RT);
      }
      cur->upd_siz();
    } else {
      _insert(cur->ch[1], val);
      if (cur->ch[1]->rank < cur->rank) {
        _rotate(cur, LF);
      }
      cur->upd_siz();
    }
  }

  void _del(Node *&cur, int val) {
    if (val > cur->val) {
      _del(cur->ch[1], val);
      cur->upd_siz();
    } else if (val < cur->val) {
      _del(cur->ch[0], val);
      cur->upd_siz();
    } else {
      if (cur->rep_cnt > 1) {
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
          break;
        case 1:  // 有左无右
          cur = tmp->ch[0];
          delete tmp;
          break;
        case 2:  // 有右无左
          cur = tmp->ch[1];
          delete tmp;
          break;
        case 3:
          rot_type dir = cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;
          _rotate(cur, dir);
          _del(cur->ch[!dir], val);
          cur->upd_siz();
          break;
      }
    }
  }

  int _query_rank(Node *cur, int val) {
    int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    if (val == cur->val)
      return less_siz + 1;
    else if (val < cur->val) {
      if (cur->ch[0] != nullptr)
        return _query_rank(cur->ch[0], val);
      else
        return 1;
    } else {
      if (cur->ch[1] != nullptr)
        return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
      else
        return cur->siz + 1;
    }
  }

  int _query_val(Node *cur, int rank) {
    int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
    if (rank <= less_siz)
      return _query_val(cur->ch[0], rank);
    else if (rank <= less_siz + cur->rep_cnt)
      return cur->val;
    else
      return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);
  }

  int _query_prev(Node *cur, int val) {
    if (val <= cur->val) {
      if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
    } else {
      q_prev_tmp = cur->val;
      if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
      return q_prev_tmp;
    }
    return NIL;
  }

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

// --8<-- [end:display]
