#include <bits/stdc++.h>
using namespace std;

void read(int& a) {
  a = 0;
  char c;
  while ((c = getchar()) < 48)
    ;
  do a = (a << 3) + (a << 1) + (c ^ 48);
  while ((c = getchar()) > 47);
}

void write(int x) {
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
}

int n, q, a[501][501], ans[60001];
int disc[250001], cntdisc;  // 离散化用
int nn;

int blockId[501], blocklen;               // 分块
int rangeblockId[250001], rangeblocklen;  // 值域分块
int counts[250001], countsum[501];        // 该值次数及值域块总和

struct Position {
  int x, y;
};

vector<Position> pos[250001];

struct Question {
  int x1, y1, x2, y2, k, qid;

  bool operator<(Question tmp) const {
    if (blockId[x1] != blockId[tmp.x1]) return blockId[x1] < blockId[tmp.x1];
    if (blockId[y1] != blockId[tmp.y1])
      return blockId[x1] & 1 ? y1 < tmp.y1 : y1 > tmp.y1;
    if (blockId[y2] != blockId[tmp.y2])
      return blockId[y1] & 1 ? y2 < tmp.y2 : y2 > tmp.y2;
    else
      return blockId[y2] & 1 ? x2 < tmp.x2 : x2 > tmp.x2;
  }
} Q[60001];

int Qcnt;

void mo_algo() {
  blocklen = 11;
  for (int i = 1; i <= n; ++i) blockId[i] = (i - 1) / blocklen + 1;
  rangeblocklen = n + 1;
  for (int i = 1; i <= nn; ++i) rangeblockId[i] = (i - 1) / rangeblocklen + 1;
  counts[a[1][1]] = countsum[rangeblockId[a[1][1]]] = 1;
  sort(Q + 1, Q + 1 + Qcnt);

  int L = 1, R = 1, D = 1, U = 1;
  for (int i = 1; i <= q; ++i) {
    while (R < Q[i].y2) {
      ++R;
      for (int i = U; i <= D; ++i)
        ++counts[a[i][R]], ++countsum[rangeblockId[a[i][R]]];
    }
    while (L > Q[i].y1) {
      --L;
      for (int i = U; i <= D; ++i)
        ++counts[a[i][L]], ++countsum[rangeblockId[a[i][L]]];
    }
    while (D < Q[i].x2) {
      ++D;
      for (int i = L; i <= R; ++i)
        ++counts[a[D][i]], ++countsum[rangeblockId[a[D][i]]];
    }
    while (U > Q[i].x1) {
      --U;
      for (int i = L; i <= R; ++i)
        ++counts[a[U][i]], ++countsum[rangeblockId[a[U][i]]];
    }
    while (R > Q[i].y2) {
      for (int i = U; i <= D; ++i)
        --counts[a[i][R]], --countsum[rangeblockId[a[i][R]]];
      --R;
    }
    while (L < Q[i].y1) {
      for (int i = U; i <= D; ++i)
        --counts[a[i][L]], --countsum[rangeblockId[a[i][L]]];
      ++L;
    }
    while (D > Q[i].x2) {
      for (int i = L; i <= R; ++i)
        --counts[a[D][i]], --countsum[rangeblockId[a[D][i]]];
      --D;
    }
    while (U < Q[i].x1) {
      for (int i = L; i <= R; ++i)
        --counts[a[U][i]], --countsum[rangeblockId[a[U][i]]];
      ++U;
    }
    int res = 1, cnt = 0;
    while (cnt + countsum[res] < Q[i].k && res <= rangeblockId[nn])
      cnt += countsum[res], ++res;
    res = (res - 1) * rangeblocklen + 1;
    while (cnt + counts[res] < Q[i].k && res <= nn) cnt += counts[res], ++res;
    ans[Q[i].qid] = disc[res];
  }
}

int main() {
  read(n);
  read(q);
  nn = n * n;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      int x;
      read(x);
      a[i][j] = disc[++cntdisc] = x;
    }
  sort(disc + 1, disc + 1 + cntdisc);
  cntdisc = unique(disc + 1, disc + cntdisc + 1) - disc - 1;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      a[i][j] = lower_bound(disc + 1, disc + 1 + cntdisc, a[i][j]) - disc;
  for (int i = 1; i <= q; ++i) {
    int x1, y1, x2, y2, k;
    read(x1);
    read(y1);
    read(x2);
    read(y2);
    read(k);
    Q[++Qcnt] = {x1, y1, x2, y2, k, i};
  }

  mo_algo();
  for (int i = 1; i <= q; ++i) write(ans[i]), puts("");
  return 0;
}