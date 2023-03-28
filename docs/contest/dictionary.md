前置知识：[分块](../ds/decompose.md)。

朴素的打表，指的是在比赛时把所有可能的输入对应的答案都计算出来并保存下来，然后在代码里开个数组把答案放里面，直接输出即可。

注意这个技巧只适用于输入的值域不大（如，输入只有一个数，而且范围很小）的问题，否则可能会导致代码过长、MLE、打表需要的时间过长等问题。

???+ note "例题 1"
    规定 $f(x)$ 为整数 $x$ 的二进制表示中 $1$ 的个数。输入一个正整数 $n$($n\leq 10^9$)，输出 $\sum_{i=1}^n f^2(i)$。

如果对于每一个 $n$，都输出 $f(n)$ 的话，除了可能会 MLE 外，还有可能代码超过最大代码长度限制，导致编译不通过。

我们考虑优化这个答案表。采用 [分块](../ds/decompose.md) 的思想，我们设置一个合理的步长 $m$（这个步长一般视代码长度而定），对于第 $i$ 块，计算出：

$$
\sum_{k=\frac{n}{m}(i-1)+1}^{\frac{ni}{m}} f^2(k)
$$

的值。

然后输出答案时采用分块思想处理即可。即，整块的答案用预处理的值计算，非整块的答案暴力计算。

一般来说，这样的问题对于处理单个函数值 $f(x)$ 很快，但是需要大量函数值求和（求积或某些可以快速合并的操作），枚举会超出时间限制，在找不到标准做法的情况下，分段打表是一个不错的选择。

???+ note "注意事项"
    当上题中指数不是定值，但是范围较小，也可以考虑打表。

???+ note "[例题 2 完全平方数](https://www.luogu.com.cn/problem/P4318)"
    求第 $n(n\le 10^9)$ 个不是 四以上完全平方数整倍数 的数。

既然值域在 $10^9$ 级别（而且题解也告诉我们这个 答案最大值略小于  $1.65\times 10^9$），就可以考虑直接 **暴力计算 + 分块处理**。

本题之中按照 $len$ 个数一段分块（这里我是钦定 $len=10^5$），先是二分跳跃到右端点刚好大于等于 $n$ 的这一块（前面所有块的和可以直接统计），然后暴力计算该块之内非完全平方数倍数的个数并且直接得出答案。使用区间筛法来解决问题，这里不做赘述。

这里为了减少程序篇幅，可以考虑数据压缩。

首先考虑计算一段长度为 $len$ 的区间之内完全平方数的个数（为了算出非完全平方数的个数），我在取 $len=10^5$ 的情况下观察到了这些数据的取值在 $[39170,39240]$ 之间，在取 $len=10^6$ 的情况下观察到了这些数据的取值在 $[392000,392127]$ 之间。在处理 $len=10^5$ 时候，为了方便存储，把所有数据减去 $39170$，加上 $48$（这样就变成了 **可见字符** 了），按照字符串存储。在处理 $len=10^6$ 的时候就把所有数据减去 $392000$ 并且转成字符即可。

注意可见字符塞进程序之前需要 **判断转义字符**，比如 `\` 和 `"` 和 `'`。

