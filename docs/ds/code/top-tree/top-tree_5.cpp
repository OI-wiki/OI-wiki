#include <algorithm>
#include <iostream>
using namespace std;
#define ls(x) son[x][0]
#define rs(x) son[x][1]
#define ms(x) son[x][2]
int son[10][3], len[10], diam[10], maxs[10][2], r[10];

// --8<-- [start:example174]
void pushup(int x, int op) {
  if (op == 0) {
    // 是 Compress Node
    len[x] = len[ls(x)] + len[rs(x)];
    diam[x] = maxs[ls(x)][1] + maxs[rs(x)][0];
    diam[x] =
        max(diam[x], max(maxs[ls(x)][1], maxs[rs(x)][0]) + maxs[ms(x)][0]);
    diam[x] = max(diam[x], max(max(diam[ls(x)], diam[rs(x)]), diam[ms(x)]));
    maxs[x][0] =
        max(maxs[ls(x)][0], len[ls(x)] + max(maxs[ms(x)][0], maxs[rs(x)][0]));
    maxs[x][1] =
        max(maxs[rs(x)][1], len[rs(x)] + max(maxs[ms(x)][0], maxs[ls(x)][1]));
  } else {
    // 是 Rake Node
    diam[x] = maxs[ls(x)][0] + maxs[rs(x)][0];
    diam[x] =
        max(diam[x], maxs[ms(x)][0] + max(maxs[ls(x)][0], maxs[rs(x)][0]));
    diam[x] = max(max(diam[x], diam[ms(x)]), max(diam[ls(x)], diam[rs(x)]));
    maxs[x][0] = max(maxs[ms(x)][0], max(maxs[ls(x)][0], maxs[rs(x)][0]));
  }
  return;
}

// --8<-- [end:example174]
// --8<-- [start:example175]
void pushrev(int x) {
  if (!x) return;
  r[x] ^= 1;
  swap(ls(x), rs(x));
  swap(maxs[x][0], maxs[x][1]);
}

// --8<-- [end:example175]
int main() {
  for (int i = 1; i <= 3; ++i) {
    cin >> len[i];
    diam[i] = maxs[i][0] = maxs[i][1] = len[i];
  }
  son[4][0] = 1;
  son[4][1] = 2;
  pushup(4, 0);
  cout << len[4] << " " << diam[4] << "\n";
  pushrev(4);
  cout << maxs[4][0] << " " << maxs[4][1] << "\n";
  son[5][0] = 1;
  son[5][1] = 2;
  son[5][2] = 3;
  pushup(5, 1);
  cout << diam[5] << " " << maxs[5][0] << "\n";
}
