本页面主要分享一下在竞赛中的小技巧。

## 利用局部性

局部性是指程序倾向于引用邻近于其他最近引用过的数据项的数据项，或者最近引用过的数据项本身。局部性分为时间局部性和空间局部性。

- 消除循环中的低效率，比如遍历字符串的时候：
  ```cpp
  for (int i = 0; i < strlen(s); ++i)
    ;
  // 不如
  int len = strlen(s);
  for (int i = 0; i < len; ++i)
    ;
  ```
- 循环展开。通过适当的循环展开可以减少整个计算中关键路径上的操作数量
  ```cpp
  for (int i = 0; i < n; ++i) {
    res = res OP a[i];
  }
  // 不如
  int i;
  for (i = 0; i < n; i += 2) {
    res = res OP a[i];
    res = res OP a[i + 1];
  }
  for (; i < n; ++i) {
    res = res OP a[i];
  }
  ```
- 重新结合变换，增加了可以并行执行的运算数量
  ```cpp
  for (int i = 0; i < n; ++i) res = (res OP a[i])OP a[i + 1];
  // 不如
  for (int i = 0; i < n; ++i) res = res OP(a[i] OP a[i + 1]);
  ```

## 善用namespace

使用namespace能使程序可读性更好，便于调试。

```cpp
//NOI 2018 屠龙勇士 40分部分分代码
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
long long n,m,a[100005],p[100005],aw[100005],atk[100005];
namespace one_game
{
 //其实namespace里也可以声明变量
 void solve()
 {
  for(int y=0;;y++)
   if((a[1]+p[1]*y)%atk[1]==0)
   {
    cout<<(a[1]+p[1]*y)/atk[1]<<endl;
    return;
   }
 }
}
namespace p_1
{
 void solve()
 {
  if(atk[1]==1)//solve 1-2
  {
   sort(a+1,a+n+1);
   cout<<a[n]<<endl;
   return;
  }
  else if(m==1)//solve 3-4
  {
   long long k=atk[1],kt=ceil(a[1]*1.0/k);
   for(int i=2;i<=n;i++)
    k=aw[i-1],kt=max(kt,(long long)ceil(a[i]*1.0/k));
   cout<<k<<endl;
  }
 }
}
int main()
{
 int T;
 cin>>T;
 while(T--)
 {
  memset(a,0,sizeof(a));
  memset(p,0,sizeof(p));
  memset(aw,0,sizeof(aw));
  memset(atk,0,sizeof(atk));
  cin>>n>>m;
  for(int i=1;i<=n;i++)
   cin>>a[i];
  for(int i=1;i<=n;i++)
   cin>>p[i];
  for(int i=1;i<=n;i++)
   cin>>aw[i];
  for(int i=1;i<=m;i++)
   cin>>atk[i];
  if(n==1&&m==1)one_game::solve();//solve 8-13
  else if(p[1]==1)p_1::solve();//solve 1-4 or 14-15
  else cout<<-1<<endl;
 }
 return 0;
}
```

## 善用标识符进行调试

我们在本地测试的时候，往往要加入一些调试语句。要提交到OJ的时候，就要把他们全部删除，有些麻烦。

我们可以通过定义标识符的方式来进行本地调试。

大致的程序框架是这样的：

```cpp
#define DEBUG
#ifdef DEBUG
 //do something
#endif
// or
#ifndef DEBUG
 //do something
#endif
```

`#ifdef`会检查程序中是否有通过`#define`定义的对应标识符，如果有定义，就会执行下面的内容，`#ifndef`恰恰相反，会在没有定义相应标识符的情况下执行后面的语句。

我们提交程序的时候，只需要将`#define DEBUG`一行注释掉即可。

当然，我们也可以不在程序中定义标识符，而是通过`-DDEBUG`的编译选项在编译的时候定义`DEBUG`标识符。这样就可以在提交的时候不用修改程序了。

不少OJ都开启了`-DONLINE_JUDGE`这一编译选项，善用这一特性可以节约不少时间。

## 对拍

有的时候我们写了一份代码，但是不知道它是不是正确的。这时候就可以用对拍的方法来进行检验或调试。

什么是对拍呢？具体而言，就是通过对比两个程序的输出来检验程序的正确性。你可以将自己程序的输出与其他程序（打的暴力或者其他dalao的标程）的输出进行对比，从而判断自己的程序是否正确。

当然，对拍过程要多次进行，我们需要通过批处理的方法来实现对拍的自动化。

具体而言，我们需要一个数据生成器，两个要进行对拍的程序。

每次运行一次数据生成器，将生成的数据写入输入文件，通过重定向的方法使两个程序读入数据，并将输出写入指定文件，利用Windows下的`fc`命令比对文件（Linux下为`diff`命令），从而检验程序的正确性。

如果发现程序出错，可以直接利用刚刚生成的数据进行调试啦。

对拍程序的大致框架如下：

```cpp
#include <stdio.h>
#include <stdlib.h>
int main()
{
 //For Windows
 //对拍时不开文件输入输出
 //当然，这段程序也可以改写成批处理的形式
 while(1)
 {
  system("gen > test.in");//数据生成器将生成数据写入输入文件
  system("test1.exe < test.in > a.out");//获取程序1输出
  system("test2.exe < test.in > b.out");//获取程序2输出
  if(system("fc a.out b.out"))
  {
   //该行语句比对输入输出
   //fc返回0时表示输出一致，否则表示有不同处
   system("pause");//方便查看不同处
   return 0;
   //该输入数据已经存放在test.in文件中，可以直接利用进行调试
  }
 }
}
```

## <span id="mempool">内存池</span>

当我们需要动态分配内存的时候，频繁使用 new/malloc 会占用大量的时间和空间，甚至生成大量的内存碎片从而降低程序的性能，可能会使原本正确的程序 TLE/MLE。

这时候我们就需要使用到「内存池」这种技巧: 在真正使用内存之前，先申请分配一定大小的内存作为备用，当需要动态分配时则直接从备用内存中分配一块即可。

当然在大多数 OI 题当中，我们可以预先算出需要使用到的最大内存并一次性申请分配。

如申请动态分配 $32$ 位有符号整数数组的代码:

```cpp
inline int* newarr(int sz){
	static int pool[maxn],*allocp=pool;
	return allocp+=sz,allocp-sz;
}

```

线段树动态开点的代码:

```cpp
inline Node* newnode(){
	static Node pool[maxn<<1],*allocp=pool-1;
	return++allocp;
}

```

注：本页面 [部分内容](https://github.com/24OI/OI-wiki/commit/e9fa69af9d7f1583cb5ddad837c04bb1b03d7939) 最初发表于[洛谷日报 #86](https://studyingfather.blog.luogu.org/some-coding-tips-for-oiers)，由原作者整理并搬运至此，略有删改。
