#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;

long long power(long long a, long long n = mod - 2) {
  long long res = 1;
  while (n) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return res;
}

const long long power24 = power(24), power2 = power(2);

int n, m;
vector<int> E[100001], E1[100001], E2[100001];
bool vis[100001];
int cnt1[100001], cnt2[100001];

long long solve1();
long long solve2();
long long solve3();
long long solve4();
long long solve5();
long long ans[6];

long long solve1() {
  if (ans[1] != -1) return ans[1];
  ans[1] = 0;
  for (int i = 1; i <= n; i++) {
    int x = E[i].size();
    ans[1] +=
        1ll * x * (x - 1) % mod * (x - 2) % mod * (x - 3) % mod * power24 % mod;
  }
  return ans[1] %= mod;
}

long long solve2() {
  if (ans[2] != -1) return ans[2];
  ans[2] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j : E1[i])
      for (int k : E1[j]) cnt1[k]++;
    for (int j : E2[i])
      for (int k : E1[j])
        if (k != i) cnt2[k]++;
    for (int j : E1[i])
      for (int k : E1[j])
        ans[2] +=
            (1ll * cnt1[k] * (cnt1[k] - 1) / 2 + 1ll * cnt1[k] * cnt2[k]) % mod,
            cnt1[k] = 0;
    for (int j : E2[i])
      for (int k : E1[j])
        if (k != i)
          ans[2] += 1ll * cnt2[k] * (cnt2[k] - 1) / 2 % mod * power2 % mod,
              cnt2[k] = 0;
  }
  return ans[2];
}

long long solve3() {
  if (ans[3] != -1) return ans[3];
  ans[0] = ans[3] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j : E1[i]) vis[j] = true;
    for (int j : E1[i])
      for (int k : E1[j])
        if (vis[k])
          ans[3] =
              (1ll * ans[3] + E[i].size() + E[j].size() + E[k].size() - 6) %
              mod,
          ans[0]++;
    for (int j : E1[i]) vis[j] = false;
  }
  return ans[3];
}

long long solve4() {
  if (ans[4] != -1) return ans[4];
  ans[4] = 0;
  for (int i = 1; i <= n; i++)
    for (int j : E[i])
      (ans[4] += 1ll * (E[j].size() - 1) * (E[j].size() - 2) / 2 *
                 (E[i].size() - 1) % mod) %= mod;
  return ans[4] = (ans[4] - 2 * solve3()) % mod;
}

long long solve5() {
  if (ans[5] != -1) return ans[5];
  ans[5] = 0;
  for (int i = 1; i <= n; i++) {
    long long sum = 0;
    for (int j : E[i]) {
      ans[5] += sum * (E[j].size() - 1) % mod;
      sum += E[j].size() - 1;
    }
  }
  solve3();
  return ans[5] =
             (ans[5] % mod - 2 * solve3() - 4 * solve2() - 3 * ans[0]) % mod;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    ans[5] = ans[1] = ans[2] = ans[4] = ans[3] = -1;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) E[i].clear(), E1[i].clear(), E2[i].clear();
    while (m--) {
      int x, y;
      scanf("%d%d", &x, &y);
      E[x].push_back(y), E[y].push_back(x);
    }
    for (int i = 1; i <= n; i++)
      for (int j : E[i]) {
        if (make_pair(E[i].size(), i) < make_pair(E[j].size(), j))
          E1[i].push_back(j);
        else
          E2[i].push_back(j);
      }
    printf(
        "%lld\n",
        ((solve5() + solve1() + solve2() + solve4() + solve3()) % mod + mod) %
            mod);
  }
  return 0;
}