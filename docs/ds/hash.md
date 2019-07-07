## 哈希表

哈希表是又称散列表，一种以 "key-value" 形式存储数据的数据结构。所谓以 "key-value" 形式存储数据，是指任意的 key 都唯一对应到内存中的某个位置。只需要输入查找的值 key，就可以快速地找到其对应的 value。可以把哈希表理解为一种高级的数组，这种数组的下标可以是很大的整数，浮点数，字符串甚至结构体。

## 哈希函数

要让 key 对应到内存中的位置，就要为 key 计算索引，也就是计算这个数据应该放到哪里。这个根据 key 计算索引的函数就叫做哈希函数，也称散列函数。举个例子，比如 key 是一个人的身份证号码，哈希函数就可以是号码的后四位，当然也可以是号码的前四位。生活中常用的“手机尾号”也是一种哈希函数。在实际的应用中，key 可能是更复杂的东西，比如浮点数、字符串、结构体等，这时候就要根据具体情况设计合适的哈希函数。哈希函数应当易于计算，并且尽量使计算出来的索引均匀分布。

在 OI 中，最常见的情况应该是 key 为整数的情况。当 key 的范围比较小的时候，可以直接把 key 作为数组的下标，但当 key 的范围比较大，比如以 $10^9$ 范围内的整数作为 key 的时候，就需要用到哈希表。一般把 key 模一个较大的质数作为索引，也就是取 $f(x)=x \bmod M$ 作为哈希函数。另一种比较常见的情况是 key 为字符串的情况，在 OI 中，一般不直接把字符串作为 key，而是先算出字符串的哈希值，再把其哈希值作为 key 插入到哈希表里。

能为 key 计算索引之后，我们就可以知道每个 value 应该放在哪里了。假设我们用数组 a 存放数据，哈希函数是 f，那键值对 (key,value) 就应该放在 a[f(key)] 上。不论 key 是什么类型，范围有多大，f(key) 都是在可接受范围内的整数，可以作为数组的下标。

## 冲突

如果对于任意的 key，哈希函数计算出来的索引都不相同，那只用根据索引把 (key,value) 放到对应的位置就行了。但实际上，常常会出现两个不同的 key，他们用哈希函数计算出来的索引是相同的。这时候就需要一些方法来处理冲突。在 OI 中，最常用的方法是拉链法。

### 拉链法

拉链发也称开散列法（open hashing）。

拉链法是在每个存放数据的地方开一个链表，如果有多个 key 索引到同一个地方，只用把他们都放到那个位置的链表里就行了。查询的时候需要把对应位置的链表整个扫一遍，对其中的每个数据比较其 key 与查询的 key 是否一致。如果索引的范围是 1~M，哈希表的大小为 N，那么一次插入 / 查询需要进行期望 $O(\frac{N}{M})$ 次比较。

### 闭散列法

闭散列方法吧所有记录直接存储在散列表中，如果发生冲突则根据某种方式继续进行探查。

比如线性探查法：如果在 `d` 处发生冲突，就依次检查 `d + 1` ， `d+2` ……

## 实现

### 拉链法

```cpp
const int SIZE = 1000000;
const int M = 999997;
struct HashTable {
  struct Node {
    int next, value, key;
  } data[SIZE];
  int head[M], size;
  int f(int key) { return key % M; }
  int get(int key) {
    for (int p = head[f(key)]; p; p = data[p].next)
      if (data[p].key == key) return data[p].value;
    return -1;
  }
  int modify(int key, int value) {
    for (int p = head[f(key)]; p; p = data[p].next)
      if (data[p].key == key) return data[p].value = value;
  }
  int add(int key, int value) {
    if (get(key) != -1) return -1;
    data[++size] = (Node){head[f(key)], value, key};
    head[f(key)] = size;
    return value;
  }
};
```

这边再为大家提供一个封装过的模板，可以像 map 一样用，并且较短

```cpp
struct hash_map{// 哈希表模板
    struct data{long long u;int v,nex;};// 前向星结构
    data e[SZ<<1];//SZ 是 const int 表示大小
    int h[SZ],cnt;
    int hash(long long u){return u%SZ;}
    int & operator[](long long u){
        int hu=hash(u);// 获取头指针
        for(int i=h[hu];i;i=e[i].nex)if(e[i].u==u)return e[i].v;
        return e[++cnt]=(data){u,-1,h[hu]},h[hu]=cnt,e[cnt].v;
    }
    hash_map(){cnt=0;memset(h,0,sizeof(h));}
};
```

解释一下，hash 函数是针对 key 的类型设计的，并且返回一个链表头指针用于查询。在这个模板中我们写了一个 $\text{(long long , int)}$ 式的 hash 表，并且当某个 key 不存在的时侯初始化对应的 val 成 -1。hash_map() 函数是在定义的时侯初始化用的。

## 例题

[\[JLOI2011\]不重复数字](https://www.lydsy.com/JudgeOnline/problem.php?id=2761)