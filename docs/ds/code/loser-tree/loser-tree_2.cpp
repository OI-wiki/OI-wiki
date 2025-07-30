#include <iostream>
#include <vector>
using namespace std;

const int INF = 0x3f3f3f3f;

template <typename T, int way>
struct loser_tree {
  vector<int> losers;  // 败者数组, losers[0] 为胜者
  vector<T> data;      // data[i] 第 i 路的首部数据
  vector<bool> empty;  // 当没有新元素填充进来时, 说明该路已为空
  using range = pair<int, int>;

  loser_tree() : losers(way), data(way), empty(way) {}

  void reset_empty() { fill(empty.begin(), empty.end(), true); }

  void reset_losers() { fill(losers.begin(), losers.end(), -INF); }

  void reset() {
    reset_empty();
    reset_losers();
  }

  // 设置第 i 元素
  void set(int i, const T& val) {
    empty[i] = false;  // 填充新元素时, 置该路 empty[i] = false
    data[i] = val;
  }

  // 对第 i 路进行调整
  void adjust(int u) {
    int v = (way + u) / 2;  // 初始为第 u 路数据节点的父亲 (败者节点)

    while (v > 0) {
      if (losers[v] == -INF) {
        losers[v] = u;
        break;
      } else {
        const T &a = empty[u] ? INF : data[u],
                &b = empty[losers[v]] ? INF : data[losers[v]];

        if (a > b) swap(losers[v], u);
      }
      v /= 2;
    }
    losers[0] = u;
  }

  // 对整个 v 数组进行 K 路合并, 合并结果输出到 res, 新区间信息输出到 rg
  void merge(vector<T>& v, vector<range>& rg, vector<T>& res) {
    int n = rg.size(), cur = 0;  // cur 为将要填入的下一个结果下标
    vector<range> new_rg;
    reset_empty();

    int L = 0;
    while (L < n) {
      int R = min(L + way, n), m = R - L;
      new_rg.emplace_back(rg[L].first, rg[R - 1].second);
      reset_losers();  // 重置上一轮的 losers 数组, 否则可能影响当前轮比较
      if (m != way) reset_empty();  // 剩下的区间个数不足 K 路时, 还要重置 emtpy

      for (int i = 0; i < m; ++i) {
        int x = L + i;
        if (rg[x].first < rg[x].second) set(i, v[rg[x].first++]);
      }
      // 无论是否填充了 K 路数据, **每路都需要进行一次调整**
      for (int i = 0; i < way; ++i) adjust(i);

      while (true) {
        int winner = losers[0];
        if (empty[winner]) break;  // 胜者已经没有新元素时, 当前轮合并完成
        empty[winner] = true;  // 取出胜者时立即置 empty = true
        res[cur++] = data[winner];

        int x = L + winner;
        if (rg[x].first < rg[x].second) set(winner, v[rg[x].first++]);
        adjust(winner);
      }

      L = R;
    }
    rg = new_rg;  // 拷贝新区间到 rg 数组
  }

  // 置换选择排序, 用于得到初始的合并段, 结果输出到 res, 区间段信息输出到 rg
  void replacement_selection(vector<T>& v, vector<T>& res, vector<range>& rg) {
    int n = v.size();
    int num = min(n, way), last = 0;
    // candidate 数组, 用于记录小于当前 minimax 的候补者 (可能进入下一个区间段)
    vector<bool> cand(way);
    reset();

    T minimax = -INF;
    for (int i = 0; i < num; ++i) set(i, v[i]);
    for (int i = 0; i < way; ++i) adjust(i);

    int cur = 0;
    while (cur < n) {
      int winner = losers[0];
      if (empty[winner]) {  // 无法再从当前工作区中选出新的 minimax
        // 左闭右开区间 [l, r)
        rg.emplace_back(last, cur);
        last = cur;
        minimax = -INF;
        for (int i = 0; i < way; ++i)
          if (cand[i]) empty[i] = cand[i] = false;  // 仅重新输入候补者
        reset_losers();  // 重置败者, 否则结果错误
        for (int i = 0; i < way; ++i) adjust(i);  // 对**所有路**重新调整
        continue;
      }

      empty[winner] = true;
      if (data[winner] >= minimax) {
        res[cur++] = minimax = data[winner];
        if (num < n) set(winner, v[num++]);
      } else {
        cand[winner] = true;  // 小于当前 minimax 的作为候补者
      }
      adjust(winner);
    }

    rg.emplace_back(last, cur);
  }

  // K 路归并排序, 最终结果保存到 v 数组
  void mergesort(vector<T>& v) {
    vector<T> t(v.size());
    vector<range> rg;

    replacement_selection(v, t, rg);
    bool f{};
    while (rg.size() != 1) {
      // 交替使用 v 和 t 数组作为输入和输出
      auto &y = f ? t : v, &x = f ? v : t;

      merge(x, rg, y);
      f = !f;
    }
    if (!f) v = t;
  }
};

int main(void) {
  ios::sync_with_stdio(false);

  int n;
  cin >> n;
  vector<int> v(n);

  for (auto& x : v) cin >> x;

  loser_tree<int, 4> t;
  t.mergesort(v);

  for (int i = 0; i < n; ++i) cout << v[i] << " \n"[i == n - 1];
}
