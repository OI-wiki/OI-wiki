本页面将简要介绍 B \* 算法。

## 定义

B \* 算法是一种最佳优先搜索算法（Best First Search），它可以从给定的起点到任何目标节点找到代价最小的路径。B \* 算法比 A\* 算法的效率更高，所以通常被选作游戏中怪物寻路的算法。

## 寻路问题

1. 有 01 网格 (格子上只有数字 0 或 1)。
2. 寻找从网格 $(S.x，S.y)$ 处走到 $(E.x，E.y)$ 的**较短路**。
3. 每次只能走上下左右四个格子。
4. 不能到达数字为 1 的格子，不能走出网格。

很容易想到A\*算法可以找出最短路，但它求解一个**较短路**的效率可能还不够高。B\* 就是这么一个算法，它效率极高，而且可以给出一个"**相对不错**"的路径。

## 算法过程

B \*算法的基本思路是贪心思想+攀爬障碍。只需要朝着目标的位置径直走去，遇到障碍物再试图绕过障碍物继续搜索。

### 贪心策略

在未遇到障碍时，径直向目标走去是一种贪心策略。下面介绍几种常见的定义。

1. 当$∣S.x−E.x∣\geq∣S.y−E.y∣$ 时横着向 $E$ 走，反之则竖着向 $E$ 走。
2. 当 $S.x−E.x \ne 0$ 时横着向 $E$ 走，反之则竖着向 $E$ 走。
3. 用 Breshenham 算法，不在本文讨论范围以内。
4. 函数解析式法，推导比较复杂。

为了代码实现方便，本文使用第一种定义做演示。如下图所示，"."为空格子，"1"为经过的格子，"#"为障碍物。
$$
\begin{array}{cccccccccc}
S & 1 & 2 & 3 & 4 & 5 & 6 & . & . & . \\
. & . & . & . & . & . & 7 & 8 & . & . \\
. & . & . & . & . & . & . & 9 & 10 & . \\
. & . & . & . & . & . & . & . & 11 & 12 \\
. & . & . & . & . & . & . & . & . & E \\
\end{array}
$$

### 攀爬障碍

遇到障碍时，需要以前方障碍为界，分出左右两个分支，分别试图绕过障碍。
$$
\begin{array}{cccccccc}
. & . & . & . & . & . & . & . \\
. & . & . & . & . & . & . & . \\
. & . & . & 5 & \# & . & . & . \\
. & . & . & 4 & \# & . & . & . \\
S & 1 & 2 & 3 & \# & . & . & E \\
. & . & . & 4 & \# & . & . & . \\
. & . & . & 5 & \# & . & . & . \\
. & . & . & . & . & . & . & . \\
. & . & . & . & . & . & . & . \\
\end{array}
$$
在绕过障碍物后，就可以按照之前的贪心策略继续走向目标了。
$$
\begin{array}{cccccccc}
. & . & . & . & . & . & . & . \\
. & . & . & 6 & 7 & . & . & . \\
. & . & . & 5 & \# & . & . & . \\
. & . & . & 4 & \# & . & . & . \\
S & 1 & 2 & 3 & \# & . & . & E \\
. & . & . & 4 & \# & . & . & . \\
. & . & . & 5 & \# & . & . & . \\
. & . & . & 6 & 7 & . & . & . \\
. & . & . & . & . & . & . & . \\
\end{array}
$$
最终到达目标位置则寻路结束。根据寻路过程可以构造出完整路径。

算法可以总结为一下三点：

- 没有遇到障碍物，"径直"向目标走去。
- 遇到障碍物，以障碍物格子为界，分别沿着障碍物的边缘行走形成分支继续搜索。
- 到达终点，输出答案。

???+ note "代码实现"
~~~c++
#include<bits/stdc++.h>
using namespace std;
const bool showmap=0; //改为 1 可以逐步查看路径
const int SIZE=500;

