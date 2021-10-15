记忆化搜索是一种通过记录已经遍历过的状态的信息，从而避免对同一状态重复遍历的搜索实现方式。

因为记忆化搜索确保了每个状态只访问一次，它也是一种常见的动态规划实现方式。

## 引子

???+note "[[NOIP2005] 采药](https://www.luogu.com.cn/problem/P1048)"
    山洞里有 $M$ 株不同的草药，采每一株都需要一些时间 $t_i$，每一株也有它自身的价值 $v_i$。给你一段时间 $T$，在这段时间里，你可以采到一些草药。让采到的草药的总价值最大。
    
    $1 \leq T \leq 10^3$，$1 \leq t_i,v_i,M \leq 100$

### 朴素的 [DFS](../search/dfs.md) 做法

很容易实现这样一个朴素的搜索做法：在搜索时记录下当前准备选第几个物品，剩余的时间是多少，已经获得的价值是多少这三个参数，然后枚举当前物品是否被选，转移到相应的状态。

```cpp
// C++ Version
int n, t;
int tcost[103], mget[103];
int ans = 0;
void dfs(int pos, int tleft, int tans) {
  if (tleft < 0) return;
  if (pos == n + 1) {
    ans = max(ans, tans);
    return;
  }
  dfs(pos + 1, tleft, tans);
  dfs(pos + 1, tleft - tcost[pos], tans + mget[pos]);
}
int main() {
  cin >> t >> n;
  for (int i = 1; i <= n; i++) cin >> tcost[i] >> mget[i];
  dfs(1, t, 0);
  cout << ans << endl;
  return 0;
}
```

```python
# Python Version
tcost = [0] * 103
mget = [0] * 103
ans = 0
def dfs(pos, tleft, tans):
    global ans
    if tleft < 0:
        return
    if pos == n + 1:
        ans = max(ans, tans)
        return
    dfs(pos + 1, tleft, tans)
    dfs(pos + 1, tleft - tcost[pos], tans + mget[pos])
t, n = map(lambda x:int(x), input().split())
for i in range(1, n + 1):
    tcost[i], mget[i] = map(lambda x:int(x), input().split())
dfs(1, t, 0)
print(ans)
```

这种做法的时间复杂度是指数级别的，并不能通过本题。

### 优化

上面的做法为什么效率低下呢？因为同一个状态会被访问多次。

如果我们每查询完一个状态后将该状态的信息存储下来，再次需要访问这个状态就可以直接使用之前计算得到的信息，从而避免重复计算。这充分利用了动态规划中很多问题具有大量重叠子问题的特点，属于用空间换时间的「记忆化」思想。

具体到本题上，我们用一个数组 `mem` 来记录每个 `dfs(pos,tleft)` 的返回值。刚开始把 `mem` 中每个值都设成 `-1`（代表没访问过）。每次需要访问一个状态时，如果相应状态的值在 `mem` 中为 `-1`，则递归访问该状态。否则我们直接使用 `mem` 中已经存储过的值即可。

通过这样的处理，我们确保了每个状态只会被访问一次，因此该算法的的时间复杂度为 $O(TM)$。

```cpp
// C++ Version
int n, t;
int tcost[103], mget[103];
int mem[103][1003];
int dfs(int pos, int tleft) {
  if (mem[pos][tleft] != -1)
    return mem[pos][tleft];  // 已经访问过的状态，直接返回之前记录的值
  if (pos == n + 1) return mem[pos][tleft] = 0;
  int dfs1, dfs2 = -INF;
  dfs1 = dfs(pos + 1, tleft);
  if (tleft >= tcost[pos]) dfs2 = dfs(pos + 1, tleft - tcost[pos]) + mget[pos];
  return mem[pos][tleft] = max(dfs1, dfs2);  // 最后将当前状态的值存下来
}
int main() {
  memset(mem, -1, sizeof(mem));
  cin >> t >> n;
  for (int i = 1; i <= n; i++) cin >> tcost[i] >> mget[i];
  cout << dfs(1, t) << endl;
  return 0;
}
```

```python
# Python Version
tcost = [0] * 103
mget = [0] * 103
mem = [[-1 for i in range(1003)] for j in range(103)]
def dfs(pos, tleft):
    if mem[pos][tleft] != -1:
        return mem[pos][tleft]
    if pos == n + 1:
        mem[pos][tleft] = 0
        return mem[pos][tleft]
    dfs1 = dfs2 = -INF
    dfs1 = dfs(pos + 1, tleft)
    if tleft >= tcost[pos]:
        dfs2 = dfs(pos + 1, tleft - tcost[pos]) + mget[pos]
    mem[pos][tleft] = max(dfs1, dfs2)
    return mem[pos][tleft]
t, n = map(lambda x:int(x), input().split())
for i in range(1, n + 1):
    tcost[i], mget[i] = map(lambda x:int(x), input().split())
print(dfs(1, t))
```

## 与递推的联系与区别

在求解动态规划的问题时，记忆化搜索和递推，都确保了同一状态至多只被访问一次。而它们实现这一点的方式则略有不同：递推通过设置明确的访问顺序来避免重复访问，记忆化搜索虽然没有明确规定访问顺序，但通过给已经访问过的状态打标记的方式，也达到了同样的目的。

与递推相比，记忆化搜索因为不用明确规定访问顺序，在实现难度上有时低于递推，且能比较方便地处理边界情况，这是记忆化搜索的一大优势。但与此同时，记忆化搜索难以使用滚动数组等优化，且由于存在递归，运行效率会低于递推。因此应该视题目选择更适合的实现方式。
