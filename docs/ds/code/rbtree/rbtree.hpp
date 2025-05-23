// --8<-- [start:full]
/**
 * @file rbtree.hpp
 * @brief An RBTree-based set implementation
 * @details The set is sorted according to the {@code compare_t} function
 * provided; This implementation provides find, insert, remove, find order, find
 * key by order in O(log(n)) time.
 * @author [Tiphereth-A](https://github.com/Tiphereth-A)
 */

#ifndef RBTREE_HPP
#define RBTREE_HPP

// --8<-- [start:class]
#include <cassert>
#include <cstdint>
#include <functional>

using std::size_t;

// --8<-- [start:class-node1]
/**
 * An RBTree-based set implementation
 *
 * @tparam key_t key type
 * @tparam compare_t compare function
 */
template <typename key_t, typename compare_t = std::less<key_t>>
struct rb_tree {
  /**
   * Tree node
   */
  struct node_t {
    node_t *fa;     // == nullptr if root of the tree, otherwise parent
    node_t *ch[2];  // == nullptr if child is empty
                    // ch[0]: left child, ch[1]: right child
    key_t data;
    size_t sz;  // Size of subtree
    bool red;   // == true if node is red, otherwise black

    /**
     * Get child direction of current non-null node
     *
     * @return true if this node is right child of its parent, otherwise false
     */
    auto child_dir() const -> bool { return this == fa->ch[1]; }
  };

  using pointer = node_t *;
  using const_pointer = const node_t *;
  using pointer_const = node_t *const;

  const compare_t compare;
  pointer root;

  rb_tree() : compare{}, root{nullptr} {}

  // --8<-- [end:class-node1]

  ~rb_tree() {
    post_order([](auto it) { delete it; });
  }

  auto size() const -> size_t { return size(root); }

