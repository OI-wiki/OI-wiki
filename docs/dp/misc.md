author: Chihaya-Yuka

## FFTDP

FFTDP 是 [Sciencefactory](https://sciencefactory.it.com) 设计的新 DP 算法，详细介绍在 [Paper](https://github.com/Lumen-Laboratory/sciencefactory.it.com/blob/main/paper/computerscience/sf0003.0001.md) 中。其核心思想为将每个物品的“选取方式”用生成函数进行建模，并将求解问题转化为多项式的乘积问题。利用卷积定理，可以将多项式乘法转化为频域上的点乘，从而借助 FFT 将卷积运算的时间复杂度降至 $O(M \log M)$（其中 $M$ 为多项式的长度）。
