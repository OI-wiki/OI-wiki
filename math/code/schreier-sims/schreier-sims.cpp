#include <iostream>
#include <vector>

// A permutation.
class Permutation {
  std::vector<int> perm;

  void shrink() {
    int m = perm.size();
    for (; m && perm[m - 1] == m - 1; --m);
    perm.resize(m);
  }

 public:
  Permutation() {}

  Permutation(const std::vector<int>& vec) : perm(vec) { shrink(); }

  int operator[](int i) const { return i < perm.size() ? perm[i] : i; }

  bool empty() const { return perm.empty(); }

  // First LHS then RHS.
  Permutation operator*(const Permutation& rhs) const {
    Permutation res;
    res.perm.resize(std::max(perm.size(), rhs.perm.size()));
    for (int i = 0; i < res.perm.size(); ++i) {
      res.perm[i] = rhs[(*this)[i]];
    }
    res.shrink();
    return res;
  }

  // First LHS^{-1} then RHS.
  Permutation operator/(const Permutation& rhs) const {
    Permutation res;
    res.perm.resize(std::max(perm.size(), rhs.perm.size()));
    for (int i = 0; i < res.perm.size(); ++i) {
      res.perm[(*this)[i]] = rhs[i];
    }
    res.shrink();
    return res;
  }

  // Inverse.
  Permutation inv() const {
    Permutation res;
    res.perm.resize(perm.size());
    for (int i = 0; i < res.perm.size(); ++i) {
      res.perm[(*this)[i]] = i;
    }
    return res;
  }
};

// A stabilizer chain (a.k.a., BSGS) for a group.
class PermutationGroup {
  size_t n, k;
  std::vector<bool> orbit;               // Orbit of the n-th point.
  std::vector<Permutation> generators;   // Generators.
  std::vector<Permutation> transversal;  // Inverse of coset representatives.
  PermutationGroup* next;                // Stabilizer.

  // Sift a permutation.
  void sift(Permutation& h) const {
    if (!n) return;
    int i = h[n - 1];
    if (!orbit[i]) return;
    h = h * transversal[i];
    next->sift(h);
  }

  // Add one more element into the transversal.
  void extend_transversal(Permutation t) {
    int i = t[n - 1];
    if (!orbit[i]) {
      ++k;
      orbit[i] = true;
      transversal[i] = t.inv();
      for (const auto& s : generators) {
        extend_transversal(t * s);
      }
    } else {
      next->extend(t * transversal[i]);
    }
  }

 public:
  PermutationGroup(int n)
      : n(n), k(1), orbit(n), transversal(n), next(nullptr) {
    if (!n) return;
    // Initialize the current layer.
    orbit[n - 1] = true;
    next = new PermutationGroup(n - 1);
  }

  // Destructor.
  ~PermutationGroup() {
    if (next) delete next;
  }

  // Add one more permutation into the group.
  void extend(Permutation g) {
    sift(g);
    if (g.empty()) return;
    generators.emplace_back(g);
    for (int i = 0; i < n; ++i) {
      if (orbit[i]) {
        extend_transversal(transversal[i] / g);
      }
    }
  }

  // Check whether a permutation belongs to the group.
  bool membership_test(Permutation h) const {
    sift(h);
    return h.empty();
  }

  // Return the size of the group.
  long long size() const { return n ? next->size() * k : 1LL; }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  PermutationGroup group(n);
  // Read permutations and insert them to the group.
  std::vector<int> vec(n);
  for (; m; --m) {
    for (int& x : vec) {
      std::cin >> x;
      --x;  // Index starting at 0.
    }
    group.extend(Permutation(vec));
  }
  // Output the size of the group.
  std::cout << group.size();
  return 0;
}
