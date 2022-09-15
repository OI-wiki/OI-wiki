author: codewasp942, Tiphereth-A

## 定义

线性空间（向量空间）是线性代数的基本概念与重要研究对象。线性空间是由向量集合 $V$、数域 $\Bbb{P}$、加法运算 $+$ 和标量乘法组成的模类代数结构。域的定义详见 [群论简介](./../group-theory.md)。

具体来说，对于集合 $V$、域 $\Bbb{P}$，定义了以下封闭的运算：

- 加法运算：$+:V\times V\mapsto V$，记为 $u+v$，其中 $u,v\in V$
- 标量乘法：$\cdot:\Bbb{P}\times V\mapsto V$，记为 $p\cdot v$ 或 $pv$，其中 $p\in \Bbb{P},v\in V$

且满足以下公理：

1. **加法交换律**：$\forall \mathbf u,\mathbf v\in V$，$\mathbf u+\mathbf v=\mathbf v+\mathbf u$
2. **加法结合律**：$\forall\mathbf u,\mathbf v,\mathbf w\in V$，$\mathbf u+(\mathbf v+\mathbf w)=(\mathbf u+\mathbf v)+\mathbf w$
3. **加法单位元**：$\exists\mathbf 0\in V$ 使得 $\forall \mathbf v\in V$，$\mathbf v+\mathbf 0=\mathbf v$. 称 $\mathbf 0$ 为零向量，也可写作 $\mathbf\theta$
4. **加法逆元**：$\forall \mathbf u\in V$，有 $v\in V$ 使 $u+v=\mathbf 0$
5. **标量乘法分配于向量加法上**：对于 $\mathbf u,\mathbf v\in V,a\in \Bbb{P}$，$a(\mathbf u+\mathbf v)=a\mathbf u+a\mathbf v$
6. **标量乘法分配于域加法上**：对于 $a,b\in \Bbb{P},\mathbf u\in V$，$(a+b)\mathbf u=a\mathbf u+b\mathbf u$
7. **标量乘法一致于域乘法**：对于 $a,b\in \Bbb{P},\mathbf u\in V$，$a(b\mathbf u)=(ab)\mathbf u$
8. **标量乘法单位元**：令 $1\in \Bbb{P}$ 是 $\Bbb{P}$ 的乘法单位元，则对于 $u\in V$，$1\mathbf u=\mathbf u$

则称代数系统 $(V,+,\cdot,\mathbb{P})$ 是 $V$ 关于 $+,\cdot$ 构成 $\Bbb{P}$ 上的一个 **线性空间**，$\Bbb{P}$ 为线性空间的 **基域**，$V$ 中元素称为 **向量**。

不管是一列数还是箭头，或是别的什么东西，只要满足上述公理，都可以认为是向量，也就都可以利用线性代数的理论来研究。

???+note
    为行文方便，下文中：
    
    1. 对 $V$ 中的元素不做加粗处理。
    2. 将满足线性空间定义的代数系统 $(V,+,\cdot,\mathbb{P})$ 也称为线性空间。
    
    请注意区分。

### 直观理解

不是很严谨地说，标量乘法对应着一种「**缩放**」，基域 $\Bbb{P}$ 中的元素就代表着缩放的「**比例**」，向量加法对应「**叠加**」。同时，$\Bbb{P}$ 中的元素还代表着向量的「**坐标**」的取值范围。

公理 1-4 描述的是向量加法的性质，包括交换律、结合律、单位元、逆元等。这些公理等价于 $(V,+)$ 是一个阿贝尔群。

公理 5-8 描述的是“缩放”与“叠加”的关联。可以结合二维平面上的箭头来理解。

### 简单性质

???+note
    以下性质可在群论等中找到。

对线性空间 $(V,+,\cdot,\Bbb{P})$,

1. $\theta$ 唯一。
1. $\forall\alpha\in V$, $-\alpha$ 唯一。
1. $\exists 0\in\mathbb{P}$, $\forall\alpha\in V$, 有 $0\alpha=\theta$.
1. $\forall k\in\mathbb{P}$, 有 $k\theta=\theta$.
1. $(-1)\alpha=-\alpha,~\forall\alpha\in V$.
1. 无零因子：$\forall\alpha\in V,k\in\mathbb{P}$, 有 $k\alpha=\theta\implies k=0\lor\alpha=\theta$.
1. 加法的消去律：$\forall\alpha,\beta,\gamma\in V$, 有 $\alpha+\beta=\alpha+\gamma\implies\beta=\gamma$.
   
   > 实际上，加法的消去律可以替换定义中的「加法单位元」和「加法逆元」两条。


