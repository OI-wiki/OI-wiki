## 简介

随机增量算法是计算几何的一个重要算法，它对理论知识要求不高，算法时间复杂度低，应用范围广大。

增量法 (Incremental Algorithm) 的思想与第一数学归纳法类似，它的本质是将一个问题化为规模刚好小一层的子问题。解决子问题后加入当前的对象。写成递归式是：

$$
T(n)=T(n-1)+g(n)
$$

增量法形式简洁，可以应用于许多的几何题目中。

增量法往往结合随机化，可以避免最坏情况的出现。

## 最小圆覆盖问题

### 题意描述

在一个平面上有 $n$ 个点，求一个半径最小的圆，能覆盖所有的点。

### 算法

假设圆 $O$ 是前 $i-1$ 个点得最小覆盖圆，加入第 $i$ 个点，如果在圆内或边上则什么也不做。否，新得到的最小覆盖圆肯定经过第 $i$ 个点。

然后以第 $i$ 个点为基础（半径为 $0$），重复以上过程依次加入第 $j$ 个点，若第 $j$ 个点在圆外，则最小覆盖圆必经过第 $j$ 个点。

重复以上步骤。（因为最多需要三个点来确定这个最小覆盖圆，所以重复三次）

遍历完所有点之后，所得到的圆就是覆盖所有点得最小圆。

**时间复杂度** $O(n)$

**空间复杂度** $O(n)$

### 代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>

using namespace std;

int n;
double r;

struct point {
	double x,y;
} p[100005],o;


inline double sqr(double x) {
	return x*x;
}

inline double dis(point a,point b) {
	return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

inline bool cmp(double a,double b) {
	return fabs(a-b)<1e-8;
}

point geto(point a,point b,point c) {
	double a1,a2,b1,b2,c1,c2;
	point ans;
	a1=2*(b.x-a.x),b1=2*(b.y-a.y),c1=sqr(b.x)-sqr(a.x)+sqr(b.y)-sqr(a.y);
	a2=2*(c.x-a.x),b2=2*(c.y-a.y),c2=sqr(c.x)-sqr(a.x)+sqr(c.y)-sqr(a.y);
	if(cmp(a1,0)) {
		ans.y=c1/b1;
		ans.x=(c2-ans.y*b2)/a2;
	} else if(cmp(b1,0)) {
		ans.x=c1/a1;
		ans.y=(c2-ans.x*a2)/b2;
	} else {
		ans.x=(c2*b1-c1*b2)/(a2*b1-a1*b2);
		ans.y=(c2*a1-c1*a2)/(b2*a1-b1*a2);
	}
	return ans;
}

int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=1; i<=n; i++) swap(p[rand()%n+1],p[rand()%n+1]);
	o=p[1];
	for(int i=1; i<=n; i++) {
		if(dis(o,p[i])<r||cmp(dis(o,p[i]),r)) continue;
		o.x=(p[i].x+p[1].x)/2;
		o.y=(p[i].y+p[1].y)/2;
		r=dis(p[i],p[1])/2;
		for(int j=2; j<i; j++) {
			if(dis(o,p[j])<r||cmp(dis(o,p[j]),r)) continue;
			o.x=(p[i].x+p[j].x)/2;
			o.y=(p[i].y+p[j].y)/2;
			r=dis(p[i],p[j])/2;
			for(int k=1; k<j; k++) {
				if(dis(o,p[k])<r||cmp(dis(o,p[k]),r)) continue;
				o=geto(p[i],p[j],p[k]);
				r=dis(o,p[i]);
			}
		}
	}
	printf("%.10lf\n%.10lf %.10lf",r,o.x,o.y);
	return 0;
}
```
## 练习

[BZOJ 1337 \[最小圆覆盖\]](http://www.lydsy.com/JudgeOnline/problem.php?id=1337)
[BZOJ 2732 \[HNOI2012 射箭\]](http://www.lydsy.com/JudgeOnline/problem.php?id=2732)

## 参考资料

http://www.doc88.com/p-007257893177.html

https://www.cnblogs.com/aininot260/p/9635757.html

https://wenku.baidu.com/view/162699d63186bceb19e8bbe6.html

