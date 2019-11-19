author: sshwy

分治可以用来优化DP。

## 前提条件

对于形如

$$
dp(i, j) =\min_{k \leq j} \{ dp(i - 1, k) + C(k, j) \}
$$

的转移方程，其中$C(k,j)$是代价函数，可以$O(1)$计算。设$opt(i,j)$表示$dp(i,j)$的最优决策，即

$$
opt(i,j)=\arg\min_{k \leq j} \{ dp(i - 1, k) + C(k, j) \}
$$

如果$\forall i,j, opt(i,j)\le opt(i,j+1)$，即同一层满足决策单调性，那么我们可以考虑分治优化DP。

具体地，固定$i$，考虑分治地计算$opt(i,j),1\le j\le n$。我们首先计算$opt\left(i,\left\lfloor\dfrac{n}{2}\right\rfloor\right)$，然后把区间分成两部分，两边递归下去做，求出所有的$opt(i,j)$。由于递归的每一层的规模都是$O(n)$，一共$O(\log_2n)$层，因此转移一层的总复杂度$O(n\log_2n)$（注意，复杂度与$opt(i,j)$是否平衡无关）。

## 参考实现

函数`compute`计算了区间$[l,r]$的最优决策值。其中`dp_before`表示$dp(i-1)$，而`dp_cur`表示计算出来的最优决策$opt(i,j)$。使用`compute(0,n-1,0,n-1)`作为调用入口。

```cpp
int n;
long long C(int i, int j);
vector<long long> dp_before(n), dp_cur(n);

// compute dp_cur[l], ... dp_cur[r] (inclusive)
void compute(int l, int r, int optl, int optr)
{
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    pair<long long, int> best = {INF, -1};

    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {dp_before[k] + C(k, mid), k});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
```

## 注意事项

做此类题目的最大难点在于找到决策单调性。当然，许多分治优化DP的题目也可以使用斜率优化解决。

## 习题

- [Codeforces - Ciel and Gondolas](https://codeforces.com/contest/321/problem/E) (Be careful with I/O!)
- [SPOJ - LARMY](https://www.spoj.com/problems/LARMY/)
- [Codechef - CHEFAOR](https://www.codechef.com/problems/CHEFAOR)
- [Hackerrank - Guardians of the Lunatics](https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14)
- [ACM ICPC World Finals 2017 - Money](https://open.kattis.com/problems/money)

## 参考文献
[Quora Answer by Michael Levin](https://www.quora.com/What-is-divide-and-conquer-optimization-in-dynamic-programming)

[Video Tutorial by "Sothe" the Algorithm Wolf](https://www.youtube.com/watch?v=wLXEWuDWnzI)

> 本页面部分内容译自博文[Divide and Conquer DP](https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html)，版权协议为 CC-BY-SA 4.0。
