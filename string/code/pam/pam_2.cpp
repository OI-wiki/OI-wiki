#include <cstring>
#include <iostream>
#include <string>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
constexpr int MAXN = 1000000 + 5;

int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}

namespace pam {
int sz, tot, last;
int ch[MAXN][26], len[MAXN], fail[MAXN];
int cnt[MAXN], dep[MAXN], dif[MAXN], slink[MAXN];
char s[MAXN];

int node(int l) {  // 建立一个长度为 l 的新节点
  sz++;
  memset(ch[sz], 0, sizeof(ch[sz]));
  len[sz] = l;
  fail[sz] = 0;
  cnt[sz] = 0;
  dep[sz] = 0;
  return sz;
}

void clear() {  // 初始化
  sz = -1;
  last = 0;
  s[tot = 0] = '$';
  node(0);
  node(-1);
  fail[0] = 1;
}

int getfail(int x) {  // 找到后缀回文
  while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
  return x;
}

void insert(char c) {  // 建树
  s[++tot] = c;
  int now = getfail(last);
  if (!ch[now][c - 'a']) {
    int x = node(len[now] + 2);
    fail[x] = ch[getfail(fail[now])][c - 'a'];
    dep[x] = dep[fail[x]] + 1;
    ch[now][c - 'a'] = x;
    dif[x] = len[x] - len[fail[x]];
    if (dif[x] == dif[fail[x]])
      slink[x] = slink[fail[x]];
    else
      slink[x] = fail[x];
  }
  last = ch[now][c - 'a'];
  cnt[last]++;
}
}  // namespace pam

using pam::dif;
using pam::fail;
using pam::len;
using pam::slink;
int n, dp[MAXN], g[MAXN];
string s;
char t[MAXN];

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  pam::clear();
  cin >> s;
  n = s.size();
  s = " " + s;
  for (int i = 1, j = 0; i <= n; i++) t[++j] = s[i], t[++j] = s[n - i + 1];
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    pam::insert(t[i]);
    for (int x = pam::last; x > 1; x = slink[x]) {
      g[x] = dp[i - len[slink[x]] - dif[x]];
      if (dif[x] == dif[fail[x]]) g[x] = add(g[x], g[fail[x]]);
      if (i % 2 == 0) dp[i] = add(dp[i], g[x]);  // 在偶数位置更新 dp 数组
    }
  }
  cout << dp[n];
  return 0;
}
