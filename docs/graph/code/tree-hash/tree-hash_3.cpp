#include <chrono>
#include <cstdio>
#include <map>
#include <random>
#include <set>
#include <vector>

typedef unsigned long long ull;
typedef std::pair<ull, ull> Hash2;

const int N = 60, M = 998244353;
const ull mask = std::chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x) {
  x ^= mask;
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  x ^= mask;
  return x;
}

int n;
int size[N], weight[N], centroid[2];
std::vector<int> edge[N];
std::map<Hash2, int> trees;

void getCentroid(int x, int fa) {
  size[x] = 1;
  weight[x] = 0;
  for (int i : edge[x]) {
    if (i == fa) {
      continue;
    }
    getCentroid(i, x);
    size[x] += size[i];
    weight[x] = std::max(weight[x], size[i]);
  }
  weight[x] = std::max(weight[x], n - size[x]);
  if (weight[x] <= n / 2) {
    int index = centroid[0] != 0;
    centroid[index] = x;
  }
}

ull getHash(int x, int fa) {
  ull hash = 1;
  for (int i : edge[x]) {
    if (i == fa) {
      continue;
    }
    hash += shift(getHash(i, x));
  }
  return hash;
}

int main() {
  int m;
  scanf("%d", &m);
  for (int t = 1; t <= m; t++) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      int fa;
      scanf("%d", &fa);
      if (fa) {
        edge[fa].push_back(i);
        edge[i].push_back(fa);
      }
    }
    getCentroid(1, 0);
    Hash2 hash;
    hash.first = getHash(centroid[0], 0);
    if (centroid[1]) {
      hash.second = getHash(centroid[1], 0);
      if (hash.first > hash.second) {
        std::swap(hash.first, hash.second);
      }
    } else {
      hash.second = hash.first;
    }
    if (!trees.count(hash)) {
      trees[hash] = t;
    }
    printf("%d\n", trees[hash]);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    centroid[0] = centroid[1] = 0;
  }
}
