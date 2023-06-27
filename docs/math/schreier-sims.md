## 引入

**Schreier–Sims 算法** 是计算群论的一种算法，以数学家 Otto Schreier 和 Charles Sims 的名字命名。它可以在多项式时间（polynomial time）内找到有限置换群的阶数、查看给定排列是否包含在群中以及其他许多任务。Schreier–Sims 算法最早由 Sims 在 1970 年基于 Schreier 的子群引理引入。1991 年，Donald Knuth 基于此改进了时序。后来，又有了该算法更快的随机版本。

???+ note "注释"
    **群论**（Group theory）是数学的一个分支。在数学和抽象代数中，群论研究称为群的代数结构。群是由一组元素和一个可以应用于该集合的两个元素的二元运算组成的系统。

## 背景

???+ note "注释"
    具体算法和时间复杂度分析请看之后章节，此节只是简单的背景介绍。

Schreier–Sims 算法是一种计算置换群的基强生成集（**BSGS**, base and strong generating set）的有效方法。特别是，SGS 确定了群的顺序并使查看给定排列是否包含在群中变得更加容易。由于 SGS 对于计算群论中的许多算法至关重要，因此计算机代数系统通常依赖 Schreier–Sims 算法进行群的有效计算。

Schreier–Sims 的运行时间因实现而异。令 $G\leq S_{n}$ 由 $t$ 个生成器给出。该算法可能的运行时间为：

-   $O(n^{2}\log ^{3}|G|+tn\log |G|)$ 需要 $O(n^{2}\log |G|+tn)$ 的内存；
-   $O(n^{3}\log ^{3}|G|+tn^{2}\log |G|)$ 需要 $O(n\log ^{2}|G|+tn)$ 的内存；

Schreier 向量的使用会对 Schreier–Sims 算法的实现性能产生重大影响。对于 Schreier–Sims 算法的 Monte Carlo 变体，预估复杂度如下：

-   $O(n\log n\log ^{4}|G|+tn\log |G|)$ 需要 $O(n\log |G|+tn)$ 的内存；

现代计算机代数系统（例如 GAP 和 Magma）通常使用优化过的蒙特卡罗算法。

## 定义

定义任意群 $G$ 是由一个子集 $S$ 生成，$G = \langle S \rangle$, 对于所有 $i$,$G$ 的每个元素都可以写成 $s_{1}, \cdots, s_{r}$ 与 $s_{i} \in S$ 或 $s_{i}^{-1} \in S$ 的乘积。

### Schreier 树

对于 $S$ 根为 $\alpha$ 的 **Schreier 树** 是 $α$ 轨道的如下表示：

-   Schreier 树是一棵以 $\alpha$ 为根，以 $\alpha^{G}$ 的元素为顶点的树，
-   它的边描述了从 $\alpha$ 到每个顶点所需的 $S$ 的元素，即树中的每条边 ${i, j}$，其中 比 $j$ 更靠近根的 $i$ 由生成器 $s \in S$ 标记，将 $i$ 移动到 $j$。
-   Schreier 树可以通过 **广度优先搜索** 或 **深度优先搜索** 从 $\alpha$ 开始用所有生成器 $s \in S$ 尝试到达新的节点 $\alpha^{s}$ 来找到。因此，计算 Schreier 树所需的时间以 $O(rn)$ 为界。这意味着我们可以以一种有效的方式找到 $|\alpha^{G}|$。

### Schreier 引理

Schreier 引理说明了如何使用 $\alpha$ 的 Schreier 树来查找稳定器 $G_{\alpha}$ 的生成器。

**Schreier 引理**：令 $G = \langle S \rangle$。那么由一组 Schreier 生成器生成的 $\alpha$ 稳定器 $G_{\alpha}$：

$$
G_{\alpha} = \langle t_{i}st_{i^{s}}^{-1} | i \in \alpha^{G}, s \in S \rangle
$$

