#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>

constexpr int MAXN = 1e5 + 5;
constexpr int MAXM = 20;

struct RMQ {
  int N, A[MAXN];
  int blockSize;
  int S[MAXN][MAXM], Pow[MAXM], Log[MAXN];
  int Belong[MAXN], Pos[MAXN];
  int Pre[MAXN], Sub[MAXN];
  int F[MAXN];

  void buildST() {
    int cur = 0, id = 1;
    Pos[0] = -1;
    for (int i = 1; i <= N; ++i) {
      if (cur == 0)
        S[id][0] = A[i];
      else
        S[id][0] = std::max(S[id][0], A[i]);
      Belong[i] = id;
      if (Belong[i - 1] != Belong[i])
        Pos[i] = 0;
      else
        Pos[i] = Pos[i - 1] + 1;
      if (++cur == blockSize) {
        cur = 0;
        ++id;
      }
    }
    if (N % blockSize == 0) --id;
    Pow[0] = 1;
    for (int i = 1; i < MAXM; ++i) Pow[i] = Pow[i - 1] * 2;
    for (int i = 2; i <= id; ++i) Log[i] = Log[i / 2] + 1;
    for (int i = 1; i <= Log[id]; ++i) {
      for (int j = 1; j + Pow[i] - 1 <= id; ++j) {
        S[j][i] = std::max(S[j][i - 1], S[j + Pow[i - 1]][i - 1]);
      }
    }
  }

  void buildSubPre() {
    for (int i = 1; i <= N; ++i) {
      if (Belong[i] != Belong[i - 1])
        Pre[i] = A[i];
      else
        Pre[i] = std::max(Pre[i - 1], A[i]);
    }
    for (int i = N; i >= 1; --i) {
      if (Belong[i] != Belong[i + 1])
        Sub[i] = A[i];
      else
        Sub[i] = std::max(Sub[i + 1], A[i]);
    }
  }

  void buildBlock() {
    static int S[MAXN], top;
    for (int i = 1; i <= N; ++i) {
      if (Belong[i] != Belong[i - 1])
        top = 0;
      else
        F[i] = F[i - 1];
      while (top > 0 && A[S[top]] <= A[i]) F[i] &= ~(1 << Pos[S[top--]]);
      S[++top] = i;
      F[i] |= (1 << Pos[i]);
    }
  }

  void init() {
    for (int i = 1; i <= N; ++i) scanf("%d", &A[i]);
    blockSize = std::max(1, static_cast<int>(log2(N) * 1.5));
    buildST();
    buildSubPre();
    buildBlock();
  }

  int queryMax(int l, int r) {
    int bl = Belong[l], br = Belong[r];
    if (bl != br) {
      int ans1 = std::numeric_limits<int>::lowest();
      if (br - bl > 1) {
        int p = Log[br - bl - 1];
        ans1 = std::max(S[bl + 1][p], S[br - Pow[p]][p]);
      }
      int ans2 = std::max(Sub[l], Pre[r]);
      return std::max(ans1, ans2);
    } else {
      unsigned mask = static_cast<unsigned>(F[r]) >> Pos[l];
      int offset = 0;
      while ((mask & 1U) == 0) {
        ++offset;
        mask >>= 1;
      }
      return A[l + offset];
    }
  }
} R;

int M;

int main() {
  scanf("%d%d", &R.N, &M);
  R.init();
  for (int i = 0, l, r; i < M; ++i) {
    scanf("%d%d", &l, &r);
    printf("%d\n", R.queryMax(l, r));
  }
  return 0;
}
