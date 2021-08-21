#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;

int read() {  //快读
  int out = 0;
  char c;
  while (!isdigit(c = getchar()))
    ;
  for (; isdigit(c); c = getchar()) out = out * 10 + c - '0';
  return out;
}

const int N = 1000010;

struct Node {
  int val, ch[2], d;
} t[N];

int& rs(int x);
int merge(int x, int y);

int find(int x);

int n, m, f[N];
bool kill[N];
char op[10];

int main() {
  int i, x, y;

  n = read();

  for (i = 1; i <= n; ++i) {
    t[i].val = read();
    f[i] = i;
  }

  m = read();

  while (m--) {
    scanf("%s", op);
    if (op[0] == 'M') {
      x = read();
      y = read();
      if (kill[x] || kill[y] || find(x) == find(y)) continue;  //这是题意
      f[find(x)] = f[find(y)] = merge(find(x), find(y));
    } else {
      x = read();
      if (!kill[x]) {
        x = find(x);
        kill[x] = true;
        f[x] = f[t[x].ch[0]] = f[t[x].ch[1]] = merge(t[x].ch[0], t[x].ch[1]);
        // 由于堆中的点会 find 到 x，所以 f[x] 也要修改
        printf("%d\n", t[x].val);
      } else
        puts("0");
    }
  }

  return 0;
}

int& rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }

int merge(int x, int y) {  //左偏树并堆
  if (!x || !y) return x | y;
  if (t[x].val > t[y].val) swap(x, y);
  rs(x) = merge(rs(x), y);
  t[x].d = t[rs(x)].d + 1;
  return x;
}

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }  //查找