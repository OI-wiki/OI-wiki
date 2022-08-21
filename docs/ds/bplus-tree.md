author: Persdre

## B+树简介

我们之前已经介绍过 [B树](docs/ds/b-tree.md)。B+树是B树的一个升级，它比B树更适合实际应用中操作系统的文件索引和数据库索引。目前现代关系型数据库最广泛的支持索引结构就是B+树。

B+树是一个N叉排序树，每个节点通常有多个孩子。一棵B+树包含根节点、内部节点和叶子节点。根节点可能是一个叶子节点，也可能是一个包含两个或两个以上孩子节点的节点。

B+树的特点是能够保持数据稳定有序，其插入与修改拥有较稳定的对数时间复杂度。B+树元素自底向上插入，这与二叉树恰好相反。

首先我们介绍一下一棵 $m$ 阶的B+树的特性。$m$ 表示这个树的每一个节点最多可以拥有的子节点个数。一棵 $m$ 阶的B+树和B树的差异在于：

1. 有n棵子树的节点中含有n个关键字(即每个关键字对应一棵子树)。
2. 所有叶子节点中包含了全部关键字的信息， 及指向含这些关键字记录的指针，且叶子节点本身依关键字的大小自小而大顺序链接。
3. 所有的非叶子节点可以看成是索引部分，节点中仅含有其子树（根节点）中的最大（或最小)关键字。
4. 除根节点外，其他所有节点中所含关键字的个数最少有 $\lceil \dfrac{m}{2} \rceil$ (注意：B树是除根以外的所有非叶子节点至少有 $\lceil \dfrac{m}{2} \rceil$ 棵子树)。

同时，B+树为了方便范围查询，叶子节点之间还用指针串联起来。

以下是一棵B+树的典型结构：

![](images/bplus-tree-1.png)

## B+树相比于B树的优势

由于索引节点上只有索引而没有数据，所以索引节点上能存储比B树更多的索引，这样树的高度就会更矮。树的高度越矮，磁盘寻道的次数就会越少。

因为数据都集中在叶子节点了，而所有叶子节点的高度相同，那么可以在叶子节点中增加前后指针，指向同一个父节点的相邻兄弟节点，给范围查询提供遍历。

比如这样的SQL语句：select * from tbl where t > 10，如果使用B+树存储数据的话，可以首先定位到数据为10的节点，再沿着它的next指针一路找到所有在该叶子节点右边的叶子节点数据返回。

而如果使用B树结构，由于数据既可以存储在内部节点也可以存储在叶子节点，范围查询可想而知是很繁琐的。

## 基本操作

与 [B树](docs/ds/b-tree.md) 类似，B+树的基本操作有查找，遍历，插入，删除。

### 查找

B+树的查找过程和B树类似。假设需要查找的是 k，那么从根节点开始，从上到下递归的遍历树。在每一层上，搜索的范围被减小到包含了搜索值的子树中。

一个实例：在如下这棵B+树上查找45。

![](images/bplus-tree-2.webp)

先和根节点相比

![](images/bplus-tree-3.webp)

因为根节点比45要小，所以去往根节点的右子树查找

![](images/bplus-tree-4.webp)

因为45比30大，所以要与右边的索引相比

![](images/bplus-tree-5.webp)

右侧的索引也为45，所以要去往该节点的右子树继续查找

![](images/bplus-tree-6.webp)

然后就可以找到45

需要注意的是，在查找时，若非叶子节点上的关键字等于给定值，并不终止，而是继续向下直到叶子节点。因此，在B+树中，不管查找成功与否，每次查找都是走了一条从根到叶子节点的路径。其余同B树的查找类似。

查找一个键的代码如下：

```cpp
T find(V key) {
    int i = 0;
    while(i < this.number){
        if(key.compareTo((V) this.keys[i]) <= 0)
            break;
        i++;
    }
    if(this.number == i)
        return null;
    return this.childs[i].find(key);
}
```

