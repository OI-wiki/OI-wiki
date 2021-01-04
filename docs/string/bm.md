author: minghu6

*本章节内容以 [《前缀函数与 KMP 算法》](./kmp.md) 作为前置章节。*

之前的 KMP 算法将前缀匹配的信息用到了极致，而 BM 算法背后的基本思想是通过后缀匹配获得比前缀匹配更多的信息来实现更快的字符跳转。

## 约定

对于字符串 $S$：

- $S$ 以 $1$ 为下标开头。
- 记其长度为 $|S|$。

定义 $S$ 的周期是一个长度最短的串 $U$ 使得 $S$ 是 $UUU\cdots$  的前缀。

$\Sigma$ 表示字符集。

## 引入

考虑从左到右匹配。但是我们匹配的时候是从右到左比较字符是否相同。举个例子：

$$
\begin{aligned}
\textit{S}:\quad &\texttt{HERE_I}{\color{blue}{\texttt{S}}}\texttt{_A_SIMPLE_EXAMPLE} \\
\textit{T}:\quad &\texttt{EXAMPL}{\color{blue}{\texttt{E}}} \\
\end{aligned}
$$

这时 $T$ 的最后一个字符 `E` 与 `S` 不匹配。而且 `S` 没有在 $T$ 中出现。因此我们把 $T$ 后移 $|T|$ 个字符：

$$
\begin{aligned}
\textit{S}:\quad &\texttt{HERE_IS_A_SIM}{\color{blue}{\texttt{P}}}\texttt{LE_EXAMPLE} \\
\textit{T}:\quad &\texttt{.......EXAMPL}{\color{blue}{\texttt{E}}} \\
\end{aligned}
$$

这时 `P` 和 `E` 仍不匹配，但 `P` 在 $T$ 中出现过。它在 $T$ 中出现的最后一次是 $T[5]$（其实也只出现了这一次），因此我们把 $T$ 往后移动 （$7-5=$）$2$ 位，让两个 `P` 对齐：

$$
\begin{aligned}
\textit{S}:\quad &\texttt{HERE_IS_A_SIM}{\color{blue}{\texttt{P}}}{\color{green}{\texttt{LE}}}\texttt{_EXAMPLE} \\
\textit{T}:\quad &\texttt{.........EXAM}{\color{blue}{\texttt{P}}}{\color{green}{\texttt{LE}}} \\
\end{aligned}
$$

然后我们再从 $T$ 的末尾开始比较：

$$
\begin{aligned}
\textit{S}:\quad &\texttt{HERE_IS_A_S}{\color{blue}{\texttt{I}}}{\color{green}{\texttt{MPLE}}}\texttt{_EXAMPLE} \\
\textit{T}:\quad &\texttt{.........EX}{\color{blue}{\texttt{A}}}{\color{green}{\texttt{MPLE}}}\\
\end{aligned}
$$

这时遇到 `I` 和 `A` 两个字符不匹配。按照刚才的方法，我们会将 $T$ 向后移动（$3-0=$） $3$ 位。但注意到 $T[|T|]=T[1]$，因此我们可以直接把两个 $E$ 对齐：

$$
\begin{aligned}
\textit{S}:\quad &\texttt{HERE_IS_A_SIMPLE_}{\color{blue}{\texttt{E}}}\texttt{XAMPLE} \\
\textit{T}:\quad &\texttt{.................}{\color{blue}{\texttt{E}}}{\texttt{XAMPLE}}\\
\end{aligned}
$$

然后再从右往左比较一轮，我们就找到了匹配。

## 朴素算法

假设 $T[1]$ 与 $S[i]$ 对齐，并且匹配到了 $T[j]$，即 $T[j+1,|T|]=S[i+j,i+|T|-1]$ ，且 $T[j] \ne S[i+j-1]$。

我们可以总结出三个移动策略：

### 坏字符策略

假设 $S[i+j-1]$ 在 $T$ 中最后一次出现的位置是 $k$（如果 $S[i+j-1]$ 不在 $T[1,j-1]$ 中出现过，则 $k=0$）。那么我们可以把 $T[k]$ 移到 $T[j]$ 的位置上，即将 $T$ 向后移动 $j-k$ 位。

![bad-character](images/BM/p3.png)

这个策略在 $j-k<0$ 的时候是显然不优的。

### 好后缀策略

