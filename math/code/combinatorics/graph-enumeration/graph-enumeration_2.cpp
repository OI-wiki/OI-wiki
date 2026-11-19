#include <iostream>
#include <vector>
using namespace std;

using LL = long long;
int MOD = int(1e9) + 7;

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

int pow(int a, LL b) {
  int c(1);
  while (b) {
    if (b & 1) MUL(c, a);
    MUL(a, a), b >>= 1;
  }
  return c;
}

template <class T>
T pow(T a, LL b) {
  T c(1);
  while (b) {
    if (b & 1) c *= a;
    a *= a, b >>= 1;
  }
  return c;
}

template <class T>
T pow(T a, int b) {
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
    return *this;
  }

  Int operator+(const int& rhs) const { return sum(val, rhs); }

  Int& operator-=(const int& rhs) {
    DEC(val, rhs);
    return *this;
  }

  Int operator-(const int& rhs) const { return dff(val, rhs); }

  Int& operator*=(const int& rhs) {
    MUL(val, rhs);
    return *this;
  }

  Int operator*(const int& rhs) const { return pdt(val, rhs); }

  Int& operator/=(const int& rhs) {
    DIV(val, rhs);
    return *this;
  }

  Int operator/(const int& rhs) const { return qtt(val, rhs); }

  Int operator-() const { return MOD - *this; }
};

}  // namespace NT

using namespace NT;

constexpr int N = int(5e1) + 9;
Int Fact[N];
vector<vector<int>> Partition;
vector<int> cur;
int n, m;

void gen(int n = ::n, int s = 1) {
  if (!n) {
    Partition.push_back(cur);
  } else if (n >= s) {
    cur.push_back(s);
    gen(n - s, s);
    cur.pop_back();
    gen(n, s + 1);
  }
}

Int w(const vector<int> P) {
  Int z = Fact[n];
  int c = 0, l = P.front();

  for (auto p : P) {
    z /= p;
    if (p != l) {
      z /= Fact[c];
      l = p;
      c = 1;
    } else {
      ++c;
    }
  }

  z /= Fact[c];
  return z;
}

int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }

int c(const vector<int> P) {
  int z = 0;
  for (int i = 0; i < P.size(); ++i) {
    z += P[i] / 2;
    for (int j = 0; j < i; ++j) z += gcd(P[i], P[j]);
  }
  return z;
}

int main() {
  cin >> n >> m >> MOD;
  Fact[0] = 1;
  for (int i = 1; i <= n; ++i) Fact[i] = Fact[i - 1] * i;

  gen();

  Int res = 0;
  for (auto P : Partition) {
    res += w(P) * pow(m, c(P));
  }
  res /= Fact[n];
  cout << res << endl;
}
