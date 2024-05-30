本页面主要介绍最大流问题相关的算法知识。

## 概述

网络流基本概念参见 [网络流简介](../flow.md)。

令 $G=(V,E)$ 是一个有源汇点的网络，我们希望在 $G$ 上指定合适的流 $f$，以最大化整个网络的流量 $|f|$（即 $\sum_{x \in V} f(s, x) - \sum_{x \in V} f(x, s)$），这一问题被称作最大流问题（Maximum flow problem）。

## Ford–Fulkerson 增广

Ford–Fulkerson 增广是计算最大流的一类算法的总称。该方法运用贪心的思想，通过寻找增广路来更新并求解最大流。

### 概述

给定网络 $G$ 及 $G$ 上的流 $f$，我们做如下定义。

对于边 $(u, v)$，我们将其容量与流量之差称为剩余容量 $c_f(u,v)$（Residual Capacity），即 $c_f(u,v)=c(u,v)-f(u,v)$。

我们将 $G$ 中所有结点和剩余容量大于 $0$ 的边构成的子图称为残量网络 $G_f$（Residual Network），即 $G_f=(V,E_f)$，其中 $E_f=\left\{(u,v) \mid c_f(u,v)>0\right\}$。

???+ warning
    正如我们马上要提到的，流量可能是负值，因此，$E_f$ 的边有可能并不在 $E$ 中。引入增广的概念后，下文将具体解释这一点。

我们将 $G_f$ 上一条从源点 $s$ 到汇点 $t$ 的路径称为增广路（Augmenting Path）。对于一条增广路，我们给每一条边 $(u, v)$ 都加上等量的流量，以令整个网络的流量增加，这一过程被称为增广（Augment）。由此，最大流的求解可以被视为若干次增广分别得到的流的叠加。

此外，在 Ford–Fulkerson 增广的过程中，对于每条边 $(u, v)$，我们都新建一条反向边 $(v, u)$。我们约定 $f(u, v) = -f(v, u)$，这一性质可以通过在每次增广时引入退流操作来保证，即 $f(u, v)$ 增加时 $f(v, u)$ 应当减少同等的量。

???+ tip
    在最大流算法的代码实现中，我们往往需要支持快速访问反向边的操作。在邻接矩阵中，这一操作是 trivial 的（$g_{u, v} \leftrightarrow g_{v, u}$）。但主流的实现是更加优秀的链式前向星。其中，一个常用的技巧是，我们令边从偶数（通常为 $0$）开始编号，并在加边时总是紧接着加入其反向边使得它们的编号相邻。由此，我们可以令编号为 $i$ 的边和编号为 $i \oplus 1$ 的边始终保持互为反向边的关系。

初次接触这一方法的读者可能察觉到一个违反直觉的情形——反向边的流量 $f(v, u)$ 可能是一个负值。实际上我们可以注意到，在 Ford–Fulkerson 增广的过程中，真正有意义的是剩余容量 $c_f$，而 $f(v, u)$ 的绝对值是无关紧要的，我们可以将反向边流量的减少视为反向边剩余容量 $c_f(v, u)$ 的增加——这也与退流的意义相吻合——反向边剩余容量的增加意味着我们接下来可能通过走反向边来和原先正向的增广抵消，代表一种「反悔」的操作。

以下案例有可能帮助你理解这一过程。假设 $G$ 是一个单位容量的网络，我们考虑以下过程：

-   $G$ 上有多条增广路，其中，我们选择进行一次先后经过 $u, v$ 的增广（如左图所示），流量增加 $1$。
-   我们注意到，如果进行中图上的增广，这个局部的最大流量不是 $1$ 而是 $2$。但由于指向 $u$ 的边和从 $v$ 出发的边在第一次增广中耗尽了容量，此时我们无法进行中图上的增广。这意味着我们当前的流是不够优的，但局部可能已经没有其他（只经过原图中的边而不经过反向边的）增广路了。
-   现在引入退流操作。第一次增广后，退流意味着 $c_f(v, u)$ 增加了 $1$ 剩余容量，即相当于新增 $(v, u)$ 这条边，因此我们可以再进行一次先后经过 $p, v, u, q$ 的增广（如右图橙色路径所示）。无向边 $(u, v)$ 上的流量在两次增广中抵消，我们惊奇地发现两次增广叠加得到的结果实际上和中图是等价的。

![](./images/flow2.png)

以上案例告诉我们，退流操作带来的「抵消」效果使得我们无需担心我们按照「错误」的顺序选择了增广路。

容易发现，只要 $G_f$ 上存在增广路，那么对其增广就可以令总流量增加；否则说明总流量已经达到最大可能值，求解过程完成。这就是 Ford–Fulkerson 增广的过程。

### 最大流最小割定理

我们大致了解了 Ford–Fulkerson 增广的思想，可是如何证明这一方法的正确性呢？为什么增广结束后的流 $f$ 是一个最大流？

实际上，Ford–Fulkerson 增广的正确性和最大流最小割定理（The Maxflow-Mincut Theorem）等价。这一定理指出，对于任意网络 $G = (V, E)$，其上的最大流 $f$ 和最小割 $\{S, T\}$ 总是满足 $|f| = ||S, T||$。

为了证明最大流最小割定理，我们先从一个引理出发：对于网络 $G = (V, E)$，任取一个流 $f$ 和一个割 $\{S, T\}$，总是有 $|f| \leq ||S, T||$，其中等号成立当且仅当 $\{(u, v) | u \in S, v \in T\}$ 的所有边均满流，且 $\{(u, v) | u \in T, v \in S\}$ 的所有边均空流。

???+ note "证明"
    $$
    \begin{aligned}
    |f| & = f(s) \\
        & = \sum_{u \in S} f(u) \\
        & = \sum_{u \in S} \left( \sum_{v \in V} f(u, v) - \sum_{v \in V} f(v, u) \right) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) + \sum_{v \in S} f(u, v) - \sum_{v \in T} f(v, u) - \sum_{v \in S} f(v, u) \right) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) - \sum_{v \in T} f(v, u) \right) + \sum_{u \in S} \sum_{v \in S} f(u, v) - \sum_{u \in S} \sum_{v \in S} f(v, u) \\
        & = \sum_{u \in S} \left( \sum_{v \in T} f(u, v) - \sum_{v \in T} f(v, u) \right) \\
        & \leq \sum_{u \in S} \sum_{v \in T} f(u, v) \\
        & \leq \sum_{u \in S} \sum_{v \in T} c(u, v) \\
        & = ||S, T|| \\
    \end{aligned}
    $$
    
    为了取等，第一个不等号需要 $\{(u, v) \mid u \in T, v \in S\}$ 的所有边均空流，第二个不等号需要 $\{(u, v) \mid u \in S, v \in T\}$ 的所有边均满流。原引理得证。

那么，对于任意网络，以上取等条件是否总是能被满足呢？如果答案是肯定的，则最大流最小割定理得证。以下我们尝试证明。

???+ note "证明"
    假设某一轮增广后，我们得到流 $f$ 使得 $G_f$ 上不存在增广路，即 $G_f$ 上不存在 $s$ 到 $t$ 的路径。此时我们记从 $s$ 出发可以到达的结点组成的点集为 $S$，并记 $T = V \setminus S$。
    
    显然，$\{S, T\}$ 是 $G_f$ 的一个割，且 $||S, T|| = \sum_{u \in S} \sum_{v \in T} c_f(u, v) = 0$。由于剩余容量是非负的，这也意味着对于任意 $u \in S, v \in T, (u, v) \in E_f$，均有 $c_f(u, v) = 0$。以下我们将这些边分为存在于原图中的边和反向边两种情况讨论：
    
    -   $(u, v) \in E$：此时，$c_f(u, v) = c(u, v) - f(u, v) = 0$，因此有 $c(u, v) = f(u, v)$，即 $\{(u, v) \mid u \in S, v \in T\}$ 的所有边均满流；
    -   $(v, u) \in E$：此时，$c_f(u, v) = c(u, v) - f(u, v) = 0 - f(u, v) = f(v, u) = 0$，即 $\{(v, u) \mid u \in S, v \in T\}$ 的所有边均空流。
    
    因此，增广停止后，上述流 $f$ 满足取等条件。根据引理指出的大小关系，自然地，$f$ 是 $G$ 的一个最大流，$\{S, T\}$ 是 $G$ 的一个最小割。

