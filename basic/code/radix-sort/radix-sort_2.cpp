#include <iostream>
#include <string>
#include <vector>
using namespace std;

// --8<-- [start:core]
constexpr int MAXN = 1000;

int get_digit(string* arr, int i, int dig) {
  if (arr[i][dig] == '\0') return 0;
  return arr[i][dig] - 'a' + 1;
}

void MSD_radix_sort_string_base(string* arr, int* begin, int* end,
                                int digit)  // 主体函数
// 对仅由小写字母构成的字符串排序
// 参数表示现在 [begin,end) 内的元素 [0,digit) 位都相同
// 现在从 digit 位开始进行排序
// 调用示例：MSD_radix_sort_string(a,a+n,0)
// 和上一份代码几乎完全相同，所以注释较少
// 为节省空间和时间，我们对下标数组进行排序，比较函数依旧比较字符串对应位
{
  if (begin >= end) return;
  static int tmp[MAXN + 5];
  static int cnt[28];
  vector<int> beg;
  beg.resize(28);
  // Q: 为什么开 28？
  // A: 0=空字符，1-26=a-z，27=额外空间（防止越界）
  for (int i = 0; i < 28; i++) cnt[i] = beg[i] = 0;
  for (int* it = begin; it != end; it++) cnt[get_digit(arr, *it, digit)] += 1;
  beg[0] = 0;
  for (int i = 1; i <= 27; i++) beg[i] = beg[i - 1] + cnt[i - 1];
  for (int i = 0; i < 28; i++) cnt[i] = 0;
  for (int* it = begin; it != end; it++) {
    int bitVal = get_digit(arr, *it, digit);
    tmp[beg[bitVal] + cnt[bitVal]] = *it;
    cnt[bitVal]++;
  }
  for (int* it = begin; it != end; it++) *it = tmp[it - begin];
  // 如果已经是空字符了就没必要递归了，所以递归 1~26
  for (int i = 1; i <= 26; i++)
    MSD_radix_sort_string_base(arr, begin + beg[i], begin + beg[i + 1],
                               digit + 1);
}

int label[MAXN + 5];

void MSD_radix_sort_string(string* begin, string* end)  // 调用接口
{
  static string tmp[MAXN + 5];
  int n = end - begin;
  for (int i = 0; i < n; i++) {
    label[i] = i;
    tmp[i] = *(begin + i);
  }
  MSD_radix_sort_string_base(tmp, label, label + n, 0);
  for (int i = 0; i < n; i++) {
    *(begin + i) = tmp[label[i]];
  }
}

// --8<-- [end:core]

string a[MAXN + 5];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  MSD_radix_sort_string(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) cout << a[i] << "\n";
}