如果 $T[j+1,|T|]$ 在 $T$ 的前面出现过，即存在 $p$ 使得 $T[p,p+|T|-j+1]=T[j+1,|T|]$（$1\le p<j+1$），那我们可以找到满足这个条件的最大的 $p$，然后把 $T[p]$ 移到 $T[j+1]$ 的位置上，即将 $T$ 向后移动 $j+1-p$ 位。

![good-suffix-1](images/BM/p1.png)

### Border 策略

如果 $T$ 有 border， 即存在 $q$（$1\le q < |T|$） 使得 $T[1,q] = T[|T|-q+1,|T|]$，那我们可以将 $T[1]$ 移到 $T[|T|-q+1]$ 的位置上，即将 $T$ 向后移动 $|T|-q$ 位。

如果不存在上述 $q$，我们可以将 $T$ 向后移动 $|T|$ 位。

![good-suffix-2](images/BM/p2.png)

应用贪心的思想，我们每次选择这三个策略（如果存在）中移动步数最大的。

### 算法实现

对于坏字符策略，我们需要用 $O(|\Sigma|)$ 的时间预处理每一个字符在 $T$ 中最后一次出现的位置。

对于好后缀策略，我们可以求出 $T$ 反串的 next 数组，进而得到每一个后缀在之前出现的最靠后的位置。时间复杂度 $O(|T|)$。这同样可以完成 Border 策略的预处理。

因此预处理复杂度 $O(|T|+|\Sigma|)$。

## Galil 规则优化

如果要寻找 $S$ 中所有匹配 $T$ 的位置，朴素的 BM 算法最坏复杂度是 $O(|S||T|)$，例如 $S=\texttt{AAAAAA...}$，$T=\texttt{AAA}$。为此我们使用 Galil 算法[^galil-rule]优化。

假设 $T$ 的周期的长度是 $k$。在匹配过程中，如果我们成功找到了一个匹配，那么我们可以将 $T$ 往后移动 $k$ 个字符，并且只用从 $T[k]$ 开始往前比较。

如何预处理 $k$：求出 $T$ 反串的 next 数组，我们就可以得到 $k=|T|-\text{nex}[|T|]$。

Galil 算法优化的 BM 算法匹配的最坏复杂度为 $O(|S|+|T|)$。

## Simplified Boyer-Moore 算法

BM 算法最复杂的地方就在于 $delta_2$ 表（通俗的名字是好后缀表）的构建，而实践中发现，在一般的字符集上的匹配性能主要依靠 $delta_1$ 表（通俗的名字是坏字符表），于是出现了仅仅使用 $delta_1$ 表的简化版 BM 算法，通常表现和完整版差距很小。

## Boyer-Moore-Horspool 算法

Horspool 算法同样是基于坏字符策略，不过它只会在 $T$ 的最后一个字符上应用这个策略。

Boyer-Moore-Horspool 算法则是每次匹配的时候，如果 $T$ 的最后一个字符与 $S$ 不匹配，则执行 Horspool 算法直到 $T$ 的最后一个字符与 $S$ 匹配，然后执行 Boyer-Moore 算法。

??? note "代码实现(rust)"
    ```rust
    pub struct HorspoolPattern<'a> {
        pat_bytes: &'a [u8],
        bm_bc: [usize; 256],
    }
    
    impl<'a> HorspoolPattern<'a> {
        // ...
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let stringlen = string_bytes.len();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let mut string_index = pat_last_pos;
    
            while string_index < stringlen {
                if &string_bytes[string_index-pat_last_pos..string_index+1] == self.pat_bytes {
                    result.push(string_index-pat_last_pos);
                }
    
                string_index += self.bm_bc[string_bytes[string_index] as usize];
            }
    
            result
        }
    }
    ```

## Boyer-Moore-Sunday 算法

Sunday 算法同样是利用坏字符规则，只不过相比 Horspool 它更进一步，在 $T[j]$ 失配时它考虑的是使得 $T[j+1]$ 匹配的位置。

Sunday 算法通常用作一般情况下实现最简单而且平均表现最好之一的实用算法，通常表现比 Horspool、BM 都要快一点。

