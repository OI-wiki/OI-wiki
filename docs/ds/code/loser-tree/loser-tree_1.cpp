#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
struct LoserTree {
  std::vector<int> losers;               // 存储败者树的数组
  std::vector<std::vector<T>> segments;  // Data segments

  explicit LoserTree(int k) : losers(k, -1), segments(k) {}

  /*
   * 调整败者树，更新败者树状态。
   */
  void adjust(int s) {
    int t = (losers.size() + s) / 2;  // 计算从叶子节点的父节点开始的位置
    int current = s;                  // 当前节点

    while (t > 0) {
      if (losers[t] == -1) {
        // 如果父节点为空，直接将当前节点设置为父节点
        losers[t] = current;
        break;
      } else {
        // 比较当前节点和父节点的值，将较小的节点设置为父节点，如果节点为空，设置为最大值
        T a = segments[current].empty() ? std::numeric_limits<T>::max()
                                        : segments[current].front();
        T b = segments[losers[t]].empty() ? std::numeric_limits<T>::max()
                                          : segments[losers[t]].front();

        if (a > b) {
          // 如果当前节点的值大于父节点的值，即当前节点为败者，交换当前节点和父节点
          std::swap(current, losers[t]);
        }
      }
      t /= 2;  // 继续向上调整
    }
    losers[0] = current;  // 将最终的胜者节点设置为根节点
  }

  /*
   * 多路归并，合并所有数据段
   */
  void multiwayMerge() {
    while (true) {
      int winner = losers[0];
      if (segments[winner].empty()) {
        // 如果胜者节点为空，说明所有节点都已经合并完成
        break;
      }
      std::cout << segments[winner].front() << " ";
      segments[winner].erase(segments[winner].begin());
      adjust(winner);
    }
    std::cout << std::endl;
  }

  /*
   * 打印败者树的初始化状态
   */
  void printTree() const {
    for (size_t i = 0; i < segments.size(); ++i) {
      std::cout << "Segment " << i << ": ";
      for (const auto &elem : segments[i]) {
        std::cout << elem << " ";
      }
      std::cout << "\n";
    }
  }
};

void runTest(const std::vector<std::vector<int>> &data) {
  int k = (int)data.size();
  LoserTree<int> tree(k);  // 构造 K 路败者树

  // 初始化败者树
  for (int i = 0; i < k; ++i) {
    tree.segments[i] = data[i];
  }

  for (int i = k - 1; i >= 0; --i) {
    tree.adjust(i);
  }
  tree.multiwayMerge();
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> data(n);
  for (int i = 0; i < n; ++i) {
    int m;
    std::cin >> m;
    data[i].resize(m);
    for (int j = 0; j < m; ++j) std::cin >> data[i][j];
  }
  runTest(data);

  return 0;
}