### 例子

1. $\Bbb{P}^n$ 关于数域 $\Bbb{P}$ 上的加法和乘法构成 $\Bbb{P}$ 上的一个线性空间。例如 $\Bbb{P}$ 可以是 $\Bbb{R}$, $\Bbb{C}$, $\Bbb{N}_p$($p$ 为素数) 等
1. 数域 $\Bbb{P}$ 上的 $n\times m$ 阶矩阵 $\Bbb{P}^{n\times m}$ 关于矩阵的加法和数乘构成 $\Bbb{P}$ 上的一个线性空间。
1. 数域 $\Bbb{P}$ 上的一元多项式环 $\Bbb{P}[x]$ 关于多项式的加法和数乘构成 $\Bbb{P}$ 上的一个线性空间。
1. 区间 $[a,b]$ 上的全体连续函数（记作 $C[a,b]$）关于「函数加法」和「值与连续函数的数乘」构成值域上的一个线性空间。

## 相关概念

### 线性相关、线性无关

对线性空间 $(V,+,\cdot,\Bbb{P})$,

1. 称 $a_1,a_2,\dots,a_n\in V$ 为 $V$ 的一个 **向量组**。
1. 对于 $k_1,k_2,\dots,k_n\in\Bbb{P}$, 称 $\sum_{i=1}^nk_ia_i$ 为向量组 $a_1,a_2,\dots,a_n$ 的一个 **线性组合**。
1. 若向量 $\beta\in V$ 可以表示为向量组 $a_1,a_2,\dots,a_n$ 的一个线性组合，则称 $\beta$ 能被向量组 $a_1,a_2,\dots,a_n$ **线性表出**。
1. 对于 $k_1,k_2,\dots,k_n\in\Bbb{P}$, 若向量组 $a_1,a_2,\dots,a_n$ 满足 $\sum_{i=1}^nk_ia_i=\theta\iff k_i=0, i=1,2,\dots,n$, 则称向量组 $a_1,a_2,\dots,a_n$ **线性无关**，否则称向量组 $a_1,a_2,\dots,a_n$ **线性相关**。

#### 性质

对线性空间 $(V,+,\cdot,\Bbb{P})$,

1. 若向量组的一部分线性相关，则向量组线性相关。

   若向量组线性无关，则其任意非空部分均线性无关。

1. 含 $\theta$ 的向量组线性相关。
1. 向量组线性相关当且仅当向量组的某个向量可以由其余向量线性表出。
1. 若向量 $\beta$ 可被向量组 $a_1,a_2,\dots,a_n$ 线性表出，则表出方式唯一当且仅当向量组 $a_1,a_2,\dots,a_n$ 线性无关。
1. 若向量组 $a_1,a_2,\dots,a_n$ 线性无关，则向量 $\beta$ 可被向量组 $a_1,a_2,\dots,a_n$ 线性表出当且仅当向量组 $a_1,a_2,\dots,a_n,\beta$ 线性相关。

### 极大线性无关组、秩

对线性空间 $(V,+,\cdot,\Bbb{P})$,

1. 对于向量组 $b_1,b_2,\dots,b_m$, 令 $\{a_1,a_2,\dots,a_n\}\subseteq\{b_1,b_2,\dots,b_m\}$, 若

   - 向量组 $a_1,a_2,\dots,a_n$ 线性无关。
   - $\forall\beta\in\{b_1,b_2,\dots,b_m\}\setminus\{a_1,a_2,\dots,a_n\}$, 向量组 $a_1,a_2,\dots,a_n,\beta$ 线性相关。

   则称向量组 $a_1,a_2,\dots,a_n$ 为向量组 $b_1,b_2,\dots,b_m$ 中的一个 **极大线性无关组**。类似地，可定义线性空间 $V$ 的极大线性无关组。

   规定向量组 $\theta,\theta,\dots,\theta$ 的极大线性无关组为空集。

   称向量组 $b_1,b_2,\dots,b_m$ 的极大线性无关组的大小为向量组的 **秩**，记作 $\operatorname{rank}\{b_1,b_2,\dots,b_m\}$, 规定 $\operatorname{rank}\{\theta,\theta,\dots,\theta\}=0$.

