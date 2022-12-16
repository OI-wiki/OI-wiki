#include <algorithm>
#include <cstdio>

const int maxN = 1e5 + 10;
const int maxK = 2e5 + 10;

int n, k;

struct Element {
  int a, b, c;
  int cnt;
  int res;

  bool operator!=(Element other) {
    if (a != other.a) return true;
    if (b != other.b) return true;
    if (c != other.c) return true;
    return false;
  }
};

Element e[maxN];
Element ue[maxN];
int m, t;
int res[maxN];

struct BinaryIndexedTree {
  int node[maxK];

  int lowbit(int x) { return x & -x; }

  void Add(int pos, int val) {
    while (pos <= k) {
      node[pos] += val;
      pos += lowbit(pos);
    }
    return;
  }

  int Ask(int pos) {
    int res = 0;
    while (pos) {
      res += node[pos];
      pos -= lowbit(pos);
    }
    return res;
  }
} BIT;

bool cmpA(Element x, Element y) {
  if (x.a != y.a) return x.a < y.a;
  if (x.b != y.b) return x.b < y.b;
  return x.c < y.c;
}

bool cmpB(Element x, Element y) {
  if (x.b != y.b) return x.b < y.b;
  return x.c < y.c;
}

void CDQ(int l, int r) {
  if (l == r) return;
  int mid = (l + r) / 2;
  CDQ(l, mid);
  CDQ(mid + 1, r);
  std::sort(ue + l, ue + mid + 1, cmpB);
  std::sort(ue + mid + 1, ue + r + 1, cmpB);
  int i = l;
  int j = mid + 1;
  while (j <= r) {
    while (i <= mid && ue[i].b <= ue[j].b) {
      BIT.Add(ue[i].c, ue[i].cnt);
      i++;
    }
    ue[j].res += BIT.Ask(ue[j].c);
    j++;
  }
  for (int k = l; k < i; k++) BIT.Add(ue[k].c, -ue[k].cnt);
  return;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].c);
  std::sort(e + 1, e + n + 1, cmpA);
  for (int i = 1; i <= n; i++) {
    t++;
    if (e[i] != e[i + 1]) {
      m++;
      ue[m].a = e[i].a;
      ue[m].b = e[i].b;
      ue[m].c = e[i].c;
      ue[m].cnt = t;
      t = 0;
    }
  }
  CDQ(1, m);
  for (int i = 1; i <= m; i++) res[ue[i].res + ue[i].cnt - 1] += ue[i].cnt;
  for (int i = 0; i < n; i++) printf("%d\n", res[i]);
  return 0;
}
