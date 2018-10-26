WBLT，全称Weight Balanced Leafy Tree，一种不常见的平衡树写法，但是具有常数较小，可以当做可并堆使用的优点。

类似于WBL（weight-balanced trees，加权平衡树），WBLT体现了leafy的性质,即节点多，怎么多呢？

对于n个数，不同于treap等，WBLT会建立2n个节点，每个节点的权值为其右儿子的权值，且右儿子的权值大于等于左儿子

每次插入，类似于堆，逐次向下交换并向上pushup更新即可，删除也是同理

当然，如果输入数据递增或递减，WBLT会退化成链状，于是我们采用旋转来维护平衡。

因为WBLT同时满足堆的性质，我们可以用它来实现堆和可并堆。

而在旋转的过程中，会产生很多垃圾节点，我们采用垃圾回收的方式就可以回收废弃节点，将建立节点的操作稍作修改即可。

附上普通平衡树代码:
```cpp
#include<cstdio>
#include<iostream>

using namespace std;

const int maxn=400005;

const int ratio=5;
int n,cnt,fa,root;
int size[maxn],ls[maxn],rs[maxn],val[maxn];

void newnode(int &cur,int v) {
    cur=++cnt;
    size[cur]=1;
    val[cur]=v;
}

void copynode(int x,int y) {
    size[x]=size[y];
    ls[x]=ls[y];
    rs[x]=rs[y];
    val[x]=val[y];
}

void merge(int l,int r) {
    size[++cnt]=size[l]+size[r];
    val[cnt]=val[r];
    ls[cnt]=l,rs[cnt]=r;
}

void rotate(int cur,bool flag) {
    if(flag){
        merge(ls[cur],ls[rs[cur]]);
        ls[cur]=cnt;
        rs[cur]=rs[rs[cur]];
    }
    else {
        merge(rs[ls[cur]],rs[cur]);
        rs[cur]=cnt;
        ls[cur]=ls[ls[cur]];
    }
}

void maintain(int cur) {
    if(size[ls[cur]]>size[rs[cur]]*ratio)
        rotate(cur,0);
    else if(size[rs[cur]]>size[ls[cur]]*ratio)
        rotate(cur,1);
    if(size[ls[cur]]>size[rs[cur]]*ratio)
        rotate(ls[cur],1),rotate(cur,0);
    else if(size[rs[cur]]>size[ls[cur]]*ratio)
        rotate(rs[cur],0),rotate(cur,1);
}

void pushup(int cur) {
    if(!size[ls[cur]]) return ;
    size[cur]=size[ls[cur]]+size[rs[cur]];
    val[cur]=val[rs[cur]];
}

void insert(int cur,int x) {
    if(size[cur]==1){
        newnode(ls[cur],min(x,val[cur]));
        newnode(rs[cur],max(x,val[cur]));
        pushup(cur);
        return;
    }
    maintain(cur);
    insert(x>val[ls[cur]]?rs[cur]:ls[cur],x);
    pushup(cur);
}

void erase(int cur,int x){
    if(size[cur]==1){
        cur=ls[fa]==cur?rs[fa]:ls[fa];
        copynode(fa,cur);
        return ;
    }
    maintain(cur);
    fa=cur;
    erase(x>val[ls[cur]]?rs[cur]:ls[cur],x);
    pushup(cur);
}

int find(int cur,int x){
    if(size[cur]==x) return val[cur];
    maintain(cur);
    if(x>size[ls[cur]])
        return find(rs[cur],x-size[ls[cur]]);
    return find(ls[cur],x);
}

int rnk(int cur,int x){
    if(size[cur]==1) return 1;
    maintain(cur);//asdasdasdasd
    if(x>val[ls[cur]])
        return rnk(rs[cur],x)+size[ls[cur]];
    return rnk(ls[cur],x);
}

int main() {
    scanf("%d", &n);
    newnode(root, 2147383647);//使根不改变
    while(n--) {
        int s, a;
        scanf("%d %d", &s, &a);
        if(s == 1) insert(root, a);
        if(s == 2) erase(root, a);
        if(s == 3) printf("%d\n", rnk(root, a));
        if(s == 4) printf("%d\n", find(root, a));
        if(s == 5) printf("%d\n", find(root, rnk(root, a) - 1));
        if(s == 6) printf("%d\n", find(root, rnk(root, a + 1)));
    }
    return 0;
}
```