其中 $t_{i}$ 被定义为将 $\alpha$ 移到 $i$ 的 $G$ 中一个元素，即 $i$ 的陪集（coset）代表。

### 强生成集

定义 $G$ 的 **基**（base）$B$ 为一个序列 $B = (b_{1},\cdots,b_{k}) \subseteq \Omega$, 因此逐点稳定器（pointwise stabilizer）$G_{b_{1},\cdots, b_{k}}$ 是可以忽略不计的。

定义 $G$ 相对于 $B$ 的 **强生成集**（SGS，strong generating set）是一个对于每个 $i$ 有 $\langle S \cap G^{(i)}\rangle = G(i)$ 的集合 $S \subseteq G$，其中 $G^{(i)} := G_{b1,\cdots,bi}$,$G^{(0)} := G$。

## 过程

用来计算排列群（permutation group）$G$ 阶数的 Schreier–Sims 算法一般有三种。它们同样也可以用来计算 $G$ 的基和强生成集。

### 基础 Schreier–Sims 算法

1.  如果 $G$ 为不平凡（non-trivial）群，选择一个尚未被选择的点 $b\in \Omega$。
2.  计算根为 $b$ 的 Schreier 树，得到 $|b^{G}|$。
3.  使用 Schreier 引理找到 $G_{b}$ 的生成器。
4.  对 $G_{b}$ 递归使此算法，到找到 $|G_{b}|$ 为止。

当算法结束时，$(b_{1},\cdots,b_{m})$ 是一个基，找到的所有生成器的并集是一个强生成集。

基础 Schreier–Sims 算法的运行时间是 **指数级** 的，但可以被优化成更高效的算法。

### 增量 Schreier–Sims 算法

**增量 Schreier–Sims 算法** 是常被用来构建强生成集的快速算法。

如果有一个群 $G$ 的强生成集，因为已经得到了所有 $G^{(i)}$ 稳定器的生成器，那么很容易得到 $G$ 的阶。**部分基**（partial base）$B = [b_{1},\cdots, b_{k}]$ 和部分强生成集 $S$ 是集合 $B \in \Omega$ 和集合 $S \subseteq G$，使得 $S$ 的任何元素都不能固定 $B$ 的每个元素。

增量 Schreier–Sims 算法可以将任意部分基和部分强生成集转化为基和强生成集。

定义 $T_{i+1}$ 为通过 Schreier 树 $G^{(i)}$ 对 $G^{(i+1)}$ 的陪集的作用。

1.  如果 $S = {}$，返回 $B, S$;
2.  非空部分基 $B = (b_{1},\cdots, b_{k}]$。部分强生成集 $S$。集 $C:= [b_{2},\cdots,b_{k}]$,$T := S \cap G_{b1}$，并递归地应用于输入 $C, T$，以将它们修改为 $H = \langle T \rangle$ 的基和强生成集。
3.  设 $B := B \cup C$,$S := S \cap T$。用筛选算法在 $H \leqslant G_{b_{1}}$ 中进行*成员资格测试*（Membership testing，检查集合（列表、集合、字典等）是否包含特定元素）。对 $G_{b_{1}}$ 测试每个 Schreier 生成器 $s$ 以查看 $s \in H$。如果都在 $H$ 中，那么有 $H = G_{b_{1}}$, 返回 $B，S$。否则到步骤 4。
4.  否则有一个 Schreier 生成器 $s \in G_{b_{1}}$ 但 $s \notin H$。设 $S := S \cup {s}$。如果 $s$ 固定了 $B$ 的所有点，将一个由 $s$ 移动的 $\Omega$ 点附加到 $B$。回到步骤 2。

当算法结束时，$B$ 为基，$S$ 是大小为 $O(n^{2}\log n)$ 的强生成集。

