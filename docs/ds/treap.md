author: Dev-XYS, ttzytt

前置知识：[朴素二叉搜索树](https://oi-wiki.org/ds/bst/)

## 简介
Treap（树堆） 是一种 **弱平衡** 的 **二叉搜索树**。它同时符合二叉搜索树和堆的性质，名字也因此为 tree （树） 和 heap （堆） 的组合。

其中，二叉搜索树的性质是：
- 左子节点的值（$\textit{val}$）比父节点大
- 右子节点的值（$\textit{priority}$）比父节点小（当然这也是可以反过来的）

堆的性质是：
- 子节点值（$\textit{priority}$）比父节点大或小（取决于是小根堆还是大根堆）

不难看出，如果用的是同一个值，那这两种数据结构的性质是矛盾的，所以我们再在搜索树的基础上，引入一个给堆的值 $\textit{priority}$。对于 $\textit{val}$ 值，我们维护搜索树的性质，对于 $\textit{priority}$ 值，我们维护堆的性质。其中 $\textit{priority}$ 这个值是随机给出的。

下图就是一个 Treap 的例子（这里使用的是小根堆，即根节点的值最小）。
![](https://ttzytt.com/img/treap/treap.svg)

那我们为什么需要大费周章的去让这个数据结构符合树和堆的性质，并且随机给出堆的值呢？

要理解这个，首先需要理解朴素二叉搜索树的问题。在给朴素搜索树插入一个新节点时，我们需要从这个搜索树的根节点开始递归，如果新节点比当前节点小，那就向左递归，反之亦然。

最后当发现当前节点没有子节点时，就根据新节点的值的大小，让新节点成为当前节点的左或右子节点。

如果新插入的节点的值是随机的，那这个朴素搜索树的形状会非常的 “胖”，上图的 Treap 就是一个例子。也就是说，每一层的节点比较多。

在这样的情况下，这个搜索树的层数是会比较接近 $\log_2{n}$（$n$ 为节点数） 的，查询的复杂度也是 $\log_2{n}$ （因为只要递归这么多层就能查到）。

不过，这只是在随机情况下的复杂度，如果我们按照下面这个非常有序的顺序给一个朴素的搜索树插入节点。
```
1 2 3 4 5
```
那……

这个树就会变得非常 “瘦长”（每次插入的节点都比前面的大，所以都被安排到右子节点了）：
![](https://ttzytt.com/img/treap/search_tree_chain.svg)

不难看出，现在这个二叉搜索树已经退化成链了，查询的复杂度也从 $\log_2{n}$ 变成了线性。

而 treap 要解决的正是这个问题。它通过随机化的 $\textit{priority}$ 属性，以及维护堆性质的过程，“打乱”了节点的插入顺序。从而让二叉搜索树达到了理想的复杂度，避免了退化成链的问题。

笔者并不清楚如何去严格的证明这样随机化的过程可以让搜索树的复杂度的**期望值**保持在 $\log_2{n}$，但我们可以试着感性的去理解一下。

首先，我们需要认识到一个节点的 $\textit{priority}$ 属性是和它所在的层数有直接关联的。再回忆堆的性质：
- 子节点值（$\textit{priority}$）比父节点大或小（取决于是小根堆还是大根堆）

我们发现层数低的节点，比如整个树的根节点，它的 $\textit{priority}$ 属性也会更小（在小根堆中）。并且，在朴素的搜索树中，先被插入的节点，也更有可能会有比较小的层数。我们可以把这个 $\textit{priority}$ 属性和被插入的顺序关联起来理解，这样，也就理解了为什么 treap 可以把节点插入的顺序通过 $\textit{priority}$ 打乱。

在给 treap 插入新节点时，需要同时维护树和堆的性质，为了达到这个目的，有两种方法被发明了出来，分别是旋转和分裂、合并。使用这两种方法的 treap 被分别成为有旋式 treap 和 无旋式 treap。
## 无旋 treap
无旋 treap 的操作方式使得它天生支持维护序列、可持久化等特性。这里以重新实现 `set<int>`（不可重集合）为例，介绍无旋式 treap。

**无旋 treap** 又称分裂合并 treap。它仅有两种核心操作，即为 **分裂** 与 **合并**。下面逐一介绍这两种操作。

???+ note "注释"
    讲解无旋 treap 应当提到 **FHQ-Treap**(by 范浩强）。即可持久化，支持区间操作的无旋 Treap。更多内容请参照《范浩强谈数据结构》ppt。

### 分裂（split）

分裂过程接受两个参数：根指针 $u$、关键值 $key$。结果为将根指针指向的 treap 分裂为两个 treap，第一个 treap 所有结点的关键值小于等于 $key$，第二个 treap 所有结点的关键值大于 $key$。该过程首先判断 $key$ 是否小于 $u$ 的关键值，若小于，则说明 $u$ 及其右子树全部属于第二个 treap，否则说明 $u$ 及其左子树全部属于第一个 treap。根据此判断决定应向左子树递归还是应向右子树递归，继续分裂子树。待子树分裂完成后按刚刚的判断情况连接 $u$ 的左子树或右子树到递归分裂所得的子树中。

```cpp
pair<node *, node *> split(node *u, int key) {
  if (u == nullptr) {
    return make_pair(nullptr, nullptr);
  }
  if (key < u->key) {
    pair<node *, node *> o = split(u->lch, key);
    u->lch = o.second;
    return make_pair(o.first, u);
  } else {
    pair<node *, node *> o = split(u->rch, key);
    u->rch = o.first;
    return make_pair(u, o.second);
  }
}
```

### 合并（merge）

合并过程接受两个参数：左 treap 的根指针 $u$、右 treap 的根指针 $v$。必须满足 $u$ 中所有结点的关键值小于等于 $v$ 中所有结点的关键值。因为两个 treap 已经有序，我们只需要考虑 $priority$ 来决定哪个 treap 应与另一个 treap 的儿子合并。若 $u$ 的根结点的 $priority$ 大于 $v$ 的，那么 $u$ 即为新根结点，$v$ 应与 $u$ 的右子树合并；反之，则 $v$ 作为新根结点，然后让 $u$ 与 $v$ 的左子树合并。不难发现，这样合并所得的树依然满足 $priority$ 的大根堆性质。

```cpp
node *merge(node *u, node *v) {
  if (u == nullptr) {
    return v;
  }
  if (v == nullptr) {
    return u;
  }
  if (u->priority > v->priority) {
    u->rch = merge(u->rch, v);
    return u;
  } else {
    v->lch = merge(u, v->lch);
    return v;
  }
}
```

### 建树（build）

将一个有 $n$ 个节点的序列 $\{a_n\}$ 转化为一棵 treap。

可以依次暴力插入这 $n$ 个节点，每次插入一个权值为 $v$ 的节点时，将整棵 treap 按照权值分裂成权值小于等于 $v$ 的和权值大于 $v$ 的两部分，然后新建一个权值为 $v$ 的节点，将两部分和新节点按从小到大的顺序依次合并，单次插入时间复杂度 $O(\log n)$，总时间复杂度 $O(n\log n)$。

在某些题目内，可能会有多次插入一段有序序列的操作，这是就需要在 $O(n)$ 的时间复杂度内完成建树操作。

方法一：在递归建树的过程中，每次选取当前区间的中点作为该区间的树根，并对每个节点钦定合适的优先值，使得新树满足堆的性质。这样能保证树高为 $O(\log n)$。

方法二：在递归建树的过程中，每次选取当前区间的中点作为该区间的树根，然后给每个节点一个随机优先级。这样能保证树高为 $O(\log n)$，但不保证其满足堆的性质。这样也是正确的，因为无旋式 treap 的优先级是用来使 `merge` 操作更加随机一点，而不是用来保证树高的。

方法三：观察到 treap 是笛卡尔树，利用笛卡尔树的 $O(n)$ 建树方法即可，用单调栈维护右子树即可。

## 将 treap 包装成为 `std::set<>`

### count 函数

直接依靠二叉搜索树的性质查找即可。

```cpp
int find(node *u, int key) {
  if (u == nullptr) {
    return 0;
  }
  if (key == u->key) {
    return 1;
  }
  if (key < u->key) {
    return find(u->lch, key);
  } else {
    return find(u->rch, key);
  }
}

int count(int key) { return find(root, key); }
```

### insert 函数

先在待插入的关键值处将整棵 treap 分裂，判断关键值是否已插入过之后新建一个结点，包含待插入的关键值，然后进行两次合并操作即可。

```cpp
void insert(int key) {
  pair<node*, node*> o = split(root, key);
  if (find(root, key) == 0) {
    o.first = merge(o.first, new node(key));
  }
  root = merge(o.first, o.second);
}
```

### erase 函数

将具有待删除的关键值的结点从整棵 treap 中孤立出来（进行两侧分裂操作），删除中间的一段（具有待删除关键值），再将左右两端合并即可。

```cpp
void erase(int key) {
  pair<node*, node*> o = split(root, key - 1);
  pair<node*, node*> p = split(o.second, key);
  delete p.first;
  root = merge(o.first, p.second);
}
```

## 旋转 treap

**旋转 treap** 维护平衡的方式为旋转，和 AVL 树的旋转操作类似，分为 **左旋** 和 **右旋**。即在满足二叉搜索树的条件下根据堆的优先级对 treap 进行平衡操作。

旋转 treap 在做普通平衡树题的时候，是所有平衡树中常数较小的。因为普通的二叉搜索树会被递增或递减的数据卡，用 treap 对每个节点定义一个由 `rand` 得到的权值，从而防止特殊数据卡。同时在每次删除/插入时通过这个权值决定要不要旋转即可，其他操作与二叉搜索树类似。

大部分的树形数据结构都有指针和数组模拟两种实现方法，下面将会详细的分部分讲解指针版的代码，如果想要学习数组实现，可以拉到最下面的完整代码部分。
???+info
    注意本代码中的 `rank` 代表前面讲的 $\textit{priority}$ 变量（堆的值）。并且，维护的堆的性质是小根堆（$\textit{priority}$ 小的在上面）。本代码来源。[^ref1]
### 节点结构
``` cpp
struct Node {
    Node *ch[2];//两个子节点的地址
    int val, rank;
    int rep_cnt;//当前这个值（val）重复出现的次数
    int siz;    //
    Node(int val) : val(val), rep_cnt(1), siz(1) {
        ch[0] = ch[1] = nullptr;
        rank = rand();
        //注意初始化的时候，rank 是随机给出的
    }

    void upd_siz() {
        //用于旋转和删除过后，重新计算 siz 的值
        siz = rep_cnt;
        if (ch[0] != nullptr) siz += ch[0]->siz;
        if (ch[1] != nullptr) siz += ch[1]->siz;
    }
};
```
### 旋转
旋转操作是 treap 的一个非常重要的操作，主要用来在保持 treap 树性质的同时，调整不同节点的层数，以达到维护堆性质的作用。

旋转操作的左旋和右旋可能不是特别容易区分，以下是两个较为明显的特点：

旋转操作的含义：
- 在不影响搜索树性质的前提下，把和旋转方向相反的子树变成根节点（如左旋，就是把右子树变成根节点）
- 不影响性质，并且在旋转过后，跟旋转方向相同的子节点变成了原来的根节点（如左旋，旋转完之后的左子节点是旋转前的根节点）

左旋和右旋操作是相互的，如下图。

![](https://ttzytt.com/img/treap/rotate.svg)

```cpp
enum rot_type { LF = 1, RT = 0 };
void _rotate(Node *&cur, rot_type dir) {  //dir参数代表旋转的方向 0为右旋，1为左旋
        //注意传进来的 cur 是指针的引用，也就是改了这个 cur，变量是跟着一起改的，如果这个 cur 是别的
        //树的子节点，根据 ch 找过来的时候，也是会找到这里的
        
        //以下的代码解释的均是左旋时的情况
        Node *tmp = cur->ch[dir];//让 C 变成根节点，
                                 //这里的 tmp 是一个临时的节点指针，指向成为新的根节点的节点
        
        /* 左旋：也就是让右子节点变成根节点
         *         A                 C
         *        / \               / \
         *       B  C    ---->     A   E
         *         / \            / \
         *        D   E          B   D
         */
        cur->ch[dir] = tmp->ch[!dir];  //让 A 的右子节点变成 D
        tmp->ch[!dir] = cur;           //让 C 的左子节点变成 A
        tmp->upd_siz(), cur->upd_siz();//更新大小信息
        cur = tmp;                     //最后把临时储存 C 树的变量赋值到当前根节点上（注意 cur 是引用）
    }
```

### 插入
跟普通搜索树插入的过程没啥区别，但是需要在插的过程中通过旋转来维护树堆中堆的性质。
```cpp
void _insert(Node *&cur, int val) {
        if (cur == nullptr) {
            //没这个节点直接新建
            cur = new Node(val);
            return;
        } else if (val == cur->val) {
            //如果有这个值相同的节点，就把重复数量加一
            cur->rep_cnt++;
            cur->siz++;
        } else if (val < cur->val) {
            //维护搜索树性质，val 比当前节点小就插到左边，反之亦然
            _insert(cur->ch[0], val);
            if (cur->ch[0]->rank < cur->rank) {
                //小根堆中，上面节点的优先级一定更小
                //因为新插的左子节点比父节点小，现在需要让左子节点变成父节点
                _rotate(cur, RT); //注意前面的旋转性质，要把左子节点转上来，需要右旋
            }
            cur->upd_siz(); //插入之后大小会变化，需要更新
        } else {
            _insert(cur->ch[1], val);
            if (cur->ch[1]->rank < cur->rank) {
                _rotate(cur, LF);
            }
            cur->upd_siz();
        }
    }
```
### 删除
主要就是分类讨论，不同的情况有不同的处理方法，删完了树的大小会有变化，要注意更新。并且如果要删的节点有左子树和右子树，就要考虑删除之后让谁来当父节点（维护 rank 小的节点在上面）。
```cpp
void _del(Node *&cur, int val) {
        if (val > cur->val) {
            _del(cur->ch[1], val);
            //值更大就在右子树，反之亦然
            cur->upd_siz();
        } else if (val < cur->val) {
            _del(cur->ch[0], val);
            cur->upd_siz();
        } else {
            if (cur->rep_cnt > 1) {
                //如果要删除的节点是重复的，可以直接把重复值减小
                cur->rep_cnt--, cur->siz--;
                return;
            }
            uint8_t state = 0;
            state |= (cur->ch[0] != nullptr);
            state |= ((cur->ch[1] != nullptr) << 1);
            // 00都无，01有左无右，10，无左有右，11都有
            Node *tmp = cur;
            switch (state) {
                case 0:
                    delete cur;
                    cur = nullptr;
                    //没有任何子节点，就直接把这个节点删了
                    break;
                case 1:  //有左无右
                    cur = tmp->ch[0];
                    //把根变成左儿子，然后把原来的根节删了，注意这里的 tmp 是从 cur 复制的，而 cur 
                    //是引用
                    delete tmp;
                    break;
                case 2:  //有右无左
                    cur = tmp->ch[1];
                    delete tmp;
                    break;
                case 3:
                    rot_type dir =
                        cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;// dir 是 rank 更小的那个儿子
                    _rotate(cur, dir);  //这里的旋转可以把优先级更小的儿子转上去，rt 是 0， 而 lf 
                                        //是 1，刚好跟实际的子树下标反过来
                    _del(cur->ch[!dir], val);//旋转完成后原来的根节点就在旋方向那边，所以需要             
                                             //继续把这个原来的根节点删掉
                                             //如果说要删的这个节点是在整个树的“上层的”，那我们会一直通过这
                                             //这里的旋转操作，把它转到没有子树了（或者只有一个），再删掉它。
                    cur->upd_siz();
                    //删除会造成大小改变
                    break;
            }
        }
    }
```
### 根据值查询排名
操作含义：查询以 cur 为根节点的子树中，val 这个值的大小的排名 （该子树中小于 val 的节点的个数 + 1）
```cpp
int _query_rank(Node *cur, int val) {
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
        //这个树中小于 val 的节点的数量
        if (val == cur->val)
            //如果这个节点就是要查的节点
            return less_siz + 1;
        else if (val < cur->val) {
            if (cur->ch[0] != nullptr)
                return _query_rank(cur->ch[0], val);
            else
                return 1;  //如果左子树是空的，说比最小的节点还要小，那这个数字就是最小的
        } else {
            if (cur->ch[1] != nullptr)
                //如果要查的值比这个节点大，那这个节点的左子树以及这个节点自身肯定都比要查的值小
                //所以要加上这两个值，再加上往右边找的结果（以右子树为根的子树中，val 这个值的大小的排名）
                return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
            else
                return cur->siz + 1;
                //没有右子树的话直接整个树 + 1 相当于 less_siz + cur->rep_cnt + 1
        }
    }
```

### 根据排名查询值
要根据排名查询值，我们首先要知道如何判断要查的节点在树的哪个部分：

以下是一个判断方法的表：

| 左子树 |根节点 / 当前节点|右子树 |
|--------|-------|--------|
|排名一定小于等于左子树的大小|排名应该 >= 左子树的大小，并且 <= 左子树的大小 + 根节点的重复次数|不然的话就在右子树|

注意如果在右子树，递归的时候需要对原来的 `rank` 进行处理。递归的时候就相当去查，在右子树中为这个排名的值，为了把排名转换成基于右子树的，需要把原来的 `rank` 减去左子树的大小和根节点的重复次数。

可以把所有节点想象成一个排好序的数组，或者数轴（如下），
```
1 -> |左子树的节点|根节点|右子树的节点| -> n
                           ^
                           要查的排名
                     ⬇转换成基于右子树的排名
1 -> |右子树的节点| -> n
       ^
       要查的排名
```
这里的转换方法就是直接把排名减去左子树的大小和根节点的重复数量。

```cpp
int _query_val(Node *cur, int rank) {
        //查询树中第 rank 大的节点的值
        int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz; 
        //less siz 是左子树的大小
        if (rank <= less_siz) 
            return _query_val(cur->ch[0], rank);
        else if (rank <= less_siz + cur->rep_cnt)
            return cur->val;
        else
            return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);//见前文
    }
```
### 查询第一个比 val 小的节点
注意这里使用了一个类中的全局变量，`q_prev_tmp`。

这个值是只有在 val 比当前节点值大的时候才会被更改的，所以返回这个变量就是返回 val 最后一次比当前节点的值大，之后就是更小了。

```cpp
int _query_prev(Node *cur, int val) {
        if (val <= cur->val) {
            //还是比 val 大，所以往右子树找
            if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
        } else {
            //只有能进到这个 else 里，才会更新 q_prev_tmp 的值
            q_prev_tmp = cur->val;
            //当前节点已经比 val，小了，但是不确定是否是最大的，所以要到右子树继续找
            if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
            //接下来的递归可能不会更改 q_prev_tmp 了，那就直接返回这个值，总之返回的就是最后一次进到
            //这个 else 中的 cur->val
            return q_prev_tmp;
        }
        return -1145;
    }
```
### 查询第一个比 val 大的节点
跟前一个很相似，只是大于小于号换了一下。
```cpp
int _query_nex(Node *cur, int val) {
        if (val >= cur->val) {
            if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
        } else {
            q_nex_tmp = cur->val;
            if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
            return q_nex_tmp;
        }
        return -1145;
    }
```

## 完整代码
### 指针实现
??? note "完整代码"
    以下是前文讲解的代码的完整版本，是普通平衡树的模板代码。
    
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    struct Node {
        Node *ch[2];
        int val, rank;
        int rep_cnt;
        int siz;
        Node(int val) : val(val), rep_cnt(1), siz(1) {
            ch[0] = ch[1] = nullptr;
            rank = rand();
        }

        void upd_siz() {
            siz = rep_cnt;
            if (ch[0] != nullptr) siz += ch[0]->siz;
            if (ch[1] != nullptr) siz += ch[1]->siz;
        }
    };

    class Treap {
    private:
        Node *root;
        enum rot_type { LF = 1, RT = 0 };
        int q_prev_tmp = 0, q_nex_tmp = 0;
        void _rotate(Node *&cur, rot_type dir) {  // 0为右旋，1为左旋
            Node *tmp = cur->ch[dir];
            cur->ch[dir] = tmp->ch[!dir];
            tmp->ch[!dir] = cur;
            tmp->upd_siz(), cur->upd_siz();
            cur = tmp;
        }

        void _insert(Node *&cur, int val) {
            if (cur == nullptr) {
                cur = new Node(val);
                return;
            } else if (val == cur->val) {
                cur->rep_cnt++;
                cur->siz++;
            } else if (val < cur->val) {
                _insert(cur->ch[0], val);
                if (cur->ch[0]->rank < cur->rank) {
                    _rotate(cur, RT);
                }
                cur->upd_siz();
            } else {
                _insert(cur->ch[1], val);
                if (cur->ch[1]->rank < cur->rank) {
                    _rotate(cur, LF);
                }
                cur->upd_siz();
            }
        }

        void _del(Node *&cur, int val) {
            if (val > cur->val) {
                _del(cur->ch[1], val);
                cur->upd_siz();
            } else if (val < cur->val) {
                _del(cur->ch[0], val);
                cur->upd_siz();
            } else {
                if (cur->rep_cnt > 1) {
                    cur->rep_cnt--, cur->siz--;
                    return;
                }
                uint8_t state = 0;
                state |= (cur->ch[0] != nullptr);
                state |= ((cur->ch[1] != nullptr) << 1);
                // 00都无，01有左无右，10，无左有右，11都有
                Node *tmp = cur;
                switch (state) {
                    case 0:
                        delete cur;
                        cur = nullptr;
                        break;
                    case 1:  //有左无右
                        cur = tmp->ch[0];
                        delete tmp;
                        break;
                    case 2:  //有右无左
                        cur = tmp->ch[1];
                        delete tmp;
                        break;
                    case 3:
                        rot_type dir =
                            cur->ch[0]->rank < cur->ch[1]->rank ? RT : LF;
                        _rotate(cur, dir);
                        _del(cur->ch[!dir], val);
                        cur->upd_siz();
                        break;
                }
            }
        }

        int _query_rank(Node *cur, int val) {
            int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
            if (val == cur->val)
                return less_siz + 1;
            else if (val < cur->val) {
                if (cur->ch[0] != nullptr)
                    return _query_rank(cur->ch[0], val);
                else
                    return 1;
            } else {
                if (cur->ch[1] != nullptr)
                    return less_siz + cur->rep_cnt + _query_rank(cur->ch[1], val);
                else
                    return cur->siz + 1;
            }
        }

        int _query_val(Node *cur, int rank) {
            int less_siz = cur->ch[0] == nullptr ? 0 : cur->ch[0]->siz;
            if (rank <= less_siz)
                return _query_val(cur->ch[0], rank);
            else if (rank <= less_siz + cur->rep_cnt)
                return cur->val;
            else
                return _query_val(cur->ch[1], rank - less_siz - cur->rep_cnt);
        }

        int _query_prev(Node *cur, int val) {
            if (val <= cur->val) {
                if (cur->ch[0] != nullptr) return _query_prev(cur->ch[0], val);
            } else {
                q_prev_tmp = cur->val;
                if (cur->ch[1] != nullptr) _query_prev(cur->ch[1], val);
                return q_prev_tmp;
            }
            return -1145;
        }

        int _query_nex(Node *cur, int val) {
            if (val >= cur->val) {
                if (cur->ch[1] != nullptr) return _query_nex(cur->ch[1], val);
            } else {
                q_nex_tmp = cur->val;
                if (cur->ch[0] != nullptr) _query_nex(cur->ch[0], val);
                return q_nex_tmp;
            }
            return -1145;
        }

    public:
        void insert(int val) { _insert(root, val); }
        void del(int val) { _del(root, val); }
        int query_rank(int val) { return _query_rank(root, val); }
        int query_val(int rank) { return _query_val(root, rank); }
        int query_prev(int val) { return _query_prev(root, val); }
        int query_nex(int val) { return _query_nex(root, val); }
    };

    Treap tr;

    int main() {
        srand(0);
        int t;
        scanf("%d", &t);
        while (t--) {
            int mode;
            int num;
            scanf("%d%d", &mode, &num);
            switch (mode) {
                case 1:
                    tr.insert(num);
                    break;
                case 2:
                    tr.del(num);
                    break;
                case 3:
                    printf("%d\n", tr.query_rank(num));
                    break;
                case 4:
                    printf("%d\n", tr.query_val(num));
                    break;
                case 5:
                    printf("%d\n", tr.query_prev(num));
                    break;
                case 6:
                    printf("%d\n", tr.query_nex(num));
                    break;
            }
        }
    }
    ```
### 数组实现
以下是 bzoj 普通平衡树模板代码，使用数组实现。

??? note "完整代码"
    ```cpp
    --8<-- "docs/ds/code/treap/treap_1.cpp"
    ```



## 例题

[普通平衡树](https://loj.ac/problem/104)

[文艺平衡树（Splay）](https://loj.ac/problem/105)

[「ZJOI2006」书架](https://www.luogu.com.cn/problem/P2596)

[「NOI2005」维护数列](https://www.luogu.com.cn/problem/P2042)

[CF 702F T-Shirts](http://codeforces.com/problemset/problem/702/F)

## 参考资料与注释
[^ref1]: [https://ttzytt.com/2022/06/treap_note/](https://ttzytt.com/2022/06/treap_note/)
