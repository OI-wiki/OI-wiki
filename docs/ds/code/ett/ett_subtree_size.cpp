#include <bits/stdc++.h>

#define CPPIO \
  std::ios::sync_with_stdio(false), std::cin.tie(0), std::cout.tie(0);
#define freep(p) p ? delete p, p = nullptr, void(1) : void(0)

#if defined(BACKLIGHT) && !defined(NASSERT)
#define ASSERT(x)                                                          \
  ((x) || (fprintf(stderr, "assertion failed (" __FILE__ ":%d): \"%s\"\n", \
                   __LINE__, #x),                                          \
           assert(false), false))
#else
#define ASSERT(x) ;
#endif

#ifdef BACKLIGHT
#include "debug.h"
#else
#define logd(...) ;
#endif

using i64 = int64_t;
using u64 = uint64_t;

void solve_case(int Case);

int main(int argc, char* argv[]) {
  CPPIO;
  int T = 1;
  // std::cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve_case(t);
  }
  return 0;
}

/**
 * Dynamic Forest Maintained With Euler Tour Tree.
 *
 * As said in reference, link and cut operation of dynamic trees can be
 * transformed into sequence split and sequence merge operation, which can be
 * easily maintained using balanced search trees like Treap.
 *
 * @reference: Dynamic trees as search trees via euler tours, applied to the
 * network simplex algorithm by Robert E. Tarjan.
 * https://link.springer.com/article/10.1007/BF02614369
 */
class DynamicForest {
 private:
  static std::mt19937 rng_;

  struct Node {
    int size_;
    int priority_;

    Node* left_;
    Node* right_;
    Node* parent_;

    int from_;
    int to_;

    int num_vertex_;
    int num_edge_;

    Node(int from, int to)
        : size_(1),
          priority_(rng_()),
          left_(nullptr),
          right_(nullptr),
          parent_(nullptr),
          from_(from),
          to_(to),
          num_vertex_(from_ == to_ ? 1 : 0),
          num_edge_(from_ == to_ ? 0 : 1) {}

    inline void Maintain() {
      size_ = 1;
      num_vertex_ = from_ == to_ ? 1 : 0;
      num_edge_ = from_ == to_ ? 0 : 1;
      if (left_) {
        size_ += left_->size_;
        left_->parent_ = this;

        num_vertex_ += left_->num_vertex_;
        num_edge_ += left_->num_edge_;
      }
      if (right_) {
        size_ += right_->size_;
        right_->parent_ = this;

        num_vertex_ += right_->num_vertex_;
        num_edge_ += right_->num_edge_;
      }
    }
  };

  static inline int GetSize(Node* p) { return p == nullptr ? 0 : p->size_; }

  static inline Node* FindRoot(Node* p) {
    if (!p) return nullptr;

    while (p->parent_ != nullptr) p = p->parent_;
    return p;
  }

  static std::string to_string(Node* p) {
    std::stringstream ss;

    ss << "Node [\n";

    std::function<void(Node*)> dfs = [&](Node* p) {
      if (!p) return;
      dfs(p->left_);
      ss << "(" << p->from_ << "," << p->to_ << "),";
      dfs(p->right_);
    };
    dfs(p);

    ss << "]\n\n";

    return ss.str();
  }

  inline Node* AllocateNode(int u, int v) {
    Node* p = new Node(u, v);
    return p;
  }

  inline void FreeNode(Node*& p) {
    if (p) {
      delete p;
      p = nullptr;
    }
  }

  /*
   * Dynamic Sequence Maintained using Treap.
   */
  class Treap {
   public:
    /**
     * Merge two treap a and b into a single treap, with keys in a less than
     * keys in b.
     *
     * In the other word, concating sequence a and sequence b.
     */
    static Node* Merge(Node* a, Node* b) {
      if (a == nullptr) return b;
      if (b == nullptr) return a;

      if (a->priority_ < b->priority_) {
        a->right_ = Merge(a->right_, b);
        a->Maintain();
        return a;
      } else {
        b->left_ = Merge(a, b->left_);
        b->Maintain();
        return b;
      }
    }

    /**
     * Get the number of nodes with keys less than or equal to the key of p.
     *
     * In the other word, the the 1-based index of p inside the sequencec
     * containing p.
     */
    static int GetPosition(Node* p) {
      ASSERT(p != nullptr);

      int position = GetSize(p->left_) + 1;
      while (p) {
        if (p->parent_ && p == p->parent_->right_)
          position += GetSize(p->parent_->left_) + 1;
        p = p->parent_;
      }
      return position;
    }