### 遍历

B+树只需要去遍历叶子节点就可以实现整棵树的遍历。从根节点出发一路搜索到最左端的叶子节点之后即可根据指针遍历。

### 插入

B+树的插入算法与B树的很相近，都是：

1. 若为空树，创建一个叶子节点，然后将记录插入其中，此时这个叶子节点也是根节点，插入操作结束。
2. 针对叶子类型节点：根据关键字找到叶子节点，向这个叶子节点插入记录。插入后，若当前节点关键字的个数小于 $m$，则插入结束。否则将这个叶子节点分裂成左右两个叶子节点，左叶子节点包含前 $m/2$ 个记录，右节点包含剩下的记录，将第 $m/2+1$ 个记录的关键字进位到父节点中（父节点一定是索引类型节点），进位到父节点的关键字左孩子指针向左节点,右孩子指针向右节点。将当前节点的指针指向父节点，然后执行第3步。
3. 针对索引类型节点（内部节点）：若当前节点关键字的个数小于等于 $m-1$，则插入结束。否则，将这个索引类型节点分裂成两个索引节点，左索引节点包含前 $(m-1)/2$ 个key，右节点包含 $m-(m-1)/2$ 个key，将第 $m/2$ 个关键字进位到父节点中，进位到父节点的关键字左孩子指向左节点, 进位到父节点的关键字右孩子指向右节点。将当前节点的指针指向父节点，然后重复这一步。

比如在下图的B+树中，插入新的数据10：

![](images/bplus-tree-7.png)

由于插入节点[7,11]在插入之后并没有溢出，所以可以直接变成[7,10,11]。

![](images/bplus-tree-8.png)

而如下图的B+树中，插入数据4：

![](images/bplus-tree-9.png)

由于所在节点[2,3,5]在插入之后数据溢出，因此需要分裂为两个新的节点，同时调整父节点的索引数据：

![](images/bplus-tree-10.png)

[2,3,4,5]分裂成了[2,3]和[4,5]，因此需要在这两个节点之间新增一个索引值，这个值应该满足：

1. 大于左子树的最大值。
2. 小于等于右子树的最小值。

综上，需要在父节点中新增索引4和两个指向新节点的指针。

更多的例子可以参考演示网站 [BPlustree](https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)

插入一个键的代码如下：