增量 Schreier–Sims 算法的运行时间为 $O(n^{8}\log^{3}n)$，即 $n$ 的多项式。$t$ 个生成器构建 Schreier 树需要 $O(n^{2}+nt)$，或对于 $t>n$ 为 $O(nt)$。因为已经用 $O(n^{2}\log n)$ 限制了 Schreier 生成器 $t$ 的数量，所以每个筛选过程都可以在 $nO(n(n^{2}\log n)) = O(n^{4}\log n)$ 中完成。

## 实现

以下为基础 Schreier–Sims 算法的参考代码。

??? note "参考代码"
    ```c++
    #include <iostream>
    using namespace std;
    
    const int maxn = 50;     // Maximum size of omega = {1, ,n}
    const int maxr = 10000;  // Maximum number of generators
    
    class Permutation {  // interface for permutations
     public:
      int p[maxn];  // the images of the points 0..   maxn-1
    
      Permutation() { n = maxn; };  // constructors
    
      Permutation(int m) { n = m; };
    
      Permutation(int m, char c) {
        n = m;
        switch (c) {
          case 'i':
            for (int i = 0; i < n; i++) p[i] = i;
            break;  // identity
          default:
            for (int i = 0; i < n; i++) p[i] = -1;
            break;  // undefined
        }
      }
    
      Permutation operator*(Permutation param) const {  // multiplication
        Permutation result(n);
        for (int i = 0; i < n; i++) result.p[i] = param.p[p[i]];
        return (result);
      }
    
      void operator*=(Permutation param) {  // direct multiplication
        for (int i = 0; i < n; i++) p[i] = param.p[p[i]];
      }
    
      Permutation inverse() const {  // inverse
        Permutation result(n);
        for (int i = 0; i < n; i++) result.p[p[i]] = i;
        return (result);
      }
    
      bool isdefined() const { return (p[0] > -1); }  // if it is     defined
    
      bool isidentity() const {  // if it is the     identity
        for (int i = 0; i < n; i++)
          if (p[i] != i) return false;
        return true;
      }
    
      bool operator==(Permutation param) const {  // comparison
        for (int i = 0; i < n; i++)
          if (param.p[i] != p[i]) return false;
        return true;
      }
    
      void input() {
        for (int i = 0; i < n; i++) {
          cin >> p[i];
          p[i]--;
        }
      }  // input
    
      void output() const {
        for (int i = 0; i < n; i++) cout << p[i] + 1 << " ";
        cout << endl;
      }  // output
    
      void setn(int m) { n = m; }
    
     private:
      int n;  // size of omega = {1, ,n}
    };
    
    int n;                                   // size of omega = {1, ,n}
    int r;                                   // number of generators
    Permutation* g = new Permutation[maxr];  // the generators
    int nr;
    Permutation* newg = new Permutation[maxr];
    int cosreps;  // number of    (= size of orbit of alpha)
    Permutation* cosrep =
        new Permutation[maxn];  // coset    representatives (to store the output of
                                // SchreierTree)
    Permutation undefined(maxn, 'u');
    
    /****** ScheierTree ******/
    void ScheierTree(
        int alpha) {  // depth first search to determine the orbit of     alpha
      static Permutation gen(
          n, 'i');    // group element moving original alpha to actual    alpha
      static int ag;  // image of actual alpha under generator g[j]
      cosrep[alpha] = gen;
      cosreps++;
      for (int j = 0; j < r; j++) {
        ag = g[j].p[alpha];
        if (!cosrep[ag].isdefined()) {
          gen *= g[j];
          ScheierTree(ag);
          gen *= g[j].inverse();
        }
      }
    }
    
    void SchreierSims() {
      int alpha = 0;
      Permutation sg;
      cout << "THE ORDER OF THE GROUP:\n";
      do {
        cosreps = 0;
        for (int i = 0; i < n; i++) cosrep[i] = undefined;
        // get the coset representatives for G(alpha)
        ScheierTree(alpha);
        // schreier lemma loop to get the schreier generators
        nr = 0;
        for (int i = 0; i < n; i++) {
          if (cosrep[i].isdefined())
            for (int j = 0; j < r; j++) {
              // calculate the (schreier) generators
              sg = cosrep[i] * g[j] * cosrep[g[j].p[i]].inverse();
              bool alreadyhavethis = sg.isidentity();
              for (int k = 0; k < nr; k++)
                if (sg == newg[k]) alreadyhavethis = true;
              if (!alreadyhavethis) newg[nr++] = sg;
            }
        }
        cout << cosreps << flush;
        if (cosreps > 1) cout << "*";
        r = 0;
        for (int j = 0; j < nr; j++) {
          g[r++] = newg[j];
        }
        alpha++;
      } while (cosreps > 1);
      cout << endl;
    }
    
    int main() {
      cout << "n ( Size of Omega = {1..n} ) ? ";
      cin >> n;
      for (int j = 0; j < n; j++) {
        g[j].setn(n);
        newg[j].setn(n);
      }
      undefined.setn(n);
    
      cout << "How many group generators ? ";
      cin >> r;
      for (int j = 0; j < r; j++) g[j].input();
    
      SchreierSims();
      delete[] g;
      delete[] newg;
      delete[] cosrep;
      return 0;
    }
    ```

