* * *

title: mmmwiki
date: 2010-08-12 10:40:23
tags:

* * *

# 旋转卡壳

前置芝士：叉积，极角排序

~~旋 (xuán) 转 (zhuàn) 卡 (qia) 壳 (qiào)~~

## 一句话总结

求凸包的直径一种方法

## 实现

首先我们求出来一个凸包（绿色），然后才能找直径（红色）~~（bushi）~~

![](https://cdn.luogu.com.cn/upload/image_hosting/8ehlpvc1.png)

~~其实只要找到最长距离的两个点就可以了~~

找直径的方式：找两个点，做一条平行线，然后比较距离~~（其实并没有什么用，但是我们要引入旋转卡壳）~~

![](https://cdn.luogu.com.cn/upload/image_hosting/paozftbk.png)

实际上我们可以转化为两个相邻的点的线段所在的直线到最远的点的距离，这样单纯的算距离就变成了求三角形面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/7cyr6wax.png)

我们在做无用功？

不是，于是精彩的来了，（如下图）CB 为底的三角形面积是单峰函数（就算不是也只有两个点能让这个三角形取最大值），我们扫描出来了 $CB$ 为底的最大值，比较 $GC,GB$ 的距离，然后逆时针上去（ $E \to F \to B \to ...$ 以此类推）

这时候对底边面积最大的点一定在逆时针移动（用手推一推就好了）

这样不难发现三角形的顶点（这里姑且认为是临边不与这条平行线重合的点）不会再回到原来的点。

因此时间复杂度达到了美妙的 $O(Nlog_2N)$ （排序占了大头）

## 代码

```cpp
#include <touwenjian.h>

#define int long long

using namespace std;

struct node {
  int x, y;
} p[200200], s[200200];

int n, size;

inline int cmp(node a, node b) {
  double k1, k2;
  k1 = atan2((a.y - p[1].y), (a.x - p[1].x));
  k2 = atan2((b.y - p[1].y), (b.x - p[1].x));
  if (k1 == k2) return a.x < b.x;
  return k1 < k2;
}

inline int getdis(node a, node b) {
  return 1ll * (a.x - b.x) * (a.x - b.x) + 1ll * (a.y - b.y) * (a.y - b.y);
}

inline int getcj(node a, node b, node c) {
  return 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (b.y - a.y) * (c.x - a.x);
}

inline int bj(node a, node b) {
  return (a.y > b.y || (a.y == b.y) && (a.x > b.x));
}

inline void gettb() {
  p[0].x = p[0].y = 0x3f3f3f3f;
  register int i, j;
  for (i = 1; i <= n; i++)
    if (bj(p[0], p[i]))
      p[0] = p[i], j = i;  //找到最小边的点，并且把他放到第一位
  swap(p[j], p[1]);
  sort(p + 2, p + n + 1, cmp);  //对后面的点极点排序
  s[++size] = p[1];
  s[++size] = p[2];  //让前两个点入栈（他们一定是在凸包上）
  for (i = 3; i <= n;) {
    if (size >= 2 && getcj(s[size - 1], p[i], s[size]) >= 0)
      size--;  //就是上面说的 (这里的上图在凸包的那里)
    else
      s[++size] = p[i++];
  }
  s[0] = s[size];  //记得凸包要首尾相连
}

inline int getmmx() {
  int ans = 0;
  if (size == 2)
    return getdis(s[0], s[1]);  //只有两个点的时候不能构成三角形，所以要特判
  int j = 2;
  for (int i = 0; i < size; i++) {
    while (getcj(s[i], s[i + 1], s[j]) < getcj(s[i], s[i + 1], s[j + 1]))
      j = (j + 1) %
          size;  //实际上这也是在找面积，由于面积只有一个顶点，所以下一个j变小的时候就退出
    ans = max(ans,
              max(getdis(s[i], s[j]), getdis(s[i + 1], s[j])));  //找到距离最远的一条线段，并且与当前最大值比较
                                                                 //(求面积即可)
  }
  return ans;  //最后就是直径了
}

signed main() {
  ios::sync_with_stdio(false);
  register int i, j;
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> p[i].x >> p[i].y;
  }
  gettb();
  cout << getmmx() << endl;
  return 0;
}
```

## 例题

 [模板题](https://www.luogu.com.cn/problem/P1452) 

 [P3187 \[HNOI2007\] 最小矩形覆盖](https://www.luogu.com.cn/problem/P3187) 

 [UVA10173 Smallest Bounding Rectangle](https://www.luogu.com.cn/problem/UVA10173) 
