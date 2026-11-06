#include <algorithm>
#include <iostream>
using std::cin;
using std::cout;
#define ls(x) son[x][0]
#define rs(x) son[x][1]
#define ms(x) son[x][2]
int son[10][3], size[10];

// --8<-- [start:example165]
// ls(x) x的左儿子
// rs(x) x的右儿子
// ms(x) x的中儿子
// type==0 是 Compress Node
// type==1 是 Rake Node
void pushup(int x, int type) {
  if (type == 0)
    size[x] = size[rs(x)] + size[ms(x)] + 1;
  else
    size[x] = size[rs(x)] + size[ms(x)] + size[ls(x)];
  return;
}

// --8<-- [end:example165]
int main() {
  son[1][0] = 2;
  son[1][1] = 3;
  son[1][2] = 4;
  cin >> size[2] >> size[3] >> size[4];
  pushup(1, 0);
  cout << size[1] << "\n";
  pushup(1, 1);
  cout << size[1] << "\n";
}
