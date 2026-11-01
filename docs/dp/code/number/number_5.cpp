#include <cstdio>
#include <cstring>

long long f[50][50][2];
int dig[50], b[50];

// --8<-- [start:program]
int check(char cc[]) {  // n 的特判
  int strc = strlen(cc);
  for (int i = 0; i < strc; ++i) {
    if (!(cc[i] == cc[strc - i - 1] &&
          (cc[i] == '1' || cc[i] == '8' || cc[i] == '0')))
      return 0ll;
  }
  return 1ll;
}

// now: 当前位, eff: 有效位, fulc: 是否全顶格, ful0: 是否全0
long long dfs(int now, int eff, bool ful0, bool fulc) {
  if (now == 0) return 1ll;
  if (!fulc && f[now][eff][ful0] != -1)  // 记忆化
    return f[now][eff][ful0];

  long long res = 0;
  int maxk = fulc ? dig[now] : 9;
  for (int i = 0; i <= maxk; ++i) {
    if (i != 0 && i != 1 && i != 8) continue;
    b[now] = i;
    if (ful0 && i == 0)  // 全前导 0
      res += dfs(now - 1, eff - 1, 1, 0);
    else if (now > eff / 2)                                  // 未过半程
      res += dfs(now - 1, eff, 0, fulc && (dig[now] == i));  // 已过半程
    else if (b[now] == b[eff - now + 1])
      res += dfs(now - 1, eff, 0, fulc && (dig[now] == i));
  }
  if (!fulc) f[now][eff][ful0] = res;
  return res;
}

char cc1[100], cc2[100];
int strc, ansm, ansn;

long long get(char cc[]) {  // 处理封装
  strc = strlen(cc);
  for (int i = 0; i < strc; ++i) dig[strc - i] = cc[i] - '0';
  return dfs(strc, strc, 1, 1);
}

int main() {
  std::memset(f, -1, sizeof(f));
  int t;
  std::scanf("%d", &t);
  while (t--) {
    std::scanf("%99s%99s", cc1, cc2);
    std::printf("%lld\n", get(cc2) - get(cc1) + check(cc1));
  }
}

// --8<-- [end:program]