```cpp
void BPTree::insert(int x) {
    if (root == NULL) {
        root = new Node;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
        root->parent = NULL;
    } else {
        Node *cursor = root;
        Node *parent;

        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }

                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            insertVal(x,cursor);
            cursor->parent = parent;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        } else split(x, parent, cursor);
    }
}

void BPTree::split(int x, Node * parent, Node *cursor) {
    Node* LLeaf=new Node;
    Node* RLeaf=new Node;
    insertVal(x,cursor);
    LLeaf->IS_LEAF=RLeaf->IS_LEAF=true;
    LLeaf->size=(MAX+1)/2;
    RLeaf->size=(MAX+1)-(MAX+1)/2;
    for(int i=0;i<MAX+1;i++)LLeaf->ptr[i]=cursor->ptr[i];
    LLeaf->ptr[LLeaf->size]= RLeaf;
    RLeaf->ptr[RLeaf->size]= LLeaf->ptr[MAX];
    LLeaf->ptr[MAX] = NULL;
    for (int i = 0;i < LLeaf->size; i++) {
        LLeaf->key[i]= cursor->key[i];
    }
    for (int i = 0,j=LLeaf->size;i < RLeaf->size; i++,j++) {
        RLeaf->key[i]= cursor->key[j];
    }
    if(cursor==root){
        Node* newRoot=new Node;
        newRoot->key[0] = RLeaf->key[0];
        newRoot->ptr[0] = LLeaf;
        newRoot->ptr[1] = RLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;
        LLeaf->parent=RLeaf->parent=newRoot;
    }
    else {insertInternal(RLeaf->key[0],parent,LLeaf,RLeaf);}

}

void BPTree::insertInternal(int x,Node* cursor,Node* LLeaf,Node* RRLeaf)
{

    if (cursor->size < MAX) {
       auto i=insertVal(x,cursor);
        for (int j = cursor->size;j > i + 1; j--) {
            cursor->ptr[j]= cursor->ptr[j - 1];
            }
        cursor->ptr[i]=LLeaf;
        cursor->ptr[i + 1] = RRLeaf;
    }

    else {

        Node* newLchild = new Node;
        Node* newRchild = new Node;
        Node* virtualPtr[MAX + 2];
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i=insertVal(x,cursor);
        for (int j = MAX + 2;j > i + 1; j--) {
            virtualPtr[j]= virtualPtr[j - 1];
        }
        virtualPtr[i]=LLeaf;
        virtualPtr[i + 1] = RRLeaf;
        newLchild->IS_LEAF=newRchild->IS_LEAF = false;
      	//这里和叶子节点有区别
        newLchild->size= (MAX + 1) / 2;
        newRchild->size= MAX - (MAX + 1) /2;
        for (int i = 0;i < newLchild->size;i++) {

            newLchild->key[i]= cursor->key[i];
        }
        for (int i = 0, j = newLchild->size+1;i < newRchild->size;i++, j++) {

            newRchild->key[i]= cursor->key[j];
        }
        for (int i = 0;i < LLeaf->size + 1;i++) {
            newLchild->ptr[i]= virtualPtr[i];
        }
        for (int i = 0, j = LLeaf->size + 1;i < RRLeaf->size + 1;i++, j++) {
            newRchild->ptr[i]= virtualPtr[j];
        }
        if (cursor == root) {
            Node* newRoot = new Node;
            newRoot->key[0]= cursor->key[newLchild->size];
            newRoot->ptr[0] = newLchild;
            newRoot->ptr[1] = newRchild;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
            newLchild->parent=newRchild->parent=newRoot;
        }
        else {
            insertInternal(cursor->key[newLchild->size],cursor->parent,newLchild,newRchild);
        }
    }
}

```

### 删除

B+树的删除也仅在叶子节点中进行，当叶子节点中的最大关键字被删除时，其在非叶子节点中的值可以作为一个分界关键字存在。若因删除而使节点中关键字的个数少于 $\lceil \dfrac{m}{2} \rceil$ 时，其和兄弟节点的合并过程亦和B-树类似。

具体步骤如下：

1. 首先查询到键值所在的叶子节点，删除该叶子节点的数据。
2. 如果删除叶子节点之后的数据数量，满足B+树的平衡条件，则直接返回。
3. 否则，就需要做平衡操作：如果该叶子节点的左右兄弟节点的数据量可以借用，就借用过来满足平衡条件。否则，就与相邻的兄弟节点合并成一个新的子节点了。

在上面平衡操作中，如果是进行了合并操作，就需要向上修正父节点的指针：删除被合并节点的键值以及指针。

由于做了删除操作，可能父节点也会不平衡，那么就按照前面的步骤也对父节点进行重新平衡操作，这样一直到某个节点平衡为止。

可以参考 [B树](docs/ds/b-tree.md) 中的删除章节。

???+ note "代码实现"
    ```cpp
    --8<-- "docs/ds/code/bplus-tree/bplus-tree_1.cpp"
    ```

## 参考资料

- [B+ tree wikipedia](https://en.wikipedia.org/wiki/B%2B_tree)  
- [B树、B+树索引算法原理（下）](https://www.codedump.info/post/20200615-btree-2/) 
- [B+树详解+代码实现（插入篇）](https://www.cnblogs.com/JayL-zxl/p/14304178.html)
- [Deletion from a B+ Tree](https://www.programiz.com/dsa/deletion-from-a-b-plus-tree)
