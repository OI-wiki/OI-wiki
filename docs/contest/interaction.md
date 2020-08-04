author: countercurrent-time, StudyingFather

上个世纪的 IOI 就已涉及交互题。虽然交互题近年来没有在省选以下的比赛中出现，不过 2019 年里 NOI 系列比赛中连续出现《P5208[WC2019]I 君的商店》、《P5473[NOI2019]I 君的探险》两道交互题，这可能代表着交互题重新回到 NOI 系列比赛中。

交互题没有很高的前置算法要求，一般也没有严格的时间限制，程序的优秀程度往往仅取决于交互次数限制。所以学习交互题时，建议按照难度循序渐进。要是有意锻炼算法思维而不只是单纯地学习算法，那么完成交互题是很不错的方法。虽然交互题对选手已掌握算法的要求通常较低，但仍建议掌握一定提高和省选算法后再尝试做交互题，因为此时自己的算法思维水平和知识面已经达到了一定水平。基础的交互题介绍可以参考 OI wiki 的 [题型介绍 - 交互题](./problems.md#interaction) 。

交互题的特殊错误：

- 选手每一次输出后都需要刷新缓冲区，否则会引起 Idleness limit exceeded 错误。另外，如果题目含多组数据并且程序可以在未读入所有数据前就知道答案，也仍然要读入所有数据，否则同样会因为读入混乱引起 ILE（可以一次提出多次询问，一次接收所有询问的回答）。同时尽量不要使用快读。
- 如果程序查询次数过多，则在 Codeforces 上会给出 Wrong Answer 的评测结果（不过评测系统会说明 Wrong Answer 的原因），而 UVA 会给出 Protocol Limit Exceeded (PLE) 的评测结果。
- 如果程序交互格式错误，UVa 会给出 Protocol Violation (PV) 的评测结果。

由于交互题输入输出较为繁琐，所以建议分别封装输入和输出函数。

比赛时如果出题人给出了 grader 头文件（用于 grader 交互题的调试）或者 checker 程序（用于 stdio 交互题的调试），则交互题的调试比较简单，因为交互题的对拍会比普通题目的对拍困难很多。没有 `testlib.h` 的情况下。交互细节较多的题目的 stdio 交互库会一般有 3k 代码量，再加上 3k 长度的对拍器，至少需要一小时实现。但是，无论是否有调试程序，调试交互题的代码都往往需要选手模拟与程序的交互过程，因此交互题需要选手能设计出高质量的程序，尽量保证一遍做对，同时拥有较强的静态查错能力。

例题：

-  [CF679A Bear and Prime 100](https://www.luogu.com.cn/problem/CF679A) 
-  [CF843B Interactive LowerBound](https://www.luogu.com.cn/problem/CF843B) 
-  [UOJ206\[APIO2016\]Gap](http://uoj.ac/problem/206) 
-  [CF750F New Year and Finding Roots](https://www.luogu.com.cn/problem/CF750F) 
-  [UVA12731 太空站之谜 Mysterious Space Station](https://www.luogu.com.cn/problem/UVA12731) 

## CF679A Bear and Prime 100

每个质数都有且只有两个因数，所以直接枚举要猜的数的因数。由于限制最多询问 20 次，并且对于较大的数（如 92）尝试分解质因数时发现需要最多枚举到 $\lfloor\frac{n}{2}\rfloor$ 的质数。所以我们先筛出 50 以内的质数，每次把所有这些数都询问一遍。

由于本题对拍比较容易，可以直接把值域内的数都尝试一遍。我们会发现程序无法有效处理质数的平方。所以我们要把 2,3,5,7 的平方 4,9,25,49 都放进去，总共 19 个数字，符合题意。

??? 参考代码
    ```cpp
    #include <cstdio>
    const int prime[] = {2,  3,  4,  5,  7,  9,  11, 13, 17, 19,
                         23, 25, 29, 31, 37, 41, 43, 47, 49};
    int cnt = 0;
    char res[5];
    int main() {
      for (int i : prime) {
        printf("%d\n", i);
        fflush(stdout);
        scanf("%s", res);
        if (res[0] == 'y' && ++cnt == 2) return printf("composite"), 0;
      }
      printf("prime");
      return 0;
    }
    ```

## CF843B Interactive LowerBound

链表最多有 $5 \times 10 ^ 4$ 个元素，但我们只能询问 $1999$ 次，并且只能获取元素的后一个元素，所以普通的遍历整个链表的方法不可用。直接设法逼近目标元素的位置只有一种方法：随机撒点。

对于 $n < 2000$ 的情况直接枚举， $n \ge 2000$ 时，我们直接撒 1000 个点，这时这些点之间的期望距离很小，我们可以直接从小于 $x$ 的最大值开始向后遍历，可以证明在到达下一个点之前我们就已得到答案。遍历的过程中一旦找到大于等于 $x$ 的元素，就可以直接推出。

虽然整体思路简单，但实际情况下，如果没有学习过模拟退火等非完美随机算法，思考起来很可能会困难一些。

同时由于 Codeforces 具有 hack 机制，很多人会刻意卡掉没有初始化随机种子的代码，所以在 `random_shuffle()` 函数前需要 `srand((size_t)new char)` 。

??? 参考代码
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstdlib>
    const int N = 50005;
    int n, start, x;
    int a[N];
    int main() {
      scanf("%d%d%d", &n, &start, &x);
      if (n < 2000) {
        int ans = 2e9;
        for (int i = 1; i <= n; i++) {
          printf("? %d\n", i), fflush(stdout);
          int val, next;
          scanf("%d%d", &val, &next);
          if (val >= x) ans = std::min(ans, val);
        }
        if (ans == 2e9) ans = -1;
        printf("! %d", ans), fflush(stdout);
      } else {
        srand((size_t) new char);
        int p = start, ans = 0;
        for (int i = 1; i <= n; i++) a[i] = i;
        std::random_shuffle(a + 1, a + n + 1);
        for (int i = 1; i <= 1000; i++) {
          printf("? %d\n", a[i]), fflush(stdout);
          int val, next;
          scanf("%d%d", &val, &next);
          if (val < x && val > ans) p = a[i], ans = val;
        }
        while (p != -1 && ans < x) {
          printf("? %d\n", p), fflush(stdout);
          int val, next;
          scanf("%d%d", &val, &next);
          ans = val;
          p = next;
        }
        if (ans < x) ans = -1;
        printf("! %d", ans), fflush(stdout);
      }
      return 0;
    }
    ```

## UOJ206[APIO2016]Gap

分两个子任务讨论：

1.  查询次数限制。

    我们考虑第一次查询。因为我们一开始不知道任何数，所以我们需要询问范围 $[1, 10 ^ {18}]$ ，获得最大最小值。

    由于查询次数限制刚好为 $\frac{N + 1}{2}$ ，所以考虑怎么每一次都能获取之前没有获取过的值，这样能大概在次数范围内获取序列内的所有数。方法也很简单：每次查询 $[s, t]$ 后，设获得的值为 $mn, mx$ ，则下一次查询 $[mn + 1, mx - 1]$ 。

2.  询问区间大小限制。

    由于题目要求询问区间内的数的数量之和不能超过 $3N$ ，所以考虑最小化询问区间。上面的方法不再可用，因为其询问区间内的数数量之和规模为 $O(N ^ 2)$ 。我们可以考虑二分值域，但这种方法并不可靠，最坏可能会被卡到 $O(N ^ 2)$ 。所以我们需要更有效的划分值域的方法，避免查询区间内的点重复查询，浪费机会。

    考虑到答案不会小于 $\lfloor\frac{a_n - a_1}{N - 1}\rfloor$ ，所以我们可以考虑按这个值划分值域，设 $i$ 初始为 0， $ans$ 初始为上述值，每次询问 $[i, i + ans]$ 并且更新 $ans$ ，之后再以 $ans$ 为步长让 $i$ 自增。

    不过这种方法也不能很好地适用于子任务 1，因为最坏可能很多询问的值域内一个数都没有。

??? 参考代码
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include "gap.h"
    
    long long findGap(int T, int N) {
      static long long a[100005] = {}, ans = 0;
      long long s = 0, t = 1e18, s1, t1;
      if (T == 1) {
        int l = 1, r = N;
        while (l <= r) {
          MinMax(s, t, &s1, &t1);
          a[l++] = s1, a[r--] = t1;
          s = s1 + 1, t = t1 - 1;
        }
        for (int i = 2; i <= N; i++) ans = std::max(ans, a[i] - a[i - 1]);
      } else if (T == 2) {
        MinMax(s, t, &s1, &t1);
        ans = (t1 - s1) / (N - 1);
        long long l = s1 + 1, r = t1, last = s1;
        for (long long i = l; i <= r;) {
          MinMax(i, i + ans, &s1, &t1);
          i += ans + 1;
          if (s1 != -1) ans = std::max(ans, s1 - last), last = t1;
        }
      }
      return ans;
    }
    ```

## CF750F New Year and Finding Roots

看到 $h \le 7$ ，询问次数 $\le 16$ 的严格要求，我们需要非常严格地最大化利用访问获得的信息。

 $h \le 4$ 时可以直接暴力枚举。然而 $h > 4$ 时需要很高效的遍历算法。

随机撒点不是好方法，因为随机撒点无法确定自己是否足够接近根节点了，并且单纯随机撒点，至少有一次碰到根节点的概率为 $1 - (\frac{2 ^ h - 2}{2 ^ h - 1})$ ，即使排除重复撒点的情况后，碰到根节点的概率仍然非常小。

由于 $1 \le k \le 3$ ，并且我们并不知道哪一边更接近根节点，所以我们考虑最坏的情况，即如果 $k = 3$ 时，前两次我们的遍历方向都是远离根节点的，第三次遍历方向是接近根节点的。所以我们必须往三个方向都遍历。

考虑 bfs 和 dfs 两种遍历方法。由于 bfs 搜索树可能很大，所以我们优先考虑 dfs。当然，如果我们知道当前的深度，并且当前深度小到深度范围内的搜索树规模小于等于剩余次数，我们就可以直接 bfs。

知道当前节点的深度，以及当前遍历的方向会获得很大优势。然而知道当前在往根节点还是在往叶子节点遍历是非常困难的事情。如果使用 dfs，只有当遍历到根节点（ $k = 2$ ）或者叶子节点（ $k = 1$ ）时才知道当前方向。所以我们需要尽可能知道当前节点深度，并且不能采用类似迭代加深搜索的方法，遍历中途停下来。

考虑随机一个初始节点，从初始节点出发可能碰到上面的最坏情况。

如果 $k = 1$ ，我们就可以直接知道当前节点的深度。

如果 $k = 2$ ，那当前节点即根节点。

如果 $k = 3$ ，我们直接考虑往三个方向 dfs。考虑到其中两个方向是直接往叶子节点的方向，遍历路径长度相同；另一个方向是往根节点的方向，不过可能中途不小心往叶子节点的方向走了，遍历路径长度会较大。此时我们就可以计算出当前节点的深度。

当 $k = 1$ 或者 $k = 3$ 时，我们需要考虑较长的遍历路径。我们可以知道路径上深度最小的点（必定比初始节点深度小）。如果我们为访问过的节点打标记，不再遍历，此时从该节点开始就只有一条遍历路径。虽然这条路径可能还是会走向叶子节点，但是这条路径上同样必然存在深度比起点小的节点，我们就可以从这个节点开始继续重复上面的步骤。

当然，我们考虑 $h = 7$ 的最坏情况时（每次只往根节点走一步，就直接往叶子节点走），会发现如果只 dfs，最坏需要 $\frac{(1 + 7) \times 7}{2} = 28$ 次询问。不过我们已经知道初始节点的深度，所以我们可以算出所有已遍历节点的深度，并且根据我们开始时对 bfs 的讨论，判断是否可以从深度最小的点直接 bfs。

这时，我们可以算出最坏需要 17 次。所以我们考虑从搜索树上去掉一个节点（根据 dfs 只能盲目遍历的性质，我们考虑 bfs）：即当进行深度为 $k$ 的 bfs 时，搜索树节点最坏有 $2 ^ k - 1$ 个，可能需要 $2 ^ k - 1$ 次询问才能确定哪个节点的邻居恰有 2 个。不过我们如果已经对其中 $2 ^ k - 2$ 个节点询问后，可以知道最后一个节点肯定是根节点。

此时最坏情况下的最优解为： $h = 7$ 时，从叶子节点 dfs，每次都是只往根节点走一步，就直接往叶子节点走，询问 10 次后，当前已知最小深度的节点深度为 4，由于已知其父亲，直接从其父亲开始 bfs（搜索树深度为 3，节点数为 $2 ^ 3 - 1 = 7$ ）。在 bfs 时询问了 $2 ^ 3 - 2 = 6$ 次后，确定 bfs 搜索树上最后一个节点为根节点。

此时我们的算法可以刚好卡到最坏 16 次。

??? 参考代码
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <queue>
    #include <vector>
    using namespace std;
    const int N = 256 + 5;
    int T, h, chance;
    bool ok;
    vector<int> to[N], path;
    bool read(int x) {
      if (to[x].empty()) {
        printf("? %d\n", x), fflush(stdout);
        int k, t;
        scanf("%d", &k);
        if (k == 0) exit(0);
        for (int i = 0; i < k; i++) {
          scanf("%d", &t);
          to[x].push_back(t);
        }
        if (k == 2) {
          printf("! %d\n", x), fflush(stdout);
          return ok = true;
        }
        chance--;
      }
      return false;
    }
    bool dfs(int x) {
      if (to[x].empty()) path.push_back(x);
      if (read(x)) return true;
      for (int i : to[x])
        if (to[i].empty()) return dfs(i);
      return false;
    }
    void bfs(int s, int k) {
      queue<int> q;
      for (int i : to[s])
        if (to[i].empty()) q.push(i);
      for (int i = 1; i < k; i++) {
        int x = q.front();
        q.pop();
        if (read(x)) return;
        for (int j : to[x])
          if (to[j].empty()) q.push(j);
      }
      for (int i = 1; i < k; i++) {
        int x = q.front();
        q.pop();
        if (read(x)) return;
      }
      printf("! %d\n", q.front()), fflush(stdout);
    }
    int main() {
      for (scanf("%d", &T); T--;) {
        ok = false;
        for (int i = 0; i < N; i++) to[i].clear();
        chance = 16;
        scanf("%d", &h);
        if (h == 0) exit(0);
        vector<int> long_path;
        if (read(1)) continue;
        int root, dep;
        if (to[1].size() == 1)
          root = 1, dep = h;
        else {
          for (int i : to[1]) {
            path.clear();
            if (dfs(i)) break;
            if (path.size() > long_path.size()) swap(path, long_path);
          }
          if (ok) continue;
          dep = h - (path.size() + long_path.size()) / 2;
          root = long_path.at((long_path.size() - (h - dep)) - 1);
        }
        while ((1 << (dep - 1)) - 2 > chance) {
          path.clear();
          if (dfs(root)) break;
          dep = h - (h - dep + path.size()) / 2;
          root = path.at((path.size() - (h - dep)) - 1);
        }
        if (ok == false) bfs(root, 1 << (dep - 2));
      }
      return 0;
    }
    ```

## UVA12731 太空站之谜 Mysterious Space Station

由于唯一的反馈是移动时是否撞墙，所以我们应该考虑在机器人不走丢的情况下，尽量接近墙边走路，这样有几个好处：

- 靠近墙边走路时，很容易知道自己会不会撞墙，获取到尽量多的信息。
- 墙边都是不会出现传送门的格子，可以避免机器人走丢。

所以，我们如果已知机器人可能在墙边的某个位置，要确定机器人是不是真的在这个位置，就可以通过 [“单手扶墙法”](https://en.wikipedia.org/wiki/Maze_solving_algorithm) 确定自己是不是真的在这个位置。根据拓扑学原理，在两边都是墙的迷宫中，如果从入口进入，并且总是用一只手扶着同一边墙，就可以保证找到出口。由于本题中的墙是闭合的，所以只需要沿着墙边的道路走，就可以保证可以回到原点而不会撞墙。另外，由于墙边的道路是地图上的最大闭合回路，所以实际代码中并不需要特意撞墙以保证机器人在墙边，可以使用标记在地图中标明墙边道路。而且一旦撞了墙，就需要赶快沿着原路返回，可以在避免机器人走丢的同时减少步数。

由上，可以推断出确定机器人是否在特定格子的试错法：将机器人在不走到未知格子或已知传送门的情况下走到墙边的道路上，然后绕着墙边道路走一圈。这个过程中如果没有撞墙，就可以确定机器人确实是在特定格子。

我们可以采用上面的方法，一开始标出图中所有未知格子，然后从上到下，从左到右依次判断每个未知格子是否是传送门。可以先走到未知格子上方，然后向下、向左走。再用上面的方法判断机器人是不是在未知格子的左侧。如果不是，说明机器人不在应该在的位置，即未知格子是传送门。

找出未知格子后就需要判断 2k 个未知格子的配对关系，实际方法也很简单：只需要暴力配对就可以了。由于 $k \le 5$ ，所以最多只需要 $9 + 7 + 5 + 3$ 次试错法。作为对比，判断图中全部未知格子的情况最多需要 $121 - 40$ 次试错法。

由于目前下面这一份代码只能通过 UOJ 的镜像题： [#247.【Rujia Liu's Present 7】Mysterious Space Station](http://uoj.ac/problem/247) ，而无法通过 UVa 原题。修改了 UOJ 上刘汝佳的标程后还是无法通过，并且暂时无法联系到刘汝佳。所以下面的代码以 UOJ 为准。

不过刘汝佳的标程质量还是比下面这份代码质量高很多的，可以在 UOJ 上查看到 [通过了 UOJ 镜像题的标程](http://uoj.ac/submission/105789) 。同一份数据下，标程使用的移动次数非常少。

??? 参考代码
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    #include <queue>
    #include <stack>
    
    #define Wall 0
    #define Unknown 1
    #define Space 2
    #define Gate 3
    #define Path 4
    
    const int N = 20;
    const int dir[8][2] = {{0, 1},  {1, 0}, {0, -1}, {-1, 0},
                           {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
    const char dirs[5] = "ESWN";
    int n, m, k;
    int a[N][N], id[N][N];
    
    struct point {
      int x, y;
      point(int x = 0, int y = 0) : x(x), y(y) {}
      bool operator==(const point& tmp) const { return x == tmp.x && y == tmp.y; }
      bool operator!=(const point& tmp) const { return !(*this == tmp); }
      point side(int d) const { return point(x + dir[d][0], y + dir[d][1]); }
      int check(int d) { return a[x + dir[d][0]][y + dir[d][1]]; }
      int id() { return ::id[x][y]; }
    } start;
    
    std::vector<std::pair<point, int>> path;
    std::pair<point, point> ans[N];
    std::pair<point, bool> vis[N];
    
    bool walk(int d) {
      printf("MoveRobot %c\n", dirs[d]);
      fflush(stdout);
      int ret;
      scanf("%d", &ret);
      return ret;
    }
    bool walk(int d, std::stack<int>& st) {
      if (walk(d)) {
        st.push(d);
        return true;
      }
      return false;
    }
    bool read() {
      if (scanf("%d%d%d", &n, &m, &k) != 3) return false;
      if (n == 0) return false;
      memset(a, 0, sizeof(a));
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
          char c;
          std::cin >> c;
          if (c == 'S') start = point(i, j);
          if (c == '*')
            a[i][j] = Wall;
          else
            a[i][j] = Unknown;
        }
      return true;
    }
    void answer() {
      for (int i = 0; i < k; i++)
        printf("Answer %d %d\n", ans[i].first.id(), ans[i].second.id());
      fflush(stdout);
    }
    // 单手扶墙法，因为靠墙的 Path 是极大闭合环，所以只需要在沿着 Path
    // 走的过程中没有碰到障碍就可以了
    void wall_follower_init(point x, int last, int wallside, point s) {
      if (x == s && !path.empty()) return;
      if (x.check(wallside) == Path) {
        path.push_back(std::make_pair(x, wallside));
        wall_follower_init(x.side(wallside), wallside, last ^ 2, s);
      } else if (x.check(last) == Wall) {
        for (int i = 0; i < 4; i++)
          if (i != (last ^ 2) && x.check(i) != Wall) {
            path.push_back(std::make_pair(x, i));
            wall_follower_init(x.side(i), i, last, s);
            return;
          }
      } else {
        path.push_back(std::make_pair(x, last));
        wall_follower_init(x.side(last), last, wallside, s);
      }
    }
    void init() {
      int cnt = 1;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
          if (a[i][j] == Unknown) {
            id[i][j] = cnt++;
            for (int k = 0; k < 8; k++)
              if (point(i, j).check(k) == Wall) {
                a[i][j] = Path;
                break;
              }
          } else
            id[i][j] = 0;
        }
      path.clear();
      int wallside = 0, last = 0;
      for (int i = 0; i < 4; i++)
        if (start.check(i) == Wall) {
          wallside = i;
          break;
        }
      for (int i = 0; i < 4; i++)
        if (start.check(i) == Path && i != (wallside ^ 2)) {
          last = i;
          break;
        }
      wall_follower_init(start, last, wallside, start);
    }
    void undo(std::stack<int>& st) {
      while (!st.empty()) walk(st.top() ^ 2), st.pop();
    }
    bool wall_follower(point x) {
      std::stack<int> st;
      bool ok = true;
      int i = 0;
      while (i < path.size() && path[i].first != x) i++;
      for (int j = i; ok && j < path.size(); j++) {
        if (walk(path[j].second))
          st.push(path[j].second);
        else
          ok = false;
      }
      for (int j = 0; ok && j < i; j++) {
        if (walk(path[j].second))
          st.push(path[j].second);
        else
          ok = false;
      }
      if (ok == false) undo(st);
      return ok;
    }
    // 确定自己当前在
    // x，使用“摸着石头过河”的方法，只需要沿着可以避开障碍、未知格子和传送门的方向走到
    // Path 就行。 在找传送门和配对传送门时使用
    void bfs(point s, point t, std::vector<int>& v) {
      static int map[N][N] = {};
      memset(map, -1, sizeof(map));
      std::queue<point> q;
      map[s.x][s.y] = 4;
      q.push(s);
      while (!q.empty()) {
        point x = q.front();
        q.pop();
        if (x == t) break;
        for (int i = 0; i < 4; i++) {
          point y = x.side(i);
          if ((x.check(i) == Path || x.check(i) == Space) && map[y.x][y.y] == -1) {
            map[y.x][y.y] = i;
            q.push(y);
          }
        }
      }
      for (point x = t; x != s; x = x.side(map[x.x][x.y] ^ 2)) {
        v.push_back(map[x.x][x.y]);
      }
      std::reverse(v.begin(), v.end());
    }
    bool move(point s, point t, std::stack<int>& st) {  // 在靠近传送门时使用
      static std::vector<int> v;
      v.clear();
      bfs(s, t, v);
      for (int i : v)
        if (walk(i, st) == false) return false;
      return true;
    }
    // 尽可能快地向墙边移动
    bool make_sure(point x, int last) {
      if (a[x.x][x.y] == Path) return wall_follower(x);
      for (int i = 0; i < 4; i++)
        if ((x.check(i) == Path || x.check(i) == Space) && i != (last ^ 2)) {
          if (!walk(i)) return false;
          bool ret = make_sure(x.side(i), i);
          walk(i ^ 2);
          return ret;
        }
      return false;
    }
    void find_gate() {
      int cnt = 0;
      std::stack<int> st;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          if (cnt == k * 2 && a[i][j] == Unknown)
            a[i][j] = Space;
          else if (a[i][j] == Unknown) {
            bool ok = true;
            if (!move(start, point(i - 1, j), st))
              ok = false;
            else if (!walk(1, st))
              ok = false;
            else if (!walk(2, st))
              ok = false;
            else if (!make_sure(point(i, j - 1), -1))
              ok = false;
            if (ok == false) {
              vis[cnt++] = std::make_pair(point(i, j), false);
              a[i][j] = Gate;
              for (int k = 0; k < 8; k++) {
                point y = point(i, j).side(k);
                if (point(i, j).check(k) == Unknown) a[y.x][y.y] = Space;
              }
            } else
              a[i][j] = Space;
            undo(st);
          }
    }
    void make_gate_pair() {
      int cnt = 0;
      std::stack<int> st;
      for (int i = 0; i < k * 2; i++)
        if (vis[i].second == false)
          for (int j = 0; vis[i].second == false && j < k * 2; j++)
            if (j != i && vis[j].second == false) {
              bool ok = true;
              if (!move(start, vis[i].first.side(2), st))
                ok = false;
              else if (!walk(0, st))
                ok = false;
              else if (!make_sure(vis[j].first.side(0), -1))
                ok = false;
              if (ok == true) {
                ans[cnt++] = std::make_pair(vis[i].first, vis[j].first);
                vis[i].second = vis[j].second = true;
              }
              undo(st);
            }
    }
    int main() {
      while (read()) {
        init();
        find_gate();
        make_gate_pair();
        answer();
      }
      return 0;
    }
    ```

## 习题

-  [刘汝佳的交互题专场比赛 Rujia Liu's Present 7 质量非常高，推荐一做。](https://onlinejudge.org/contests/328-9976a2e2/) 
-  [P5473\[NOI2019\]I 君的探险](https://www.luogu.com.cn/problem/P5473) 
-  [P5208\[WC2019\]I 君的商店](https://www.luogu.com.cn/problem/P5208) 

## References

-  [用 Linux 管道实现 online judge 的交互题功能](https://www.cnblogs.com/tsreaper/p/pipe-interactive.html) 
