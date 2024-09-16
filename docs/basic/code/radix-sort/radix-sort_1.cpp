#include <algorithm>
#include <stack>
#include <tuple>
#include <vector>

using std::copy;  // from <algorithm>
using std::make_tuple;
using std::stack;
using std::tie;
using std::tuple;
using std::vector;

typedef unsigned int u32;
typedef unsigned int* u32ptr;

void MSD_radix_sort(u32ptr first, u32ptr last) {
  const size_t maxW = 0x100000000llu;
  const u32 maxlogW = 32;  // = log_2 W

  const u32 W = 256;  // 计数排序的值域
  const u32 logW = 8;
  const u32 mask = W - 1;  // 用位运算替代取模，详见下面的 key 函数

  u32ptr tmp =
      (u32ptr)calloc(last - first, sizeof(u32));  // 计数排序用的输出空间

  typedef tuple<u32ptr, u32ptr, u32> node;
  stack<node, vector<node>> s;
  s.push(make_tuple(first, last, maxlogW - logW));

  while (!s.empty()) {
    u32ptr begin, end;
    size_t shift, length;

    tie(begin, end, shift) = s.top();
    length = end - begin;
    s.pop();

    if (begin + 1 >= end) continue;  // elements <= 1

    // 计数排序
    u32 cnt[W] = {};
    auto key = [](const u32 x, const u32 shift) { return (x >> shift) & mask; };

    for (u32ptr it = begin; it != end; ++it) ++cnt[key(*it, shift)];
    for (u32 value = 1; value < W; ++value) cnt[value] += cnt[value - 1];

    // 求完前缀和后，计算相同关键字的元素范围
    if (shift >= logW) {
      s.push(make_tuple(begin, begin + cnt[0], shift - logW));
      for (u32 value = 1; value < W; ++value)
        s.push(make_tuple(begin + cnt[value - 1], begin + cnt[value],
                          shift - logW));
    }

    u32ptr it = end;
    do {
      --it;
      --cnt[key(*it, shift)];
      tmp[cnt[key(*it, shift)]] = *it;
    } while (it != begin);

    copy(tmp, tmp + length, begin);
  }
}