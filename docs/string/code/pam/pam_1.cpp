#include <bits/stdc++.h>
using namespace std;
const int maxn = 300000 + 5;
namespace pam {
int sz, tot, last;
int cnt[maxn], ch[maxn][26], len[maxn], fail[maxn];
char s[maxn];
int node(int l) {  //建立一个新节点，长度为 l
  sz++;
  memset(ch[sz], 0, sizeof(ch[sz]));
  len[sz] = l;
  fail[sz] = cnt[sz] = 0;
  return sz;
}
void clear() {  //初始化
  sz = -1;
  last = 0;
  s[tot = 0] = '$';
  node(0);
  node(-1);
  fail[0] = 1;
}
int getfail(int x) {  //找后缀回文
  while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
  return x;
}
void insert(char c) {  //建树
  s[++tot] = c;
  int now = getfail(last);
  if (!ch[now][c - 'a']) {
    int x = node(len[now] + 2);
    fail[x] = ch[getfail(fail[now])][c - 'a'];
    ch[now][c - 'a'] = x;
  }
  last = ch[now][c - 'a'];
  cnt[last]++;
}
long long solve() {
  long long ans = 0;
  for (int i = sz; i >= 0; i--) {
    cnt[fail[i]] += cnt[i];
  }
  for (int i = 1; i <= sz; i++) {  //更新答案
    ans = max(ans, 1ll * len[i] * cnt[i]);
  }
  return ans;
}
}  // namespace pam
char s[maxn];
int main() {
  pam::clear();
  scanf("%s", s + 1);
  for (int i = 1; s[i]; i++) {
    pam::insert(s[i]);
  }
  printf("%lld\n", pam::solve());
  return 0;
}
