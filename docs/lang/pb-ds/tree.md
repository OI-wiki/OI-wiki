## `__gnu_pbds :: tree`

附：[官方文档地址](https://gcc.gnu.org/onlinedocs/libstdc++/ext/pb_ds/tree_based_containers.html)

```cpp
#include <ext/pb_ds/assoc_container.hpp>  // 因为tree定义在这里 所以需要包含这个头文件
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
__gnu_pbds ::tree<Key, Mapped, Cmp_Fn = std::less<Key>, Tag = rb_tree_tag,
                  Node_Update = null_tree_node_update,
                  Allocator = std::allocator<char> >
```

## 模板形参

- `Key`: 储存的元素类型，如果想要存储多个相同的 `Key` 元素，则需要使用类似于 `std::pair` 和 `struct` 的方法，并配合使用 `lower_bound` 和 `upper_bound` 成员函数进行查找
- `Mapped`: 映射规则（Mapped-Policy）类型，如果要指示关联容器是 **集合**，类似于存储元素在 `std::set` 中，此处填入 `null_type`，低版本 `g++` 此处为 `null_mapped_type`；如果要指示关联容器是 **带值的集合**，类似于存储元素在 `std::map` 中，此处填入类似于 `std::map<Key, Value>` 的 `Value` 类型
- `Cmp_Fn`: 关键字比较函子，例如 `std::less<Key>`
- `Tag`: 选择使用何种底层数据结构类型，默认是 `rb_tree_tag`。`__gnu_pbds` 提供不同的三种平衡树，分别是：
- `rb_tree_tag`：红黑树，一般使用这个，后两者的性能一般不如红黑树
- `splay_tree_tag`：splay 树
- `ov_tree_tag`：有序向量树，只是一个由 `vector` 实现的有序结构，类似于排序的 `vector` 来实现平衡树，性能取决于数据想不想卡你
- `Node_Update`：用于更新节点的策略，默认使用 `null_node_update`，若要使用 `order_of_key` 和 `find_by_order` 方法，需要使用 `tree_order_statistics_node_update`
- `Allocator`：空间分配器类型

## 构造方式

```c++
__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type,
                 std::less<std::pair<int, int> >, __gnu_pbds::rb_tree_tag,
                 __gnu_pbds::tree_order_statistics_node_update>
    trr;
```

## 成员函数

- `insert(x)`：向树中插入一个元素 x，返回 `std::pair<point_iterator, bool>`。
- `erase(x)`：从树中删除一个元素/迭代器 x，返回一个 `bool` 表明是否删除成功。
- `order_of_key(x)`：返回 x 以 `Cmp_Fn` 比较的排名。
- `find_by_order(x)`：返回 `Cmp_Fn` 比较的排名所对应元素的迭代器。
- `lower_bound(x)`：以 `Cmp_Fn` 比较做 `lower_bound`，返回迭代器。
- `upper_bound(x)`：以 `Cmp_Fn` 比较做 `upper_bound`，返回迭代器。
- `join(x)`：将 x 树并入当前树，前提是两棵树的类型一样，x 树被删除。
- `split(x,b)`：以 `Cmp_Fn` 比较，小于等于 x 的属于当前树，其余的属于 b 树。
- `empty()`：返回是否为空。
- `size()`：返回大小。

## 示例

```cpp
// Common Header Simple over C++11
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
#define pb push_back
#define mp make_pair
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
__gnu_pbds ::tree<pair<int, int>, __gnu_pbds::null_type, less<pair<int, int> >,
                  __gnu_pbds::rb_tree_tag,
                  __gnu_pbds::tree_order_statistics_node_update>
    trr;
int main() {
  int cnt = 0;
  trr.insert(mp(1, cnt++));
  trr.insert(mp(5, cnt++));
  trr.insert(mp(4, cnt++));
  trr.insert(mp(3, cnt++));
  trr.insert(mp(2, cnt++));
  //树上元素{{1,0},{2,4},{3,3},{4,2},{5,1}}
  auto it = trr.lower_bound(mp(2, 0));
  trr.erase(it);
  //树上元素{{1,0},{3,3},{4,2},{5,1}}
  auto it2 = trr.find_by_order(1);
  cout << (*it2).first << endl;
  //输出排名0 1 2 3中的排名1的元素的first:1
  int pos = trr.order_of_key(*it2);
  cout << pos << endl;
  //输出排名
  decltype(trr) newtr;
  trr.split(*it2, newtr);
  for (auto i = newtr.begin(); i != newtr.end(); ++i) {
    cout << (*i).first << ' ';
  }
  cout << endl;
  //{4,2},{5,1}被放入新树
  trr.join(newtr);
  for (auto i = trr.begin(); i != trr.end(); ++i) {
    cout << (*i).first << ' ';
  }
  cout << endl;
  cout << newtr.size() << endl;
  //将newtr树并入trr树，newtr树被删除。
  return 0;
}
```
