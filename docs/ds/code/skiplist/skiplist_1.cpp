// --8<-- [start:core]
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
using namespace std;

template <typename K, typename V>
struct SkipListNode {
  int level;
  K key;
  V value;
  SkipListNode **forward;

  SkipListNode() : level(0), key(), value(), forward(nullptr) {}

  SkipListNode(K k, V v, int l, SkipListNode *nxt = NULL) {
    key = k;
    value = v;
    level = l;
    forward = new SkipListNode *[l + 1];
    for (int i = 0; i <= l; ++i) forward[i] = nxt;
  }

  ~SkipListNode() {
    if (forward != NULL) delete[] forward;
  }
};

template <typename K, typename V>
struct SkipList {
  static constexpr int MAXL = 32;
  static constexpr int P = 4;
  static constexpr int S = 0xFFFF;
  static constexpr int PS = S / P;
  static constexpr int INVALID = INT_MAX;

  SkipListNode<K, V> *head, *tail;
  int length;
  int level;

  SkipList() {
    srand(time(nullptr));

    level = length = 0;
    tail = new SkipListNode<K, V>(INVALID, 0, 0);
    head = new SkipListNode<K, V>(INVALID, 0, MAXL, tail);
  }

  ~SkipList() {
    auto p = head;
    while (p != tail) {
      auto next = p->forward[0];
      delete p;
      p = next;
    }
    delete tail;
  }

  // --8<-- [start:example154]
  int randomLevel() {
    int lv = 1;
    // MAXL = 32, S = 0xFFFF, PS = S * P, P = 1 / 4
    while ((rand() & S) < PS) ++lv;
    return min(MAXL, lv);
  }

  // --8<-- [end:example154]

  // --8<-- [start:example156]
  void insert(const K &key, const V &value) {
    // 用于记录需要修改的节点
    SkipListNode<K, V> *update[MAXL + 1];

    SkipListNode<K, V> *p = head;
    for (int i = level; i >= 0; --i) {
      while (p->forward[i]->key < key) {
        p = p->forward[i];
      }
      // 第 i 层需要修改的节点为 p
      update[i] = p;
    }
    p = p->forward[0];

    // 若已存在则修改
    if (p->key == key) {
      p->value = value;
      return;
    }

    // 获取新节点的最大层数
    int lv = randomLevel();
    if (lv > level) {
      lv = ++level;
      update[lv] = head;
    }

    // 新建节点
    SkipListNode<K, V> *newNode = new SkipListNode<K, V>(key, value, lv);
    // 在第 0~lv 层插入新节点
    for (int i = lv; i >= 0; --i) {
      p = update[i];
      newNode->forward[i] = p->forward[i];
      p->forward[i] = newNode;
    }

    ++length;
  }

  // --8<-- [end:example156]

  // --8<-- [start:example157]
  bool erase(const K &key) {
    // 用于记录需要修改的节点
    SkipListNode<K, V> *update[MAXL + 1];

    SkipListNode<K, V> *p = head;
    for (int i = level; i >= 0; --i) {
      while (p->forward[i]->key < key) {
        p = p->forward[i];
      }
      // 第 i 层需要修改的节点为 p
      update[i] = p;
    }
    p = p->forward[0];

    // 节点不存在
    if (p->key != key) return false;

    // 从最底层开始删除
    for (int i = 0; i <= level; ++i) {
      // 如果这层没有 p 删除就完成了
      if (update[i]->forward[i] != p) {
        break;
      }
      // 断开 p 的连接
      update[i]->forward[i] = p->forward[i];
    }

    // 回收空间
    delete p;

    // 删除节点可能导致最大层数减少
    while (level > 0 && head->forward[level] == tail) --level;

    // 跳表长度
    --length;
    return true;
  }

  // --8<-- [end:example157]

  V &operator[](const K &key) {
    if (!count(key)) insert(key, 0);
    return find(key);
  }

  // --8<-- [start:example155]
  V &find(const K &key) {
    SkipListNode<K, V> *p = head;

    // 找到该层最后一个键值小于 key 的节点，然后走向下一层
    for (int i = level; i >= 0; --i) {
      while (p->forward[i]->key < key) {
        p = p->forward[i];
      }
    }
    // 现在是小于，所以还需要再往后走一步
    p = p->forward[0];

    // 成功找到节点
    if (p->key == key) return p->value;

    // 节点不存在，返回 INVALID
    return tail->value;
  }

  // --8<-- [end:example155]

  bool count(const K &key) {
    auto p = head;
    for (int i = level; i >= 0; --i)
      while (p->forward[i] != tail && p->forward[i]->key < key)
        p = p->forward[i];
    p = p->forward[0];
    return p != tail && p->key == key;
  }
};

int benchmark() {
  SkipList<int, int> L;
  map<int, int> M;

  clock_t s = clock();

  for (int i = 0; i < 1e5; ++i) {
    int key = rand(), value = rand();
    L[key] = value;
    M[key] = value;
  }

  for (int i = 0; i < 1e5; ++i) {
    int key = rand();
    if (i & 1) {
      L.erase(key);
      M.erase(key);
    } else {
      int r1 = L.count(key) ? L[key] : 0;
      int r2 = M.count(key) ? M[key] : 0;
      assert(r1 == r2);
    }
  }

  clock_t e = clock();
  cout << "Time elapsed: " << (double)(e - s) / CLOCKS_PER_SEC << endl;
  // about 0.2s

  return 0;
}

// --8<-- [end:core]

int main() {
  SkipList<int, int> values;
  int q;
  cin >> q;
  while (q--) {
    int op, key, value;
    cin >> op >> key;
    if (op == 1) {
      cin >> value;
      values.insert(key, value);
    } else if (op == 2)
      cout << values.erase(key) << '\n';
    else if (op == 3)
      cout << values.count(key) << '\n';
    else if (op == 4)
      cout << values.find(key) << '\n';
    else
      cout << values[key] << '\n';
  }
}
