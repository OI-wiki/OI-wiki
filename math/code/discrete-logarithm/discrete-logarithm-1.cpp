#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;

const int N = 1'000'000;  // sqrt(P * sqrt(P) / ln(P))

unordered_map<int, int> M;
int Lg[N], p[N], t;
bool vis[N];
int P, g, B, sq, LP_1, inv;

int fadd(int x, int y, int P) {
  x += y;
  if (x >= P) x -= P;
  return x;
}

int fsub(int x, int y, int P) {
  x -= y;
  if (x < 0) x += P;
  return x;
}

int fmul(int x, int y, int P) { return 1ll * x * y % P; }

int qpow(int x, int y) {
  int ans = 1;
  while (y) {
    if (y & 1) ans = fmul(ans, x, P);
    x = fmul(x, x, P);
    y >>= 1;
  }
  return ans;
}

int calc(int x) {
  int s = x;
  for (int i = 0; i <= P / B; ++i) {
    if (M.find(s) != M.end()) return i * B + M[s];
    s = fmul(s, inv, P);
  }
  return -1;
}

void init() {
  int s = 1;
  for (int i = 0; i < B; ++i) {
    if (M.find(s) != M.end()) break;
    M[s] = i, s = fmul(s, g, P);
  }
  inv = qpow(qpow(g, B), P - 2);
  for (int i = 2; i <= sq; ++i) {
    if (!vis[i]) {
      p[++t] = i;
      Lg[i] = calc(i);
    }
    for (int j = 1; j <= t && p[j] * i <= sq; ++j) {
      vis[p[j] * i] = true;
      Lg[p[j] * i] = fadd(Lg[p[j]], Lg[i], P - 1);
      if (i % p[j] == 0) break;
    }
  }
}

int solve(int y) {
  if (y <= sq) return Lg[y];
  int v = P / y, r = P % y;
  if (r < y - r) return fadd(fsub(solve(r), Lg[v], P - 1), LP_1, P - 1);
  return fsub(solve(y - r), Lg[v + 1], P - 1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> P >> g;
  sq = sqrt(P) + 1;
  B = sqrt(1ll * P * sqrt(P) / log(P));
  init();
  LP_1 = (P - 1) / 2;  // g ^ LP_1 = P - 1 (mod P)
  int T;
  cin >> T;
  while (T--) {
    int x;
    cin >> x;
    cout << solve(x) << '\n';
  }
  return 0;
}
