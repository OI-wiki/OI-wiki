## 一些约定

字符串相关的定义请参考 [字符串基础](./basic.md) 。

字符串下标从 $1$ 开始。

" 后缀 $i$ " 代指以第 $i$ 个字符开头的后缀。

## 后缀数组是什么？

后缀数组（Suffix Array）主要是两个数组： $sa$ 和 $rk$ 。

其中， $sa[i]$ 表示将所有后缀排序后第 $i$ 小的后缀的编号。 $rk[i]$ 表示后缀 $i$ 的排名。

这两个数组满足性质： $sa[rk[i]]=rk[sa[i]]=i$ 。

后缀数组示例：

[![](./images/sa1.png)][2]

## 后缀数组怎么求？

### O(n^2logn) 做法

我相信这个做法大家还是能自己想到的，用 `string` + `sort` 就可以了。由于比较两个字符串是 $O(n)$ 的，所以排序是 $O(n^2\log n)$ 的。

### O(nlog^2n) 做法

这个做法要用到倍增的思想。

先对每个长度为 $1$ 的子串（即每个字符）进行排序。

假设我们已经知道了长度为 $w$ 的子串的排名 $rk_w[1..n]$ （即， $rk_w[i]$ 表示 $s[i..\min(i+w-1,n)]$ 在 $\{s[x..\min(x+w-1,n)]\ |\ x\in[1,n]\}$ 中的排名），那么，以 $rk_w[i]$ 为第一关键字， $rk_w[i+w]$ 为第二关键字（若 $i+w>n$ 则令 $rk_w[i+w]$ 为无穷小）进行排序，就可以求出 $rk_{2w}[1..n]$ 。

倍增排序示意图：

[![](./images/sa2.png)][2]

如果用 `sort` 进行排序，复杂度就是 $O(n\log^2n)$ 的。

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    const int N = 1000010;
    
    char s[N];
    int n, w, sa[N], rk[N << 1], oldrk[N << 1];
    // 为了防止访问 rk[i+w] 导致数组越界，开两倍数组。
    // 当然也可以在访问前判断是否越界，但直接开两倍数组方便一些。
    
    int main() {
      int i, p;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      for (i = 1; i <= n; ++i) rk[i] = s[i];
    
      for (w = 1; w < n; ++w) {
        for (i = 1; i <= n; ++i) sa[i] = i;
        sort(sa + 1, sa + n + 1, [](int x, int y) {
          return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
        });  // 这里用到了 lambda
        memcpy(oldrk, rk, sizeof(rk));
        // 由于计算 rk 的时候原来的 rk 会被覆盖，要先复制一份
        for (p = 0, i = 1; i <= n; ++i) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
            rk[sa[i]] = p;
          } else {
            rk[sa[i]] = ++p;
          }  // 若两个子串相同，它们对应的 rk 也需要相同，所以要去重
        }
      }
    
      for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### O(nlogn) 做法

在刚刚的 $O(n\log^2n)$ 做法中，单次排序是 $O(n\log n)$ 的，如果能 $O(n)$ 排序，就能 $O(n\log n)$ 计算后缀数组了。

前置知识： [计数排序](../basic/counting-sort.md) ， [基数排序](../basic/radix-sort.md) 。

由于计算后缀数组的过程中排序的关键字是排名，值域为 $O(n)$ ，并且是一个双关键字的排序，可以使用基数排序优化至 $O(n)$ 。

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    const int N = 1000010;
    
    char s[N];
    int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], cnt[N];
    
    int main() {
      int i, m, p, w;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      m = max(n, 300);
      for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    
      for (w = 1; w < n; w <<= 1) {
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) id[i] = sa[i];
        for (i = 1; i <= n; ++i) ++cnt[rk[id[i] + w]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[id[i] + w]]--] = id[i];
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) id[i] = sa[i];
        for (i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i) {
          if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
              oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
            rk[sa[i]] = p;
          } else {
            rk[sa[i]] = ++p;
          }
        }
      }
    
      for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### 一些常数优化