const short direx[]={1,0,-1,0};
const short direy[]={0,1,0,-1};

struct Point
{
    int x,y,step;
    short WD,D;
    const bool operator == (Point ob)
    {return x==ob.x && y==ob.y;}
    void Scan () {scanf ("%d %d",&x,&y);}
    void Print() {printf("%d %d\n",x,y);}
    void Walk(short dire)
    {x+=direx[dire],y+=direy[dire];}
    Point Next(short dire)
    {return Point{x+direx[dire],y+direy[dire],step,WD};}
}start,end;

int n,m;
bool mapn[SIZE+5][SIZE+5],visit[SIZE+5][SIZE+5];
queue<Point> B_star;

void maprint(Point ob)//展示路径
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            if(mapn[i][j]) cout<<setw(3)<<"#";
            else if(Point{j,i}==ob) cout<<setw(3)<<ob.step;
            else if(Point{j,i}==end) cout<<setw(3)<<"E";
            else if(Point{j,i}==start) cout<<setw(3)<<"S";
            else if(visit[i][j]) cout<<setw(3)<<"1";
            else cout<<setw(3)<<".";
        printf("\n");
    }
}

bool NW(Point ob)//near the wall
{
    for(short i=0;i<4;i++)
    {
        Point rear=ob;
        rear.Walk(i);
        if(mapn[rear.y][rear.x]) return 1;
    }
    return 0;
}

bool Allowed(Point ob)
{return !mapn[ob.y][ob.x] && !visit[ob.y][ob.x];}

bool AtWall(Point ob)
{return mapn[ob.y][ob.x];}

short SD(Point ob)//straight dire
{
    if(abs(ob.x-end.x)>=abs(ob.y-end.y))
    {
        if(ob.x<end.x) return 0;
        if(ob.x>end.x) return 2;
    }
    if(ob.y<end.y) return 1;
    return 3;
}