  template <typename F>
  void pre_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      callback(p), f(f, p->ch[0]), f(f, p->ch[1]);
    };
    f(f, root);
  }

  template <typename F>
  void in_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      f(f, p->ch[0]), callback(p), f(f, p->ch[1]);
    };
    f(f, root);
  }

  template <typename F>
  void post_order(F callback) {
    auto f = [&](auto &&f, pointer p) {
      if (!p) return;
      f(f, p->ch[0]), f(f, p->ch[1]), callback(p);
    };
    f(f, root);
  }

  auto leftmost(const_pointer p) const { return most(p, 0); }

  auto rightmost(const_pointer p) const { return most(p, 1); }

  auto prev(const_pointer p) const { return neighbour(p, 0); }

  auto next(const_pointer p) const { return neighbour(p, 1); }

  auto lower_bound(const key_t &key) const -> pointer {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (!compare(now->data, key))
        ans = now, now = now->ch[0];
      else
        now = now->ch[1];
    }
    return (pointer)ans;
  }

  auto upper_bound(const key_t &key) const -> pointer {
    const_pointer now = root, ans = nullptr;
    while (now) {
      if (compare(key, now->data))
        ans = now, now = now->ch[0];
      else
        now = now->ch[1];
    }
    return (pointer)ans;
  }

  // Order start from 0
  auto order_of_key(const key_t &key) const -> size_t {
    size_t ans = 0;
    auto now = root;
    while (now) {
      if (!compare(now->data, key))
        now = now->ch[0];
      else
        ans += size(now->ch[0]) + 1, now = now->ch[1];
    }
    return ans;
  }

  // Order start from 0
  auto find_by_order(size_t order) const -> const_pointer {
    const_pointer now = root, ans = nullptr;
    while (now && now->sz >= order) {
      auto lsize = size(now->ch[0]);
      if (order < lsize)
        now = now->ch[0];
      else {
        ans = now;
        if (order == lsize) break;
        now = now->ch[1], order -= lsize + 1;
      }
    }
    return ans;
  }

  // --8<-- [start:insert]
  /**
   * @return nullptr if insert failed, otherwise pointer of inserted node
   */
  auto insert(const key_t &data) -> const_pointer {
    pointer n = new node_t;
    n->fa = n->ch[0] = n->ch[1] = nullptr;
    n->data = data, n->sz = 1;
    pointer now = root, p = nullptr;
    bool dir = 0;
    while (now) {
      p = now;
      dir = compare(now->data, data);
      now = now->ch[dir];
    }
    insert_fixup_leaf(p, n, dir);
    return n;
  }

  // --8<-- [end:insert]
  // --8<-- [start:delete]
  /**
   * @return succeed or not
   */
  auto erase(const key_t &key) -> bool {
    auto p = lower_bound(key);
    if (!p || p->data != key) return false;
    erase(p);
    return true;
  }

  /**
   * @return {@code next(p)}
   */
  auto erase(pointer p) -> const_pointer {
    if (!p) return nullptr;
    pointer result;
    if (p->ch[0] && p->ch[1]) {
      auto s = leftmost(p->ch[1]);
      std::swap(s->data, p->data);
      result = p, p = s;
    } else
      result = next(p);
    erase_fixup_branch_or_leaf(p);
    delete p;
    return result;
  }

  // --8<-- [end:delete]
 private:
  static auto size(const_pointer p) -> size_t { return p ? p->sz : 0; }

  static auto is_red(const_pointer p) -> bool { return p ? p->red : false; }

  /**
   * @param dir 0: leftmost, 1: rightmost
   */
  auto most(const_pointer p, bool dir) const -> pointer {
    if (!p) return nullptr;
    while (p->ch[dir]) p = p->ch[dir];
    return (pointer)p;
  }

  /**
   * @param dir 0: prev, 1: next
   */
  auto neighbour(const_pointer p, bool dir) const -> pointer {
    if (!p) return nullptr;
    if (p->ch[dir]) return most(p->ch[dir], !dir);
    if (p == root) return nullptr;
    while (p && p->fa && p->child_dir() == dir) p = p->fa;
    return p ? p->fa : nullptr;
  }

  // --8<-- [start:insert-leaf]
  /**
   * Insert leaf node {@code n} to {@code p}
   *
   * @param p parent of node which will be inserted
   * @param n leaf node which will be inserted
   * @param dir direction of n, 0: left; 1: right
   */
  void insert_leaf(pointer_const p, pointer_const n, bool dir) {
    if (!p) {
      root = n;
      return;
    }
    p->ch[dir] = n, n->fa = p;
    auto now = p;
    while (now) now->sz++, now = now->fa;
  }

  // --8<-- [end:insert-leaf]
  // --8<-- [start:delete-leaf]
  /**
   * Erase node {@code n}
   *
   * @param n node which will be deleted, must have no more than 2 child
   */
  void erase_branch_or_leaf(pointer_const n) {
    auto p = n->fa, s = n->ch[0] ? n->ch[0] : n->ch[1];
    if (s) s->fa = p;
    if (!p) {
      root = s;
      return;
    }
    p->ch[n->child_dir()] = s;
    auto now = p;
    while (now) now->sz--, now = now->fa;
  }

  // --8<-- [end:delete-leaf]
  // --8<-- [start:rotate]
  /**
   * @param p root of subtree (may be same as {@code root})
   * @param dir direction. 0: left rotate; 1: right rotate
   * @return new root of subtree
   */
  auto rotate(pointer p, bool dir) -> pointer {
    auto g = p->fa;
    auto s = p->ch[!dir];  // new root of subtree
    assert(s);             // pointer to true node required
    s->sz = p->sz, p->sz = size(p->ch[dir]) + size(s->ch[dir]) + 1;
    auto c = s->ch[dir];
    if (c) c->fa = p;
    p->ch[!dir] = c, s->ch[dir] = p;
    p->fa = s, s->fa = g;
    if (g)
      g->ch[p == g->ch[1]] = s;
    else
      root = s;
    return s;
  }

  // --8<-- [end:rotate]
