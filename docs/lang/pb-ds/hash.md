## `__gnu_pbds :: *_hash_table`

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
cc_hash_table<Key_Type, Val_Type> h;	//拉链法
gp_hash_table<Key_Type, Val_Type> h;	//探测法
```

在阅读之前，请确保熟悉 [`Hash表`](../../ds/hash.md) 的相关内容。

## 模板形参

- `Key_Type`: Hash表中储存的 `Key` 值类型。
- `Key_Val`: Hash表中存储的 `Key` 指向的 `Value` 的类型

## 成员函数

- `insert({x,y})`：向Hash表中加入一组数据 `{x,y}`。
- `operator[](x)=y`：同 `insert()`，提供 `[]` 运算符插入数据。比如：`H["555"] = "awa"`。

- `find(x)`：在Hash表中搜索元素 `x`，如果没有找到则返回 `end()`。

不难发现，其与C++标准库中的 `map` 有一定相似之处。

总的时间复杂度为  $O(n)$。

## 示例

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

gp_hash_table<string, int> h;
h["akioi"] = 555;
h.insert({"aknoi",777});

if(h.find("aknoi") != h.end())
    cout<<"OvO"<<endl;
```

## 关于拉链法和探测法的说明

一般情况下，认为探测法要优于拉链法。