int main()
{
    memset(mapn,1,sizeof mapn);
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>mapn[i][j];
    start.Scan(),start.step=0,start.WD=start.D=4;
    end.Scan();
    B_star.push(start);
    if(showmap) system("cls");
    while(!B_star.empty())
    {
        Point now=B_star.front();B_star.pop();
        if(now==end) {printf("B-star ans: %d\n",now.step);return 0;}
        if(!Allowed(now)) continue;
        visit[now.y][now.x]=1;
        if(showmap)
        {
            maprint(now);
            system("pause");
            system("cls");
        }
        /*
            0 右
            1 下
            2 左
            3 上 
        */
        if(abs(now.x-end.x)>=abs(now.y-end.y))
        {
            if(now.x<end.x && Allowed(now.Next(0)))//朝右走
            {
                Point rear=now.Next(0);
                rear.step++,rear.WD=rear.D=4;
                B_star.push(rear);
                continue;
            }
            if(now.x>end.x && Allowed(now.Next(2)))//朝左走
            {
                Point rear=now.Next(2);
                rear.step++,rear.WD=rear.D=4;
                B_star.push(rear);
                continue;
            }
        }
        else
        {
            if(now.y<end.y && Allowed(now.Next(1)))//朝下走 
            {
                Point rear=now.Next(1);
                rear.step++,rear.WD=rear.D=4;
                B_star.push(rear);
                continue;
            }
            if(now.y>end.y && Allowed(now.Next(3)))//朝上走 
            {
                Point rear=now.Next(3);
                rear.step++,rear.WD=rear.D=4;
                B_star.push(rear);
                continue;
            }
        }
        /*
            0 右
            1 下
            2 左
            3 上 
        */
        //不能径直走
         if(now.WD==4 && AtWall(now.Next(SD(now))))//第一次撞到墙2
         {
            if(SD(now)==0) //墙在右边
            {
                Point rear;
                rear=now.Next(1),rear.D=1,rear.step++,rear.WD=0,B_star.push(rear);
                rear=now.Next(3),rear.D=3,rear.step++,rear.WD=0,B_star.push(rear);
                continue;
            }
            if(SD(now)==1) //墙在下边
            {
                Point rear;
                rear=now.Next(0),rear.D=0,rear.step++,rear.WD=1,B_star.push(rear);
                rear=now.Next(2),rear.D=2,rear.step++,rear.WD=1,B_star.push(rear);
                continue;
            }
            if(SD(now)==2) //墙在左边
            {
                Point rear;
                rear=now.Next(1),rear.D=1,rear.step++,rear.WD=2,B_star.push(rear);
                rear=now.Next(3),rear.D=3,rear.step++,rear.WD=2,B_star.push(rear);
                continue;
            }
            if(SD(now)==3) //墙在上边
            {
                Point rear;
                rear=now.Next(0),rear.D=0,rear.step++,rear.WD=3,B_star.push(rear);
                rear=now.Next(2),rear.D=2,rear.step++,rear.WD=3,B_star.push(rear);
                continue;
            }
        }
        /*
            0 右
            1 下
            2 左
            3 上 
        */
        else//早就已经撞到墙了
        {
            if(now.WD==0)//墙在右边
            {
                if(!AtWall(now.Next(0)))//右边根本没墙
                {
                    if(now.D==1)//向下走
                    {
                        Point rear;
                        rear=now.Next(0),rear.D=0,rear.step++,rear.WD=3,B_star.push(rear);
                        continue;
                    }
                    if(now.D==3)
                    {
                        Point rear;
                        rear=now.Next(0),rear.D=0,rear.step++,rear.WD=1,B_star.push(rear);
                        continue;
                    }
                }
                //右边有墙，沿着 now.D 继续走
                if(!AtWall(now.Next(now.D)))//能继续走
                {
                    Point rear;
                    rear=now.Next(now.D),rear.D=now.D,rear.step++,rear.WD=0,B_star.push(rear);
                    continue;
                }
                //沿着这个方向不能再走了
                Point rear;
                rear=now.Next(2),rear.D=2,rear.step++,rear.WD=now.D,B_star.push(rear);
                continue;
            }
            if(now.WD==1)//墙在下边
            {
                if(!AtWall(now.Next(1)))//下边根本没墙
                {
                    if(now.D==0)//向右走
                    {
                        Point rear;
                        rear=now.Next(1),rear.D=1,rear.step++,rear.WD=2,B_star.push(rear);
                        continue;
                    }
                    if(now.D==2)//向左走 
                    {
                        Point rear;
                        rear=now.Next(1),rear.D=1,rear.step++,rear.WD=0,B_star.push(rear);
                        continue;
                    }
                }
                //下边有墙，沿着 now.D 继续走
                if(!AtWall(now.Next(now.D)))//能继续走
                {
                    Point rear;
                    rear=now.Next(now.D),rear.D=now.D,rear.step++,rear.WD=1,B_star.push(rear);
                    continue;
                }
                //沿着这个方向不能再走了
                Point rear;
                rear=now.Next(3),rear.D=3,rear.step++,rear.WD=now.D,B_star.push(rear);
                continue;
            }
            /*
                0 右
                1 下
                2 左
                3 上
            */
            if(now.WD==2)//墙在左边
            {
                if(!AtWall(now.Next(2)))//左边根本没墙
                {
                    if(now.D==1)//本来向下走
                    {
                        Point rear;
                        rear=now.Next(2),rear.D=2,rear.step++,rear.WD=3,B_star.push(rear);
                        continue;
                    }
                    if(now.D==3)
                    {
                        Point rear;
                        rear=now.Next(2),rear.D=2,rear.step++,rear.WD=1,B_star.push(rear);
                        continue;
                    }
                }
                //右边有墙，沿着 now.D 继续走
                if(!AtWall(now.Next(now.D)))//能继续走
                {
                    Point rear;
                    rear=now.Next(now.D),rear.D=now.D,rear.step++,rear.WD=2,B_star.push(rear);
                    continue;
                }
                //沿着这个方向不能再走了
                Point rear;
                rear=now.Next(0),rear.D=0,rear.step++,rear.WD=now.D,B_star.push(rear);
                continue;
            }
            if(now.WD==3)//墙在上边
            {
                if(!AtWall(now.Next(3)))//上边根本没墙
                {
                    if(now.D==0)//向右走
                    {
                        Point rear;
                        rear=now.Next(3),rear.D=3,rear.step++,rear.WD=2,B_star.push(rear);
                        continue;
                    }
                    if(now.D==2)//向左走 
                    {
                        Point rear;
                        rear=now.Next(3),rear.D=3,rear.step++,rear.WD=0,B_star.push(rear);
                        continue;
                    }
                }
                //下边有墙，沿着 now.D 继续走
                if(!AtWall(now.Next(now.D)))//能继续走
                {
                    Point rear;
                    rear=now.Next(now.D),rear.D=now.D,rear.step++,rear.WD=3,B_star.push(rear);
                    continue;
                }
                //沿着这个方向不能再走了
                Point rear;
                rear=now.Next(1),rear.D=1,rear.step++,rear.WD=now.D,B_star.push(rear);
                continue;
            }
            /*
                0 右
                1 下
                2 左
                3 上
            */
        }
    }
    printf("No way!\n");
    return 0;
}
/*
5 5
0 0 0 0 0
0 0 1 0 0
0 0 1 0 0
0 0 1 0 0
0 0 0 0 0
1 3
5 3

17 17
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
1 7
17 7

7 7
0 0 0 0 0 0 0
0 0 1 1 1 1 0
0 0 1 0 0 1 0
0 0 1 0 0 1 0
0 0 1 0 0 1 0
0 0 1 1 1 1 0
0 0 0 0 0 0 0
1 4
5 4

5 7
0 0 0 0 0 0 0
0 0 1 1 1 1 0
0 0 0 0 0 1 0
0 0 1 1 1 1 0
0 0 0 0 0 0 0
1 3
7 3

7 5
0 0 0 0 0
0 1 1 1 0
0 1 0 1 0
0 1 0 1 0
0 1 0 1 0
0 0 0 0 0
0 0 0 0 0
3 7
3 1

6 7
0 0 0 0 0 0 0
0 0 1 1 1 1 0
0 0 0 0 0 1 0
0 0 0 0 0 1 0
0 0 1 1 1 1 0
0 0 0 0 0 0 0
1 3
7 3

6 7
0 0 0 0 0 0 0
0 0 1 1 0 1 1
0 0 1 0 0 0 0
0 0 1 0 0 0 0
0 0 1 1 1 1 1
0 0 0 0 0 0 0
1 3
7 3
*/
~~~

