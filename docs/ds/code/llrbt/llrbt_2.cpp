#include <functional>
#include <iostream>
#include <string>
// --8<-- [start:core]
#include <algorithm>
#include <memory>
#include <vector>

template <class Key, class Compare = std::less<Key>>
class Set {
 private:
  enum NodeColor { kBlack = 0, kRed = 1 };

  struct Node {
    Key key;
    Node *lc{nullptr}, *rc{nullptr};
    size_t size{0};
    NodeColor color;  // the color of the parent link

    Node(Key key, NodeColor color, size_t size)
        : key(key), color(color), size(size) {}

    Node() = default;
  };

  void destroyTree(Node *root) const {
    if (root != nullptr) {
      destroyTree(root->lc);
      destroyTree(root->rc);
      root->lc = root->rc = nullptr;
      delete root;
    }
  }

  bool is_red(const Node *nd) const {
    return nd == nullptr ? false : nd->color;  // kRed == 1, kBlack == 0
  }

  size_t size(const Node *nd) const { return nd == nullptr ? 0 : nd->size; }

  Node *rotate_left(Node *node) const {
    // left rotate a red link
    //          <1>                   <2>
    //        /    \\               //    \
    //       *      <2>    ==>     <1>     *
    //             /   \          /   \
    //            *     *        *     *
    Node *res = node->rc;
    node->rc = res->lc;
    res->lc = node;
    res->color = node->color;
    node->color = kRed;
    res->size = node->size;
    node->size = size(node->lc) + size(node->rc) + 1;
    return res;
  }

  Node *rotate_right(Node *node) const {
    // right rotate a red link
    //            <1>               <2>
    //          //    \           /    \\
    //         <2>     *   ==>   *      <1>
    //        /   \                    /   \
    //       *     *                  *     *
    Node *res = node->lc;
    node->lc = res->rc;
    res->rc = node;
    res->color = node->color;
    node->color = kRed;
    res->size = node->size;
    node->size = size(node->lc) + size(node->rc) + 1;
    return res;
  }

  NodeColor neg_color(NodeColor n) const { return n == kBlack ? kRed : kBlack; }

  void color_flip(Node *node) const {
    node->color = neg_color(node->color);
    node->lc->color = neg_color(node->lc->color);
    node->rc->color = neg_color(node->rc->color);
  }

  Node *insert(Node *root, const Key &key) const;
  Node *delete_arbitrary(Node *root, Key key) const;
  Node *delete_min(Node *root) const;
  Node *move_red_right(Node *root) const;
  Node *move_red_left(Node *root) const;
  Node *fix_up(Node *root) const;
  const Key &get_min(Node *root) const;
  void serialize(Node *root, std::vector<Key> *) const;
  void print_tree(Set::Node *root, int indent) const;
  Compare cmp_ = Compare();
  Node *root_{nullptr};

 public:
  using KeyType = Key;
  using ValueType = Key;
  using SizeType = std::size_t;
  using DifferenceType = std::ptrdiff_t;
  using KeyCompare = Compare;
  using ValueCompare = Compare;
  using Reference = Key &;
  using ConstReference = const Key &;

  Set() = default;

  Set(const Set &) = delete;

  Set(Set &&) = delete;

  ~Set() { destroyTree(root_); }

  SizeType size() const;

  SizeType count(const KeyType &key) const;

  SizeType erase(const KeyType &key);

  void clear();

  void insert(const KeyType &key);

  bool empty() const;

  std::vector<Key> serialize() const;

  void print_tree() const;
};

template <class Key, class Compare>
typename Set<Key, Compare>::SizeType Set<Key, Compare>::count(
    ConstReference key) const {
  Node *x = root_;
  while (x != nullptr) {
    if (key == x->key) return 1;
    if (cmp_(key, x->key))  // if (key < x->key)
      x = x->lc;
    else
      x = x->rc;
  }
  return 0;
}

template <class Key, class Compare>
typename Set<Key, Compare>::SizeType Set<Key, Compare>::erase(
    const KeyType &key) {
  if (count(key) > 0) {
    if (!is_red(root_->lc) && !(is_red(root_->rc))) root_->color = kRed;
    root_ = delete_arbitrary(root_, key);
    if (root_ != nullptr) root_->color = kBlack;
    return 1;
  } else {
    return 0;
  }
}

template <class Key, class Compare>
void Set<Key, Compare>::clear() {
  destroyTree(root_);
  root_ = nullptr;
}

template <class Key, class Compare>
void Set<Key, Compare>::insert(const KeyType &key) {
  root_ = insert(root_, key);
  root_->color = kBlack;
}

template <class Key, class Compare>
bool Set<Key, Compare>::empty() const {
  return size(root_) == 0;
}

template <class Key, class Compare>
typename Set<Key, Compare>::Node *Set<Key, Compare>::insert(
    Set::Node *root, const Key &key) const {
  if (root == nullptr) return new Node(key, kRed, 1);
  if (root->key == key)
    ;
  else if (cmp_(key, root->key))  // if (key < root->key)
    root->lc = insert(root->lc, key);
  else
    root->rc = insert(root->rc, key);
  return fix_up(root);
}

