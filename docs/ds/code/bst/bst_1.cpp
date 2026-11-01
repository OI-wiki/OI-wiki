#include <iostream>

// --8<-- [start:example17]
struct TreeNode {
  int key;
  TreeNode* left;
  TreeNode* right;
  // 维护其他信息，如高度，节点数量等
  int size;   // 当前节点为根的子树大小
  int count;  // 当前节点的重复数量

  TreeNode(int value)
      : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
};

// --8<-- [end:example17]

TreeNode* findMinNode(TreeNode* root);

void updateHeight(TreeNode* root) {
  root->size = root->count + (root->left ? root->left->size : 0) +
               (root->right ? root->right->size : 0);
}

// --8<-- [start:example18]
void inorderTraversal(TreeNode* root) {
  if (root == nullptr) {
    return;
  }
  inorderTraversal(root->left);
  std::cout << root->key << " ";
  inorderTraversal(root->right);
}

// --8<-- [end:example18]
// --8<-- [start:example19]
int findMin(TreeNode* root) {
  if (root == nullptr) {
    return -1;
  }
  while (root->left != nullptr) {
    root = root->left;
  }
  return root->key;
}

int findMax(TreeNode* root) {
  if (root == nullptr) {
    return -1;
  }
  while (root->right != nullptr) {
    root = root->right;
  }
  return root->key;
}

// --8<-- [end:example19]
// --8<-- [start:example20]
bool search(TreeNode* root, int target) {
  if (root == nullptr) {
    return false;
  }
  if (root->key == target) {
    return true;
  } else if (target < root->key) {
    return search(root->left, target);
  } else {
    return search(root->right, target);
  }
}

// --8<-- [end:example20]
// --8<-- [start:example21]
TreeNode* insert(TreeNode* root, int value) {
  if (root == nullptr) {
    return new TreeNode(value);
  }
  if (value < root->key) {
    root->left = insert(root->left, value);
  } else if (value > root->key) {
    root->right = insert(root->right, value);
  } else {
    root->count++;  // 节点值相等，增加重复数量
  }
  root->size = root->count + (root->left ? root->left->size : 0) +
               (root->right ? root->right->size : 0);  // 更新节点的子树大小
  return root;
}

// --8<-- [end:example21]
// --8<-- [start:example22]
// 此处返回值为删除 value 后的新 root
TreeNode* remove(TreeNode* root, int value) {
  if (root == nullptr) {
    return root;
  }
  if (value < root->key) {
    root->left = remove(root->left, value);
  } else if (value > root->key) {
    root->right = remove(root->right, value);
  } else {
    if (root->count > 1) {
      root->count--;  // 节点重复数量大于1，减少重复数量
    } else {
      if (root->left == nullptr) {
        TreeNode* temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        TreeNode* temp = root->left;
        delete root;
        return temp;
      } else {
        TreeNode* successor = findMinNode(root->right);
        root->key = successor->key;
        root->count = successor->count;  // 更新重复数量
        // 当 successor->count > 1时，也应该删除该节点，否则
        // 后续的删除只会减少重复数量
        successor->count = 1;
        root->right = remove(root->right, successor->key);
      }
    }
  }
  // 继续维护size，不写成 --root->size;
  // 是因为value可能不在树中，从而可能未发生删除
  root->size = root->count + (root->left ? root->left->size : 0) +
               (root->right ? root->right->size : 0);
  return root;
}

// 此处以右子树的最小值为例
TreeNode* findMinNode(TreeNode* root) {
  while (root->left != nullptr) {
    root = root->left;
  }
  return root;
}

// --8<-- [end:example22]
// --8<-- [start:example23]
int queryRank(TreeNode* root, int v) {
  if (root == nullptr) return 1;
  if (root->key == v) return (root->left ? root->left->size : 0) + 1;
  if (root->key > v) return queryRank(root->left, v);
  return queryRank(root->right, v) + (root->left ? root->left->size : 0) +
         root->count;
}

// --8<-- [end:example23]
// --8<-- [start:example24]
int querykth(TreeNode* root, int k) {
  if (root == nullptr) return -1;  // 或者根据需求返回其他合适的值
  if (root->left) {
    if (root->left->size >= k) return querykth(root->left, k);
    if (root->left->size + root->count >= k) return root->key;
  } else {
    if (k <= root->count) return root->key;
  }
  return querykth(root->right,
                  k - (root->left ? root->left->size : 0) - root->count);
}

// --8<-- [end:example24]
// --8<-- [start:example25]
TreeNode* rotateLeft(TreeNode* root) {
  TreeNode* newRoot = root->right;
  root->right = newRoot->left;
  newRoot->left = root;
  // 更新相关节点的信息
  updateHeight(root);
  updateHeight(newRoot);
  return newRoot;  // 返回新的根节点
}

TreeNode* rotateRight(TreeNode* root) {
  TreeNode* newRoot = root->left;
  root->left = newRoot->right;
  newRoot->right = root;
  updateHeight(root);
  updateHeight(newRoot);
  return newRoot;
}

// --8<-- [end:example25]

int main() {
  TreeNode* root = nullptr;
  int q;
  std::cin >> q;
  while (q--) {
    int op, x;
    std::cin >> op >> x;
    if (op == 1)
      root = insert(root, x);
    else if (op == 2)
      root = remove(root, x);
    else if (op == 3)
      std::cout << queryRank(root, x) << '\n';
    else if (op == 4)
      std::cout << querykth(root, x) << '\n';
    else if (op == 5 || op == 6) {
      TreeNode* p = root;
      int answer = -1;
      while (p) {
        if (op == 5 ? p->key < x : p->key > x) {
          answer = p->key;
          p = op == 5 ? p->right : p->left;
        } else
          p = op == 5 ? p->left : p->right;
      }
      std::cout << answer << '\n';
    } else if (op == 7) {
      inorderTraversal(root);
      std::cout << '\n';
    } else if (op == 8)
      std::cout << findMin(root) << ' ' << findMax(root) << '\n';
    else if (op == 9)
      std::cout << search(root, x) << '\n';
    else if (op == 10 && root && root->right)
      root = rotateLeft(root);
    else if (op == 11 && root && root->left)
      root = rotateRight(root);
  }
  while (root) root = remove(root, root->key);
}