1. 若向量组 $a_1,a_2,\dots,a_n$ 能线性表出向量组 $b_1,b_2,\dots,b_m$ 中的所有向量，称向量组 $b_1,b_2,\dots,b_m$ 能被向量组 $a_1,a_2,\dots,a_n$ 线性表出。
1. 若向量组 $a_1,a_2,\dots,a_n$ 能被向量组 $b_1,b_2,\dots,b_m$ 线性表出，且向量组 $b_1,b_2,\dots,b_m$ 能被向量组 $a_1,a_2,\dots,a_n$ 线性表出，则称两向量组 **等价**，记作 $\{a_1,a_2,\dots,a_n\}\cong\{b_1,b_2,\dots,b_m\}$

#### 性质

对线性空间 $(V,+,\cdot,\Bbb{P})$,

1. 设向量组 $a_1,a_2,\dots,a_n$ 能被线性表出向量组 $b_1,b_2,\dots,b_m$ 线性表出。
   - 若 $n>m$, 则向量组 $a_1,a_2,\dots,a_n$ 线性相关。
   - 若向量组 $a_1,a_2,\dots,a_n$ 线性无关，则 $n\leq m$.
1. 等价的线性无关向量组的大小相等。

    向量组的任意极大线性无关组的大小均相等。

1. 向量组线性无关当且仅当其秩等于其大小。
1. 若向量组 $a_1,a_2,\dots,a_n$ 能被线性表出向量组 $b_1,b_2,\dots,b_m$ 线性表出，则 $\operatorname{rank}\{a_1,a_2,\dots,a_n\}\leq\operatorname{rank}\{b_1,b_2,\dots,b_m\}$.
1. 等价的向量组的秩相等。

### 线性包

对线性空间 $(V,+,\cdot,\Bbb{P})$, 称 $\left\{v=\sum_{i=1}^nk_ia_i:a_i\in V,k_i\in\Bbb{P},i=1,2,\dots,n\right\}$ 为由向量组 $a_1,a_2,\dots,a_n$ 张成的线性空间（或**线性包**），记作 $\operatorname{span}\{a_1,a_2,\dots,a_n\}$.

### 线性子空间

对线性空间 $(V,+,\cdot,\Bbb{P})$, 若代数系统 $(V_1,+,\cdot,\Bbb{P})$ 满足：

1. $\varnothing\ne V_1$.
1. $V_1\subseteq V$.
1. $V_1$ 关于 $+,\cdot$ 构成$\mathbb{P}$上的线性空间。

则称 $V_1$ 为 $V$ 的线性子空间，记作 $V_1\leq V$.

若第 2 条中的 $\subseteq$ 换为 $\subset$, 则称 $V_1$ 为 $V$ 的线性真子空间，记作 $V_1<V$.

不难证明：线性空间 $V$ 的非空子集 $V_1$ 是其线性子空间当且仅当加法和数乘在 $V_1$ 上封闭，即：

1. $\forall u,v\in V_1$, $u+v\in V_1$.
1. $\forall v\in V_1$, $\forall k\in \Bbb{P}$, $kv\in V_1$.

### 交、和与直和、直积

对线性空间 $(V_1,+,\cdot,\Bbb{P})$ 与 $(V_2,+,\cdot,\Bbb{P})$,

1. 不难验证：加法和数乘在 $V_1\cap V_2$ 上封闭，故可称 $V_1\cap V_2$ 为线性空间 $V_1$ 和 $V_2$ 的**交**。
   
    类似地，可定义多个线性空间的交 $\bigcap_{i=1}^m V_i$.
1. 若线性空间 $V$ 满足 $V=\{u+v|u\in V_1,v\in V_2\}$, 则称 $V$ 为线性空间 $V_1$ 和 $V_2$ 的**和**，记为 $V=V_1+V_2$.

    可以验证：$V_1+V_2$ 是包含 $V_1\cup V_2$ 的最小子空间。

    类似地，可定义多个线性空间的和 $\sum_{i=1}^m V_i$.
1. 设 $V=V_1+V_2$, 若线性空间 $V$ 中的任意元素 $v$, 均只能找到唯一一组向量 $v_1,v_2$ 满足 $v=v_1+v_2$, 则称 $V$ 为线性空间 $V_1$ 和 $V_2$ 的**直和** (direct sum)，记为 $V_1\oplus V_2$.

    类似地，可定义多个线性空间的直和 $\bigoplus_{i=1}^m V_i$.