如果你把上面那份代码交到 LOJ 上：

![](./images/sa3.png)

这是因为，上面那份代码的常数的确很大。

#### 第二关键字无需计数排序

实际上，像这样就可以了：

```cpp
for (p = 0, i = n; i > n - w; --i) id[++p] = i;
for (i = 1; i <= n; ++i) {
  if (sa[i] > w) id[++p] = sa[i] - w;
}
```

意会一下，先把 $s[i+w..i+2w-1]$ 为空串（即第二关键字为无穷小）的位置放前面，再把剩下的按排好的顺序放进去。

#### 优化计数排序的值域

每次对 $rk$ 进行去重之后，我们都计算了一个 $p$ ，这个 $p$ 即是 $rk$ 的值域，将值域改成它即可。

#### 将 rk\[id[i]] 存下来，减少不连续内存访问

这个优化在数据范围较大时效果非常明显。

#### 用函数 cmp 来计算是否重复

同样是减少不连续内存访问，在数据范围较大时效果比较明显。

把 `oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]` 替换成 `cmp(sa[i], sa[i - 1], w)` ， `bool cmp(int x, int y, int w) { return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w]; }` 。

??? note "参考代码"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    const int N = 1000010;
    
    char s[N];
    int n, sa[N], rk[N], oldrk[N << 1], id[N], px[N], cnt[N];
    // px[i] = rk[id[i]]（用于排序的数组所以叫 px）
    
    bool cmp(int x, int y, int w) {
      return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    }
    
    int main() {
      int i, m = 300, p, w;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    
      for (w = 1; w < n; w <<= 1, m = p) {  // m=p 就是优化计数排序值域
        for (p = 0, i = n; i > n - w; --i) id[++p] = i;
        for (i = 1; i <= n; ++i)
          if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
          rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
      }
    
      for (i = 1; i <= n; ++i) printf("%d ", sa[i]);
    
      return 0;
    }
    ```

### O(n) 做法

在一般的题目中，常数较小的倍增求后缀数组是完全够用的，求后缀数组以外的部分也经常有 $O(n\log n)$ 的复杂度，倍增求解后缀数组不会成为瓶颈。

但如果遇到特殊题目、时限较紧的题目，或者是你想追求更短的用时，就需要学习 $O(n)$ 求后缀数组的方法。

#### SA-IS

可以参考 [诱导排序与 SA-IS 算法](https://riteme.site/blog/2016-6-19/sais.html) 。

#### DC3

可以参考[\[2009\]后缀数组——处理字符串的有力工具 by. 罗穗骞][2]。

## 后缀数组的应用

### 寻找最小的循环移动位置

将字符串 $S$ 复制一份变成 $SS$ 就转化成了后缀排序问题。

例题： [「JSOI2007」字符加密](https://www.luogu.org/problem/P4051) 。

### 在字符串中找子串

任务是在线地在主串 $T$ 中寻找模式串 $S$ 。在线的意思是，我们已经预先知道知道主串 $T$ ，但是当且仅当询问时才知道模式串 $S$ 。我们可以先构造出 $T$ 的后缀数组，然后查找子串 $S$ 。若子串 $S$ 在 $T$ 中出现，它必定是 $T$ 的一些后缀的前缀。因为我们已经将所有后缀排序了，我们可以通过在 $p$ 数组中二分 $S$ 来实现。比较子串 $S$ 和当前后缀的时间复杂度为 $O(|S|)$ ，因此找子串的时间复杂度为 $O(|S|\log |T|)$ 。注意，如果该子串在 $T$ 中出现了多次，每次出现都是在 $p$ 数组中相邻的。因此出现次数可以通过再次二分找到，输出每次出现的位置也很轻松。

### 从字符串首尾取字符最小化字典序

例题： [「USACO07DEC」Best Cow Line](https://www.luogu.org/problem/P2870) 。

题意：给你一个字符串，每次从首或尾取一个字符组成字符串，问所有能够组成的字符串中字典序最小的一个。

??? note "题解"
    暴力做法就是每次最坏 $O(n)$ 地判断当前应该取首还是尾（即比较取首得到的字符串与取尾得到的反串的大小），只需优化这一判断过程即可。

    由于需要在原串后缀与反串后缀构成的集合内比较大小，可以将反串拼接在原串后，并在中间加上一个没出现过的字符（如 `#`，代码中可以直接使用空字符），求后缀数组，即可 $O(1)$ 完成这一判断。

