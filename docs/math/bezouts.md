## 什么是贝祖定理？

贝祖定理，又称裴蜀定理。是代数几何中一个定理。

其内容是：

$x,y$ 的不定方程 $ax + by = c$ 有整数解的充要条件是 $\gcd(a, b)\mid c$ 。

即为如果 $a$ 与 $b$ 互质，那么一定存在两个整数 $x$ 与 $y$，使得 $ax+by=1$。

## 证明

还没有添加。

## 应用

[Codeforces Round #290 (Div. 2) D. Fox And Jumping](http://codeforces.com/contest/510/problem/D)

给出 $n$ 张卡片，分别有 $l_i$ 和 $c_i$。在一条无限长的纸带上，你可以选择花 $c_i$ 的钱来购买卡片 $i$，从此以后可以向左或向右跳 $l_i$ 个单位。问你至少花多少元钱才能够跳到纸带上全部位置。若不行，输出 $-1$。
   
- 正解：裴蜀定理+动态规划

- 最优解：裴蜀定理+ Dijkstra

分析该问题，先考虑两个数的情况，发现想要跳到每一个格子上，必须使得这些数通过数次相加或相加得出的绝对值为 $1$，进而想到了裴蜀定理。

如果 $a$ 与 $b$ 互质，那么一定存在两个整数 $x$ 与 $y$，使得 $ax+by=1$。

由此得出了若选择的卡牌的数通过数次相加或相减得出的绝对值为 $1$，那么这些数一定互质，此时可以考虑动态规划求解。

不过可以转移思想，因为这些数互质，即为 $0$ 号节点开始，每走一步求 $\gcd$(节点号,下一个节点)，同时记录代价，就成为了从 $0$ 通过不断 $\gcd$ 最后变为 $1$ 的最小代价。

由于：互质即为最大公因数为 $1$，$\gcd(0,x)=x$ 这两个定理，可以证明该算法的正确。选择优先队列优化 Dijkstra 求解。

不过还有个问题，即为需要记录是否已经买过一个卡片，开数组标记由于数据范围达到 $10^9$ 会超出内存限制，可以想到使用 `unordered_map` （比普通的 `map` 更快地访问各个元素，迭代效率较低）来标记。

另外，`__gcd` 是 OI 禁用的函数，仅供平时练习所用。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t[300],k[300];
unordered_map<int,int>mp;
priority_queue<pair<int,int>>q;
void add(int g,int k)
{
    if(mp.find(g)==mp.end()||mp[g]>k)
    {
        mp[g]=k;
        q.push({-k,g});
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&t[i]);
    for(int i=0;i<n;i++) scanf("%d",&k[i]);
    add(0,1);
    while(!q.empty())
    {
        int u=q.top().second;
        int w=-q.top().first;
        q.pop();
        if(mp[u]!=w)  continue;
        if(u==1) return printf("%d\n",w-1),0;
        for(int i=0;i<n;i++) add(__gcd(u,t[i]),k[i]+w);
    }
    puts("-1");
    return 0;
}
```