## 例题

???+ note "[Grand Prix of Yekaterinburg 2015 Problem H Heimdall](http://opencup.ru/files/ocg/gp5/problems1-e.pdf)"
    海姆达尔——阿斯加德最伟大的儿子之一，众神和世界之树的守护者。自古以来古他的主要职责就是守卫阿斯嘉德的入口——一座世界之间的桥梁。现存唯一古老的技术是将一定数量的桥梁结合起来，创造出一座穿越中间世界的桥梁。例如：如果第一座桥将物质从世界 A 传输到世界 B，第二座桥——从 B 到 C，那么它们的组合可以直接将物质从世界 A 传输到世界 C. 而且，这个古老的技术甚至可以让你自己结合一座桥。海姆达尔想知道——使用他所知道的桥梁以及它们的组合，可以创造出多少不同的桥梁。输入两个整数 $R$,$N$ 分别是海姆达尔发现的桥梁总数和宇宙中的世界数（$1 \leqslant N \leqslant 15$,$1 \leqslant R \leqslant 1000$）。接下来的 R 行包含这些桥的信息。每个桥由 $N$ 个整数 $a_{1}, a_{2},\cdots a_{n}$ 组成。其中 $a_{i}$ 表示物质可以通过当前的桥梁转移到世界 $i$。如果当前的桥不影响那些世界，$a_{i} = i$。请输出一个可以通过古老技术建造的不同桥梁的总数。

## 参考资料与拓展阅读

1.  [Schreier–Sims algorithm - Wikipedia](https://en.wikipedia.org/wiki/Schreier%E2%80%93Sims_algorithm)
2.  Knuth, Donald E，[Efficient representation of perm groups](https://arxiv.org/abs/math/9201304), Combinatorica 11 (1991), no. 1, 33–43.
3.  Ákos Seress,[Permutation Group Algorithms](https://www.cambridge.org/core/books/permutation-group-algorithms/199629665EC545A10BCB99FFE6AAFD25), Cambridge University Press
4.  Sims, Charles C,[Computational methods in the study of permutation groups](https://www.sciencedirect.com/science/article/pii/B9780080129754500205), Computational Problems in Abstract Algebra, pp. 169–183, Pergamon, Oxford, 1970.
5.  Martin Jaggi,[Implementations of 3 Types of the Schreier-Sims Algorithm](https://www.m8j.net/data/List/Files-118/Documentation.pdf), MAS334 - Mathematics Computing Project, 2005
6.  [The Schreier-Sims algorithm for finite permutation groups](https://blogs.cs.st-andrews.ac.uk/codima/files/2015/11/CoDiMa2015_Holt.pdf)
7.  Henrik B¨a¨arnhielm,[The Schreier-Sims algorithm for matrix groups](https://henrik.baarnhielm.net/schreiersims.pdf)