template <class Key, class Compare>
typename Set<Key, Compare>::Node *Set<Key, Compare>::delete_min(
    Set::Node *root) const {
  if (root->lc == nullptr) {
    delete root;
    return nullptr;
  }
  if (!is_red(root->lc) && !is_red(root->lc->lc)) {
    // make sure either root->lc or root->lc->lc is red
    // thus make sure we will delete a red node in the end
    root = move_red_left(root);
  }
  root->lc = delete_min(root->lc);
  return fix_up(root);
}

template <class Key, class Compare>
typename Set<Key, Compare>::Node *Set<Key, Compare>::move_red_right(
    Set::Node *root) const {
  color_flip(root);
  if (is_red(root->lc->lc)) {  // assume that root->lc != nullptr when calling
                               // this function
    root = rotate_right(root);
    color_flip(root);
  }
  return root;
}

template <class Key, class Compare>
typename Set<Key, Compare>::Node *Set<Key, Compare>::move_red_left(
    Set::Node *root) const {
  color_flip(root);
  if (is_red(root->rc->lc)) {
    // assume that root->rc != nullptr when calling this function
    root->rc = rotate_right(root->rc);
    root = rotate_left(root);
    color_flip(root);
  }
  return root;
}

template <class Key, class Compare>
typename Set<Key, Compare>::Node *Set<Key, Compare>::fix_up(
    Set::Node *root) const {
  if (is_red(root->rc) && !is_red(root->lc))  // fix right leaned red link
    root = rotate_left(root);
  if (is_red(root->lc) &&
      is_red(root->lc->lc))  // fix doubly linked left leaned red link
    // if (root->lc == nullptr), then the second expr won't be evaluated
    root = rotate_right(root);
  if (is_red(root->lc) && is_red(root->rc))
    // break up 4 node
    color_flip(root);
  root->size = size(root->lc) + size(root->rc) + 1;
  return root;
}

template <class Key, class Compare>
const Key &Set<Key, Compare>::get_min(Set::Node *root) const {
  Node *x = root;
  // will crash as intended when root == nullptr
  for (; x->lc != nullptr; x = x->lc);
  return x->key;
}

template <class Key, class Compare>
typename Set<Key, Compare>::SizeType Set<Key, Compare>::size() const {
  return size(root_);
}

template <class Key, class Compare>
typename Set<Key, Compare>::Node *Set<Key, Compare>::delete_arbitrary(
    Set::Node *root, Key key) const {
  if (cmp_(key, root->key)) {
    // key < root->key
    if (!is_red(root->lc) && !(is_red(root->lc->lc)))
      root = move_red_left(root);
    // ensure the invariant: either root->lc or root->lc->lc (or root and
    // root->lc after dive into the function) is red, to ensure we will
    // eventually delete a red node. therefore we will not break the black
    // height balance
    root->lc = delete_arbitrary(root->lc, key);
  } else {
    // key >= root->key
    if (is_red(root->lc)) root = rotate_right(root);
    if (key == root->key && root->rc == nullptr) {
      delete root;
      return nullptr;
    }
    if (!is_red(root->rc) && !is_red(root->rc->lc)) root = move_red_right(root);
    if (key == root->key) {
      root->key = get_min(root->rc);
      root->rc = delete_min(root->rc);
    } else {
      root->rc = delete_arbitrary(root->rc, key);
    }
  }
  return fix_up(root);
}

template <class Key, class Compare>
std::vector<Key> Set<Key, Compare>::serialize() const {
  std::vector<Key> v;
  serialize(root_, &v);
  return v;
}

template <class Key, class Compare>
void Set<Key, Compare>::serialize(Set::Node *root,
                                  std::vector<Key> *res) const {
  if (root == nullptr) return;
  serialize(root->lc, res);
  res->push_back(root->key);
  serialize(root->rc, res);
}

template <class Key, class Compare>
void Set<Key, Compare>::print_tree(Set::Node *root, int indent) const {
  if (root == nullptr) return;
  print_tree(root->lc, indent + 4);
  std::cout << std::string(indent, '-') << root->key << std::endl;
  print_tree(root->rc, indent + 4);
}

template <class Key, class Compare>
void Set<Key, Compare>::print_tree() const {
  print_tree(root_, 0);
}

// --8<-- [end:core]

int main() {
  Set<int> values;
  int q;
  std::cin >> q;
  while (q--) {
    int op, x;
    std::cin >> op >> x;
    if (op == 1)
      values.insert(x);
    else if (op == 2)
      std::cout << values.erase(x) << '\n';
    else if (op == 3)
      std::cout << values.count(x) << '\n';
    else if (op == 4) {
      auto a = values.serialize();
      for (std::size_t i = 0; i < a.size(); ++i)
        std::cout << (i ? " " : "") << a[i];
      std::cout << '\n';
    } else if (op == 5)
      std::cout << values.size() << '\n';
    else
      values.clear();
  }
}
