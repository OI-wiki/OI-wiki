## 概述

回文树 (EER Tree，Palindromic Tree，也被称为回文自动机）是一种可以存储一个串中所有回文子串的高效数据结构，最初是由 Mikhail Rubinchik 和 Arseny M. Shur 在 2015 年发表。它的灵感来源于后缀树等字符串后缀数据结构，使用回文树可以简单高效地解决一系列涉及回文串的问题。

## 结构

回文树大概长这样

![](./images/pam1.png)

和其它自动机类似的，回文树也是由转移边和后缀链接 (fail 指针）组成，每个节点都可以代表一个回文子串。

因为回文串长度分为奇数和偶数，我们可以像 manacher 那样加入一个不在字符集中的字符（如 '#'）作为分隔符来将所有回文串的长度都变为奇数，但是这样过于麻烦了。有没有更好的办法呢？

答案自然是有。更好的办法就是建两棵树，一棵树中的节点对应的回文子串长度均为奇数，另一棵树中的节点对应的回文子串长度均为偶数。

和其它的自动机一样，一个节点的 fail 指针指向的是这个节点所代表的回文串的最长回文后缀所对应的节点，但是转移边并非代表在原节点代表的回文串后加一个字符，而是表示在原节点代表的回文串前后各加一个相同的字符（不难理解，因为要保证存的是回文串）。

我们还需要在每个节点上维护此节点对应回文子串的长度 len，这个信息保证了我们可以轻松地构造出回文树。

## 建造

回文树有两个初始状态，分别代表长度为 $-1,0$ 的回文串。我们可以称它们为奇根，偶根。它们不表示任何实际的字符串，仅作为初始状态存在，这与其他自动机的根节点是异曲同工的。

偶根的 fail 指针指向奇根，而我们并不关心奇根的 fail 指针，因为奇根不可能失配（奇根转移出的下一个状态长度为 $1$ ，即单个字符。一定是回文子串）

类似后缀自动机，我们增量构造回文树。

考虑构造完前 $p-1$ 个字符的回文树后，向自动机中添加在原串里位置为 $p$ 的字符。

我们从以上一个字符结尾的最长回文子串对应的节点开始，不断沿着 fail 指针走，直到找到一个节点满足 $s_{p}=s_{p-len-1}$ ，即满足此节点所对应回文子串的上一个字符与待添加字符相同。

这里贴出论文中的那张图

![](./images/pam2.png)

我们通过跳 fail 指针找到 A 所对应的节点，然后两边添加 `X` 就到了现在的回文串了（即 `XAX` ），很显然，这个节点就是以 $p$ 结尾的最长回文子串对应的树上节点。（同时，这个时候长度 $-1$ 节点优势出来了，如果没有 `X` 能匹配条件就是同一个位置的 $s_p=s_p$ ，就自然得到了代表字符 `X` 的节点。）此时要判断一下：没有这个节点，就需要新建。

然后我们还需要求出新建的节点的 fail 指针。具体方法与上面的过程类似，不断跳转 fail 指针，从 `A` 出发，即可找到 `XAX` 的最长回文后缀 `XBX` ，将对应节点设为 fail 指针所指的对象即可。

显然，这个节点是不需新建的， `A` 的前 $len_B$ 位和后 $len_B$ 位相同，都是 `B` ，前 $len_B$ 位的两端根据回文串对应关系，都是 `X` ，后面被钦定了是 `X` ，于是这个节点 `XBX` 肯定已经被包含了。

如果 fail 没匹配到，那么将它连向长度为 $0$ 的那个节点，显然这是可行的（因为这是所有节点的后缀）。

## 线性状态数证明

定理：对于一个字符串 $s$ ，它的本质不同回文子串个数最多只有 $|s|$ 个。

证明：考虑使用数学归纳法。

-   当 $|s| =1$ 时， $s$ 只有一个字符，同时也只有一个子串，并且这个子串是回文的，因此结论成立。

-   当 $|s| >1$ 时，设 $t=sc$ ，其中 $t$ 表示 $s$ 最后增加一个字符 $c$ 后形成的字符串，假设结论对 $s$ 串成立。考虑以最后一个字符 $c$ 结尾的回文子串，假设它们的左端点由小到大排序为 $l_1,l_2,\dots,l_k$ 。由于 $t[l_1..|t|]$ 是回文串，因此对于所有位置 $l_1 \le p \le |t|$ ，有 $t[p..|t|]=t[l_1..l_1+|t|-p]$ 。所以，对于 $1 < i \le k$ ， $t[l_i..|t|]$ 已经在 $t[1..|t|-1]$ 中出现过。因此，每次增加一个字符，本质不同的回文子串个数最多增加 $1$ 个。

由数学归纳法，可知该定理成立。

因此回文树状态数是 $O(|s|)$ 的。对于每一个状态，它实际只代表一个本质不同的回文子串，即转移到该节点的状态唯一，因此总转移数也是 $O(|s|)$ 的。

## 正确性证明

以上图为例，增加当前字符 `X` ，由线性状态数的证明，我们只需要找到包含最后一个字符 `X` 的最长回文后缀，也就是 `XAX` 。继续寻找 `XAX` 的最长回文后缀 `XBX` ，建立后缀链接。 `XBX` 对应状态已经在回文树中出现，包含最后一个字符的回文后缀就是 `XAX` ， `XBX` 本身及其对应状态在 fail 树上的所有祖先。

对于 $s$ 回文树的构造，令 $n=|s|$ ，显然除了跳 fail 指针的其他操作都是 $O(n)$ 的。

加入字符时，在上一次的基础上，每次跳 fail 后对应节点在 fail 树的深度 $-1$ ，而连接 fail 后，仅为深度 + 1（但 fail 为 $0$ 时（即到 $-1$ 才符合），深度相当于在 $-1$ 的基础上 $+2$ ）。

因为只加入 $n$ 个字符，所以只会加 $n$ 次深度，最多也只会跳 $2n$ 次 fail。

因此，构造 $s$ 的回文树的时间复杂度是 $O(|s|)$ 。

## 应用

### 本质不同回文子串个数

由线性状态数的证明，容易知道一个串的本质不同回文子串个数等于回文树的状态数（排除奇根和偶根两个状态）。

### 回文子串出现次数

建出回文树，使用类似后缀自动机统计出现次数的方法。

由于回文树的构造过程中，节点本身就是按照拓扑序插入，因此只需要逆序枚举所有状态，将当前状态的出现次数加到其 fail 指针对应状态的出现次数上即可。

例题： [「APIO2014」回文串](https://www.luogu.org/problem/P3649) 

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 300000 + 5;

namespace pam {
int sz, tot, last;
int cnt[maxn], ch[maxn][26], len[maxn], fail[maxn];
char s[maxn];
int node(int l) {
  sz++;
  memset(ch[sz], 0, sizeof(ch[sz]));
  len[sz] = l;
  fail[sz] = cnt[sz] = 0;
  return sz;
}
void clear() {
  sz = -1;
  last = 0;
  s[tot = 0] = '$';
  node(0);
  node(-1);
  fail[0] = 1;
}
int getfail(int x) {
  while (s[tot - len[x] - 1] != s[tot]) x = fail[x];
  return x;
}
void insert(char c) {
  s[++tot] = c;
  int now = getfail(last);
  if (!ch[now][c - 'a']) {
    int x = node(len[now] + 2);
    fail[x] = ch[getfail(fail[now])][c - 'a'];
    ch[now][c - 'a'] = x;
  }
  last = ch[now][c - 'a'];
  cnt[last]++;
}
ll solve() {
  ll ans = 0;
  for (int i = sz; i >= 0; i--) {
    cnt[fail[i]] += cnt[i];
  }
  for (int i = 1; i <= sz; i++) {
    ans = max(ans, 1ll * len[i] * cnt[i]);
  }
  return ans;
}
}  // namespace pam

char s[maxn];

int main() {
  pam::clear();
  scanf("%s", s + 1);
  for (int i = 1; s[i]; i++) {
    pam::insert(s[i]);
  }
  printf("%lld\n", pam::solve());
  return 0;
}
```

## 例题

-    [最长双回文串](https://www.luogu.org/problem/P4555) 

-    [拉拉队排练](https://www.luogu.org/problem/P1659) 

-    [「SHOI2011」双倍回文](https://www.luogu.org/problem/P4287) 

-    [HDU 5421 Victor and String](http://acm.hdu.edu.cn/showproblem.php?pid=5421) 

-    [CodeChef Palindromeness](https://www.codechef.com/LTIME23/problems/PALPROB) 

## 相关资料

-    [EERTREE: An Efficient Data Structure for Processing Palindromes in Strings](https://arxiv.org/pdf/1506.04862)

-    [Palindromic tree](http://adilet.org/blog/palindromic-tree/) 

-   2017 年 IOI 国家候选队论文集 回文树及其应用 翁文涛
