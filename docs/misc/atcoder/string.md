下面，我们令 $s$ 为字符串，$s[l..r)$ 表示 $l$ 到 $r-1$ 的子串，**注意是左闭右开**。

## 非成员函数

### suffix_array

``` cpp
vector<int> suffix_array(string s);                 // (1)
vector<int> suffix_array<T>(vector<T> s);           // (2)
vector<int> suffix_array(vector<int> s, int upper); // (3)
```

计算 $s$ 的 [后缀数组](../../string/sa.md)。

**约束条件**

- $0\le n\le 10^8$。
- (2) `T` 是 `int`、`uint`、`ll`、`ull` 其中的一个。
- (3) $0\le \mathrm{upper}\le 10^8$。
- (3) $\forall x\in S,\ 0\le x\le \mathrm{upper}$。

**复杂度**

1. $O(n)$。
2. $O(n\log n)$，并需要 $O(n)$ 空间。
3. $O(n+\mathrm{upper})$。

### lcp_array

``` cpp
vector<int> lcp_array(string s, vector<int> sa);       // (1)
vector<int> lcp_array<T>(vector<T> s, vector<int> sa); // (2)
```

计算 $s$ 的 LCP 数组（相邻两个后缀的最长公共前缀）。

**约束条件**

- $1\le n\le 10^8$。
- $sa$ 是 $s$ 的后缀数组。
- (2) `T` 是 `int`、`uint`、`ll`、`ull` 其中的一个。

**复杂度**

- $O(n)$。

### z_algorithm

``` cpp
vector<int> z_algorithm(string s);       // (1)
vector<int> z_algorithm<T>(vector<T> s); // (2)
```

计算 $s$ 的 [Z 函数数组](../../string/z-func.md)。

**约束条件**

- $0\le n\le 10^8$。
- (2) `T` 是 `int`、`uint`、`ll`、`ull` 其中的一个。

**复杂度**

- $O(n)$。

## 示例

尝试使用 AtCoder Library 通过 [Number of Substrings](https://atcoder.jp/contests/practice2/tasks/practice2_i)。

??? 代码

    ``` cpp
    #include <atcoder/string>
    #include <iostream>
    #include <string>
    #include <vector>

    using namespace std;
    using namespace atcoder;

    int main() {
        static char buf[500'001];
        scanf("%s", buf);
        string s = buf;
        vector<int> sa = suffix_array(s);
        long long answer = 1LL * s.size() * (s.size() + 1) / 2;
        for (auto x : lcp_array(s, sa)) {
            answer -= x;
        }
        printf("%lld\n", answer);
        return 0;
    }
    ```
