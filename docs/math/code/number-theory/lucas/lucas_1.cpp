#include <iostream>
#include <vector>
using namespace std;
vector<long long> fact, invfact;

long long power(long long a, long long b, long long mod) {
  long long r = 1;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) r = r * a % mod;
  return r;
}

long long C(long long n, long long k, long long p) {
  if (k > n) return 0;
  return fact[n] * invfact[k] % p * invfact[n - k] % p;
}

// --8<-- [start:core]
long long Lucas(long long n, long long k, long long p) {
  if (k == 0) return 1;
  return (C(n % p, k % p, p) * Lucas(n / p, k / p, p)) % p;
}

// --8<-- [end:core]
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long n, m, p;
    cin >> n >> m >> p;
    fact.resize(p);
    invfact.resize(p);
    fact[0] = 1;
    for (int i = 1; i < p; ++i) fact[i] = fact[i - 1] * i % p;
    invfact[p - 1] = power(fact[p - 1], p - 2, p);
    for (int i = p - 1; i; --i) invfact[i - 1] = invfact[i] * i % p;
    cout << Lucas(n + m, n, p) << "\n";
  }
}
