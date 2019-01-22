## 点着色

（讨论的是无环无向图）

对无向图顶点着色，且相邻顶点不能同色。若 $G$ 是 $k$ -可着色的，但不是 $(k-1)$ -可着色的，则称 $k$ 是 $G$ 的色数，记为 $\chi'(G)$。

对任意图 $G$，有 $\chi(G) \leq \Delta(G) + 1$，其中 $\Delta(G)$ 为最大度。

### Brooks 定理

设连通图不是完全图也不是奇圈，则 $\chi(G) \leq \Delta(G)$。

## 边着色

对无向图的边着色，要求相邻的边涂不同种颜色。若 $G$ 是 $k$ -边可着色的，但不是 $(k-1)$ -边可着色的，则称 $k$ 是 $G$ 的边色数，记为 $\chi'(G)$。

### Vizing 定理

设 $G$ 是简单图，则 $\Delta(G) \leq \chi'(G) \leq \Delta(G) + 1$

若 $G$ 是二部图，则 $\chi'(G)=\Delta(G)$

若 $n$ 为奇数（$n \neq 1$）时，$\chi'(K_n)=n$，当 $n$ 为偶数时，$\chi'(K_n)=n-1$

## 色多项式

$f(G,k)$ 表示 $G$ 的不同 $k$ 着色方式的总数。

$$f(K_n, k) = k(k-1)\cdots(k-n+1)$$

$$f(N_n, k) = k^n$$

在无向五环图 $G$ 中，

1. $e=(v_i, v_j) \notin E(G)$，则 $f(G, k) = f(G \cup (v_i, v_j), k)+f(G\backslash(v_i, v_j), k)$
2. $e=(v_i, v_j) \in E(G)$，则 $f(G,k)=f(G-e,k)-f(G\backslash e,k)$

定理：设 $V_1$ 是 $G$ 的点割集，且 $G[V_1]$ 是 $G$ 的 $|V_1|$ 阶完全子图，$G-V_1$有$p(p \geq 2)$ 个连通分支，则：

$$f(G,k)=\frac{\Pi_{i=1}^{p}{(f(H_i, k))}}{f(G[V_1], k)^{p-1}}$$

其中 $H_i=G[V_1 \cup V(G_i)]$

