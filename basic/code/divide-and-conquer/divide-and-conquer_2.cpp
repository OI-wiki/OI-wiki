#include "divide-and-conquer_2.h"

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
