## 树哈希

我们有时需要判断一些树是否同构。这时，选择恰当的哈希方式将树哈希成数字是一个优秀的方案。

与字符串哈希不同的是，树哈希有很多种哈希方式，下面将选出几种较为常用的介绍。

### Method I

#### Formula

$$
f_{now}=size_{now} \times \sum f_{son_{now,i}}\times bas^{i-1}
$$

##### Notes

其中 $f_x$ 为以节点 $x$ 为根的子树对应的哈希值，特殊地，我们令叶子节点的哈希值为 $1$

$size_{x}$ 表示以节点 $x$ 为根的子树大小。

$son_{x,i}$ 表示 $x$ 所有子节点按 $f$ 排序后排名为 $i$ 的儿子。

$bas$ 为选定的一个合适的质数（对字符串 hash 有了解的人一定不陌生）

上述哈希过程中，可以适当取模避免溢出或加快运行速度。

### Method II

#### Formula

$$
f_{now}=\bigoplus f_{son_{now,i}}\times bas+size_{son_{now,i}}
$$

##### Notes

其中 $f_x$ 为以节点 $x$ 为根的子树对应的哈希值，特殊地，我们令叶子节点的哈希值为 $1$

$size_{x}$ 表示以节点 $x$ 为根的子树大小。

$son_{x,i}$ 表示 $x$ 所有子节点之一（不用排序）。

$bas$ 为选定的一个合适的质数

$\large\bigoplus$表示异或和

### Example

#### Problem

[Luogu P5403](<https://www.luogu.org/problemnew/show/P5043>)

#### Solution

我们用上述方式任选其一进行哈希，注意到我们求得的是子树的hash值，也就是说只有当根一样时同构的两棵子树hash值才相同。由于数据范围较小，我们可以暴力求出以每个点为根时的哈希值，排序后比较。

如果数据范围较大，我们可以通过找重心的方式来优化复杂度。（一棵树的重心最多只有两个，分别比较即可）

#### Code 

##### Method I

```

```



##### Method II

```
#include<cstdio>
#include<algorithm>
#include<vector>
#include<tr1/unordered_map>

class Solution{
private :
    typedef unsigned long long ull;
    typedef std::vector<int>::iterator it;
    static const ull seed = 2333233233;
    static const int maxn = 107;

    int n, m, size[maxn], lastRoot, root, lastMax, Max, ans;
    ull hash[maxn], res;
    std::vector<int> e[maxn];
    std::tr1::unordered_map<ull, int> id;

    ull getHash(int now, int fa) {
        size[now] = 1;
        hash[now] = 1;
        for (register it i = e[now].begin(); i != e[now].end(); ++i) {
            int v = *i;
            if (v == fa) {
                continue;
            }
            hash[now] ^= getHash(v, now) * seed + size[v];
            size[now] += size[v];
        }
        return hash[now];
    }

    void getRoot(int now, int fa) {
        int max = 0;
        size[now] = 1;
        for (register it i = e[now].begin(); i != e[now].end(); ++i) {
            int v = *i;
            if (v == fa) {
                continue;
            }
            getRoot(v, now);
            size[now] += size[v];
            max = std::max(max, size[v]);
        }
        max = std::max(max, n - size[now]);
        if (max < Max && now != lastRoot) {
            root = now;
            Max = max;
        }
    }
    
public :
    Solution() {
        get();
        solve();
    }

    void get() {
        scanf("%d", &m);
        for (register int i = 1; i <= m; i++) {
            scanf("%d", &n);
            for (register int j = 1; j <= n; j++) {
                std::vector<int>().swap(e[j]);
            }
            for (register int j = 1, fa; j <= n; j++) {
                scanf("%d", &fa);
                if (!fa) {
                    root = j;
                } else {
                    e[fa].push_back(j);
                    e[j].push_back(fa);
                }
            }
            lastRoot = root = 0;
            Max = n;
            getRoot(1, 0);
            lastRoot = root, lastMax = Max;
            res = getHash(root, 0);
            if (!id.count(res)) {
                id[res] = i;
            }
            ans = id[res];

            Max = n;
            getRoot(1, 0);
            if (lastMax == Max) {
                res = getHash(root, 0);
                if (!id.count(res)) {
                    id[res] = i;
                }
                ans = std::min(ans, id[res]);
            }
            printf("%d\n", ans);
        }
    }

    void solve() {
        
    }
};
Solution sol;

int main() {}

```



### At Last

事实上，树哈希是很灵活的。可以有各种各样奇怪的姿势来进行 hash，只需注意充分性与必要性，选手完全可以设计出与上述方式不同的 hash 方式。
