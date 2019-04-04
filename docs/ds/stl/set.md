## set 是什么？

`set` 正如其字面意思，是一个集合。它可以 **有序地** 存储一些 **两两不同** 的元素，并支持在单次最坏 $\mathcal O(\log N)$ 的时间内插入、删除、查找一个元素本身/前后继，且遍历整个 set 的总复杂度是 $\mathcal O(N)$ 的。

声明一个 set：

```cpp
#include <set>

std::set<int> st; // a set which contains ints 
```

## set 支持哪些操作？

### 插入

#### insert

```
st.insert(x);
```

其实 `insert` 是有返回值的，但返回值并不常用：

其返回值是一个  `pair`，第一个元素是指向 `set` 中的元素 `x` 的迭代器，第二个元素是插入是否成功（即 `x` 是否之前就存在于 `set` 中）。

#### emplace

和 `insert` 类似，但在插入某些较复杂的结构体/类时效率较高。

### 删除

#### 删除某个值

```cpp
st.erase(x); // x is a value
```
#### 删除某个迭代器指向的元素

```cpp
st.erase(pos); // pos is an iterator
```

#### 删除一段区间

```cpp
st.erase(l,r); // l and r are both iterators
```

删除 $[l,r)$ 的所有元素（包括 `l`，不包括 `r`）。

#### 清空整个set

```cpp
st.clear();
```

### 查找

#### find

```cpp
st.find(x);
```

若存在元素 `x` 返回其迭代器，否则返回 `st.end()`。

#### lower/upper_bound

```cpp
st.lower_bound(x);
```

返回大于等于 `x` 的最小元素的迭代器，若所有元素都小于 `x` 则返回 `st.end()`。

```cpp
st.upper_bound(x);
```

返回大于 `x` 的最小元素的迭代器，若所有元素都小于等于 `x` 则返回 `st.end()`。

#### count

```
st.count(x);
```

由于 `set` 是不可重集，所以只会返回 `0/1`。

### 前驱/后继

若有迭代器则可以使用 `--`/`++` 得到前驱/后继。

若只有值可以用 `lower_bound()` + `--` 得到前驱，用 `upper_bound()` 得到后继。

### 交换

```cpp
s1.swap(s2);
swap(s1,s2);
```

## 如何遍历 set？

可以使用迭代器。

```cpp
for (set<int>::iterator i=st.begin();i!=st.end();++i)
```

在 C++11 中当然也可以使用 `auto :`

```cpp
for (auto i : st)
```

还可以倒着遍历：

```cpp
for (std::set<int>::reverse_iterator i=st.rbegin();i!=st.rend();++i)
```

遍历一遍的总复杂度是 $\mathcal O(N)$ 的。

## set 有什么用？

可以代替哈希来判断元素是否出现过。

在保证无重复元素的情况下也可以用来代替简单的平衡树。

更加常用的还是 **可重集**——`multiset`。

## multiset 怎么用？

与 `set` 大致相同，但它的元素是 **可重** 的。

删除元素时需要注意，`ms.erase(x)` 会将所有等于 `x` 的元素删除，如果只需要删除一个的话，可以 `ms.erase(ms.find(x))`。

`multiset` 在某些情况下可以代替平衡树。但如果要维护一些复杂的信息，或者查询排名、查询第 $k​$ 大，就无法使用 `multiset` 了。

例题：[「HNOI2004」宠物收养场](https://www.luogu.org/problemnew/show/P2286)

??? "宠物收养场 set 参考代码"

    ```cpp
    #include <iostream>
    #include <cstdio>
    #include <set>
    
    using namespace std;
    
    set<int> a;
    int n,cur;
    long long ans;
    
    int main()
    {
        int x,y;
        set<int>::iterator succ,pre;
    
        scanf("%d",&n);
    
        while (n--)
        {
            scanf("%d%d",&x,&y);
            if (a.empty()) cur=x;
            if (cur==x) a.insert(y);
            else
            {
                succ=a.upper_bound(y);
                pre=a.lower_bound(y);
                if (pre==a.begin()||((--pre,true)&&succ!=a.end()&&abs(*pre-y)>abs(*succ-y)))
                {
                    ans+=abs(*succ-y);
                    a.erase(succ);
                }
                else
                {
                    ans+=abs(*pre-y);
                    a.erase(pre);
                }
            }
        }
    
        cout<<ans%1000000;
    
        return 0;
    }
    ```