#pragma GCC diagnostic ignored "-Wcomment"

  // --8<-- [start:insert-fixup1]
  /**
   * Insert leaf node {@code n} to {@code p}, then fixup
   *
   * @param p parent of node which will be inserted
   * @param n node which will be inserted
   * @param dir direction of n, 0: left; 1: right
   */
  void insert_fixup_leaf(pointer p, pointer n, bool dir) {
    n->red = p;
    insert_leaf(p, n, dir);
    // Fix double red
    // --8<-- [end:insert-fixup1]
    // --8<-- [start:insert-aux1]
    while (is_red(p = n->fa)) {
      bool p_dir = p->child_dir();
      auto g = p->fa, u = g->ch[!p_dir];
      // --8<-- [end:insert-aux1]
      // --8<-- [start:insert-case1]
      // Case 1: both p and u are red
      //      g              [g]
      //     / \             / \
      //   [p] [u]   ==>    p   u
      //   /               /
      // [n]             [n]
      if (is_red(u)) {
        p->red = u->red = false;
        g->red = true;
        n = g;
        continue;
      }
      // --8<-- [end:insert-case1]
      // --8<-- [start:insert-case2]
      // p is red and u is black
      // Case 2: dir of n is different with dir of p
      //    g              g
      //   / \            / \
      // [p]  u   ==>   [n]  u
      //   \            /
      //   [n]        [p]
      if (n->child_dir() != p_dir) rotate(p, p_dir), std::swap(n, p);
      // --8<-- [end:insert-case2]
      // --8<-- [start:insert-case3]
      // Case 3: p is red, u is black and dir of n is same as dir of p
      //      g             p
      //     / \           / \
      //   [p]  u   ==>  [n] [g]
      //   /                   \
      // [n]                    u
      p->red = false, g->red = true;
      rotate(g, !p_dir);
      // --8<-- [end:insert-case3]
      // --8<-- [start:insert-aux2]
    }
    // --8<-- [end:insert-aux2]
    // --8<-- [start:insert-fixup2]
    // Post process: color root black
    root->red = false;
  }

  // --8<-- [end:insert-fixup2]
  // --8<-- [start:delete-fixup1]
  /**
   * Erase node {@code n}, then fixup
   *
   * @param n node which will be deleted, must have no more than 2 child
   */
  void erase_fixup_branch_or_leaf(pointer n) {
    bool n_dir = n == root ? false : n->child_dir();
    erase_branch_or_leaf(n);
    auto p = n->fa;
    if (!p) {  // n is root
      if (root) root->red = false;
      return;
    } else {
      auto s = p->ch[n_dir];
      if (s) {  // n has 1 child
        // n must be black and s must be red, so we need to color s black
        s->red = false;
        return;
      }
    }
    // n is not root but leaf with black color, need to be fixup
    // --8<-- [end:delete-fixup1]
    // --8<-- [start:delete-aux1]
    while (p && !n->red) {
      auto s = p->ch[!n_dir];
      // --8<-- [end:delete-aux1]
      // --8<-- [start:delete-case1]
      // Case 1: s is red
      //    p               s
      //   / \             / \
      // |n| [s]   ==>   [p]  d
      //     / \         / \
      //    c   d      |n|  c
      if (is_red(s)) {
        s->red = false, p->red = true;
        rotate(p, n_dir);
        s = p->ch[!n_dir];
      }
      // --8<-- [end:delete-case1]
      // --8<-- [start:delete-aux2]
      // s must be black
      auto c = s->ch[n_dir], d = s->ch[!n_dir];
      // --8<-- [end:delete-aux2]
      // --8<-- [start:delete-case2]
      // Case 2: both c and d are black
      //   {p}          {p}
      //   / \          / \
      // |n|  s   ==> |n| [s]
      //     / \          / \
      //    c   d        c   d
      // p will be colored black in the end
      if (!is_red(c) && !is_red(d)) {
        s->red = true;
        n = p;
        goto end_erase_fixup;
      }
      // --8<-- [end:delete-case2]
      // --8<-- [start:delete-case3]
      // Case 3: c is red and d is black
      //   {p}          {p}
      //   / \          / \
      // |n|  s   ==> |n|  c
      //     / \            \
      //   [c]  d           [s]
      //                      \
      //                       d
      if (!is_red(d)) {
        c->red = false, s->red = true;
        rotate(s, !n_dir);
        s = p->ch[!n_dir], c = s->ch[n_dir], d = s->ch[!n_dir];
      }
      // --8<-- [end:delete-case3]
      // --8<-- [start:delete-case4]
      // Case 4: d is red
      //   {p}            {s}
      //   / \            / \
      // |n|  s   ==>    p   d
      //     / \        / \
      //   {c} [d]    |n| {c}
      s->red = p->red, p->red = d->red = false;
      rotate(p, n_dir), n = root;
      // --8<-- [end:delete-case4]
      // --8<-- [start:delete-aux3]
    end_erase_fixup:
      p = n->fa;
      if (!p) break;
      n_dir = n->child_dir();
    }
    // --8<-- [end:delete-aux3]
    // --8<-- [start:delete-fixup2]
    // Post process: see case 2 & case 4
    n->red = false;
  }

  // --8<-- [end:delete-fixup2]
  // --8<-- [start:class-node2]
};

// --8<-- [end:class-node2]
#pragma GCC diagnostic warning "-Wcomment"

// --8<-- [end:class]
#endif  // RBTREE_HPP
        // --8<-- [end:full]