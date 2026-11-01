#include <cstdlib>
#include <iostream>
#include <string>

// --8<-- [start:node]
// 二叉树结点的定义
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// --8<-- [end:node]

// --8<-- [start:core]
// 统计以 node 为起点、向下延伸且权值和为 sum 的路径．
int count(TreeNode *node, int sum) {
  if (node == nullptr) return 0;
  return (node->val == sum) + count(node->left, sum - node->val) +
         count(node->right, sum - node->val);
}

// 分别统计从当前结点出发、完全位于左子树和完全位于右子树的路径．
int pathSum(TreeNode *root, int sum) {
  if (root == nullptr) return 0;
  return count(root, sum) + pathSum(root->left, sum) +
         pathSum(root->right, sum);
}

// --8<-- [end:core]

constexpr int MAXN = 1000;  // maximum number of nodes

int main() {
  // build tree
  int n;
  std::cin >> n;  // number of nodes
  TreeNode *treeNodes[MAXN];
  for (int i = 0; i < n; i++) {
    std::string temp;
    std::cin >> temp;
    treeNodes[i] =
        (temp == "null") ? nullptr : new TreeNode(std::atoi(temp.c_str()));
    if (i & 1)
      treeNodes[i >> 1]->left = treeNodes[i];
    else if (i)
      treeNodes[(i - 1) >> 1]->right = treeNodes[i];
  }
  int sum;
  std::cin >> sum;
  std::cout << pathSum(treeNodes[0], sum) << std::endl;
  for (int i = 0; i < n; i++) {
    if (treeNodes[i]) delete treeNodes[i];
  }
}