??? note "代码实现(rust)"
    ```rust
    pub struct SundayPattern<'a> {
        pat_bytes: &'a [u8],
        sunday_bc: [usize; 256],
    }
    
    impl<'a> SundayPattern<'a> {
        // ...
        fn build_sunday_bc(p: &'a [u8]) -> [usize; 256] {
            let mut sunday_bc_table = [p.len() + 1; 256];
    
            for i in 0..p.len() {
                sunday_bc_table[p[i] as usize] = p.len() - i;
            }
    
            sunday_bc_table
        }
    
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let stringlen = string_bytes.len();
            let mut string_index = pat_last_pos;
    
            while string_index < stringlen {
                if &string_bytes[string_index - pat_last_pos..string_index+1] == self.pat_bytes {
                    result.push(string_index - pat_last_pos);
                }
    
                if string_index + 1 == stringlen {
                    break;
                }
    
                string_index += self.sunday_bc[string_bytes[string_index + 1] as usize];
            }
    
            result
        }
    }
    ```

## BMHBNFS 算法

该算法结合了 Horspool 和 Sunday，是 CPython 实现 `stringlib` 模块时用到的 `find` 的算法[^b5s]，似乎国内更有名气，不清楚为何叫这个名字，怎么就“AKA”了？

以下简称 B5S。

B5S 基本想法是：

1.  假设 $T[|T|]$ 与 $S[i]$ 对齐。按照后缀匹配的思路，首先比较 $T[|T|]$ 与 $S[i]$ 是否相等，如果相等就比较 $T[1,T]$ 与 $S[i-|T|+1,i]$ 是否相等，如果仍然相等，那么就发现一个匹配；
2.  如果任何一个阶段发生不匹配，就进入跳转阶段；
3.  在跳转阶段，首先观察 $S[i+1]$ 是否在 $T$ 中，如果不在，直接将 $T$ 向右移动 $|T|+1$ 位，这是 Sunday 算法的运用；否则对 $T[|T|]$ 使用 Horspool 算法跳转。

### 时间节省版本

??? note "代码实现(rust)"
    ```rust
    pub struct B5STimePattern<'a> {
        pat_bytes: &'a [u8],
        alphabet: [bool;256],
        bm_bc: [usize;256],
        k: usize
    }
    
    impl<'a> B5STimePattern<'a> {
        pub fn new(pat: &'a str) -> Self {
            assert_ne!(pat.len(), 0);
    
            let pat_bytes = pat.as_bytes();
            let (alphabet, bm_bc, k) = B5STimePattern::build(pat_bytes);
    
            B5STimePattern { pat_bytes, alphabet, bm_bc, k }
        }
    
        fn build(p: &'a [u8]) -> ([bool;256], [usize;256], usize)  {
            let mut alphabet = [false;256];
            let mut bm_bc = [p.len(); 256];
            let lastpos = p.len() - 1;
    
            for i in 0..lastpos {
                alphabet[p[i] as usize] = true;
                bm_bc[p[i] as usize] = lastpos - i;
            }
    
            alphabet[p[lastpos] as usize] = true;
    
            (alphabet, bm_bc, compute_k(p))
        }
    
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let patlen = self.pat_bytes.len();
            let stringlen = string_bytes.len();
            let mut string_index = pat_last_pos;
            let mut offset = pat_last_pos;
            let offset0 = self.k - 1;
    
            while string_index < stringlen {
                if string_bytes[string_index] == self.pat_bytes[pat_last_pos] {
                    if &string_bytes[string_index-offset..string_index] == &self.pat_bytes[pat_last_pos-offset..pat_last_pos] {
                        result.push(string_index-pat_last_pos);
    
                        offset = offset0;
    
                        // Galil rule
                        string_index += self.k;
                        continue;
                    }
                }
    
                if string_index + 1 == stringlen {
                    break;
                }
    
                offset = pat_last_pos;
    
                if !self.alphabet[string_bytes[string_index+1] as usize] {
                    string_index += patlen + 1;  // sunday
                } else {
                    string_index += self.bm_bc[string_bytes[string_index] as usize];  // horspool
                }
            }
    
            result
        }
    }
    ```

这个版本的 B5S 性能表现非常理想，是通常情况下，目前介绍的后缀匹配系列算法中最快的。

### 空间节省版本

这也是 CPython `stringlib` 中实现的版本，使用了两个整数近似取代了字符表和 $delta_1$ 的作用，极大地节省了空间：

优化1：用 Bloom 过滤器取代字符表（alphabet）：

??? note "代码实现(rust)"
    ```rust
    pub struct BytesBloomFilter {
        mask: u64,
    }
    
    impl BytesBloomFilter {
        pub fn new() -> Self {
            SimpleBloomFilter {
                mask: 0,
            }
        }
    
        fn insert(&mut self, byte: &u8) {
            (self.mask) |= 1u64 << (byte & 63);
        }
    
        fn contains(&self, char: &u8) -> bool {
            (self.mask & (1u64 << (byte & 63))) != 0
        }
    }
    ```

