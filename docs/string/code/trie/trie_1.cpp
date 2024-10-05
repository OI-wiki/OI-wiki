#include <iostream>
#include <string>
using namespace std;
const int N = 500010;

string s;
int n, m, ch[N][26], tag[N], tot = 1;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;

  for (int i = 1; i <= n; ++i) {
    cin >> s;
    s = " " + s;
    int u = 1;
    for (int j = 1; s[j]; ++j) {
      int c = s[j] - 'a';
      if (!ch[u][c])
        ch[u][c] =
            ++tot;  // 如果这个节点的子节点中没有这个字符，添加上并将该字符的节点号记录为++tot
      u = ch[u][c];  // 往更深一层搜索
    }
    tag[u] = 1;  // 最后一个字符为节点 u 的名字未被访问到记录为 1
  }

  cin >> m;

  while (m--) {
    cin >> s;
    s = " " + s;
    int u = 1;
    for (int j = 1; s[j]; ++j) {
      int c = s[j] - 'a';
      u = ch[u][c];
      if (!u) break;  // 不存在对应字符的出边说明名字不存在
    }
    if (tag[u] == 1) {
      tag[u] = 2;  // 最后一个字符为节点 u 的名字已经被访问
      cout << "OK\n";
    } else if (tag[u] == 2)  // 已经被访问，重复访问
      cout << "REPEAT\n";
    else
      cout << "WRONG\n";
  }

  return 0;
}