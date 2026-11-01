#include <iostream>
#include <queue>
#include <vector>
using namespace std;
constexpr int N = 100005;

// --8<-- [start:storage]
int parent[N];
int lch[N], rch[N];
// -- or --
int child[N][2];

// --8<-- [end:storage]

struct BinaryNode {
  int key, val;
  BinaryNode *left = nullptr, *right = nullptr;
};

using BiTree = BinaryNode;
using TreeNode = BinaryNode;
bool first;

void visit(int v) {
  if (!first) cout << ' ';
  first = false;
  cout << v;
}

// --8<-- [start:preorder]
void preorder(BiTree* root) {
  if (root) {
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
  }
}

// --8<-- [end:preorder]
// --8<-- [start:inorder]
void inorder(BiTree* root) {
  if (root) {
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
  }
}

// --8<-- [end:inorder]
// --8<-- [start:postorder]
void postorder(BiTree* root) {
  if (root) {
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
  }
}

// --8<-- [end:postorder]
// --8<-- [start:morris]
void morris(TreeNode* root) {
  TreeNode* cur = root;
  while (cur) {
    if (!cur->left) {
      // 如果当前节点没有左子节点，则输出当前节点的值并进入右子树
      std::cout << cur->val << " ";
      cur = cur->right;
      continue;
    }
    // 找到当前节点的左子树的最右节点
    TreeNode* mostRight = cur->left;
    while (mostRight->right && mostRight->right != cur) {
      mostRight = mostRight->right;
    }
    if (!mostRight->right) {
      // 如果最右节点的right指针为空，将其指向当前节点，并进入左子树
      mostRight->right = cur;
      cur = cur->left;
    } else {
      // 如果最右节点的right指针指向当前节点，说明左子树已经遍历完毕，输出当前节点的值并进入右子树
      mostRight->right = nullptr;
      std::cout << cur->val << " ";
      cur = cur->right;
    }
  }
}

// --8<-- [end:morris]

int main() {
  int n;
  cin >> n;
  vector<BinaryNode> nodes(n);
  for (int i = 0; i < n; ++i) {
    cin >> nodes[i].key >> lch[i] >> rch[i];
    nodes[i].val = nodes[i].key;
    child[i][0] = lch[i];
    child[i][1] = rch[i];
  }
  for (int i = 0; i < n; ++i) {
    if (lch[i] >= 0) {
      nodes[i].left = &nodes[lch[i]];
      parent[lch[i]] = i;
    }
    if (rch[i] >= 0) {
      nodes[i].right = &nodes[rch[i]];
      parent[rch[i]] = i;
    }
  }
  BinaryNode* root = n ? &nodes[0] : nullptr;
  first = true;
  preorder(root);
  cout << '\n';
  first = true;
  inorder(root);
  cout << '\n';
  first = true;
  postorder(root);
  cout << '\n';
  first = true;
  morris(root);
  cout << '\n';
}
