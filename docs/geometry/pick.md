## Pick 定理

Pick 定理：给定顶点座标均是整点（或正方形格子点）的简单多边形，皮克定理说明了其面积 ${\displaystyle A}$ 和内部格点数目 ${\displaystyle i}$ 、边上格点数目 ${\displaystyle b}$ 的关系： ${\displaystyle A=i+{\frac {b}{2}}-1}$ 。

具体证明：[Pick's theorem](https://en.wikipedia.org/wiki/Pick%27s_theorem)

它有以下推广：

-   取格点的组成图形的面积为一单位。在平行四边形格点，皮克定理依然成立。套用于任意三角形格点，皮克定理则是 ${\displaystyle A=2 \times i+b-2}$ 。
-   对于非简单的多边形 ${\displaystyle P}$ ，皮克定理 ${\displaystyle A=i+{\frac {b}{2}}-\chi (P)}$ ，其中 ${\displaystyle \chi (P)}$ 表示 ${\displaystyle P}$ 的**欧拉特征数**。
-   高维推广：Ehrhart 多项式
-   皮克定理和**欧拉公式**（ ${\displaystyle V-E+F=2}$ ）等价。

## 一道例题 (POJ 1265)

### 题目大意

给一个平面上的简单多边形，求边上的点，多边形内的点，多边形面积。

### Solution

这道题目其实用了以下三个知识：

-   以格子点为顶点的线段，覆盖的点的个数为 $\gcd(dx,dy)$ ，其中， $dx,dy$ 分别为线段横向占的点数和纵向占的点数。如果 $dx$ 或 $dy$ 为 $0$ ，则覆盖的点数为 $dy$ **或** $dx$ 。
-   Pick 定理：平面上以格子点为顶点的简单多边形的面积 = 边上的点数/2 + 内部的点数 + 1。
-   任意一个多边形的面积等于按顺序求相邻两个点与原点组成的向量的叉积之和（这个也可以通过顺时针定积分求得）。
     于是这题就愉快地做完了

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int MAXN = 110;
struct node {
  int x, y;
} p[MAXN];
inline int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
inline int area(int a, int b) { return p[a].x * p[b].y - p[a].y * p[b].x; }
int main() {
  int t, ncase = 1;
  scanf("%d", &t);
  while (t--) {
    int n, dx, dy, x, y, num = 0, sum = 0;
    scanf("%d", &n);
    p[0].x = 0, p[0].y = 0;
    for (int i = 1; i &lt; = n; i++) {
      scanf("%d%d", &x, &y);
      p[i].x = x + p[i - 1].x, p[i].y = y + p[i - 1].y;
      dx = x, dy = y;
      if (x & lt; 0) dx = -x;
      if (y & lt; 0) dy = -y;
      num += gcd(dx, dy);
      sum += area(i - 1, i);
    }
    if (sum & lt; 0) sum = -sum;
    printf("Scenario #%d:\\n", ncase++);
    printf("%d %d %.1f\\n\\n", (sum - num + 2) >> 1, num, sum \* 0.5);
  }
  return 0;
}
```