## B* 算法的问题

B\*算法的贪心思想+攀爬障碍显然会造成一些错误，比如求不出解等。下面依次讨论B \*算法的几个问题。

### 解决"锐角"问题

根据寻路最优原理，进入死路后无法后退，所以无法找到可走的路径。如下图所示。但显然从S到E是有解的。
$$
\begin{array}{cccccccc}
. & . & . & . & . & . & . & . \\
. & . & \# & \# & \# & \# & . & . \\
S & 1 & 2 & 3 & 4 & \# & . & E \\
. & . & \# & \# & \# & \# & . & . \\
. & . & . & . & . & . & . & . \\
\end{array}
$$

解决方法是在前方还没有障碍物，但是左右的前方有障碍物时设置"重生点"，相当于多了一个选择。实现的时候就相当于在队列里插入一个新的方向。

代码中，设当前在 now 位置时要往 ND 方向走了，先判断一下左右的前方是否有障碍，如果有，加入向左向右的新分支就行了。


```c++
Point rear;
rear = now.Next(ND), rear.Walk(TL(ND));//左前
if(AtWall(rear)) rear = now.Next(TL(ND)), rear.step++, B_star.push(rear);
rear = now.Next(ND), rear.Walk(TR(ND));//右前
if(AtWall(rear)) rear = now.Next(TR(ND)), rear.step++, B_star.push(rear);
```

