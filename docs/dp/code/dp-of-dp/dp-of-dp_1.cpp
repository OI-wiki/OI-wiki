#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 100;

int T, a[MAXN + 1], h[MAXN + 1]; // a[]: 原始字符串对应的数值化表示；h[]: 临时数组，用于计算转移
int g[MAXN + 1], m, n;
int nx[1 << 16][4];              // 状态转移表：nx[mask][ch] 表示 mask 状态下追加 ch 后的新状态
int f[1001][1 << 16];            // DP 数组：f[i][mask] 表示长度为 i，处于状态 mask 的方案数
int ans[MAXN + 1];               // 最终答案：ans[i] 表示长度为 m 时，包含 i 个匹配位置的方案数

void add(int &x, int y) { x = (x + y) % MOD; } // 快速加法取模

// 状态转移函数：给定当前 mask 状态和当前字符 x（0~3），返回新状态
int calc(int mask, int x) {
  int res = 0;
  
  // g[i] 表示前 i 个字符中，在 mask 中出现过的位置数
  for (int i = 0; i < n; ++i)
    g[i + 1] = g[i] + ((mask >> i) & 1);

  // 构造 h[]：表示当前位置 i 处，最长前缀匹配长度
  for (int i = 1; i <= n; ++i) {
    if (a[i] == x)
      h[i] = g[i - 1] + 1;         // 当前字符匹配，继承之前的匹配长度 +1
    else
      h[i] = max(h[i - 1], g[i]);  // 否则取之前最大匹配长度
  }

  // 构造新的状态 mask
  for (int i = 1; i <= n; ++i)
    if (h[i] > h[i - 1])           // 新增了一个匹配字符
      res |= (1 << (i - 1));       // 标记这个位置为 1

  return res;
}

// 计算 mask 中有多少个 1（即匹配了多少位置）
int popcount(int x) {
  int res = 0;
  while (x) {
    res += x & 1;
    x >>= 1;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> T;
  while (T--) {
    string S;
    cin >> S >> m;
    n = S.length();

    memset(f, 0, sizeof(f));
    memset(ans, 0, sizeof(ans));
    memset(a, 0, sizeof(a));

    // 将字符串 S 转换为数字序列（A=0, C=1, G=2, T=3）
    for (int i = 0; i < n; ++i) {
      if (S[i] == 'A') a[i + 1] = 0;
      if (S[i] == 'C') a[i + 1] = 1;
      if (S[i] == 'G') a[i + 1] = 2;
      if (S[i] == 'T') a[i + 1] = 3;
    }

    int lim = (1 << n); // 所有可能的状态总数（n 位 01 状态）

    // 预处理所有状态的转移：nx[i][j] 表示当前状态 i，添加字符 j 后的状态
    for (int i = 0; i < lim; ++i)
      for (int j = 0; j < 4; ++j)
        nx[i][j] = calc(i, j);

    f[0][0] = 1; // 初始状态：长度为 0，状态为 0 的方案数为 1

    // DP 状态转移：每次添加一个字符，更新状态
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < lim; ++j)
        if (f[i][j])
          for (int k = 0; k < 4; ++k)
            add(f[i + 1][nx[j][k]], f[i][j]);

    // 按照匹配位置个数分类统计答案
    for (int i = 0; i < lim; ++i)
      add(ans[popcount(i)], f[m][i]);

    for (int i = 0; i <= n; ++i)
      cout << ans[i] << '\n';
  }

  return 0;
}