1. $V_1$ 与 $V_2$ 的 **直积** $V_1\times V_2$ 定义为二者的笛卡儿积关于如下的加法和数乘构成 $\Bbb{P}$ 上的线性空间：
   1. $+:(V_1\times V_2)\times(V_1\times V_2)\mapsto V_1\times V_2; ((u_1,v_1),(u_2,v_2))\to (u_1+u_2,v_1+v_2)$
   1. $\cdot:\Bbb{P}\times(V_1\times V_2)\mapsto V_1\times V_2; (k,(u,u))\to (ku,kv)$
    
    类似地，可定义多个线性空间的直积 $\prod_{i=1}^m V_i$.

#### 例子

对于线性空间 $V=\Bbb{R}^3$, 设线性空间

- $V_1:=\{(x,0,0)|x\in\Bbb{R}\}$.
- $V_2:=\{(x,y,0)|x,y\in\Bbb{R}\}$.
- $V_3:=\{(0,y,z)|y,z\in\Bbb{R}\}$.
- $V_4:=\{(x,0,z)|x,z\in\Bbb{R}\}$.

则：

1. $V_1<V_2<V$, $V_3<V$.
1. $V_2=V_1+V_2$.
1. $V=V_1\oplus V_3=V_2+V_3$.
1. $V_2\oplus V_3=V_4$, $V_2\oplus V_4=V_3$, $V_3\oplus V_4=V_2$.
1. $V_2+V_3\leq V$.

#### 性质

1. 令 $V_1,V_2,V_3$ 是关于 $\Bbb{P}$ 的线性空间，和集合的交一样，线性空间的交适用如下法则：
   1. 交换律：$V_1\cap V_2=V_2\cap V_1$.
   1. 结合律：$V_1\cap(V_2\cap V_3)=(V_1\cap V_2)\cap V_3$.
1. 令 $V_1,V_2,V_3$ 是关于 $\Bbb{P}$ 的线性空间，类似于集合的并，线性空间的和适用如下法则：
   1. 交换律：$V_1+V_2=V_2+V_1$.
   1. 结合律：$V_1+(V_2+V_3)=(V_1+V_2)+V_3$.
1. 令 $V_1,V_2,V_3$ 是关于 $\Bbb{P}$ 的线性空间，线性空间的交与并有如下关系：
   1. $V_1\cap (V_2+V_3)\supseteq (V_1\cap V_2)+(V_1\cap V_3)$.
   1. $V_1+(V_2\cap V_3)\subseteq (V_1+V_2)\cap (V_1+V_3)$.
1. 令 $V$ 是关于 $\Bbb{P}$ 的线性空间，$V_1,V_2\leqslant V$, 则下列诸款等价：

   1. $V_1+V_2=V_1\oplus V_2$.
   2. $\exists \beta\in V_1+V_2$, 使得拆分为 $V_1$ 和 $V_2$ 中的向量和的方式唯一（任意 $\to$ 存在）。
   3. $\theta$ 拆分为 $V_1$ 和 $V_2$ 中向量的和的方式唯一。
   4. $V_1\cap V_2=\{\theta\}$.

   ???+note "证明"
        $1\implies 2$: 由定义立得。
        
        $2 \implies 3$:
        
        令 $\beta=\beta_1+\beta_2$, 其中 $\beta_1\in V_1, \beta_2\in V_2$, 若 $\theta=\alpha_1+\alpha_2$, $\theta\ne\alpha_1\in V_1,\alpha_2\in V_2$, 则 $\beta=\beta+\theta=(\beta_1+\alpha_1)+(\beta_2+\alpha_2)$.
        
        而 $\beta_1\ne\beta_1+\alpha_1$, 与条件矛盾。
        
        $3 \implies 4$:
        
        在 $V_1$ 和 $V_2$ 中取一非零向量 $\alpha$, 则 $\theta=\alpha+(-\alpha)=(-\alpha)+\alpha$, 这与条件矛盾。
        
        $4 \implies 1$:
        
        若 $V_1+V_2$ 不是直和, 则存在 $\beta\in V_1+V_2$ 使得$\beta=\beta_1+\beta_2=\gamma_1+\gamma_2$, 其中 $\beta_1,\gamma_1\in V_1,\beta_2,\gamma_2\in V_2$ 且 $\beta_1,\beta_2,\gamma_1,\gamma_2)$ 互不相同。
        
        进而 $\theta\ne\beta_1-\gamma_1=\gamma_2-\beta_2\in V_1\cap V_2$, 与条件矛盾。

## 参考资料与注释

1. 丘维声, 高等代数（下）. 清华大学出版社.
1. [Vector space](https://en.wikipedia.org/w/index.php?title=Vector_space&oldid=1108546097). _Wikipedia, The Free Encyclopedia_.