容易看出，Kőnig 定理是最大流最小割定理的特殊情形。实际上，它们都和线性规划中的对偶有关。

### 时间复杂度分析

在整数流量的网络 $G = (V, E)$ 上，平凡地，我们假设每次增广的流量都是整数，则 Ford–Fulkerson 增广的时间复杂度的一个上界是 $O(|E||f|)$，其中 $f$ 是 $G$ 上的最大流。这是因为单轮增广的时间复杂度是 $O(|E|)$，而增广会导致总流量增加，故增广轮数不可能超过 $|f|$。

对于 Ford–Fulkerson 增广的不同实现，时间复杂度也各不相同。其中较主流的实现有 Edmonds–Karp, Dinic, SAP, ISAP 等算法，我们将在下文中分别介绍。

### Edmonds–Karp 算法

#### 算法思想

如何在 $G_f$ 中寻找增广路呢？当我们考虑 Ford–Fulkerson 增广的具体实现时，最自然的方案就是使用 BFS。此时，Ford–Fulkerson 增广表现为 Edmonds–Karp 算法。其具体流程如下：

-   如果在 $G_f$ 上我们可以从 $s$ 出发 BFS 到 $t$，则我们找到了新的增广路。

-   对于增广路 $p$，我们计算出 $p$ 经过的边的剩余容量的最小值 $\Delta = \min_{(u, v) \in p} c_f(u, v)$。我们给 $p$ 上的每条边都加上 $\Delta$ 流量，并给它们的反向边都退掉 $\Delta$ 流量，令最大流增加了 $\Delta$。

-   因为我们修改了流量，所以我们得到新的 $G_f$，我们在新的 $G_f$ 上重复上述过程，直至增广路不存在，则流量不再增加。

以上算法即 Edmonds–Karp 算法。

#### 时间复杂度分析

接下来让我们尝试分析 Edmonds–Karp 算法的时间复杂度。

显然，单轮 BFS 增广的时间复杂度是 $O(|E|)$。

增广总轮数的上界是 $O(|V||E|)$。这一论断在网络资料中常被伪证（或被含糊其辞略过）。以下我们尝试给出一个较正式的证明[^ref_EK]。

