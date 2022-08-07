#include <algorithm>
#include <cstdio>
#include <tr1/unordered_map>
#include <vector>

class Solution {
 private:
  typedef unsigned long long ull;
  typedef std::vector<int>::iterator it;
  static const ull seed = 2333233233;
  static const int maxn = 107;

  int n, m, size[maxn], lastRoot, root, lastMax, Max, ans;
  ull hashval[maxn], res;
  std::vector<int> e[maxn];
  std::tr1::unordered_map<ull, int> id;

  ull getHash(int now, int fa) {  // 得到哈希值
    size[now] = 1;
    hashval[now] = 1;
    for (register it i = e[now].begin(); i != e[now].end(); ++i) {
      int v = *i;
      if (v == fa) {
        continue;
      }
      hashval[now] ^= getHash(v, now) * seed + size[v];
      size[now] += size[v];
    }
    return hashval[now];
  }

  void getRoot(int now, int fa) {  // 找根，递归向上找
    int max = 0;
    size[now] = 1;
    for (register it i = e[now].begin(); i != e[now].end(); ++i) {
      int v = *i;
      if (v == fa) {
        continue;
      }
      getRoot(v, now);
      size[now] += size[v];
      max = std::max(max, size[v]);
    }
    max = std::max(max, n - size[now]);
    if (max < Max && now != lastRoot) {
      root = now;
      Max = max;
    }
  }

 public:
  Solution() {
    get();
    solve();
  }

  void get() {
    scanf("%d", &m);
    for (register int i = 1; i <= m; i++) {
      scanf("%d", &n);
      for (register int j = 1; j <= n; j++) {
        std::vector<int>().swap(e[j]);
      }
      for (register int j = 1, fa; j <= n; j++) {
        scanf("%d", &fa);
        if (!fa) {
          root = j;
        } else {
          e[fa].push_back(j);
          e[j].push_back(fa);
        }
      }
      lastRoot = root = 0;
      Max = n;
      getRoot(1, 0);
      lastRoot = root, lastMax = Max;
      res = getHash(root, 0);
      if (!id.count(res)) {
        id[res] = i;
      }
      ans = id[res];

      Max = n;
      getRoot(1, 0);
      if (lastMax == Max) {
        res = getHash(root, 0);
        if (!id.count(res)) {
          id[res] = i;
        }
        ans = std::min(ans, id[res]);
      }
      printf("%d\n", ans);
    }
  }

  void solve() {}
};

Solution sol;

int main() {}