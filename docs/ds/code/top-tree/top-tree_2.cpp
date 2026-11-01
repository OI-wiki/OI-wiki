#include <algorithm>
#include <iostream>
using namespace std;
#define ls(x) son[x][0]
#define rs(x) son[x][1]
#define ms(x) son[x][2]
int son[10][3], father[10], chain[10], subtree[10], val[10];

bool isroot(int x) { return ls(father[x]) != x && rs(father[x]) != x; }

// --8<-- [start:example166]
void pushdown(int x, int type) {
  if (type == 0) {
    // 处理链
    if (ls(x)) chain[ls(x)] += chain[x];
    if (rs(x)) chain[rs(x)] += chain[x];
    if (ls(x)) val[ls(x)] += chain[x];
    if (rs(x)) val[rs(x)] += chain[x];
    chain[x] = 0;
    // 处理子树
    if (ls(x)) subtree[ls(x)] += subtree[x];
    if (rs(x)) subtree[rs(x)] += subtree[x];
    if (ms(x)) subtree[ms(x)] += subtree[x];
    if (ls(x)) val[ls(x)] += subtree[x];
    if (rs(x)) val[rs(x)] += subtree[x];
    if (ms(x)) val[ms(x)] += subtree[x];
    subtree[x] = 0;
  } else {
    if (ls(x)) subtree[ls(x)] += subtree[x];
    if (rs(x)) subtree[rs(x)] += subtree[x];
    if (ms(x)) subtree[ms(x)] += subtree[x];
    if (ls(x)) val[ls(x)] += subtree[x];
    if (rs(x)) val[rs(x)] += subtree[x];
    if (ms(x)) val[ms(x)] += subtree[x];
    subtree[x] = 0;
  }
  return;
}

// 下传标记
void pushall(int x, int type) {
  if (!isroot(x)) pushall(father[x], type);
  pushdown(x, type);
  return;
}

// --8<-- [end:example166]
int main() {
  son[1][0] = 2;
  son[1][1] = 3;
  son[1][2] = 4;
  father[2] = father[3] = father[4] = 1;
  cin >> chain[1] >> subtree[1];
  pushall(2, 0);
  pushdown(1, 0);
  for (int i = 2; i <= 4; ++i) cout << val[i] << (i == 4 ? "\n" : " ");
  cout << chain[1] << " " << subtree[1] << "\n";
}
