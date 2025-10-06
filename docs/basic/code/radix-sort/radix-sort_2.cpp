#include <iostream>
#include <string>
#include <vector>
using namespace std;

// --8<-- [start:core]
int conv(char ch) {
  if (ch == '\0') return 0;
  return ch - 'a' + 1;
}

constexpr int MAXN = 1000;

void MSD_radix_sort_string(string* begin, string* end,
                           int digit)  // 对仅由小写字母构成的字符串排序
// 表示现在 [begin,end) 内的元素 [0,digit) 位都相同
// 现在从 digit 位（第 digit-1 到 0 位）开始进行排序
// 调用示例：MSD_radix_sort_string(a,a+n,0)
// 和上一份代码几乎完全相同，所以注释较少
{
  if (begin >= end) return;
  static string tmp[MAXN + 5];
  static int cnt[28];
  vector<int> beg;
  beg.resize(28);
  // Q: 为什么开 28？
  // A: 0=空字符，1-26=a-z，27=额外空间（防止越界）
  for (int i = 0; i < 28; i++) cnt[i] = beg[i] = 0;
  for (string* it = begin; it != end; it++) cnt[conv((*it)[digit])] += 1;
  beg[0] = 0;
  for (int i = 1; i <= 27; i++) beg[i] = beg[i - 1] + cnt[i - 1];
  for (int i = 0; i < 28; i++) cnt[i] = 0;
  for (string* it = begin; it != end; it++) {
    int bitVal = conv((*it)[digit]);
    tmp[beg[bitVal] + cnt[bitVal]] = *it;
    cnt[bitVal]++;
  }
  for (string* it = begin; it != end; it++) *it = tmp[it - begin];
  // 如果已经是空字符了就没必要递归了，所以递归 1~26
  for (int i = 1; i <= 26; i++)
    MSD_radix_sort_string(begin + beg[i], begin + beg[i + 1], digit + 1);
}

// --8<-- [end:core]
string a[MAXN + 5];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  MSD_radix_sort_string(a + 1, a + n + 1, 0);
  for (int i = 1; i <= n; i++) cout << a[i] << "\n";
}
