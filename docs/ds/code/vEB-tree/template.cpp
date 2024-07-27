namespace van_Emde_Boas_tree {
// 一些重要函数和定义
#define lg2(u) (31 - __builtin_clz(u))  // 使用内置函数计算对数
#define sqdown(u) (1 << (lg2(u) >> 1))  // 下根号
#define low(x) (x % sqdown(t->u))       // x 所在的簇号
#define high(x) (x / sqdown(t->u))      // x 在簇内的编号
#define index(x, y) (x * sqdown(t->u) + y)  // 根据簇号等计算原结点中编号

const int NIL = -1;  // 值不存在

struct vEB_node {
  typedef vEB_node *vEB;
  int u;          // 当前维护的值域大小
  int min, max;   // 当前值域的最值；min 不出现在子结构中
  vEB *clusters;  // 子结构
  vEB summary;
};
typedef vEB_node *vEB;

template <typename _T>
void swap(_T &a, _T &b) {
  _T t = a;
  a = b;
  b = t;
}

// 树 t 中是否有 x 元素
bool member(int x, vEB t) {
  if (x == t->min || x == t->max) return true;  // 特判一下加快速度
  if (t->u == 2) return false;                  // 否则不存在
  return member(low(x), t->clusters[high(x)]);
}

// 树 t 中的最大值
int query_max(vEB t) { return t->max; }

// 树 t 中的最小值
int query_min(vEB t) { return t->min; }

// 返回 t 是否为空
bool empty(vEB t) { return t->min == NIL; }

// 树 t 中元素 x 的前驱
int query_pre(int x, vEB t) {
  if (t->u == 2)  // 基本情况
  {
    if (x == 1 && t->min == 0) return t->min;
    return NIL;
  }
  // 特判一下加速
  if (t->max != NIL && t->max < x) return t->max;
  int hi = high(x), lo = low(x);
  // 对应簇非空，并且前驱在这个簇中（最小值小于 low）
  if (!empty(t->clusters[hi]) && t->clusters[hi]->min < lo)
    return index(hi, query_pre(lo, t->clusters[hi]));
  // 否则，尝试在前一个簇中寻找。
  int pre_cluster = query_pre(hi, t->summary);
  if (pre_cluster != NIL)  // 存在前一个簇，返回最大值
    return index(pre_cluster, t->clusters[pre_cluster]->max);
  // 不存在前一个簇
  // 但是由于 min 不存在于子结构中，有可能 x 的前驱是 min
  if (t->min != NIL && t->min < x) return t->min;
  return NIL;  // 真的没有了
}

// 后继同理，但是不需要考虑 min 了
int query_suc(int x, vEB t) {
  if (t->u == 2) {
    if (x == 0 && t->max == 1) return 1;
    return NIL;
  }
  // 同样特判加速
  if (t->min != NIL && x < t->min) return t->min;
  int hi = high(x), lo = low(x);
  // 当前簇内存在后继
  if (!empty(t->clusters[hi]) && t->clusters[hi]->max > lo)
    return index(hi, query_suc(lo, t->clusters[hi]));
  // 不存在，找下一个簇
  int suc_cluster = query_suc(hi, t->summary);
  if (suc_cluster != NIL)  // 有下一个，返回最小值
    return index(suc_cluster, query_min(t->clusters[suc_cluster]));
  return NIL;  // 不存在，直接 return
}

// 假定树 t 中原本不含有元素 x
void insert(int x, vEB t) {
  // 特判当前结点为空的情况
  if (empty(t)) {
    t->min = t->max = x;
    return;
  }
  // 基本情况，直接修改 min 和 max
  // 由于已经判断过空结点的情况，此时结点中只有一个元素
  // 请注意我们假定 x 不在原树内
  if (t->u == 2) {
    if (t->min == 1)  // 这个元素是 1
      t->min = 0;
    else  // 否则元素是 0
      t->max = 1;
    return;
  }
  if (x < t->min) swap(x, t->min);
  int hi = high(x), lo = low(x);
  // 如果簇为空，则需在 summary 中插入簇号
  if (empty(t->clusters[hi])) insert(hi, t->summary);
  // 不论簇是否为空直接调用
  // 注意如果簇为空，则这次调用是 O(1) 的
  // 并不会造成复杂度错误（这样只是方便实现）
  insert(lo, t->clusters[hi]);
  // 最后更新 max 即可
  if (t->max < x) t->max = x;
}

// 假定树 t 中原本包含元素 x
void erase(int x, vEB t) {
  // 特判当前结点只有一个元素的情况
  if (t->min != NIL && t->min == t->max) {
    // 由于此时 min 表示的元素不存在于任何子结构中，因此无需修改 summary
    t->min = t->max = NIL;
    return;
  }
  if (t->u == 2) {
    // 基本情况，此时有两个元素（一个元素的情况上面处理过了）
    t->min = t->max = 1 - x;
    return;
  }
  if (x == t->min)  // 如果当前删除的是最小值
  {
    int min2_cluster = query_min(t->summary);  // 找到第二小的值所在的簇
    int min2_value =
        query_min(t->clusters[min2_cluster]);  // 然后找到它在簇里的编号
    t->min = index(min2_cluster, min2_value);  // 更新最小值
    x = t->min;                                // 现在要删除最小值了
  }
  int hi = high(x), lo = low(x);
  erase(lo, t->clusters[hi]);  // 递归删 x
  if (empty(t->clusters[hi]))  // 簇删空了，需要更新 summary
  {
    // 注意能进入这个 if 说明簇里原来只有一个元素
    // 递归时直接进入特判，O(1) 返回
    // 因此虽然看起来调用两次递归，但是复杂度还是正确的
    erase(hi, t->summary);
    if (x == t->max)  // 把结点的 max 删了，要更新 max
    {
      // 由于现在原先的最大值已经被删除
      // 此时的 query_max 等实际上找的是原来的第二大
      int max2_cluster = query_max(t->summary);  // 先找到第二大所在的结点
      if (max2_cluster == NIL)  // 没有最大值，要么删光了，要么只剩一个 min
        t->max = t->min;  // 直接赋值，就算是 NIL 也一样
      else                // 还有第二大的，就更新
      {
        int max2_value = query_max(t->clusters[max2_cluster]);
        t->max = index(max2_cluster, max2_value);  // 更新第二大为现在的 max
      }
    }
  } else if (x == t->max)  // 没删空同样讨论最大值
  {
    // 原先的第二大值一定在 hi 这个簇里
    int max2_value = query_max(t->clusters[hi]);
    t->max = index(hi, max2_value);
  }
}

// 一次性建出整棵 vEB(u)
void build(int u, vEB t) {
  t->u = u;
  t->min = t->max = NIL;
  // 基本情况，则不需要进行递归
  if (u == 2) {
    t->summary = nullptr;
    t->clusters = nullptr;
  } else {
    int lg = lg2(u);            // 对 u 取以 2 为底的对数并向下取整
    int sqdn = 1 << (lg >> 1);  // sqrt down，下根号
    int squp = sqdn << (lg & 1);         // sqrt up，上根号
    t->summary = new vEB_node;           // 申请空间
    build(squp, t->summary);             // 先建 summary
    t->clusters = new vEB [squp];  // 申请出 squp 个指针的空间
                                         // clusters 都是 vEB(sqdn)
    for (int i = 0; i < squp; i++) {
      t->clusters[i] = new vEB_node;
      build(sqdn, t->clusters[i]);
    }
  }
}
// 取消定义，防止污染
#undef lg2
#undef sqdown
#undef low
#undef high
#undef index
}  // namespace van_Emde_Boas_tree