??? note "参考代码"
    ```cpp
    #include <cctype>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    const int N = 1000010;
    
    char s[N];
    int n, sa[N], id[N], oldrk[N << 1], rk[N << 1], px[N], cnt[N];
    
    bool cmp(int x, int y, int w) {
      return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    }
    
    int main() {
      int i, w, m = 200, p, l = 1, r, tot = 0;
    
      cin >> n;
      r = n;
    
      for (i = 1; i <= n; ++i)
        while (!isalpha(s[i] = getchar()))
          ;
      for (i = 1; i <= n; ++i) rk[i] = rk[2 * n + 2 - i] = s[i];
    
      n = 2 * n + 1;
    
      for (i = 1; i <= n; ++i) ++cnt[rk[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    
      for (w = 1; w < n; w <<= 1, m = p) {
        for (p = 0, i = n; i > n - w; --i) id[++p] = i;
        for (i = 1; i <= n; ++i)
          if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
          rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
      }
    
      while (l <= r) {
        printf("%c", rk[l] < rk[n + 1 - r] ? s[l++] : s[r--]);
        if ((++tot) % 80 == 0) puts("");
      }
    
      return 0;
    }
    ```

## height 数组

### LCP（最长公共前缀）

两个字符串 $S$ 和 $T$ 的 LCP 就是最大的 $x$ ( $x\le \min(|S|, |T|)$ ) 使得 $S_i=T_i\ (\forall\ 1\le i\le x)$ 。

下文中以 $lcp(i,j)$ 表示后缀 $i$ 和后缀 $j$ 的最长公共前缀（的长度）。

### height 数组的定义

 $height[i]=lcp(sa[i],sa[i-1])$ ，即第 $i$ 名的后缀与它前一名的后缀的最长公共前缀。

 $height[1]$ 可以视作 $0$ 。

### O(n) 求 height 数组需要的一个引理

 $height[rk[i]]\ge height[rk[i-1]]-1$ 

证明：

当 $height[rk[i-1]]\le1$ 时，上式显然成立（右边小于等于 $0$ ）。

当 $height[rk[i-1]]>1$ 时：

设后缀 $i-1$ 为 $aAD$ （ $A$ 是一个长度为 $height[rk[i-1]]-1$ 的字符串），那么后缀 $i$ 就是 $AD$ 。设后缀 $sa[rk[i-1]-1]$ 为 $aAB$ ，那么 $lcp(i-1,sa[rk[i-1]-1])=aA$ 。由于后缀 $sa[rk[i-1]-1]+1$ 是 $AB$ ，一定排在后缀 $i$ 的前面，所以后缀 $sa[rk[i]-1]$ 一定含有前缀 $A$ ，所以 $lcp(i,sa[rk[i]-1])$ 至少是 $height[rk[i-1]]-1$ 。

简单来说：

 $i-1$ ： $aAD$ 

 $i$ ： $AD$ 

 $sa[rk[i-1]-1]$ ： $aAB$ 

 $sa[rk[i-1]-1]+1$ ： $AB$ 

 $sa[rk[i]-1]$ ： $A[B/C]$ 

 $lcp(i,sa[rk[i]-1])$ ： $AX$ （ $X$ 可能为空）

### O(n) 求 height 数组的代码实现

利用上面这个引理暴力求即可：

