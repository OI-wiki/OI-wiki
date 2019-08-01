### struct基本操作

结构体是一种重要的工具，可以记录与 $num_{i}$ 有关的各种信息。

其基本操作如下：
```cpp
struct node
{
    int num,id;
};
```

我们一般不会单独使用结构体，会定义 **结构体数组**

结构体数组有两种定义方式，这里推荐大家使用这一种：

```cpp
struct node
{
    int num,id;
}a[20005];
```

### struct基本运用

结构体一般会配合sort和priority_queue使用。

sort的写法如下：

```cpp
struct node
{
    int num,id;
}a[20005];
bool cmp(node p,node q)
{
    return p.num>q.num;
}
int main()
{
    sort(a+1,a+1+n,cmp);
}
```

priority_queue的写法如下：（大跟堆）

```cpp
struct node{
    int num,id;
    bool operator<(const node &T)const{
        return T.num>num;
    }
}t;
priority_queue<node>q;
```
