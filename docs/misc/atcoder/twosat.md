解决 [2-SAT问题](../../graph/2-sat.md)。

## 构造函数

``` cpp
two_sat(int n);
```

构造一个 $n$ 变量 $0$ 限制的 2-SAT。

**约束条件**

- $0\le n\le 10^8$。

**复杂度**

- $O(n)$。

## 成员函数

### add_clause

``` cpp
void add_clause(int i, bool f, int j, bool g);
```

添加限制 $(x_i=f)\lor(x_j=g)$。

**约束条件**

- $0\le i, j < n$。

**复杂度**

- 均摊 $O(1)$。

### satisfiable

``` cpp
bool satisfiable();
```

返回是否所有限制都能满足，可以运行多次。

**复杂度**

- $O(n+m)$。

### answer

``` cpp
vector<bool> answer();
```

返回满足最后一次调用 `satisfiable` 时所有限制的变量分配方案。

注意如果上一次 `satisfiable` 返回 `false`（或者根本没有调用），则返回列表中的元素是未定义的。

## 示例

尝试使用 AtCoder Library 通过 [Two SAT](https://atcoder.jp/contests/practice2/tasks/practice2_h)。

??? 代码

    ``` cpp
    #include <atcoder/twosat>
    #include <iostream>
    #include <vector>

    using namespace std;
    using namespace atcoder;

    int main() {
        int n, d;
        cin >> n >> d;
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }

        // ts[i] = (i-th flag is located on x[i])
        two_sat ts(n);

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (abs(x[i] - x[j]) < d) {
                    // cannot use both of x[i] and x[j]
                    ts.add_clause(i, false, j, false);
                }
                if (abs(x[i] - y[j]) < d) {
                    ts.add_clause(i, false, j, true);
                }
                if (abs(y[i] - x[j]) < d) {
                    ts.add_clause(i, true, j, false);
                }
                if (abs(y[i] - y[j]) < d) {
                    ts.add_clause(i, true, j, true);
                }
            }
        }

        if (!ts.satisfiable()) {
            cout << "No" << endl;
            return 0;
        }

        cout << "Yes" << endl;
        auto answer = ts.answer();
        for (int i = 0; i < n; i++) {
            if (answer[i])
                cout << x[i] << endl;
            else
                cout << y[i] << endl;
        }

        return 0;
    }
    ```