```cpp
for (i = 1, k = 0; i <= n; ++i) {
  if (k) --k;
  while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
  ht[rk[i]] = k;  // height太长了缩写为ht
}
```

 $k$ 不会超过 $n$ ，最多减 $n$ 次，所以最多加 $2n$ 次，总复杂度就是 $O(n)$ 。

## height 数组的应用

### 两子串最长公共前缀

 $lcp(sa[i],sa[j])=\min\{height[i+1..j]\}$ 

感性理解：如果 $height$ 一直大于某个数，前这么多位就一直没变过；反之，由于后缀已经排好序了，不可能变了之后变回来。

严格证明可以参考[\[2004\]后缀数组 by. 徐智磊][1]。

有了这个定理，求两子串最长公共前缀就转化为了 [RMQ 问题](../topic/rmq.md) 。

### 比较一个字符串的两个子串的大小关系

假设需要比较的是 $A=S[a..b]$ 和 $B=S[c..d]$ 的大小关系。

若 $lcp(a, c)\ge\min(|A|, |B|)$ ， $A<B\iff |A|<|B|$ 。

否则， $A<B\iff rk[a]< rk[b]$ 。

### 不同子串的数目

子串就是后缀的前缀，所以可以枚举每个后缀，计算前缀总数，再减掉重复。

“前缀总数”其实就是子串个数，为 $n(n+1)/2$ 。

如果按后缀排序的顺序枚举后缀，每次新增的子串就是除了与上一个后缀的 LCP 剩下的前缀。这些前缀一定是新增的，否则会破坏 $lcp(sa[i],sa[j])=\min\{height[i+1..j]\}$ 的性质。只有这些前缀是新增的，因为 LCP 部分在枚举上一个前缀时计算过了。

所以答案为：

 $\frac{n(n+1)}{2}-\sum\limits_{i=2}^nheight[i]$ 

### 出现至少 k 次的子串的最大长度

