author: codewasp942, Tiphereth-A

## 定义

线性空间是线性代数的基本概念与重要研究对象。线性空间是由向量集合 $V$、域 $\Bbb{P}$、加法运算 $+$ 和标量乘法组成的代数结构。域的定义详见 [群论简介](/math/group-theory/)。

具体来说，对于集合 $V$、域 $\Bbb{P}$，定义了以下封闭的运算：

- 加法运算：$+:V\times V\mapsto V$，记为 $u+v$，其中 $u,v\in V$
- 标量乘法：$\cdot:\Bbb{P}\times V\mapsto V$，记为 $p\cdot v$ 或 $pv$，其中 $p\in \Bbb{P},v\in V$

且满足以下公理：

1. **加法交换律**：$\forall \mathbf u,\mathbf v\in V$，$\mathbf u+\mathbf v=\mathbf v+\mathbf u$
2. **加法结合律**：$\forall\mathbf u,\mathbf v,\mathbf w\in V$，$\mathbf u+(\mathbf v+\mathbf w)=(\mathbf u+\mathbf v)+\mathbf w$
3. **加法单位元**：$\exist\mathbf 0\in V$ 使得 $\forall \mathbf v\in V$，$\mathbf v+\mathbf 0=\mathbf v$. 称 $\mathbf 0$ 为零向量，也可写作 $\mathbf\theta$
4. **加法逆元**：$\forall \mathbf u\in V$，有 $v\in V$ 使 $u+v=\mathbf 0$
5. **标量乘法分配于向量加法上**：对于 $\mathbf u,\mathbf v\in V,a\in \Bbb{P}$，$a(\mathbf u+\mathbf v)=a\mathbf u+a\mathbf v$
6. **标量乘法分配于域加法上**：对于 $a,b\in \Bbb{P},\mathbf u\in V$，$(a+b)\mathbf u=a\mathbf u+b\mathbf u$
7. **标量乘法一致于域乘法**：对于 $a,b\in \Bbb{P},\mathbf u\in V$，$a(b\mathbf u)=(ab)\mathbf u$
8. **标量乘法单位元**：令 $1\in \Bbb{P}$ 是 $\Bbb{P}$ 的乘法单位元，则对于 $u\in V$，$1\mathbf u=\mathbf u$

则称代数系统 $(V,+,\cdot,\mathbb{P})$ 是 $V$ 关于 $+,\cdot$ 构成 $\Bbb{P}$ 上的一个线性空间，$\Bbb{P}$ 为线性空间的基域，$V$ 中元素称为 **向量**。

不管是一列数还是箭头，或是别的什么东西，只要满足上述公理，都可以认为是向量，也就都可以利用线性代数的理论来研究。

### 直观理解

不是很严谨地说，标量乘法对应着一种「**缩放**」，基域 $\Bbb{P}$ 中的元素就代表着缩放的「**比例**」，向量加法对应「**叠加**」。同时，$\Bbb{P}$ 中的元素还代表着向量的「**坐标**」的取值范围。

公理 1-4 描述的是向量加法的性质，包括交换律、结合律、单位元、逆元等。这些公理等价于 $(V,+)$ 是一个阿贝尔群。

公理 5-8 描述的是“缩放”与“叠加”的关联。可以结合二维平面上的箭头来理解。

### 例子

1. $\Bbb{P}^n$ 关于数域 $\Bbb{P}$ 上的加法和乘法构成 $\Bbb{P}$ 上的一个线性空间。例如 $\Bbb{P}$ 可以是 $\R$, $\Complex$, $\N_p$($p$ 为素数) 等
1. 数域 $\Bbb{P}$ 上的 $n\times m$ 阶矩阵 $\Bbb{P}^{n\times m}$ 关于矩阵的加法和数乘构成 $\Bbb{P}$ 上的一个线性空间。
1. 区间 $[a,b]$ 上的全体连续函数（记作 $C[a,b]$）关于「函数加法」和「值与连续函数的数乘」构成值域上的一个线性空间。
