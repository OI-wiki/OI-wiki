#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int inv2 = (MOD + 1) / 2;
template <typename T>
inline int mint(T x) {
  x %= MOD;
  if (x < 0) x += MOD;
  return x;
}
inline int add(int x, int y) {
  return x + y >= MOD ? x + y - MOD : x + y;
}  //防止大于模数
inline int mul(int x, int y) { return (long long)1 * x * y % MOD; }
inline int sub(int x, int y) { return x < y ? x - y + MOD : x - y; }  //防负数

namespace PNS {
const int N = 2e6 + 5;
const int M = 35;

long long global_n;

int s1[N], s2[N];

int h[N][M];
bool vis_h[N][M];

int ans;

int pcnt, prime[N], phi[N];
bool isp[N];

void sieve(int n) {
  pcnt = 0;
  for (int i = 2; i <= n; ++i) isp[i] = true;  //判断质数数组
  phi[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (isp[i]) {
      ++pcnt;
      prime[pcnt] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= pcnt; ++j) {  //筛去非质数
      long long nxt = (long long)1 * i * prime[j];
      if (nxt > n) break;
      isp[nxt] = false;
      if (i % prime[j] == 0) {  // i是非质数的情况
        phi[nxt] = phi[i] * prime[j];
        break;
      }
      phi[nxt] = phi[i] * phi[prime[j]];
    }
  }

  s1[0] = 0;
  for (int i = 1; i <= n; ++i) s1[i] = add(s1[i - 1], phi[i]);

  s2[0] = 0;
  for (int i = 1; i <= n / 2; ++i) {
    s2[i] = add(s2[i - 1], phi[2 * i]);
  }
}

void init() {
  sieve(N - 1);
  for (int i = 1; i <= pcnt; ++i) h[i][0] = 1;
  for (int i = 1; i <= pcnt; ++i) vis_h[i][0] = true;
}

map<long long, int> mp_s1;

int S1(long long n) {
  if (n < N) return s1[n];
  if (mp_s1.count(n)) return mp_s1[n];

  int ret = mul(mul(mint(n), mint(n + 1)), inv2);
  for (long long i = 2, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ret = sub(ret, mul(mint(j - i + 1), S1(n / i)));
  }
  mp_s1[n] = ret;
  return ret;
}

map<long long, int> mp_s2;

int S2(long long n) {
  if (n < N / 2) return s2[n];
  if (mp_s2.count(n)) return mp_s2[n];
  int ret = add(S1(n), S2(n / 2));
  mp_s2[n] = ret;
  return ret;
}

int G(long long n) { return add(S1(n), mul(2, S2(n / 2))); }

void dfs(long long d, int hd, int pid) {
  ans = add(ans, mul(hd, G(global_n / d)));

  for (int i = pid, p; i <= pcnt; ++i) {
    if (i > 1 && d > global_n / prime[i] / prime[i]) break;  //剪枝

    int c = 2;
    for (long long x = d * prime[i] * prime[i]; x <= global_n;
         x *= prime[i], ++c) {
      if (!vis_h[i][c]) {
        int f = prime[i] ^ c, g = prime[i] - 1;

        // p = 2时特判一下
        if (i == 1) g = mul(g, 3);

        for (int j = 1; j <= c; ++j) {
          f = sub(f, mul(g, h[i][c - j]));
          g = mul(g, prime[i]);
        }
        h[i][c] = f;
        vis_h[i][c] = true;
      }

      if (h[i][c]) dfs(x, mul(hd, h[i][c]), i + 1);
    }
  }
}

int solve(long long n) {
  global_n = n;
  ans = 0;
  dfs(1, 1, 1);
  return ans;
}
}  // namespace PNS

int main() {
  PNS::init();  //预处理函数
  long long n;
  scanf("%lld", &n);
  printf("%d\n", PNS::solve(n));
  return 0;
}
