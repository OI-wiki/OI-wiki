#include "divide-and-conquer_1.h"
#include <iostream>
#include <cstring>
#define MAXN 1000  // maximum number of nodes

extern int pathSum(TreeNode *root, int sum);

TreeNode * build_tree(char valstr[][20]) {
  TreeNode *root = (strcmp(valstr[0], "null") == 0) ? nullptr : new TreeNode(atoi(valstr[0]));
  
  return root;
}

int main() {
  // build tree
  int n;
  std::cin >> n;  // number of nodes
  TreeNode *treeNodes[MAXN];
  for (int i = 0; i < n; i++) {
    char temp[20];
    std::cin >> temp;
    treeNodes[i] = (strcmp(temp, "null") == 0) ? nullptr : new TreeNode(atoi(temp));
    if (i & 1) treeNodes[i >> 1]->left = treeNodes[i];
    else treeNodes[i >> 1]->right = treeNodes[i];
  }
  int sum;
  std::cin >> sum;
  return pathSum(treeNodes[0], 0);
}
