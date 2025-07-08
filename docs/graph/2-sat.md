> SAT 是适定性（Satisfiability）问题的简称。一般形式为 k - 适定性问题，简称 k-SAT。而当 $k>2$ 时该问题为 NP 完全的。所以我们只研究 $k=2$ 的情况。

## 定义

2-SAT，简单的说就是给出 $n$ 个布尔方程，每个方程和两个变量相关，如 $a \vee b$，表示变量 $a, b$ 至少满足一个。然后判断是否存在可行方案，显然可能有多种选择方案，一般题中只需要求出一种即可。另外，$\neg a$ 表示 $a$ 取反。

## 例题引入

???+ note "[洛谷的「P4782」](https://www.luogu.com.cn/problem/P4782)"
    有 $n$ 个布尔变量 $x_1\sim x_n$，另有 $m$ 个需要满足的条件，每个条件的形式都是「$x_i$ 为 `true`/`false` 或 $x_j$ 为 `true`/`false`」。比如「$x_1$ 为真或 $x_3$ 为假」、「$x_7$ 为假或 $x_2$ 为假」。
    
    2-SAT 问题的目标是给每个变量赋值使得所有条件得到满足。

转化题意为：装饰一个房间，有 $m$ 种装饰品。有 $n$ 个人，每人提出两点要求（要不要用某种装饰品），当其中至少有一条被满足时（当然允许两条都满足），这个人会感到满意。问你是否可以让所有人都感到满意，进一步的，还可以让你输出让所有人都感到满意的方案。

## 重点：建图

使用布尔方程表示上述问题。设 $a$ 表示要用第 A 种装饰品（$\neg a$ 就表示不用第 A 种装饰品）。如果有个人提出的要求分别是 $a$ 和 $b$，即 $(a \vee b)$（变量 $a, b$ 至少满足一个）。对这些变量关系建有向图，**则把 $a$ 成立或不成立用图中的点表示，$\neg a\to b$ $\neg b\to a$，表示 $a$ 不成立则 $b$ 一定成立；同理，$b$ 不成立则 $a$ 一定成立。建图之后，我们就可以使用缩点算法来求解 2-SAT 问题了**。

|         原式         |                建图               |
| :----------------: | :-----------------------------: |
|   $\neg a \vee b$  | $a \to b$ 和 $\neg b \to \neg a$ |
|     $a \vee b$     | $\neg a \to b$ 和 $\neg b \to a$ |
| $\neg a\vee\neg b$ |   $a \to -b$ 和 $b \to \neg a$   |

**许多 2-SAT 问题都需要找出如 $a$ 不成立，则 $b$ 成立的关系。**

## 求解

思考如果两点在同一强连通分量里有什么含义。根据前文边的逻辑意义可知：若两点在同一强连通分量内，则这两点代表的条件 **要么都满足，要么都不满足**。

建图周我们跑一遍 [Tarjan 找 SCC](./scc.md)，判断对于任意布尔变量 $a$，表示 $a$ 成立的点和表示 $a$ 不成立的点是否在同一个 SCC 中（同一条件不可能既满足又不满足，或既不满足，又并非不满足），若有则输出无解，否则有解。

输出方案时可以通过变量在图中的拓扑序确定该变量的取值。如果变量 $x$ 的拓扑序在 $\neg x$ 之后，那么取 $x$ 值为真。应用到 Tarjan 算法的缩点，即 $x$ 所在 SCC 编号在 $\neg x$ 之前时，取 $x$ 为真。因为 Tarjan 算法求强连通分量时使用了栈，如果跑完 Tarjan 缩点之后呈现出的拓扑序更大，在 Tarjan 会更晚被遍历到，就会更早地被弹出栈而缩点，分量编号会更小，所以 Tarjan 求得的 SCC 编号 **相当于反拓扑序**。

算法会把整张图遍历一遍，并且在结算答案时复杂度为 $O(n)$，认为 $n$ 和 $m$ 同阶，复杂度为 $O(n)$。

??? note "代码实现"
    ```cpp
    ```