    /**
     * Split sequence containning p into two sequences, the first one contains
     * the first k elements, the second one contains the remaining elements.
     */
    static std::pair<Node*, Node*> Split(Node* p, int k) {
      if (!p) return {nullptr, nullptr};

      std::pair<Node*, Node*> result;

      if (GetSize(p->left_) < k) {
        auto right_result = Split(p->right_, k - GetSize(p->left_) - 1);
        p->right_ = right_result.first;

        result.first = p;
        result.second = right_result.second;
      } else {
        auto left_result = Split(p->left_, k);
        p->left_ = left_result.second;

        result.first = left_result.first;
        result.second = p;
      }

      p->Maintain();

      if (result.first) result.first->parent_ = nullptr;

      if (result.second) result.second->parent_ = nullptr;

      return result;
    }

    /*
     * Bottom up split treap p into 2 treaps a and b.
     *   - a: a treap containing nodes with position less than or equal to p.
     *   - b: a treap containing nodes with postion greater than p.
     *
     * In the other word, split sequence containning p into two sequences, the
     * first one contains elements before p and element p, the second one
     * contains elements after p.
     */
    static std::pair<Node*, Node*> SplitUp2(Node* p) {
      ASSERT(p != nullptr);

      Node *a = nullptr, *b = nullptr;
      b = p->right_;
      if (b) b->parent_ = nullptr;
      p->right_ = nullptr;

      bool is_p_left_child_of_parent = false;
      bool is_from_left_child = false;
      while (p) {
        Node* parent = p->parent_;

        if (parent) {
          is_p_left_child_of_parent = (parent->left_ == p);
          if (is_p_left_child_of_parent) {
            parent->left_ = nullptr;
          } else {
            parent->right_ = nullptr;
          }
          p->parent_ = nullptr;
        }

        if (!is_from_left_child) {
          a = Merge(p, a);
        } else {
          b = Merge(b, p);
        }

        is_from_left_child = is_p_left_child_of_parent;
        p->Maintain();
        p = parent;
      }

      return {a, b};
    }

    /*
     * Bottom up split treap p into 3 treaps a, b and c.
     *   - a: a treap containing nodes with key less than p.
     *   - b: a treap containing nodes with key greater than p.
     *   - c: a treap containing nodes with key equal p.
     *
     * In the other word, split sequence containning p into three sequences, the
     * first one contains elements before p, the second one contains element p,
     * the third one contains elements after p.
     */
    static std::tuple<Node*, Node*, Node*> SplitUp3(Node* p) {
      ASSERT(p != nullptr);

      Node* a = p->left_;
      if (a) a->parent_ = nullptr;
      p->left_ = nullptr;

      Node* b = p->right_;
      if (b) b->parent_ = nullptr;
      p->right_ = nullptr;

      Node* c = p;

      bool is_p_left_child_of_parent = false;
      bool is_from_left_child = false;
      Node* parent = p->parent_;
      if (parent) {
        is_p_left_child_of_parent = (parent->left_ == p);
        if (is_p_left_child_of_parent) {
          parent->left_ = nullptr;
        } else {
          parent->right_ = nullptr;
        }
        p->parent_ = nullptr;
      }
      is_from_left_child = is_p_left_child_of_parent;
      p->Maintain();
      p = parent;

      while (p) {
        Node* parent = p->parent_;

        if (parent) {
          is_p_left_child_of_parent = (parent->left_ == p);
          if (is_p_left_child_of_parent) {
            parent->left_ = nullptr;
          } else {
            parent->right_ = nullptr;
          }
          p->parent_ = nullptr;
        }

        if (!is_from_left_child) {
          a = Merge(p, a);
        } else {
          b = Merge(b, p);
        }

        is_from_left_child = is_p_left_child_of_parent;
        p->Maintain();
        p = parent;
      }

      return {a, c, b};
    }
  };

 public:
  DynamicForest(int n) : n_(n), vertices_(n_), tree_edges_(n_) {
    ASSERT(n_ > 0);

    for (int i = 0; i < n_; ++i) vertices_[i] = AllocateNode(i, i);
  }

  ~DynamicForest() {
    for (int i = 0; i < n_; ++i) {
      for (auto [_, e] : tree_edges_[i]) {
        FreeNode(e);
      }
    }
    for (int i = 0; i < n_; ++i) {
      FreeNode(vertices_[i]);
    }
  }

  void MakeRoot(int u) {
    Node* vertex_u = vertices_[u];

    int position_u = Treap::GetPosition(vertex_u);

    auto [L1, L2] = Treap::SplitUp2(vertex_u);
    ASSERT(GetSize(L1) == position_u);

    Treap::Merge(L2, L1);
  }