???+ info "增广总轮数的上界的证明"
    首先，我们引入一个引理——最短路非递减引理。具体地，我们记 $d_f(u)$ 为 $G_f$ 上结点 $u$ 到源点 $s$ 的距离（即最短路长度，下同）。对于某一轮增广，我们用 $f$ 和 $f'$ 分别表示增广前的流和增广后的流，我们断言，对于任意结点 $u$，增广总是使得 $d_{f'}(u) \geq d_f(u)$。我们将在稍后证明这一引理。
    
    不妨称增广路上剩余容量最小的边是饱和边（存在多条边同时最小则取任一）。如果一条有向边 $(u, v)$ 被选为饱和边，增广会清空其剩余容量导致饱和边的消失，并且退流导致反向边的新增（如果原先反向边不存在），即 $(u, v) \not \in E_{f'}$ 且 $(v, u) \in E_{f'}$。以上分析使我们知道，对于无向边 $(u, v)$，其被增广的两种方向总是交替出现。
    
    在 $G_f$ 上沿 $(u, v)$ 增广时，$d_f(u) + 1 = d_f(v)$，此后残量网络变为 $G_{f'}$。在 $G_{f'}$ 上沿 $(v, u)$ 增广时，$d_{f'}(v) + 1 = d_{f'}(u)$。根据最短路非递减引理又有 $d_{f'}(v) \geq d_f(v)$，我们连接所有式子，得到 $d_{f'}(u) \geq d_{f}(u) + 2$。换言之，如果有向边 $(u, v)$ 被选为饱和边，那么与其上一次被选为饱和边时相比，$u$ 到 $s$ 的距离至少增加 $2$。
    
    $s$ 到任意结点的距离不可能超过 $|V|$，结合上述性质，我们发现每条边被选为饱和边的次数是 $O(|V|)$ 的，与边数相乘后得到增广总轮数的上界 $O(|V||E|)$。
    
    接下来我们证明最短路非递减引理，即 $d_{f'}(u) \geq d_f(u)$。这一证明并不难，但可能稍显绕口，读者可以停下来认真思考片刻。
    
    ???+ info "最短路非递减引理的证明"
        考虑反证。对于某一轮增广，我们假设存在若干结点，它们在该轮增广后到 $s$ 的距离较增广前减小。我们记 $v$ 为其中到 $s$ 的距离最小的一者（即 $v = \arg \min_{x \in V, d_{f'}(x) < d_f(x)} d_{f'}(x)$）。注意，根据反证假设，此时 $d_{f'}(v) < d_f(v)$ 是已知条件。
        
        在 $G_{f'}$ 中 $s$ 到 $v$ 的最短路上，我们记 $u$ 是 $v$ 的上一个结点，即 $d_{f'}(u) + 1 = d_{f'}(v)$。
        
        为了不让 $u$ 破坏 $v$ 的「距离最小」这一性质，$u$ 必须满足 $d_{f'}(u) \geq d_f(u)$。
        
        对于上式，我们令不等号两侧同加，得 $d_{f'}(v) \geq d_f(u) + 1$。根据反证假设进行放缩，我们得到 $d_f(v) > d_f(u) + 1$。
        
        以下我们尝试讨论 $(u, v)$ 上的增广方向。
        
        -   假设有向边 $(u, v) \in E_f$。根据 BFS「广度优先」的性质，我们有 $d_f(u) + 1 \geq d_f(v)$。该式与放缩结果冲突，导出矛盾。
        -   假设有向边 $(u, v) \not \in E_f$。根据 $u$ 的定义我们已知 $(u, v) \in E_{f'}$，因此这条边的存在必须是当前轮次的增广经过了 $(v, u)$ 并退流产生反向边的结果，也即 $d_f(v) + 1 = d_f(u)$。该式与放缩结果冲突，导出矛盾。
        
        由于 $(u, v)$ 沿任何方向增广都会导出矛盾，我们知道反证假设不成立，最短路非递减引理得证。

将单轮 BFS 增广的复杂度与增广轮数的上界相乘，我们得到 Edmonds–Karp 算法的时间复杂度是 $O(|V||E|^2)$。

#### 代码实现

Edmonds–Karp 算法的可能实现如下。

??? note "参考代码"
    ```cpp
    #define maxn 250
    #define INF 0x3f3f3f3f
    
    struct Edge {
      int from, to, cap, flow;
    
      Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    
    struct EK {
      int n, m;             // n：点数，m：边数
      vector<Edge> edges;   // edges：所有边的集合
      vector<int> G[maxn];  // G：点 x -> x 的所有边在 edges 中的下标
      int a[maxn], p[maxn];  // a：点 x -> BFS 过程中最近接近点 x 的边给它的最大流
                             // p：点 x -> BFS 过程中最近接近点 x 的边
    
      void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
      }
    
      void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
      }
    
      int Maxflow(int s, int t) {
        int flow = 0;
        for (;;) {
          memset(a, 0, sizeof(a));
          queue<int> Q;
          Q.push(s);
          a[s] = INF;
          while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < G[x].size(); i++) {  // 遍历以 x 作为起点的边
              Edge& e = edges[G[x][i]];
              if (!a[e.to] && e.cap > e.flow) {
                p[e.to] = G[x][i];  // G[x][i] 是最近接近点 e.to 的边
                a[e.to] =
                    min(a[x], e.cap - e.flow);  // 最近接近点 e.to 的边赋给它的流
                Q.push(e.to);
              }
            }
            if (a[t]) break;  // 如果汇点接受到了流，就退出 BFS
          }
          if (!a[t])
            break;  // 如果汇点没有接受到流，说明源点和汇点不在同一个连通分量上
          for (int u = t; u != s;
               u = edges[p[u]].from) {  // 通过 u 追寻 BFS 过程中 s -> t 的路径
            edges[p[u]].flow += a[t];      // 增加路径上边的 flow 值
            edges[p[u] ^ 1].flow -= a[t];  // 减小反向路径的 flow 值
          }
          flow += a[t];
        }
        return flow;
      }
    };
    ```

### Dinic 算法

#### 算法思想

考虑在增广前先对 $G_f$ 做 BFS 分层，即根据结点 $u$ 到源点 $s$ 的距离 $d(u)$ 把结点分成若干层。令经过 $u$ 的流量只能流向下一层的结点 $v$，即删除 $u$ 向层数标号相等或更小的结点的出边，我们称 $G_f$ 剩下的部分为层次图（Level Graph）。形式化地，我们称 $G_L = (V, E_L)$ 是 $G_f = (V, E_f)$ 的层次图，其中 $E_L = \left\{ (u, v) \mid (u, v) \in E_f, d(u) + 1 = d(v) \right\}$。

如果我们在层次图 $G_L$ 上找到一个最大的增广流 $f_b$，使得仅在 $G_L$ 上是不可能找出更大的增广流的，则我们称 $f_b$ 是 $G_L$ 的阻塞流（Blocking Flow）。

??? warning
    尽管在上文中我们仅在单条增广路上定义了增广/增广流，广义地，「增广」一词不仅可以用于单条路径上的增广流，也可以用于若干增广流的并——后者才是我们定义阻塞流时使用的意义。

定义层次图和阻塞流后，Dinic 算法的流程如下。

1.  在 $G_f$ 上 BFS 出层次图 $G_L$。
2.  在 $G_L$ 上 DFS 出阻塞流 $f_b$。
3.  将 $f_b$ 并到原先的流 $f$ 中，即 $f \leftarrow f + f_b$。
4.  重复以上过程直到不存在从 $s$ 到 $t$ 的路径。

此时的 $f$ 即为最大流。

在分析这一算法的复杂度之前，我们需要特别说明「在 $G_L$ 上 DFS 出阻塞流 $f_b$」的过程。尽管 BFS 层次图对于本页面的读者应当是 trivial 的，但 DFS 阻塞流的过程则稍需技巧——我们需要引入当前弧优化。

注意到在 $G_L$ 上 DFS 的过程中，如果结点 $u$ 同时具有大量入边和出边，并且 $u$ 每次接受来自入边的流量时都遍历出边表来决定将流量传递给哪条出边，则 $u$ 这个局部的时间复杂度最坏可达 $O(|E|^2)$。为避免这一缺陷，如果某一时刻我们已经知道边 $(u, v)$ 已经增广到极限（边 $(u, v)$ 已无剩余容量或 $v$ 的后侧已增广至阻塞），则 $u$ 的流量没有必要再尝试流向出边 $(u, v)$。据此，对于每个结点 $u$，我们维护 $u$ 的出边表中第一条还有必要尝试的出边。习惯上，我们称维护的这个指针为当前弧，称这个做法为当前弧优化。

??? info "多路增广"
    多路增广是 Dinic 算法的一个常数优化——如果我们在层次图上找到了一条从 $s$ 到 $t$ 的增广路 $p$，则接下来我们未必需要重新从 $s$ 出发找下一条增广路，而可能从 $p$ 上最后一个仍有剩余容量的位置出发寻找一条岔路进行增广。考虑到其与回溯形式的一致性，这一优化在 DFS 的代码实现中也是自然的。
    
    ??? failure "常见误区"
        可能是由于大量网络资料的错误表述引发以讹传讹的情形，相当数量的选手喜欢将当前弧优化和多路增广并列称为 Dinic 算法的两种优化。实际上，当前弧优化是用于保证 Dinic 时间复杂度正确性的一部分，而多路增广只是一个不影响复杂度的常数优化。

#### 时间复杂度分析

应用当前弧优化后，对 Dinic 算法的时间复杂度分析如下。

首先，我们尝试证明单轮增广中 DFS 求阻塞流的时间复杂度是 $O(|V||E|)$。

???+ info "单轮增广的时间复杂度的证明"
    考虑阻塞流 $f_b$ 中的每条增广路，它们都是在 $G_L$ 上每次沿当前弧跳转而得到的结果，其中每条增广路经历的跳转次数不可能多于 $|V|$。
    
    每找到一条增广路就有一条饱和边消失（剩余容量清零）。考虑阻塞流 $f_b$ 中的每条增广路，我们将被它们清零的饱和边形成的边集记作 $E_1$。考虑到 $G_L$ 分层的性质，饱和边消失后其反向边不可能在同一轮增广内被其他增广路经过，因此，$E_1$ 是 $E_L$ 的子集。
    
    此外，对于沿当前弧跳转但由于某个位置阻塞所以没有成功得到增广路的情形，我们将这些不完整的路径上的最后一条边形成的边集记作 $E_2$。$E_2$ 的成员不饱和，所以 $E_1$ 与 $E_2$ 不交，且 $E_1 \cup E_2$ 仍是 $E_L$ 的子集。
    
    由于 $E_1 \cup E_2$ 的每个成员都没有花费超过 $|V|$ 次跳转（且在使用多路增广优化后一些跳转将被重复计数），因此，综上所述，DFS 过程中的总跳转次数不可能多于 $|V||E_L|$。
    
    ??? failure "常见伪证一则"
        对于每个结点，我们维护下一条可以增广的边，而当前弧最多变化 $|E|$ 次，从而单轮增广的最坏时间复杂度为 $O(|V||E|)$。
    
    ??? bug
        「当前弧最多变化 $|E|$ 次」并不能推得「每个结点最多访问其出边 $|E|$ 次」。这是因为，访问当前弧并不一定耗尽上面的剩余容量，结点 $u$ 可能多次访问同一条当前弧。

注意到层次图的层数显然不可能超过 $|V|$，如果我们可以证明层次图的层数在增广过程中严格单增，则 Dinic 算法的增广轮数是 $O(|V|)$ 的。接下来我们尝试证明这一结论[^ref_Dinic]。

???+ info "层次图层数单调性的证明"
    我们需要引入预流推进类算法（另一类最大流算法）中的一个概念——高度标号。为了更方便地结合高度标号表述我们的证明，在证明过程中，我们令 $d_f(u)$ 为 $G_f$ 上结点 $u$ 到 **汇点**  $t$ 的距离，从 **汇点** 而非源点出发进行分层（这并没有本质上的区别）。对于某一轮增广，我们用 $f$ 和 $f'$ 分别表示增广前的流和增广后的流。在该轮增广中求解并加入阻塞流后，记层次图由 $G_L = (V, E_L)$ 变为 $G'_{L} = (V, E'_L)$。
    
    我们给高度标号一个不严格的临时定义——在网络 $G = (V, E)$ 上，令 $h$ 是点集 $V$ 到整数集 $N$ 上的函数，$h$ 是 $G$ 上合法的高度标号当且仅当 $h(u) \leq h(v) + 1$ 对于 $(u, v) \in E$ 恒成立。
    
    考察所有 $E_{f'}$ 的成员 $(u, v)$，我们发现 $(u, v) \in E_{f'}$ 的原因是以下二者之一。
    
    -   $(u, v) \in E_f$，且剩余容量在该轮增广过程中未耗尽——根据最短路的定义，此时我们有 $d_f(u) \leq d_f(v) + 1$；
    -   $(u, v) \not \in E_f$，但在该轮增广过程中阻塞流经过 $(v, u)$ 并退流产生反向边——根据层次图和阻塞流的定义，此时我们有 $d_f(u) + 1 = d_f(v)$。
    
    以上观察让我们得出一个结论——$d_f$ 在 $G_{f'}$ 上是一个合法的高度标号。当然，在 $G_{f'}$ 的子图 $G'_L$ 上也是。
    
    现在，对于一条 $G'_L$ 上的增广路 $p = (s, \dots, u, v, \dots, t)$，按照 $p$ 上结点的反序（从 $t$ 到 $s$ 的顺序）考虑从空路径开始每次添加一个结点的过程。假设结点 $v$ 已加入，结点 $u$ 正在加入，我们发现，加入结点 $u$ 后，根据层次图的定义，$d_{f'}(u)$ 的值较 $d_{f'}(v)$ 增加 $1$；与此同时，由于 $d_f$ 是 $G'_L$ 上的高度标号，$d_f(u)$ 的值既可能较 $d_f(v)$ 增加 $1$，也可能保持不变或减少。因此，在整条路径被添加完成后，我们得到 $d_{f'}(s) \geq d_f(s)$，其中取等的充要条件是 $d_f(u) = d_f(v) + 1$ 对于 $(u, v) \in p$ 恒成立。如果该不等式不能取等，则有 $d_{f'}(s) > d_f(s)$——即我们想要的结论「层次图的层数在增广过程中严格单增」。以下我们尝试证明该不等式不能取等。
    
    考虑反证，我们假设 $d_{f'}(s) = d_f(s)$ 成立，并尝试导出矛盾。现在我们断言，在 $G'_L$ 上，$p$ 至少包含一条边 $(u, v)$ 满足 $(u, v)$ 在 $G_L$ 上不存在。如果没有这样的边，考虑到 $d_f(s) = d_{f'}(s)$，结合层次图和阻塞流的定义，$G_L$ 上的增广应尚未完成。为了不产生以上矛盾，我们的断言只好是正确的。
    
    令 $(u, v)$ 是满足断言条件的那条边，其满足断言的原因只能是以下二者之一。
    
    -   $(u, v) \in E_f$ 但 $d_f(u) \leq d_f(v) + 1$ 未取等，故根据层次图的定义可知 $(u, v) \not \in E_L$，并在增广后新一轮重分层中被加入到 $E'_L$ 中；
    -   $(u, v) \not \in E_f$，这意味着 $(u, v)$ 这条边的产生是当前轮次增广中阻塞流经过 $(v, u)$ 并退流产生反向边的结果，也即 $d_f(u) = d_f(v) - 1$。
    
    由于我们无论以何种方式满足断言均得到 $d_f(u) \neq d_f(v) + 1$，也即 $d_{f'}(s) \geq d_f(s)$ 取等的充要条件无法被满足，这与反证假设 $d_{f'}(s) = d_f(s)$ 冲突，原命题得证。
    
    ??? failure "常见伪证另一则"
        考虑反证。假设层次图的层数在一轮增广结束后较原先相等，则层次图上应仍存在至少一条从 $s$ 到 $t$ 的增广路满足相邻两点间的层数差为 $1$。这条增广路未被增广说明该轮增广尚未结束。为了不产生上述矛盾，原命题成立。
    
    ??? bug
        「一轮增广结束后新的层次图上 $s$-$t$ 最短路较原先相等」并不能推得「旧的层次图上该轮增广尚未结束」。这是因为，没有理由表明两张层次图的边集相同，新的层次图上的 $s$-$t$ 最短路有可能经过旧的层次图上不存在的边。

将单轮增广的时间复杂度 $O(|V||E|)$ 与增广轮数 $O(|V|)$ 相乘，Dinic 算法的时间复杂度是 $O(|V|^2|E|)$。

如果需要令 Dinic 算法的实际运行时间接近其理论上界，我们需要构造有特殊性质的网络作为输入。由于在算法竞赛实践中，对于网络流知识相关的考察常侧重于将原问题建模为网络流问题的技巧。此时，我们的建模通常不包含令 Dinic 算法执行缓慢的特殊性质；恰恰相反，Dinic 算法在大部分图上效率非常优秀。因此，网络流问题的数据范围通常较大，「将 $|V|, |E|$ 的值代入 $|V|^2|E|$ 以估计运行时间」这一方式并不适用。实际上，进行准确的估计需要选手对 Dinic 算法的实际效率有一定的经验，读者可以多加练习。

#### 特殊情形下的时间复杂度分析

在一些性质良好的图上，Dinic 算法有更好的时间复杂度。

对于网络 $G = (V, E)$，如果其所有边容量均为 $1$，即 $c(u, v) \in \{0, 1\}$ 对于 $(u, v) \in E$ 恒成立，则我们称 $G$ 是单位容量（Unit Capacity）的。

在单位容量的网络中，Dinic 算法的单轮增广的时间复杂度为 $O(|E|)$。

???+ info "证明"
    这是因为，每次增广都会导致增广路上的所有边均饱和并消失，故单轮增广中每条边只能被增广一次。

在单位容量的网络中，Dinic 算法的增广轮数是 $O(|E|^{\frac{1}{2}})$ 的。

???+ info "证明"
    以源点 $s$ 为中心分层，记 $d_f(u)$ 为 $G_f$ 上结点 $u$ 到源点 $s$ 的距离。另外，我们定义将点集 $\left\{u \mid u \in V, d_f(u) = k \right\}$ 定义为编号为 $k$ 的层次 $D_k$，并记 $S_k = \cup_{i \leq k} D_i$。
    
    假设我们已经进行了 $|E|^{\frac{1}{2}}$ 轮增广。根据鸽巢原理，至少存在一个 $k$ 满足边集 $\left\{ (u, v) \mid u \in D_k, v \in D_{k+1}, (u, v) \in E_f \right\}$ 的大小不超过 $\frac {|E|} {|E|^{\frac{1}{2}}} \approx |E|^{\frac{1}{2}}$。显然，$\{S_k, V - S_k\}$ 是 $G_f$ 上的 $s$-$t$ 割，且其割容量不超过 $|E|^{\frac{1}{2}}$。根据最大流最小割定理，$G_f$ 上的最大流不超过 $|E|^{\frac{1}{2}}$，也即 $G_f$ 上最多还能执行 $|E|^{\frac{1}{2}}$ 轮增广。因此，总增广轮数是 $O(|E|^{\frac{1}{2}})$ 的。

在单位容量的网络中，Dinic 算法的增广轮数是 $O(|V|^{\frac{2}{3}})$ 的。

???+ info "证明"
    假设我们已经进行了 $2 |V|^{\frac{2}{3}}$ 轮增广。由于至多有半数的（$|V|^{\frac{2}{3}}$ 个）层次包含多于 $|V|^{\frac{1}{3}}$ 个点，故无论我们如何分配所有层次的大小，至少存在一个 $k$ 满足相邻两个层次同时包含不多于 $|V|^{\frac{1}{3}}$ 个点，即 $|D_k| \leq |V|^{\frac{1}{3}}$ 且 $|D_{k+1}| \leq |V|^{\frac{1}{3}}$。
    
    为最大化 $D_k$ 和 $D_{k+1}$ 之间的边数，我们假定这是一个完全二分图，此时边集 $\left\{ (u, v) \mid u \in D_k, v \in D_{k+1}, (u, v) \in E_f \right\}$ 的大小不超过 $|V|^{\frac{2}{3}}$。显然，$\{S_k, V - S_k\}$ 是 $G_f$ 上的 $s$-$t$ 割，且其割容量不超过 $|V|^{\frac{2}{3}}$。根据最大流最小割定理，$G_f$ 上的最大流不超过 $|V|^{\frac{2}{3}}$，也即 $G_f$ 上最多还能执行 $|V|^{\frac{2}{3}}$ 轮增广。因此，总增广轮数是 $O(|V|^{\frac{2}{3}})$ 的。

在单位容量的网络中，如果除源汇点外每个结点 $u$ 都满足 $\mathit{deg}_{\mathit{in}}(u) = 1$ 或 $\mathit{deg}_{\mathit{out}}(u) = 1$，则 Dinic 算法的增广轮数是 $O(|V|^{\frac{1}{2}})$ 的。其中，$\mathit{deg}_{\mathit{in}}(u)$ 和 $\mathit{deg}_{\mathit{out}}(u)$ 分别代表结点 $u$ 的入度和出度。

???+ info "证明"
    我们引入以下引理——对于这一形式的网络，其上的任意流总是可以分解成若干条单位流量的、**点不交** 的增广路。
    
    假设我们已经进行了 $|V|^{\frac{1}{2}}$ 轮增广。根据层次图的定义，此时任意新的增广路的长度至少为 $|V|^{\frac{1}{2}}$。
    
    考虑 $G_f$ 上的最大流的增广路分解，我们得到的增广路的数量不能多于 $\frac {|V|} {|V|^{\frac{1}{2}}} \approx |V|^{\frac{1}{2}}$，这意味着 $G_f$ 上最多还能执行 $|V|^{\frac{1}{2}}$ 轮增广。因此，总增广轮数是 $O(|V|^{\frac{1}{2}})$ 的。

综上，我们得出一些推论。

-   在单位容量的网络上，Dinic 算法的总时间复杂度是 $O(|E| \min(|E|^\frac{1}{2}, |V|^{\frac{2}{3}}))$。
-   在单位容量的网络上，如果除源汇点外每个结点 $u$ 都满足 $\mathit{deg}_{\mathit{in}}(u) = 1$ 或 $\mathit{deg}_{\mathit{out}}(u) = 1$，Dinic 算法的总时间复杂度是 $O(|E||V|^{\frac{1}{2}})$。对于二分图最大匹配问题，我们常使用 Hopcroft–Karp 算法解决，而这一算法实际上是 Dinic 算法在满足上述度数限制的单位容量网络上的特例。

#### 代码实现

??? note "参考代码"
    ```cpp
    struct MF {
      struct edge {
        int v, nxt, cap, flow;
      } e[N];
    
      int fir[N], cnt = 0;
    
      int n, S, T;
      ll maxflow = 0;
      int dep[N], cur[N];
    
      void init() {
        memset(fir, -1, sizeof fir);
        cnt = 0;
      }
    
      void addedge(int u, int v, int w) {
        e[cnt] = {v, fir[u], w, 0};
        fir[u] = cnt++;
        e[cnt] = {u, fir[v], 0, 0};
        fir[v] = cnt++;
      }
    
      bool bfs() {
        queue<int> q;
        memset(dep, 0, sizeof(int) * (n + 1));
    
        dep[S] = 1;
        q.push(S);
        while (q.size()) {
          int u = q.front();
          q.pop();
          for (int i = fir[u]; ~i; i = e[i].nxt) {
            int v = e[i].v;
            if ((!dep[v]) && (e[i].cap > e[i].flow)) {
              dep[v] = dep[u] + 1;
              q.push(v);
            }
          }
        }
        return dep[T];
      }
    
      int dfs(int u, int flow) {
        if ((u == T) || (!flow)) return flow;
    
        int ret = 0;
        for (int& i = cur[u]; ~i; i = e[i].nxt) {
          int v = e[i].v, d;
          if ((dep[v] == dep[u] + 1) &&
              (d = dfs(v, min(flow - ret, e[i].cap - e[i].flow)))) {
            ret += d;
            e[i].flow += d;
            e[i ^ 1].flow -= d;
            if (ret == flow) return ret;
          }
        }
        return ret;
      }
    
      void dinic() {
        while (bfs()) {
          memcpy(cur, fir, sizeof(int) * (n + 1));
          maxflow += dfs(S, INF);
        }
      }
    } mf;
    ```

### MPM 算法

**MPM**(Malhotra, Pramodh-Kumar and Maheshwari) 算法得到最大流的方式有两种：使用基于堆的优先队列，时间复杂度为 $O(n^3\log n)$；常用 BFS 解法，时间复杂度为 $O(n^3)$。注意，本章节只专注于分析更优也更简洁的 $O(n^3)$ 算法。

MPM 算法的整体结构和 Dinic 算法类似，也是分阶段运行的。在每个阶段，在 $G$ 的残量网络的分层网络中找到增广路。它与 Dinic 算法的主要区别在于寻找增广路的方式不同：MPM 算法中寻找增广路的部分的只花了 $O(n^2)$, 时间复杂度要优于 Dinic 算法。

MPM 算法需要考虑顶点而不是边的容量。在分层网络 $L$ 中，如果定义点 $v$ 的容量 $p(v)$ 为其传入残量和传出残量的最小值，则有：

$$
\begin{aligned}
p_{in}(v) &= \sum\limits_{(u,v) \in L} (c(u, v) - f(u, v)) \\
p_{out}(v) &= \sum\limits_{(v,u) \in L} (c(v, u) - f(v, u)) \\
p(v) &= \min (p_{in}(v), p_{out}(v))
\end{aligned}
$$

我们称节点 $r$ 是参考节点当且仅当 $p(r) = \min {p(v)}$。对于一个参考节点 $r$，我们一定可以让经过 $r$ 的流量增加 $p(r)$ 以使其容量变为 $0$。这是因为 $L$ 是有向无环图且 $L$ 中节点容量至少为 $p(r)$，所以我们一定能找到一条从 $s$ 经过 $r$ 到达 $t$ 的有向路径。那么我们让这条路上的边流量都增加 $p(r)$ 即可。这条路即为这一阶段的增广路。寻找增广路可以用 BFS。增广完之后所有满流边都可以从 $L$ 中删除，因为它们不会在此阶段后被使用。同样，所有与 $s$ 和 $t$ 不同且没有出边或入边的节点都可以删除。

#### 时间复杂度分析

MPM 算法的每个阶段都需要 $O(V^2)$，因为最多有 $V$ 次迭代（因为至少删除了所选的参考节点），并且在每次迭代中，我们删除除最多 $V$ 之外经过的所有边。求和，我们得到 $O(V^2+E)=O(V^2)$。由于阶段总数少于 $V$，因此 MPM 算法的总运行时间为 $O(V^3)$。

##### 阶段总数小于 V 的证明

MPM 算法在少于 $V$ 个阶段内结束。为了证明这一点，我们必须首先证明两个引理。

**引理 1**：每次迭代后，从 $s$ 到每个点的距离不会减少，也就是说，$level_{i+1}[v] \ge level_{i}[v]$。

**证明**：固定一个阶段 $i$ 和点 $v$。考虑 $G_{i}^R$ 中从 $s$ 到 $v$ 的任意最短路径 $P$。$P$ 的长度等于 $level_{i}[v]$。注意 $G_{i}^R$ 只能包含 $G_{i}^R$ 的后向边和前向边。如果 $P$ 没有 $G_{i}^R$ 的后边，那么 $level_{i+1}[v] \ge level_{i}[v]$。因为 $P$ 也是 $G_{i}^R$ 中的一条路径。现在，假设 $P$ 至少有一个后向边且第一个这样的边是 $(u,w)$，那么 $level_{i+1}[u] \ge level_{i}[u]$（因为第一种情况）。边 $(u,w)$ 不属于 $G_{i}^R$，因此 $(u,w)$ 受到前一次迭代的增广路的影响。这意味着 $level_{i}[u] = level_{i}[w]+1$。此外，$level_{i+1}[w] = level_{i+1}[u]+1$。从这两个方程和 $level_{i+1}[u] \ge level_{i}[u]$ 我们得到 $level_{i+1}[w] \ge level_{i}[w]+2$。路径的剩余部分也可以使用相同思想。

**引理 2**：$level_{i+1}[t] > level_{i}[t]$。

**证明**：从引理一我们得出，$level_{i+1}[t] \ge level_{i}[t]$。假设 $level_{i+1}[t] = level_{i}[t]$，注意 $G_{i}^R$ 只能包含 $G_{i}^R$ 的后向边和前向边。这意味着 $G_{i}^R$ 中有一条最短路径未被增广路阻塞。这就形成了矛盾。

#### 实现

??? note "参考代码"
    ```cpp
    struct MPM {
      struct FlowEdge {
        int v, u;
        long long cap, flow;
    
        FlowEdge() {}
    
        FlowEdge(int _v, int _u, long long _cap, long long _flow)
            : v(_v), u(_u), cap(_cap), flow(_flow) {}
    
        FlowEdge(int _v, int _u, long long _cap)
            : v(_v), u(_u), cap(_cap), flow(0ll) {}
      };
    
      const long long flow_inf = 1e18;
      vector<FlowEdge> edges;
      vector<char> alive;
      vector<long long> pin, pout;
      vector<list<int> > in, out;
      vector<vector<int> > adj;
      vector<long long> ex;
      int n, m = 0;
      int s, t;
      vector<int> level;
      vector<int> q;
      int qh, qt;
    
      void resize(int _n) {
        n = _n;
        ex.resize(n);
        q.resize(n);
        pin.resize(n);
        pout.resize(n);
        adj.resize(n);
        level.resize(n);
        in.resize(n);
        out.resize(n);
      }
    
      MPM() {}
    
      MPM(int _n, int _s, int _t) {
        resize(_n);
        s = _s;
        t = _t;
      }
    
      void add_edge(int v, int u, long long cap) {
        edges.push_back(FlowEdge(v, u, cap));
        edges.push_back(FlowEdge(u, v, 0));
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
      }
    
      bool bfs() {
        while (qh < qt) {
          int v = q[qh++];
          for (int id : adj[v]) {
            if (edges[id].cap - edges[id].flow < 1) continue;
            if (level[edges[id].u] != -1) continue;
            level[edges[id].u] = level[v] + 1;
            q[qt++] = edges[id].u;
          }
        }
        return level[t] != -1;
      }
    
      long long pot(int v) { return min(pin[v], pout[v]); }
    
      void remove_node(int v) {
        for (int i : in[v]) {
          int u = edges[i].v;
          auto it = find(out[u].begin(), out[u].end(), i);
          out[u].erase(it);
          pout[u] -= edges[i].cap - edges[i].flow;
        }
        for (int i : out[v]) {
          int u = edges[i].u;
          auto it = find(in[u].begin(), in[u].end(), i);
          in[u].erase(it);
          pin[u] -= edges[i].cap - edges[i].flow;
        }
      }
    
      void push(int from, int to, long long f, bool forw) {
        qh = qt = 0;
        ex.assign(n, 0);
        ex[from] = f;
        q[qt++] = from;
        while (qh < qt) {
          int v = q[qh++];
          if (v == to) break;
          long long must = ex[v];
          auto it = forw ? out[v].begin() : in[v].begin();
          while (true) {
            int u = forw ? edges[*it].u : edges[*it].v;
            long long pushed = min(must, edges[*it].cap - edges[*it].flow);
            if (pushed == 0) break;
            if (forw) {
              pout[v] -= pushed;
              pin[u] -= pushed;
            } else {
              pin[v] -= pushed;
              pout[u] -= pushed;
            }
            if (ex[u] == 0) q[qt++] = u;
            ex[u] += pushed;
            edges[*it].flow += pushed;
            edges[(*it) ^ 1].flow -= pushed;
            must -= pushed;
            if (edges[*it].cap - edges[*it].flow == 0) {
              auto jt = it;
              ++jt;
              if (forw) {
                in[u].erase(find(in[u].begin(), in[u].end(), *it));
                out[v].erase(it);
              } else {
                out[u].erase(find(out[u].begin(), out[u].end(), *it));
                in[v].erase(it);
              }
              it = jt;
            } else
              break;
            if (!must) break;
          }
        }
      }
    
      long long flow() {
        long long ans = 0;
        while (true) {
          pin.assign(n, 0);
          pout.assign(n, 0);
          level.assign(n, -1);
          alive.assign(n, true);
          level[s] = 0;
          qh = 0;
          qt = 1;
          q[0] = s;
          if (!bfs()) break;
          for (int i = 0; i < n; i++) {
            out[i].clear();
            in[i].clear();
          }
          for (int i = 0; i < m; i++) {
            if (edges[i].cap - edges[i].flow == 0) continue;
            int v = edges[i].v, u = edges[i].u;
            if (level[v] + 1 == level[u] && (level[u] < level[t] || u == t)) {
              in[u].push_back(i);
              out[v].push_back(i);
              pin[u] += edges[i].cap - edges[i].flow;
              pout[v] += edges[i].cap - edges[i].flow;
            }
          }
          pin[s] = pout[t] = flow_inf;
          while (true) {
            int v = -1;
            for (int i = 0; i < n; i++) {
              if (!alive[i]) continue;
              if (v == -1 || pot(i) < pot(v)) v = i;
            }
            if (v == -1) break;
            if (pot(v) == 0) {
              alive[v] = false;
              remove_node(v);
              continue;
            }
            long long f = pot(v);
            ans += f;
            push(v, s, f, false);
            push(v, t, f, true);
            alive[v] = false;
            remove_node(v);
          }
        }
        return ans;
      }
    };
    ```

### ISAP

在 Dinic 算法中，我们每次求完增广路后都要跑 BFS 来分层，有没有更高效的方法呢？

答案就是下面要介绍的 ISAP 算法。

#### 过程

和 Dinic 算法一样，我们还是先跑 BFS 对图上的点进行分层，不过与 Dinic 略有不同的是，我们选择在反图上，从 $t$ 点向 $s$ 点进行 BFS。

执行完分层过程后，我们通过 DFS 来找增广路。

增广的过程和 Dinic 类似，我们只选择比当前点层数少 $1$ 的点来增广。

与 Dinic 不同的是，我们并不会重跑 BFS 来对图上的点重新分层，而是在增广的过程中就完成重分层过程。

具体来说，设 $i$ 号点的层为 $d_i$，当我们结束在 $i$ 号点的增广过程后，我们遍历残量网络上 $i$ 的所有出边，找到层最小的出点 $j$，随后令 $d_i \gets d_j+1$。特别地，若残量网络上 $i$ 无出边，则 $d_i \gets n$。

容易发现，当 $d_s \geq n$ 时，图上不存在增广路，此时即可终止算法。

和 Dinic 类似，ISAP 中也存在 **当前弧优化**。

而 ISAP 还存在另外一个优化，我们记录层数为 $i$ 的点的数量 $num_i$，每当将一个点的层数从 $x$ 更新到 $y$ 时，同时更新 $num$ 数组的值，若在更新后 $num_x=0$，则意味着图上出现了断层，无法再找到增广路，此时可以直接终止算法（实现时直接将 $d_s$ 标为 $n$），该优化被称为 **GAP 优化**。

#### 实现

??? note "参考代码"
    ```cpp
    struct Edge {
      int from, to, cap, flow;
    
      Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };
    
    bool operator<(const Edge& a, const Edge& b) {
      return a.from < b.from || (a.from == b.from && a.to < b.to);
    }
    
    struct ISAP {
      int n, m, s, t;
      vector<Edge> edges;
      vector<int> G[maxn];
      bool vis[maxn];
      int d[maxn];
      int cur[maxn];
      int p[maxn];
      int num[maxn];
    
      void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
      }
    
      bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = 1;
        d[t] = 0;
        while (!Q.empty()) {
          int x = Q.front();
          Q.pop();
          for (int i = 0; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i] ^ 1];
            if (!vis[e.from] && e.cap > e.flow) {
              vis[e.from] = 1;
              d[e.from] = d[x] + 1;
              Q.push(e.from);
            }
          }
        }
        return vis[s];
      }
    
      void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
      }
    
      int Augment() {
        int x = t, a = INF;
        while (x != s) {
          Edge& e = edges[p[x]];
          a = min(a, e.cap - e.flow);
          x = edges[p[x]].from;
        }
        x = t;
        while (x != s) {
          edges[p[x]].flow += a;
          edges[p[x] ^ 1].flow -= a;
          x = edges[p[x]].from;
        }
        return a;
      }
    
      int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        BFS();
        memset(num, 0, sizeof(num));
        for (int i = 0; i < n; i++) num[d[i]]++;
        int x = s;
        memset(cur, 0, sizeof(cur));
        while (d[s] < n) {
          if (x == t) {
            flow += Augment();
            x = s;
          }
          int ok = 0;
          for (int i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if (e.cap > e.flow && d[x] == d[e.to] + 1) {
              ok = 1;
              p[e.to] = G[x][i];
              cur[x] = i;
              x = e.to;
              break;
            }
          }
          if (!ok) {
            int m = n - 1;
            for (int i = 0; i < G[x].size(); i++) {
              Edge& e = edges[G[x][i]];
              if (e.cap > e.flow) m = min(m, d[e.to]);
            }
            if (--num[d[x]] == 0) break;
            num[d[x] = m + 1]++;
            cur[x] = 0;
            if (x != s) x = edges[p[x]].from;
          }
        }
        return flow;
      }
    };
    ```

## Push-Relabel 预流推进算法

该方法在求解过程中忽略流守恒性，并每次对一个结点更新信息，以求解最大流。

### 通用的预流推进算法

首先我们介绍预流推进算法的主要思想，以及一个可行的暴力实现算法。

预流推进算法通过对单个结点的更新操作，直到没有结点需要更新来求解最大流。

算法过程维护的流函数不一定保持流守恒性，对于一个结点，我们允许进入结点的流超过流出结点的流，超过的部分被称为结点 $u(u\in V-\{s,t\})$ 的 **超额流**  $e(u)$：

$$
e(u)=\sum_{(x,u)\in E}f(x,u)-\sum_{(u,y)\in E}f(u,y)
$$

若 $e(u)>0$，称结点 $u$  **溢出**[^note1]，注意当我们提到溢出结点时，并不包括 $s$ 和 $t$。

预流推进算法维护每个结点的高度 $h(u)$，并且规定溢出的结点 $u$ 如果要推送超额流，只能向高度小于 $u$ 的结点推送；如果 $u$ 没有相邻的高度小于 $u$ 的结点，就修改 $u$ 的高度（重贴标签）。

#### 高度函数[^note2]

准确地说，预流推进维护以下的一个映射 $h:V\to \mathbf{N}$：

-   $h(s)=|V|,h(t)=0$
-   $\forall (u,v)\in E_f,h(u)\leq h(v)+1$

称 $h$ 是残量网络 $G_f=(V_f,E_f)$ 的高度函数。

引理 1：设 $G_f$ 上的高度函数为 $h$，对于任意两个结点 $u,v\in V$，如果 $h(u)>h(v)+1$，则 $(u,v)$ 不是 $G_f$ 中的边。

算法只会在 $h(u)=h(v)+1$ 的边执行推送。

#### 推送（Push）

适用条件：结点 $u$ 溢出，且存在结点 $v((u,v)\in E_f,c(u,v)-f(u,v)>0,h(u)=h(v)+1)$，则 push 操作适用于 $(u,v)$。

于是，我们尽可能将超额流从 $u$ 推送到 $v$，推送过程中我们只关心超额流和 $c(u,v)-f(u,v)$ 的最小值，不关心 $v$ 是否溢出。

如果 $(u,v)$ 在推送完之后满流，将其从残量网络中删除。

#### 重贴标签（Relabel）

适用条件：如果结点 $u$ 溢出，且 $\forall (u,v)\in E_f,h(u)\leq h(v)$，则 relabel 操作适用于 $u$。

则将 $h(u)$ 更新为 $\min_{(u,v)\in E_f}h(v)+1$ 即可。

#### 初始化

$$
\forall (u,v)\in E,~~f(u,v)=\begin{cases}
c(u,v),&u=s\\
0,&u\neq s
\end{cases}
$$

$$
\forall u\in V,~~h(u)=\begin{cases}
|V|,&u=s\\
0,&u\neq s
\end{cases}
$$

$$
e(u)=\sum_{(x,u)\in E}f(x,u)-\sum_{(u,y)\in E}f(u,y)
$$

上述将 $(s,v)\in E$ 充满流，并将 $h(s)$ 抬高，使得 $(s,v)\notin E_f$，因为 $h(s)>h(v)$，而且 $(s,v)$ 毕竟满流，没必要留在残量网络中；上述还将 $e(s)$ 初始化为 $\sum_{(s,v)\in E}f(s,v)$ 的相反数。

#### 过程

我们每次扫描整个图，只要存在结点 $u$ 满足 push 或 relabel 操作的条件，就执行对应的操作。

如图，每个结点中间表示编号，左下表示高度值 $h(u)$，右下表示超额流 $e(u)$，结点颜色的深度也表示结点的高度；边权表示 $c(u,v)-f(u,v)$，绿色的边表示满足 $h(u)=h(v)+1$ 的边 $(u,v)$（即残量网络的边 $E_f$）：

![p1](./images/2148.png)

整个算法我们大致浏览一下过程，这里笔者使用的是一个暴力算法，即暴力扫描是否有溢出的结点，有就更新

![p2](./images/2149.gif)

最后的结果

![p3](./images/2150.png)

可以发现，最后的超额流一部分回到了 $s$，且除了源点汇点，其他结点都没有溢出；这时的流函数 $f$ 满足流守恒性，为最大流，流量即为 $e(t)$。

但是实际上论文[^ref1]指出只处理高度小于 $n$ 的溢出节点也能获得正确的最大流值，不过这样一来算法结束的时候预流还不满足流函数性质，不能知道每条边上真实的流量。

#### 实现

???+ "核心代码"
    ```cpp
    const int N = 1e4 + 4, M = 1e5 + 5, INF = 0x3f3f3f3f;
    int n, m, s, t, maxflow, tot;
    int ht[N], ex[N];
    
    void init() {  // 初始化
      for (int i = h[s]; i; i = e[i].nex) {
        const int &v = e[i].t;
        ex[v] = e[i].v, ex[s] -= ex[v], e[i ^ 1].v = e[i].v, e[i].v = 0;
      }
      ht[s] = n;
    }
    
    bool push(int ed) {
      const int &u = e[ed ^ 1].t, &v = e[ed].t;
      int flow = min(ex[u], e[ed].v);
      ex[u] -= flow, ex[v] += flow, e[ed].v -= flow, e[ed ^ 1].v += flow;
      return ex[u];  // 如果 u 仍溢出，返回 1
    }
    
    void relabel(int u) {
      ht[u] = INF;
      for (int i = h[u]; i; i = e[i].nex)
        if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
      ++ht[u];
    }
    ```

### HLPP 算法

最高标号预流推进算法（Highest Label Preflow Push）在上述通用的预流推送算法中，在每次选择结点时，都优先选择高度最高的溢出结点，其算法算法复杂度为 $O(n^2\sqrt m)$。

#### 过程

具体地说，HLPP 算法过程如下：

1.  初始化（基于预流推进算法）；
2.  选择溢出结点中高度最高的结点 $u$，并对它所有可以推送的边进行推送；
3.  如果 $u$ 仍溢出，对它重贴标签，回到步骤 2；
4.  如果没有溢出的结点，算法结束。

一篇对最大流算法实际表现进行测试的论文[^ref2]表明，实际上基于预流的算法，有相当一部分时间都花在了重贴标签这一步上。以下介绍两种来自论文[^ref3]的能显著减少重贴标签次数的优化。

#### BFS 优化

HLPP 的上界为 $O(n^2\sqrt m)$，但在使用时卡得比较紧；我们可以在初始化高度的时候进行优化。具体来说，我们初始化 $h(u)$ 为 $u$ 到 $t$ 的最短距离；特别地，$h(s)=n$。

在 BFS 的同时我们顺便检查图的连通性，排除无解的情况。

#### GAP 优化

HLPP 推送的条件是 $h(u)=h(v)+1$，而如果在算法的某一时刻，存在某个 $k$，使得 $h(u)=k$ 的结点个数为 $0$，那么对于 $h(u)>k$ 的结点就永远无法推送超额流到 $t$，因此只能送回 $s$，那么我们就在这时直接让他们的高度变成至少 $n+1$，以尽快推送回 $s$，减少重贴标签的操作。

以下的实现采取论文[^ref2]中的实现方法，使用 $N*2-1$ 个桶 `B`，其中 `B[i]` 中记录所有当前高度为 $i$ 的溢出节点。加入了以上提到的两种优化，并且只处理了高度小于 $n$ 的溢出节点。

值得注意的是论文[^ref2]中使用的桶是基于链表的栈，而 STL 中的 `stack` 默认的容器是 `deque`。经过简单的测试发现 `vector`，`deque`，`list` 在本题的实际运行过程中效率区别不大。

#### 实现

??? "LuoguP4722【模板】最大流 加强版/预流推进"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    #include <stack>
    using namespace std;
    const int N = 1200, M = 120000, INF = 0x3f3f3f3f;
    int n, m, s, t;
    
    struct qxx {
      int nex, t;
      long long v;
    };
    
    qxx e[M * 2 + 1];
    int h[N + 1], cnt = 1;
    
    void add_path(int f, int t, long long v) {
      e[++cnt] = qxx{h[f], t, v}, h[f] = cnt;
    }
    
    void add_flow(int f, int t, long long v) {
      add_path(f, t, v);
      add_path(t, f, 0);
    }
    
    int ht[N + 1];        // 高度;
    long long ex[N + 1];  // 超额流;
    int gap[N];           // gap 优化. gap[i] 为高度为 i 的节点的数量
    stack<int> B[N];      // 桶 B[i] 中记录所有 ht[v]==i 的v
    int level = 0;        // 溢出节点的最高高度
    
    int push(int u) {      // 尽可能通过能够推送的边推送超额流
      bool init = u == s;  // 是否在初始化
      for (int i = h[u]; i; i = e[i].nex) {
        const int &v = e[i].t;
        const long long &w = e[i].v;
        // 初始化时不考虑高度差为1
        if (!w || (init == false && ht[u] != ht[v] + 1) || ht[v] == INF) continue;
        long long k = init ? w : min(w, ex[u]);
        // 取到剩余容量和超额流的最小值，初始化时可以使源的溢出量为负数。
        if (v != s && v != t && !ex[v]) B[ht[v]].push(v), level = max(level, ht[v]);
        ex[u] -= k, ex[v] += k, e[i].v -= k, e[i ^ 1].v += k;  // push
        if (!ex[u]) return 0;  // 如果已经推送完就返回
      }
      return 1;
    }
    
    void relabel(int u) {  // 重贴标签（高度）
      ht[u] = INF;
      for (int i = h[u]; i; i = e[i].nex)
        if (e[i].v) ht[u] = min(ht[u], ht[e[i].t]);
      if (++ht[u] < n) {  // 只处理高度小于 n 的节点
        B[ht[u]].push(u);
        level = max(level, ht[u]);
        ++gap[ht[u]];  // 新的高度，更新 gap
      }
    }
    
    bool bfs_init() {
      memset(ht, 0x3f, sizeof(ht));
      queue<int> q;
      q.push(t), ht[t] = 0;
      while (q.size()) {  // 反向 BFS, 遇到没有访问过的结点就入队
        int u = q.front();
        q.pop();
        for (int i = h[u]; i; i = e[i].nex) {
          const int &v = e[i].t;
          if (e[i ^ 1].v && ht[v] > ht[u] + 1) ht[v] = ht[u] + 1, q.push(v);
        }
      }
      return ht[s] != INF;  // 如果图不连通，返回 0
    }
    
    // 选出当前高度最大的节点之一, 如果已经没有溢出节点返回 0
    int select() {
      while (level > -1 && B[level].size() == 0) level--;
      return level == -1 ? 0 : B[level].top();
    }
    
    long long hlpp() {            // 返回最大流
      if (!bfs_init()) return 0;  // 图不连通
      memset(gap, 0, sizeof(gap));
      for (int i = 1; i <= n; i++)
        if (ht[i] != INF) gap[ht[i]]++;  // 初始化 gap
      ht[s] = n;
      push(s);  // 初始化预流
      int u;
      while ((u = select())) {
        B[level].pop();
        if (push(u)) {  // 仍然溢出
          if (!--gap[ht[u]])
            for (int i = 1; i <= n; i++)
              if (i != s && ht[i] > ht[u] && ht[i] < n + 1)
                ht[i] = n + 1;  // 这里重贴成 n+1 的节点都不是溢出节点
          relabel(u);
        }
      }
      return ex[t];
    }
    
    int main() {
      scanf("%d%d%d%d", &n, &m, &s, &t);
      for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add_flow(u, v, w);
      }
      printf("%lld", hlpp());
      return 0;
    }
    ```

感受一下运行过程

![HLPP](./images/1152.png)

其中 pic13 到 pic14 执行了 Relabel(4)，并进行了 GAP 优化。

## 脚注

[^ref_EK]: <http://pisces.ck.tp.edu.tw/~peng/index.php?action=showfile&file=f6cdf7ef750d7dc79c7d599b942acbaaee86a2e3e>

[^ref_Dinic]: <https://people.orie.cornell.edu/dpw/orie633/LectureNotes/lecture9.pdf>

[^ref1]: Cherkassky B V, Goldberg A V. On implementing push-relabel method for the maximum flow problem\[C]//International Conference on Integer Programming and Combinatorial Optimization. Springer, Berlin, Heidelberg, 1995: 157-171.

[^ref2]: Ahuja R K, Kodialam M, Mishra A K, et al. Computational investigations of maximum flow algorithms\[J]. European Journal of Operational Research, 1997, 97(3): 509-542.

[^ref3]: Derigs U, Meier W. Implementing Goldberg's max-flow-algorithm—A computational investigation\[J]. Zeitschrift für Operations Research, 1989, 33(6): 383-403.

[^note1]: 英语文献中通常称为「active」。

[^note2]: 在英语文献中，一个结点的高度通常被称为「distance label」。此处使用的「高度」这个术语源自算法导论中的相关章节。你可以在机械工业出版社算法导论（原书第 3 版）的 P432 脚注中找到这么做的理由。
