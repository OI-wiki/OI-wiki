#include <cstdint>
#include <vector>
using i32 = int32_t;
using u32 = uint32_t;

class dsu {
  // p[i] < 0 时表示 i 为根节点，其对应的子树大小为 -p[i]
  // p[i] >= 0 时表示 i 不为根节点，其父亲节点的编号为 p[i]
  std::vector<i32> p;

 public:
  // 节点编号从 0 到 sz-1
  explicit dsu(u32 sz) : p(sz, -1) {}

  i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }

  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }

  bool same_root(u32 x, u32 y) { return find(x) == find(y); }

  bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) std::swap(x, y);  // 启发式合并
    p[x] += p[y], p[y] = (i32)x;
    return true;
  }
};