#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
constexpr unsigned MAXN = 1000;  // 要排序的数的个数
constexpr unsigned RADIX = 10;   // 基数
constexpr unsigned powRADIX[10] = {1,         10,        100,     1000,
                                   10000,     100000,    1000000, 10000000,
                                   100000000, 1000000000};  // RADIX 的幂

unsigned get_digit(unsigned value, int digit)  // 提取第 digit 位
{
  return (value / powRADIX[digit]) % RADIX;
}

void MSD_radix_sort(unsigned* begin, unsigned* end, int digit)
// 表示现在 [begin,end) 内的元素（10 进制下）前若干位都相同
// 只有最后 digit 位（第 digit-1 到 0 位）需要进行排序
// 调用示例：MSD_radix_sort(a,a+n,9)
{
  if (begin >= end)  // 空区间
  {
    return;
  }
  /**计数排序（个人写法仅供参考）**/
  static unsigned cnt[RADIX + 1],
      tmp[MAXN + 5];  // 由于不同层递归不会同时使用 cnt,tmp
                      // 数组（每层使用完毕才会调用下一层），使用 static
                      // 关键字可以节省空间
  vector<unsigned> beg;
  beg.resize(RADIX + 1);  // 对 beg 的访问可能冲突，使用局部变量
  for (int i = 0; i <= RADIX; i++) {
    cnt[i] = beg[i] = 0;  // 清空是一个好习惯
  }
  for (unsigned* it = begin; it != end; it++)  // 计数
  {
    int bitVal = get_digit(*it, digit - 1);
    cnt[bitVal] += 1;
  }
  beg[0] = 0;  // 计算每个数码开始存储的位置（偏移量）
  for (int i = 1; i <= RADIX; i++) {
    beg[i] = beg[i - 1] + cnt[i - 1];
  }
  // 多计算 beg[RADIX] 是因为这样可以直接定义 i 对应的范围是 [beg[i],beg[i+1])
  // 而不用担心那个 beg[i+1] 越界
  for (int i = 0; i < RADIX; i++) {
    cnt[i] = 0;
  }
  for (unsigned* it = begin; it != end; it++)  // 将计数排序结果放入 tmp
  {
    unsigned bitVal = get_digit(*it, digit - 1);  // 提取第 bit-1 位
    tmp[beg[bitVal] + cnt[bitVal]] =
        *it;  // 因为是倒序枚举，所以当前是第 cnt[bitVal]+1 个第 bit-1 位是
              // cnt[bitVal] 的
    cnt[bitVal]++;
  }
  for (unsigned* it = begin; it != end; it++)  // 将 tmp 拷贝回原数组
  {
    *it = tmp[it - begin];
  }
  /**迭代计算**/
  if (digit == 1)  // 已经是最低位
  {
    return;
  }
  for (int i = 0; i < RADIX; i++)  // 递归排序下一位
  {
    MSD_radix_sort(begin + beg[i], begin + beg[i + 1], digit - 1);
  }
}

// --8<-- [end:core]
unsigned a[MAXN + 5];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  MSD_radix_sort(a + 1, a + n + 1, 9);
  for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
}