include<cstdio>#include<algorithm>#include<stack>using namespace std;
const int N=2e6+2;
int n,m,dfn\[N],low\[N],t,tot,head\[N],a\[N];
bool vis\[N];
stack<int>s;
struct node{int to,Next;}e\[N];

void adde(int u,int v){
e\[++tot].to=v;
e\[tot].Next=head\[u];
head\[u]=tot;
}

void Tarjan(int u){
dfn\[u]=low\[u]=++t;
s.push(u);
vis\[u]=1;
for(int i=head\[u];i;i=e\[i].Next){
int v=e\[i].to;
if(!dfn\[v]){
Tarjan(v);
low\[u]=min(low\[u],low\[v]);
}
else if(vis\[v])
low\[u]=min(low\[u],dfn\[v]);
}
if(dfn\[u]==low\[u]){
int cur;
\++tot;
do{
cur=s.top();
s.pop();
vis\[cur]=0;
a\[cur]=tot;
}while(cur!=u);
}
}

int main(){scanf("%d%d",&n,&m);
for(int i=1,I,J,A,B;i<=m;i++){
scanf("%d%d%d%d",&I,&A,&J,&B);
adde(A?I+n:I,B?J:J+n);
adde(B?J+n:J,A?I:I+n);
}
tot=0;
for(int i=1;i<=(n<<1);i++) if(!dfn\[i]) Tarjan(i);
for(int i=1;i<=n;i++){
if(a\[i]==a\[i+n]){
printf("IMPOSSIBLE");
return 0;
}
}
puts("POSSIBLE");
for(int i=1;i<=n;i++){
putchar(a\[i]\<a\[i+n]?'1':'0');
putchar(' ');
}
return 0;
}
\`\`\`

## 例题

### **HDU3062 [Party](https://acm.hdu.edu.cn/showproblem.php?pid=3062)**

> 题面：有 n 对夫妻被邀请参加一个聚会，因为场地的问题，每对夫妻中只有 $1$ 人可以列席。在 $2n$ 个人中，某些人之间有着很大的矛盾（当然夫妻之间是没有矛盾的），有矛盾的 $2$ 个人是不会同时出现在聚会上的。有没有可能会有 $n$ 个人同时列席？

这是一道多校题，裸的 2-SAT 判断是否有方案，按照我们上面的分析，如果 $a1$ 中的丈夫和 $a2$ 中的妻子不合，我们就把 $a1$ 中的丈夫和 $a2$ 中的丈夫连边，把 $a2$ 中的妻子和 $a1$ 中的妻子连边，然后缩点染色判断即可。

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_1.cpp"
    ```

### **2018-2019 ACM-ICPC Asia Seoul Regional K [TV Show Game](http://codeforces.com/gym/101987)**

> 题面：有 $k(k>3)$ 盏灯，每盏灯是红色或者蓝色，但是初始的时候不知道灯的颜色。有 $n$ 个人，每个人选择 3 盏灯并猜灯的颜色。一个人猜对两盏灯或以上的颜色就可以获得奖品。判断是否存在一个灯的着色方案使得每个人都能领奖，若有则输出一种灯的着色方案。

这道题在判断是否有方案的基础上，在有方案时还要输出一个可行解。

根据 [伍昱 -《由对称性解 2-sat 问题》](https://wenku.baidu.com/view/31fd7200bed5b9f3f90f1ce2.html)，我们可以得出：如果要输出 2-SAT 问题的一个可行解，只需要在 tarjan 缩点后所得的 DAG 上自底向上地进行选择和删除。

具体实现的时候，可以通过构造 DAG 的反图后在反图上进行拓扑排序实现；也可以根据 tarjan 缩点后，所属连通块编号越小，节点越靠近叶子节点这一性质，优先对所属连通块编号小的节点进行选择。

下面给出第二种实现方法的代码。

??? note "参考代码"
    ```cpp
    --8<-- "docs/graph/code/2-sat/2-sat_2.cpp"
    ```

## 练习题

[洛谷 P5782 和平委员会](https://www.luogu.com.cn/problem/P5782)

POJ3683 [牧师忙碌日](http://poj.org/problem?id=3683)
