#include "divide-and-conquer_1.h"

int pathSum(TreeNode *root, int sum) {
  if (root == nullptr) return 0;
  return count(root, sum) + pathSum(root->left, sum) +
    pathSum(root->right, sum);
}
    
int count(TreeNode *node, int sum) {
  if (node == nullptr) return 0;
  return (node->val == sum) + count(node->left, sum - node->val) +
    count(node->right, sum - node->val);
}