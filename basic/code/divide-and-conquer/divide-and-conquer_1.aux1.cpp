#include "divide-and-conquer_1.h"

#include <cstring>
#include <iostream>
constexpr int MAXN = 1000;  // maximum number of nodes

extern int pathSum(TreeNode *root, int sum);

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
