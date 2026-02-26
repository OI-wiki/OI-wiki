author: Ir1d, sshwy, StudyingFather, Marcythm, partychicken, H-J-Granger, NachtgeistW, countercurrent-time, Enter-tainer, Tiphereth-A, weiranfu, greyqz, iamtwz, Konano, ksyx, ouuan, paigeman, wolfdan666, AngelKitty, CCXXXI, cjsoft, diauweb, Early0v0, ezoixx130, GekkaSaori, GoodCoder666, Henry-ZHR, HeRaNO, Link-cute, LovelyBuggies, LuoshuiTianyi, Makkiy, mgt, minghu6, odeinjul, oldoldtea, P-Y-Y, PotassiumWings, SamZhangQingChuan, shenshuaijie, Suyun514, weiyong1024, Xeonacid, xyf007, Alisahhh, Alphnia, c-forrest, cbw2007, dhbloo, fps5283, GavinZhengOI, Gesrua, hsfzLZH1, hydingsy, kenlig, kxccc, lychees, Menci, Peanut-Tang, PlanariaIce, sbofgayschool, shawlleyw, Siyuan, SukkaW, TianKong-y, tLLWtG, WAAutoMaton, x4Cx58x54, xk2013, zhb2000, zhufengning, hhc0001

## 输出方案

输出方案其实就是记录下来背包中的某一个状态是怎么推出来的．我们可以用 $g_{i,v}$ 表示第 $i$ 件物品占用空间为 $v$ 的时候是否选择了此物品．然后在转移时记录是选用了哪一种策略（选或不选）．输出时的伪代码：

```cpp
int v = V;  // 记录当前的存储空间

// 因为最后一件物品存储的是最终状态，所以从最后一件物品进行循环
for (从最后一件循环至第一件) {
  if (g[i][v]) {
    选了第 i 项物品;
    v -= 第 i 项物品的重量;
  } else {
    未选第 i 项物品;
  }
}
```

## 混合背包

混合背包就是将前面三种的背包问题混合起来，有的只能取一次，有的能取无限次，有的只能取 $k$ 次．

这种题目看起来很难，但是每一种物品的选择依然是独立的，因此可以判断当前物品是哪一种背包，然后使用这种背包的解决方案即可．

### 例题

???+ note "[「Luogu P1833」樱花](https://www.luogu.com.cn/problem/P1833)"
    有 $n$ 种樱花树和长度为 $T$ 的时间，有的樱花树只能看一遍，有的樱花树最多看 $A_{i}$ 遍，有的樱花树可以看无数遍．每棵樱花树都有一个美学值 $C_{i}$，求在 $T$ 的时间内看哪些樱花树能使美学值最高．

??? note "核心代码"
    ```cpp
    for (int i = 1; i <= n; i++) {
      if (cnt[i] == 0) {  // 如果数量没有限制使用完全背包的核心代码
        for (int weight = w[i]; weight <= W; weight++) {
          dp[weight] = max(dp[weight], dp[weight - w[i]] + v[i]);
        }
      } else {  // 物品有限使用多重背包的核心代码，它也可以处理0-1背包问题
        for (int weight = W; weight >= w[i]; weight--) {
          for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
            dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
          }
        }
      }
    }
    ```

习题：[HDU 5410 CRB and His Birthday](https://acm.hdu.edu.cn/showproblem.php?pid=5410)

## 二维费用背包

???+ note "[「Luogu P1855」榨取 kkksc03](https://www.luogu.com.cn/problem/P1855)"
    有 $n$ 个任务需要完成，完成第 $i$ 个任务需要花费 $t_i$ 分钟，产生 $c_i$ 元的开支．
    
    现在有 $T$ 分钟时间，$W$ 元钱来处理这些任务，求最多能完成多少任务．

这道题是很明显的 0-1 背包问题，可是不同的是选一个物品会消耗两种费用（经费、时间），只需在状态中增加一维存放第二种费用即可．这时状态转移方程变为 $f_{i, j, k} = \max(f_{i - 1, j, k}, f_{i - 1, j - t_i, k - c_i} + w_i)$．

这时候就要注意，再开一维存放物品编号就不合适了，因为容易 MLE．

### 实现

=== "C++"
    ```cpp
    for (int k = 1; k <= n; k++)
      for (int i = m; i >= mi; i--)    // 对经费进行一层枚举
        for (int j = t; j >= ti; j--)  // 对时间进行一层枚举
          dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1);
    ```

=== "Python"
    ```python
    for k in range(1, n + 1):
        for i in range(m, mi - 1, -1):  # 对经费进行一层枚举
            for j in range(t, ti - 1, -1):  # 对时间进行一层枚举
                dp[i][j] = max(dp[i][j], dp[i - mi][j - ti] + 1)
    ```

## 分组背包

???+ note "[「Luogu P1757」通天之分组背包](https://www.luogu.com.cn/problem/P1757)"
    有 $n$ 件物品和一个大小为 $m$ 的背包，第 $i$ 个物品的价值为 $w_i$，体积为 $v_i$．同时，每个物品属于一个组，同组内最多只能选择一个物品．求背包能装载物品的最大总价值．

这种题其实只是从「在所有物品中选择一件」变成了「从当前组中选择一件」，于是就对每一组进行一次 0-1 背包就可以了．然后，使用「泛化物品的背包」中提到的合并方法把每一组背包合并即可．

再说一说如何进行存储．我们可以将 $t_{k,i}$ 表示第 $k$ 组的第 $i$ 件物品的编号是多少，再用 $\mathit{cnt}_k$ 表示第 $k$ 组物品有多少个．

### 实现

=== "C++"
    ```cpp
    for (int k = 1; k <= ts; k++)          // 循环每一组
      for (int i = m; i >= 0; i--)         // 循环背包容量
        for (int j = 1; j <= cnt[k]; j++)  // 循环该组的每一个物品
          if (i >= w[t[k][j]])             // 背包容量充足
            dp[i] = max(dp[i],
                        dp[i - w[t[k][j]]] + c[t[k][j]]);  // 像0-1背包一样状态转移
    ```

=== "Python"
    ```python
    for k in range(1, ts + 1):  # 循环每一组
        for i in range(m, -1, -1):  # 循环背包容量
            for j in range(1, cnt[k] + 1):  # 循环该组的每一个物品
                if i >= w[t[k][j]]:  # 背包容量充足
                    dp[i] = max(
                        dp[i], dp[i - w[t[k][j]]] + c[t[k][j]]
                    )  # 像0-1背包一样状态转移
    ```

这里要注意：**一定不能搞错循环顺序**，这样才能保证正确性．

## 有依赖的背包

???+ note "[「Luogu P1064」金明的预算方案](https://www.luogu.com.cn/problem/P1064)"
    金明有 $n$ 元钱，想要买 $m$ 个物品，第 $i$ 件物品的价格为 $v_i$，重要度为 $p_i$．有些物品是从属于某个主件物品的附件，要买这个物品，必须购买它的主件．
    
    目标是让所有购买的物品的 $v_i \times p_i$ 之和最大．

直接当成 [树上背包](../tree.md) 处理即可．注意在最后将所有背包合并在一起．

## 参考资料与注释

-   [背包问题九讲 - 崔添翼](https://github.com/tianyicui/pack)．