函数TL和TR的定义如下。

```c++
short TL(short dire){ //左转
    return (dire==0 ? 3 : dire-1);
}

short TR(short dire){ //右转
	return (dire==3 ? 0 : dire+1);
}
```

最终结果如下图所示。
$$
\begin{array}{cccccccc}
. & 3 & 4 & . & . & . & . & . \\
. & 2 & \# & \# & \# & \# & . & . \\
S & 1 & 2 & 3 & 4 & \# & . & E \\
. & 2 & \# & \# & \# & \# & . & . \\
. & 3 & . & . & . & . & . & . \\
\end{array}
$$

### "展平"优化

如下图所示，可以很明显地发现在凹形的障碍物内就可以抄近道走，但是由于B\*要贴着墙跑，所以没有意识到可以走捷径。
$$
\begin{array}{cccccccc}
. & . & . & . & . & . & . & . \\
. & . & \# & \# & \# & \# & . & . \\
S & 1 & 2 & 3 & 4 & \# & . & E \\
. & 8 & 7 & 6 & 5 & \# & . & . \\
. & 9 & \# & \# & \# & \# & . & . \\
. & 10 & 11 & 12 & 13 & . & . & . \\
\end{array}
$$
解决方法是增加特判，当完全可以从临近的格子直接过来的时候，更新步数，将相邻的回路变成比较直的路径。

```c++
for(short i = 0; i < 4; i ++){
    Point rear = now;
    rear.Walk(i);
    if(mem[rear.y][rear.x] != INT_MAX) { //是否可以从附近的格子过来
        now.step = min(now.step, mem[rear.y][rear.x] + 1);
    }
}
```

mem 记录搜索到每一个格子的最小步数，初始值赋为 *INT_MAX* （或足够大的数）。

由于 *INT_MAX + 1* 会越界 ，所以在周围格子是 *INT_MAX* 的情况下是万万不能赋过来的，需要特判一下。

下面是 mem 初始化代码：

```c++
for(int i = 0; i <= n + 1; i++){
    for(int j = 0; j <= m + 1; j++){
        mem[i][j] = INT_MAX;    
    }
}
```

最终结果如下图所示。
$$
\begin{array}{cccccccc}
. & . & . & . & . & . & . & . \\
. & . & \# & \# & \# & \# & . & . \\
S & 1 & 2 & 3 & 4 & \# & . & E \\
. & 2 & 7 & 6 & 5 & \# & . & . \\
. & 3 & \# & \# & \# & \# & . & . \\
. & . & . & . & . & . & . & . \\
\end{array}
$$


### 双向 B*

双向B \* 就是从起点和终点开始双向搜索，可以进一步提升搜索效率。

具体方法是另开一个队列，从终点 E开始搜索，如果过程中碰见了起点队列更新过的 mem，说明起点也可以到达这个位置，就可以将
$$
now.step+mem[now.y][now.x]−1
$$
作为答案输出。如果起点队列碰见了终点队列经过的位置也要这么做。

注意必需要有方法区分起点队列与终点队列更新过的 mem 还有 visit，可以另开数组进行标记，或者把每一个格子写成如下的结构体。

```c++
struct msg
{
    int val;
    bool pass; //谁经过了
};
```



## 参考资料

1. [B* - Wikipedia](https://en.wikipedia.org/wiki/B*)
2. [另类寻路算法——B*算法浅谈](https://www.luogu.com.cn/blog/JHN021/ling-lei-xun-lu-suan-fa-b-suan-fa-qian-tan)

