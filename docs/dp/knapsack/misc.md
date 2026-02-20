author: Ir1d, sshwy, StudyingFather, Marcythm, partychicken, H-J-Granger, NachtgeistW, countercurrent-time, Enter-tainer, Tiphereth-A, weiranfu, greyqz, iamtwz, Konano, ksyx, ouuan, paigeman, wolfdan666, AngelKitty, CCXXXI, cjsoft, diauweb, Early0v0, ezoixx130, GekkaSaori, GoodCoder666, Henry-ZHR, HeRaNO, Link-cute, LovelyBuggies, LuoshuiTianyi, Makkiy, mgt, minghu6, odeinjul, oldoldtea, P-Y-Y, PotassiumWings, SamZhangQingChuan, shenshuaijie, Suyun514, weiyong1024, Xeonacid, xyf007, Alisahhh, Alphnia, c-forrest, cbw2007, dhbloo, fps5283, GavinZhengOI, Gesrua, hsfzLZH1, hydingsy, kenlig, kxccc, lychees, Menci, Peanut-Tang, PlanariaIce, sbofgayschool, shawlleyw, Siyuan, SukkaW, TianKong-y, tLLWtG, WAAutoMaton, x4Cx58x54, xk2013, zhb2000, zhufengning, hhc0001

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

## 有依赖的背包

???+ note "[「Luogu P1064」金明的预算方案](https://www.luogu.com.cn/problem/P1064)"
    金明有 $n$ 元钱，想要买 $m$ 个物品，第 $i$ 件物品的价格为 $v_i$，重要度为 $p_i$．有些物品是从属于某个主件物品的附件，要买这个物品，必须购买它的主件．
    
    目标是让所有购买的物品的 $v_i \times p_i$ 之和最大．

直接当成 [树上背包](../tree.md) 处理即可．注意在最后将所有背包合并在一起．

## 求方案数

对于给定的一个背包容量、物品费用、其他关系等的问题，求装到一定容量的方案总数．

这种问题就是把求最大值换成求和即可．

例如 0-1 背包问题的转移方程就变成了：

$$
\mathit{dp}_j \leftarrow \mathit{dp}_j + \mathit{dp}_{j-c_i} \qquad (j \ge c_i)
$$

初始条件：$f_0=1$

因为当容量为 $0$ 时也有一个方案，即什么都不装．

## 参考资料与注释

-   [背包问题九讲 - 崔添翼](https://github.com/tianyicui/pack)．