  void Insert(int u, int v) {
    ASSERT(not tree_edges_[u].count(v));
    ASSERT(not tree_edges_[v].count(u));

    Node* vertex_u = vertices_[u];
    Node* vertex_v = vertices_[v];

    Node* edge_uv = AllocateNode(u, v);
    Node* edge_vu = AllocateNode(v, u);
    tree_edges_[u][v] = edge_uv;
    tree_edges_[v][u] = edge_vu;

    int position_u = Treap::GetPosition(vertex_u);
    int position_v = Treap::GetPosition(vertex_v);

    auto [L11, L12] = Treap::SplitUp2(vertex_u);
    auto [L21, L22] = Treap::SplitUp2(vertex_v);

    ASSERT(GetSize(L11) == position_u);
    ASSERT(GetSize(L21) == position_v);

    Node* result = nullptr;
    result = Treap::Merge(result, L12);
    result = Treap::Merge(result, L11);
    result = Treap::Merge(result, edge_uv);
    result = Treap::Merge(result, L22);
    result = Treap::Merge(result, L21);
    result = Treap::Merge(result, edge_vu);
  }

  void Delete(int u, int v) {
    ASSERT(tree_edges_[u].count(v));
    ASSERT(tree_edges_[v].count(u));

    Node* edge_uv = tree_edges_[u][v];
    Node* edge_vu = tree_edges_[v][u];
    tree_edges_[u].erase(v);
    tree_edges_[v].erase(u);

    int position_uv = Treap::GetPosition(edge_uv);
    int position_vu = Treap::GetPosition(edge_vu);
    if (position_uv > position_vu) {
      std::swap(edge_uv, edge_vu);
      std::swap(position_uv, position_vu);
    }

    auto [L1, uv, _] = Treap::SplitUp3(edge_uv);
    ASSERT(GetSize(L1) == position_uv - 1);
    ASSERT(GetSize(uv) == 1);

    auto [L2, vu, L3] = Treap::SplitUp3(edge_vu);
    ASSERT(GetSize(L2) == position_vu - position_uv - 1);
    ASSERT(GetSize(vu) == 1);

    L1 = Treap::Merge(L1, L3);

    FreeNode(edge_uv);
    FreeNode(edge_vu);
  }

  bool IsConnected(int u, int v) {
    Node* vertex_u = vertices_[u];
    Node* vertex_v = vertices_[v];
    return FindRoot(vertex_u) == FindRoot(vertex_v);
  }

  int GetComponentSize(int u) {
    Node* vertex_u = vertices_[u];
    Node* root_of_vertex_u = FindRoot(vertex_u);
    return GetSize(root_of_vertex_u);
  }

  int GetComponentNumberOfVertex(int u) {
    Node* vertex_u = vertices_[u];
    Node* root_of_vertex_u = FindRoot(vertex_u);
    return root_of_vertex_u ? root_of_vertex_u->num_vertex_ : 0;
  }

  std::string to_string() const {
    std::stringstream ss;

    ss << "DynamicForest [\n";

    std::function<void(Node*)> dfs = [&](Node* p) {
      if (!p) return;
      dfs(p->left_);
      ss << "(" << p->from_ << "," << p->to_ << "),";
      dfs(p->right_);
    };
    for (int i = 0; i < n_; ++i) {
      if (vertices_[i]->parent_ == nullptr) {
        ss << "  Component [";
        dfs(vertices_[i]);
        ss << "]\n";
      }
    }
    for (int i = 0; i < n_; ++i) {
      for (auto [_, j] : tree_edges_[i]) {
        if (j->parent_ == nullptr) {
          ss << "  Component [";
          dfs(j);
          ss << "]\n";
        }
      }
    }

    ss << "]\n\n";

    return ss.str();
  }

 private:
  int n_;
  std::vector<Node*> vertices_;
  std::vector<std::map<int, Node*>> tree_edges_;
};

std::mt19937 DynamicForest::rng_(
    std::chrono::steady_clock::now().time_since_epoch().count());

void solve_case(int Case) {
  int n, q;
  std::cin >> n >> q;

  DynamicForest t(n + 1);
  std::string op;
  int u, v;
  for (int i = 1; i <= q; ++i) {
    std::cin >> op >> u >> v;
    if (op[0] == 'A') {
      t.Insert(u, v);
    } else if (op[0] == 'Q') {
      t.Delete(u, v);
      int ans = i64(1) * t.GetComponentNumberOfVertex(u) *
                t.GetComponentNumberOfVertex(v);
      t.Insert(u, v);
      std::cout << ans << "\n";
    }
  }
}