例题： [「USACO06DEC」Milk Patterns](https://www.luogu.org/problemnew/show/P2852) 。

??? note "题解"
    出现至少 $k$ 次意味着后缀排序后有至少连续 $k$ 个后缀的 LCP 是这个子串。

    所以，求出每相邻 $k-1$ 个 $height$ 的最小值，再求这些最小值的最大值就是答案。

    可以使用单调队列 $O(n)$ 解决，但使用其它方式也足以 AC。

??? note "参考代码"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    #include <set>
    
    using namespace std;
    
    const int N = 40010;
    
    int n, k, a[N], sa[N], rk[N], oldrk[N], id[N], px[N], cnt[1000010], ht[N], ans;
    multiset<int> t;  // multiset 是最好写的实现方式
    
    bool cmp(int x, int y, int w) {
      return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    }
    
    int main() {
      int i, j, w, p, m = 1000000;
    
      scanf("%d%d", &n, &k);
      --k;
    
      for (i = 1; i <= n; ++i) scanf("%d", a + i);
      for (i = 1; i <= n; ++i) ++cnt[rk[i] = a[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    
      for (w = 1; w < n; w <<= 1, m = p) {
        for (p = 0, i = n; i > n - w; --i) id[++p] = i;
        for (i = 1; i <= n; ++i)
          if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
          rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
      }
    
      for (i = 1, j = 0; i <= n; ++i) {
        if (j) --j;
        while (a[i + j] == a[sa[rk[i] - 1] + j]) ++j;
        ht[rk[i]] = j;
      }
    
      for (i = 1; i <= n; ++i) {
        t.insert(ht[i]);
        if (i > k) t.erase(t.find(ht[i - k]));
        ans = max(ans, *t.begin());
      }
    
      cout << ans;
    
      return 0;
    }
    ```

### 是否有某字符串在文本串中至少不重叠地出现了两次

可以二分目标串的长度 $|s|$ ，将 $h$ 数组划分成若干个连续 LCP 大于等于 $|s|$ 的段，利用 RMQ 对每个段求其中出现的数中最大和最小的下标，若这两个下标的距离满足条件，则一定有长度为 $|s|$ 的字符串不重叠地出现了两次。

### 连续的若干个相同子串

我们可以枚举连续串的长度 $|s|$ ，按照 $|s|$ 对整个串进行分块，对相邻两块的块首进行 LCP 与 LCS 查询，具体可见[\[2009\]后缀数组——处理字符串的有力工具][2]。

### 结合并查集

某些题目求解时要求你将后缀数组划分成若干个连续 LCP 长度大于等于某一值的段，亦即将 $h$ 数组划分成若干个连续最小值大于等于某一值的段并统计每一段的答案。如果有多次询问，我们可以将询问离线。观察到当给定值单调递减的时候，满足条件的区间个数总是越来越少，而新区间都是两个或多个原区间相连所得，且新区间中不包含在原区间内的部分的 $h$ 值都为减少到的这个值。我们只需要维护一个并查集，每次合并相邻的两个区间，并维护统计信息即可。

经典题目： [「NOI2015」品酒大会](http://uoj.ac/problem/131) 

### 结合线段树

某些题目让你求满足条件的前若干个数，而这些数又在后缀排序中的一个区间内。这时我们可以用归并排序的性质来合并两个结点的信息，利用线段树维护和查询区间答案。

### 结合单调栈

例题： [「AHOI2013」差异](https://loj.ac/problem/2377) 

??? note "题解"
    被加数的前两项很好处理，为 $n(n-1)(n+1)/2$ （每个后缀都出现了 $n-1$ 次，后缀总长是 $n(n+1)/2$ ），关键是最后一项，即后缀的两两 LCP。

    我们知道 $lcp(i,j)=k$ 等价于 $\min\{height[i+1..j]\}=k$。所以，可以把 $lcp(i,j)$ 记作 $\min\{x|i+1\le x\le j, height[x]=lcp(i,j)\}$ 对答案的贡献。

    考虑每个位置对答案的贡献是哪些后缀的 LCP，其实就是从它开始向左若干个连续的 $height$ 大于它的后缀中选一个，再从向右若干个连续的 $height$ 不小于它的后缀中选一个。这个东西可以用 [单调栈](../ds/monotonous-stack.md) 计算。

    单调栈部分类似于 [Luogu P2659 美丽的序列](https://www.luogu.org/problem/P2659) 以及 [悬线法](../misc/largest-matrix.md)。

??? note "参考代码"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    
    using namespace std;
    
    const int N = 500010;
    
    char s[N];
    int n, sa[N], rk[N << 1], oldrk[N << 1], id[N], px[N], cnt[N], ht[N], sta[N],
        top, l[N];
    long long ans;
    
    bool cmp(int x, int y, int w) {
      return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
    }
    
    int main() {
      int i, k, w, p, m = 300;
    
      scanf("%s", s + 1);
      n = strlen(s + 1);
      ans = 1ll * n * (n - 1) * (n + 1) / 2;
      for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
      for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
    
      for (w = 1; w < n; w <<= 1, m = p) {
        for (p = 0, i = n; i > n - w; --i) id[++p] = i;
        for (i = 1; i <= n; ++i)
          if (sa[i] > w) id[++p] = sa[i] - w;
        memset(cnt, 0, sizeof(cnt));
        for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
        for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
        memcpy(oldrk, rk, sizeof(rk));
        for (p = 0, i = 1; i <= n; ++i)
          rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
      }
    
      for (i = 1, k = 0; i <= n; ++i) {
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        ht[rk[i]] = k;
      }
    
      for (i = 1; i <= n; ++i) {
        while (ht[sta[top]] > ht[i]) --top;
        l[i] = i - sta[top];
        sta[++top] = i;
      }
    
      sta[++top] = n + 1;
      ht[n + 1] = -1;
      for (i = n; i >= 1; --i) {
        while (ht[sta[top]] >= ht[i]) --top;
        ans -= 2ll * ht[i] * l[i] * (sta[top] - i);
        sta[++top] = i;
      }
    
      cout << ans;
    
      return 0;
    }
    ```

类似的题目： [「HAOI2016」找相同字符](https://loj.ac/problem/2064) 。

## 习题

-    [Uva 760 - DNA Sequencing](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=701) 
-    [Uva 1223 - Editor](http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=3664) 
-    [Codechef - Tandem](https://www.codechef.com/problems/TANDEM) 
-    [Codechef - Substrings and Repetitions](https://www.codechef.com/problems/ANUSAR) 
-    [Codechef - Entangled Strings](https://www.codechef.com/problems/TANGLED) 
-    [Codeforces - Martian Strings](http://codeforces.com/problemset/problem/149/E) 
-    [Codeforces - Little Elephant and Strings](http://codeforces.com/problemset/problem/204/E) 
-    [SPOJ - Ada and Terramorphing](http://www.spoj.com/problems/ADAPHOTO/) 
-    [SPOJ - Ada and Substring](http://www.spoj.com/problems/ADASTRNG/) 
-    [UVA - 1227 - The longest constant gene](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3668) 
-    [SPOJ - Longest Common Substring](http://www.spoj.com/problems/LCS/en/) 
-    [UVA 11512 - GATTACA](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2507) 
-    [LA 7502 - Suffixes and Palindromes](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=720&page=show_problem&problem=5524) 
-    [GYM - Por Costel and the Censorship Committee](http://codeforces.com/gym/100923/problem/D) 
-    [UVA 1254 - Top 10](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3695) 
-    [UVA 12191 - File Recover](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3343) 
-    [UVA 12206 - Stammering Aliens](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3358) 
-    [Codechef - Jarvis and LCP](https://www.codechef.com/problems/INSQ16F) 
-    [LA 3943 - Liking's Letter](https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1944) 
-    [UVA 11107 - Life Forms](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2048) 
-    [UVA 12974 - Exquisite Strings](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=862&page=show_problem&problem=4853) 
-    [UVA 10526 - Intellectual Property](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1467) 
-    [UVA 12338 - Anti-Rhyme Pairs](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=3760) 
-    [DevSkills Reconstructing Blue Print of Life](https://devskill.com/CodingProblems/ViewProblem/328) 
-    [UVA 12191 - File Recover](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3343) 
-    [SPOJ - Suffix Array](http://www.spoj.com/problems/SARRAY/) 
-    [LA 4513 - Stammering Aliens](https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2514) 
-    [SPOJ - LCS2](http://www.spoj.com/problems/LCS2/) 
-    [Codeforces - Fake News (hard)](http://codeforces.com/contest/802/problem/I) 
-    [SPOJ - Longest Commong Substring](http://www.spoj.com/problems/LONGCS/) 
-    [SPOJ - Lexicographical Substring Search](http://www.spoj.com/problems/SUBLEX/) 
-    [Codeforces - Forbidden Indices](http://codeforces.com/contest/873/problem/F) 
-    [Codeforces - Tricky and Clever Password](http://codeforces.com/contest/30/problem/E) 
-    [LA 6856 - Circle of digits](https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=4868) 

## 参考资料

本页面中（ [4070a9b](https://github.com/24OI/OI-wiki/pull/950/commits/4070a9b3db8576db16c74d3ec33806ad10476eef) 引入的部分）主要译自博文 [Суффиксный массив](http://e-maxx.ru/algo/suffix_array) 与其英文翻译版 [Suffix Array](https://cp-algorithms.com/string/suffix-array.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。

论文：

1.  [\[2004\]后缀数组 by. 徐智磊][1]

2.  [\[2009\]后缀数组——处理字符串的有力工具 by. 罗穗骞][2]

[1]: https://wenku.baidu.com/view/0dc03d2b1611cc7931b765ce0508763230127479.html "[2004] 后缀数组 by. 徐智磊"

[2]: https://wenku.baidu.com/view/5b886b1ea76e58fafab00374.html "[2009] 后缀数组——处理字符串的有力工具 by. 罗穗骞"