Bloom 过滤器设设计通过牺牲准确率（实际还有运行时间）来极大地节省存储空间的 `Set` 类型的数据结构，它的特点是会将集合中不存在的项误判为存在（False Positives，简称 FP），但不会把集合中存在的项判断为不存在（False Negatives，简称 FN），因此使用它时间复杂度可能不是最优，但正确性是保证的。

优化2：简化坏字符策略。

具体地，如果 $T[|T|]$ 与 $S[i]$ 对齐，且 $S[i]$ 不在 $T$ 中出现过，我们直接把 $T$ 向后移动 $|T|$ 位。否则我们向后移动一位。

??? note "代码实现(rust)"
    ```rust
    pub struct B5SSpacePattern<'a> {
        pat_bytes: &'a [u8],
        alphabet: BytesBloomFilter,
        skip: usize,
    }
    
    impl<'a> B5SSpacePattern<'a> {
        pub fn new(pat: &'a str) -> Self {
            assert_ne!(pat.len(), 0);
    
            let pat_bytes = pat.as_bytes();
            let (alphabet, skip) = B5SSpacePattern::build(pat_bytes);
    
            B5SSpacePattern { pat_bytes, alphabet, skip}
        }
    
        fn build(p: &'a [u8]) -> (BytesBloomFilter, usize)  {
            let mut alphabet = BytesBloomFilter::new();
            let lastpos = p.len() - 1;
            let mut skip = p.len();
    
            for i in 0..p.len()-1 {
                alphabet.insert(&p[i]);
    
                if p[i] == p[lastpos] {
                    skip = lastpos - i;
                }
            }
    
            alphabet.insert(&p[lastpos]);
    
            (alphabet, skip)
        }
    
        pub fn find_all(&self, string: &'a str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let patlen = self.pat_bytes.len();
            let stringlen = string_bytes.len();
            let mut string_index = pat_last_pos;
    
            while string_index < stringlen {
                if string_bytes[string_index] == self.pat_bytes[pat_last_pos] {
                    if &string_bytes[string_index-pat_last_pos..string_index] == &self.pat_bytes[..patlen-1] {
                        result.push(string_index-pat_last_pos);
                    }
    
                    if string_index + 1 == stringlen {
                        break;
                    }
    
                    if !self.alphabet.contains(&string_bytes[string_index+1]) {
                        string_index += patlen + 1;  // sunday
                    } else {
                        string_index += self.skip;  // horspool
                    }
                } else {
                    if string_index + 1 == stringlen {
                        break;
                    }
    
                    if !self.alphabet.contains(&string_bytes[string_index+1]) {
                        string_index += patlen + 1;  // sunday
                    } else {
                        string_index += 1;
                    }
                }
    
            }
    
            result
        }
    }
    ```

通常情况下，这个版本的算法相对于前面的后缀匹配算法不够快，但差距并不大，仍然比 KMP 这种快得多，特别是考虑到它极为优秀的空间复杂度：至多两个 `u64` 的整数，这确实是极为实用的适合作为标准库实现的一种算法！

## 算法比较

在字符集大小为 $256$ 时：

<img src="../images/BM/plot256.svg" style="zoom: 200%;" />

这印证了 BM 算法在一般字符集下随机文本搜索复杂度能达到 $O\left(\dfrac{n}{m}\right)$ 。

在字符集大小为 $4$ 时：（比如 DNA {A, C, T, G} 碱基对序列）：

<img src="../images/BM/plot4.svg" style="zoom:200%;" />

曲线出现了明显的分化。

总结一下，在较大的字符集，比如日常搜索的过程中 BoyerMoore 系列算法表现优越；另一方面，在较小的字符集里，如果有一定富裕空间的情况下，使用完整的空间复杂度为 $O(m)$ 的 BoyerMoore 算法应该是一种适用各种情况、综合表现都很优异的算法选择。

## 引用

[^bm]:  [1977 年 Boyer-Moore 算法论文](https://dl.acm.org/doi/10.1145/359842.359859) 

[^rytter]:  [1980 年 Rytter 纠正 Knuth 的论文](https://epubs.siam.org/doi/10.1137/0209037) 

[^galil-rule]:  [1979 年介绍 Galil 算法的论文](https://doi.org/10.1145%2F359146.359148) 

[^b5s]:  [B5S 算法的介绍](http://effbot.org/zone/stringlib.htm#BMHBNFS) 