为了精简篇幅，贴了 $len=10^6$ 的代码。而 $len=10^5$ 的代码可以拿十倍的代码长度换得十倍的运行速度。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef int I;
char a[1710] =
    "0J1h%gL5e=3INI_S]9X\'%HT`/"
    "`GGAOASML2XYVDHWAA2OKUG8TOCNJ0F9VQM=i(IMV?F8]PBHfMN<tFRV5;h\'U@"
    "\\QMATDPAKEe?2XDNXB-BOJGM=?VGE\\;4`2cFKABRV#F^HF;/TMO7JO2](UONQYKI3z!NLd4/"
    "Iq?M;R.aADbh>Z6ZHFZ@DUCO69HIf<ELOKEIh([4/"
    "ZM2AV=PO4Z:C:_NO]4<P8\\,`IKQV@D>N^L/"
    "uGAFZG2qHCNCTCBCGa8-J@OJ(KeC=]Q8B;SJN=l3N?ANDMCFz=S6HAM?r4UHBP."
    "MJHPFJJd51Y8a>_3FP\\6J,fDNSG<WLC;FO3[8HXLV\\JTJFR\\AC;\'P7SN:L<J\"Q^<?X "
    "L0K[GZGFCNG`CVTJAK\\&W>FB<TFV5MXV;R$ZMJ.J[J "
    "PIU7=`BTCc.hI2NHCO`!JLc7RMOLm+@JW&Sc3^oBDF4dB=@K.[\\V "
    "V;_;TRF\\FR9ONTWFVgUM=`InH<B@PF?7TYN;C6PO8O^82W@BGGQFa@mGFMEEd>%"
    "WECgHHRNa6KP?C=KL4iERO6O0QBKQOD?c3UTFDJO8~T-I[6NDT;H<Q\\aCJ3;HlM6M:UK=6:"
    "SA;OCRS=5HO5D[AGX5Eg@\'WGf7_(XG>\\:r*Y^+KUJQN2T1M2rLV2>M=INjAD@OEQT1Q6@WF?"
    "DOLoF@_LQ,MP+PKQ)Q[>n6ELYC5CDKEEAZ1YC\\GEQPI/"
    "rJ:.HO3^DG\\TXI0_%^9pOWMF@:EQa@OBF\'j6Q6S^D_JVRB=D<EKAPO)=wZ9Y=E<CH]"
    "BN2fF@GRGS/"
    "LQ?b?\\*0AQ]BC>F1U_SiC*Y4a2L6^[\\+D=@vO=<GJZJM3IO]4:PN92e@W[`KEFF@HU<C^"
    "N3NZ@-/g^M;,m2_9LBCQD4]bHUK<UR;U8:\\+N9^ "
    "KlY%XE4V:UF75PPUS^.=GI]<a7;S6QgBE:NP@jDB4?D\\[.ODaYM)]KEO5YAMOFQH*ZSDMZ@,"
    "WBBa8L[ZDP?BEMCJQ<NQHOIDFJ@>aGUDPA6LI@(d-u_7G+WGJS>Y1P^FQ;FY;[WOJ9gH@M@"
    "6W6/"
    "`-;_POTITV[(Q\'XN`OKHB?OEXG\\=ID?7<VHIQKVVK8:_G;J=S6E[<9B<@GF9ZER+"
    "AU\\PSK1GfVd4OJ8QCOOUJ;eHP@KSUDUTM)>e:OKOQQHEQ=1NN;QWN8UDRDEPMMU?QN8SS/"
    "J[9W7POWC7MB>HVP;>XS4>L^MGA\\J?>?CRTT3QNA>5*NdE-^CETU,OP2IGQTNPNICc/"
    "L:OGFNKJ`6D7S)TQT0HAN7I]84y?C=51XL@S6k;8Kb.X6LXU2AT1\\E-aGX5ZZLe,FDKVb0_"
    "HK]A6CRBOZ@\"MU@Z?^8Z2[.jJIDRQ<9jJEW84eQ>K@QDGS^4EU`*\\<.WMS7I-XQWOF:PN/"
    "ZCLOAh/"
    "PQ>V9mBG45?d-EIaD_:P<@dD@QA6cPTE[Ba:TR5ACDIN@0[,TTX(ZKGJ=dT:P:Y<"
    "DJFJNfJfE8E9GXJD1T\"2\\_?OFMEf6QOL9>CV@CMQEWIF,W`ALTUe,;UDO8M9?DMUEA>"
    "K2P7e>^=Bf:@NXZVM:ZOMDD^;?JJL>P]IW83GHBS2NAL;hSG>S8[9<=ZD;UUQS;WJO:1M?@"
    "Tm3E\\78NQ2UbL^2[FGR:5SA;U-NCJZXRf1;J=R3c9WG?k%`MU@W0C<NQ^BR?<6MJI_G<"
    "K4GWZKQKIJ8J;U9OXK>>R`4MB\\4T?_:";
I s[1710];
const I BL = 1e6;
bitset<BL> b;

I sol(I n) {
  I p = lower_bound(s + 1, s + 1701, n) - s;
  I l = (p - 1) * BL + 1, r = p * BL, cnt = 0;
  b.reset();
  for (I i = 2; 1ll * i * i <= r; ++i)
    for (I j = ceil(l * 1.0 / i / i); 1ll * j * i * i <= r; ++j)
      b[i * i * j - l] = 1;
  for (I i = l; i <= r; ++i)
    if (!b[i - l]) {
      cnt++;
      if (cnt == n - s[p - 1]) return i;
    }
  return -114514;
}

int main() {
  for (I i = 1; i <= 1700; ++i) s[i] = s[i - 1] + BL - (392000 + a[i]);
  I T, n;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    printf("%d\n", sol(n));
  }
  return 0;
}
```

### 例题

[「BZOJ 3798」特殊的质数](https://hydro.ac/d/bzoj/p/3798)：求 $[l,r]$ 区间内有多少个质数可以分解为两个正整数的平方和。

[「Luogu P1822」魔法指纹](https://www.luogu.com.cn/problem/show?pid=P1822)
