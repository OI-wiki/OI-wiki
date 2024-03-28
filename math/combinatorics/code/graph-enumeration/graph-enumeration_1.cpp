#include <bits/stdc++.h>
using namespace std;

#define Ts *this
#define rTs return Ts
typedef long long LL;
const int MOD = int(1e9) + 7;

// <<= '2. Number Theory .,//{
namespace NT {
void INC(int& a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}

int sum(int a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
  return a;
}

void DEC(int& a, int b) {
  a -= b;
  if (a < 0) a += MOD;
}

int dff(int a, int b) {
  a -= b;
  if (a < 0) a += MOD;
  return a;
}

void MUL(int& a, int b) { a = (LL)a * b % MOD; }

int pdt(int a, int b) { return (LL)a * b % MOD; }

int _I(int b) {
  int a = MOD, x1 = 0, x2 = 1, q;
  while (1) {
    q = a / b, a %= b;
    if (!a) return x2;
    DEC(x1, pdt(q, x2));

    q = b / a, b %= a;
    if (!b) return x1;
    DEC(x2, pdt(q, x1));
  }
}

void DIV(int& a, int b) { MUL(a, _I(b)); }

int qtt(int a, int b) { return pdt(a, _I(b)); }

inline int pow(int a, LL b) {
  int c(1);
  while (b) {
    if (b & 1) MUL(c, a);
    MUL(a, a), b >>= 1;
  }
  return c;
}

template <class T>
inline T pow(T a, LL b) {
  T c(1);
  while (b) {
    if (b & 1) c *= a;
    a *= a, b >>= 1;
  }
  return c;
}

template <class T>
inline T pow(T a, int b) {
  return pow(a, (LL)b);
}

struct Int {
  int val;

  operator int() const { return val; }

  Int(int _val = 0) : val(_val) {
    val %= MOD;
    if (val < 0) val += MOD;
  }

  Int(LL _val) : val(_val) {
    _val %= MOD;
    if (_val < 0) _val += MOD;
    val = _val;
  }

  Int& operator+=(const int& rhs) {
    INC(val, rhs);
    rTs;
  }

  Int operator+(const int& rhs) const { return sum(val, rhs); }

  Int& operator-=(const int& rhs) {
    DEC(val, rhs);
    rTs;
  }

  Int operator-(const int& rhs) const { return dff(val, rhs); }

  Int& operator*=(const int& rhs) {
    MUL(val, rhs);
    rTs;
  }

  Int operator*(const int& rhs) const { return pdt(val, rhs); }

  Int& operator/=(const int& rhs) {
    DIV(val, rhs);
    rTs;
  }

  Int operator/(const int& rhs) const { return qtt(val, rhs); }

  Int operator-() const { return MOD - *this; }
};

}  // namespace NT

using namespace NT;

const int N = int(1e3) + 9;
Int binom[N][N], C[N], E[N], B[N], B1[N], G[N];
int n;

void ln(Int C[], Int G[]) {
  for (int i = 1; i <= n; ++i) {
    C[i] = G[i];
    for (int j = 1; j <= i - 1; ++j)
      C[i] -= binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}

void exp(Int G[], Int C[]) {
  for (int i = 1; i <= n; ++i) {
    G[i] = C[i];
    for (int j = 1; j <= i - 1; ++j)
      G[i] += binom[i - 1][j - 1] * C[j] * G[i - j];
  }
}

int main() {
#ifndef ONLINE_JUDGE
  // freopen("in.txt", "r", stdin);
#endif

  n = 1000;
  for (int i = 0; i < n + 1; ++i) {
    binom[i][0] = 1;
    for (int j = 0; j < i; ++j)
      binom[i][j + 1] = binom[i - 1][j] + binom[i - 1][j + 1];
  }

  for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i][2]);
  ln(C, G);
  for (int i = 1; i <= n; ++i) G[i] = pow(2, binom[i - 1][2]);
  ln(E, G);
  for (int i = 1; i <= n; ++i) {
    G[i] = 0;
    for (int j = 0; j < i + 1; ++j) G[i] += binom[i][j] * pow(2, j * (i - j));
  }
  ln(B1, G);
  for (int i = 1; i <= n; ++i) B1[i] /= 2;
  exp(B, B1);

  int T;
  cin >> T;
  while (T--) {
    scanf("%d", &n);
    printf("Connected: %d\n", C[n]);
    printf("Eulerian: %d\n", E[n]);
    printf("Bipartite: %d\n", B[n]);
    puts("");
  }
}
