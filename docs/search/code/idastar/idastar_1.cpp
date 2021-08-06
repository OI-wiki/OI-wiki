// 埃及分数问题
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int a, b, maxd;

long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }

// 返回满足 1/c <= a/b 的最小 c 值
inline int get_first(long long a, long long b) { return b / a + 1; }

const int maxn = 100 + 5;

long long v[maxn], ans[maxn];

// 如果当前解 v 比目前最优解 ans 更优，更新 ans
bool better(int d) {
  for (int i = d; i >= 0; i--)
    if (v[i] != ans[i]) {
      return ans[i] == -1 || v[i] < ans[i];
    }
  return false;
}

// 当前深度为 d，分母不能小于 from，分数之和恰好为 aa/bb
bool dfs(int d, int from, long long aa, long long bb) {
  if (d == maxd) {
    if (bb % aa) return false;  // aa/bb 必须是埃及分数
    v[d] = bb / aa;
    if (better(d)) memcpy(ans, v, sizeof(long long) * (d + 1));
    return true;
  }
  bool ok = false;
  from = max(from, get_first(aa, bb));  // 枚举的起点
  for (int i = from;; i++) {
    // 剪枝：如果剩下的 maxd+1-d 个分数全部都是 1/i，加起来仍然不超过
    // aa/bb，则无解
    if (bb * (maxd + 1 - d) <= i * aa) break;
    v[d] = i;
    // 计算 aa/bb - 1/i，设结果为 a2/b2
    long long b2 = bb * i;
    long long a2 = aa * i - bb;
    long long g = gcd(a2, b2);  // 以便约分
    if (dfs(d + 1, i + 1, a2 / g, b2 / g)) ok = true;
  }
  return ok;
}

int main() {
  int kase = 0;
  while (cin >> a >> b) {
    int ok = 0;
    for (maxd = 1; maxd <= 100; maxd++) {  //枚举深度上限
      memset(ans, -1, sizeof(ans));
      if (dfs(0, get_first(a, b), a, b)) {  //开始进行搜索
        ok = 1;
        break;
      }
    }
    cout << "Case " << ++kase << ": ";
    if (ok) {
      cout << a << "/" << b << "=";
      for (int i = 0; i < maxd; i++) cout << "1/" << ans[i] << "+";
      cout << "1/" << ans[maxd] << "\n";
    } else
      cout << "No solution.\n";
  }
  return 0;
}
