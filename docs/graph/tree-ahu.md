author: Backl1ght
AHU算法用于判断两棵树是否同构。另外还有一种常见的做法是[树哈希](/graph/tree-hash )。

前置知识：[树基础](/graph/tree-basic)，[树的重心](/graph/tree-centroid)

建议配合参考资料里给的例子观看。

## 树同构问题

### 有根树同构

对于两棵有根树$T_1(V_1,E_1,r_1)$和$T_2(V_2,E_2,r_2)$，如果存在一个双射$\varphi: V_1 \rightarrow V_2$，使得

$$
\forall u,v \in V_1,(u,v) \in E_1 \Leftrightarrow (\varphi(u),\varphi(v))  \in E_2 
$$

且$\varphi(r_1)=r_2$成立，那么称有根树$T_1(V_1,E_1,r_1)$和$T_2(V_2,E_2,r_2)$同构。

### 无根树同构


对于两棵无根树$T_1(V_1,E_1)$和$T_2(V_2,E_2)$，如果存在一个双射$\varphi: V_1 \rightarrow V_2$，使得

$$
\forall u,v \in V_1,(u,v) \in E_1 \Leftrightarrow (\varphi(u),\varphi(v))  \in E_2
$$

成立，那么称无根树$T_1(V_1,E_1)$和$T_2(V_2,E_2)$同构。



简单的说就是，如果能够通过把树$T_1$的所有节点重新标号，使得树$T_1$和树$T_2$完全相同，那么称这两棵树同构。

## 引理

如果存在一个解决有根树同构问题的$O(n)$算法，那么存在一个解决无根树同构问题的$O(n)$算法。

### 证明


$$
\begin{array}{ll}

1 & \textbf{输入：} \text{解决有根树同构问题的算法}A\text{和两棵无根树}T_1\text{,}T_2\text{。}\\

2 & \textbf{输出：} \text{两棵无根树是否同构。}\\

3 & \textbf{方法：}\\

4 & \text{分别找到两棵无根树的所有重心。}\\

5 &	\text{if 两棵无根树的重心数量不同：}\\

6 & \qquad \text{返回 两棵无根树不同构。}\\

7 &	\text{if 两棵无根树都只有1个重心，记为}c_1\text{和}c_2\text{：}\\

8 & \qquad \text{返回 }A(T_1,c_1,T_2,c_2)\text{。}\\

9 &	\text{if 两棵无根树都有两个重心，记为}c_1,c_1^\prime\text{和}c_2,c_2^\prime\text{:}\\

10 & \qquad \text{返回 }A(T_1,c_1,T_2,c_2) \quad or \quad A(T_1,c_1^\prime,T_2,c_2)。

\end{array}
$$



无根树同构问题可以通过上述方法转换为有根树同构问题，再加上找树的重心也有$O(n)$的算法，所以整体的复杂度为$O(n)$。

由此，只需要讨论有根树同构问题的解决。

## 朴素AHU算法

朴素的AHU算法是基于括号序(01序)的，具体算法如下：


$$
\begin{array}{ll}

1 & \textbf{输入：} \text{一有根棵树}T\text{。}\\

2 & \textbf{输出：} \text{所有树节点的名字。}\\

3 & \text{ASSIGN-NAME(v)：}\\

4 & \qquad \text{if  } v \text{  是叶子节点：}\\

5 & \qquad \qquad \text{NAME(} v \text{) = 10。}\\

6 & \qquad \text{else： }\\

7 & \qquad \qquad \text{for  所有  } v \text{  的子节点  } u\\

8 & \qquad \qquad \qquad \text{ASSIGN-NAME(}u\text{)。}\\

9 & \qquad \text{将所有  } v \text{  的子节点按名字字典序排序。}\\

10 & \qquad \text{将所有  } v \text{  的子节点的名字连接起来记为temp。}\\

11 & \qquad \text{NAME(} v \text{) = 1+temp+0。}

\end{array}
$$



这里的$+$号表示字符串拼接。

这个算法有什么用呢？我们可以根据根的名字判断两棵树是否同构。


$$
\begin{array}{ll}

1 & \textbf{输入：} \text{两棵有根树}T_1(V_1,E_1,r_1)\text{和}T_2(V_2,E_2,r_2) \\

2 & \textbf{输出：} \text{两棵有根树是否同构}\\

3 & \text{AHU}(T_1(V_1,E_1,r_1), T_2(V_2,E_2,r_2))\text{：}\\

4 &  \qquad \text{ASSIGN-NAME(}r_1\text{)。}\\

5 &  \qquad \text{ASSIGN-NAME(}r_2\text{)。}\\

6 & \qquad \text{if  NAME}(r_1) = \text{NAME}(r_2)\text{：}\\

7 & \qquad \qquad \text{返回  两棵树同构。}\\

8 & \qquad \text{else ：}\\

10 & \qquad \qquad \text{返回  两棵树不同构。}

\end{array}
$$



对于一颗有$n$个节点的有根树，假设他是链状的，那么节点名字长度最长可以是$n$，那么ASSIGN-NAME的复杂度是$1+2+\cdots+n$的倍数，即$\Omega(n^2)$。

## 优化

朴素的AHU算法的缺点是节点名字的长度可能会过长。针对这一点，对于某一层的节点，如果层的NAME相等，那么就把层内节点的名字替换成节点名字在层内的排名。这样即不影响算法的正确性也大大减少了节点名字的最大长度。

### 复杂度证明

假设采用线性复杂度的排序算法，那么

$$
T(n)= \sum T(a_i)+O(n).
$$

其中，$\sum a_i=n$。

假设$T(n)=O(n)$，那么存在$c$使得$T(n) \leq cn$成立。由此，

$$
\begin{array}{ll}
T(n) & \leq & c\sum a_i+O(n)\\
	 & =	& cn + O(n)\\
	 & = 	& O(n)
\end{array}
$$

同理，假设使用快排，那么$T(n)=O(n \log n)$。

## 例题

[SPOJ-TREEISO]( https://www.spoj.com/problems/TREEISO/en/ )

题意翻译：给你两颗无根树，判断两棵树是否同构。

???+ note "参考代码"
    ```cpp
    // Tree Isomorphism, O(nlogn)
    // replace quick sort with radix sort ==> O(n)
    // Author: _Backl1ght
    #include<bits/stdc++.h>
    using namespace std;
    typedef long long ll;
    const int N=1e5+5;
    const int maxn=N<<1;
    ```

    int n;
    struct Edge{
        int v,nxt;	
    }e[maxn<<1];
    int head[maxn],sz[maxn],f[maxn],maxv[maxn],tag[maxn],tot,Max;
    vector<int>center[2],L[maxn],subtree_tags[maxn];
    void addedge(int u,int v){
        e[tot].v=v;e[tot].nxt=head[u];head[u]=tot++;
        e[tot].v=u;e[tot].nxt=head[v];head[v]=tot++;
    }
    
    void dfs_size(int u,int fa){
        sz[u]=1; maxv[u]=0;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].v;
            if(v==fa)continue;
            dfs_size(v,u);
            sz[u]+=sz[v];
            maxv[u]=max(maxv[u],sz[v]);
        }
    }
    
    void dfs_center(int rt,int u,int fa,int id){
        maxv[u]=max(maxv[u],sz[rt]-sz[u]);
        if(Max>maxv[u]){
            center[id].clear();
            Max=maxv[u];
        }
        if(Max==maxv[u])center[id].push_back(u);
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].v;
            if(v==fa)continue;
            dfs_center(rt,v,u,id);	
        }
    }
    
    int dfs_height(int u,int fa,int depth){
        L[depth].push_back(u); f[u]=fa;
        int h=0;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].v;
            if(v==fa)continue;
            h=max(h,dfs_height(v,u,depth+1));
        }
        return h+1;
    }
    
    void init(int n){
        for(int i=1;i<=2*n;i++)head[i]=0;
        tot=1; center[0].clear(); center[1].clear();
    
        int u,v;
        for(int i=1;i<=n-1;i++){
            scanf("%d %d",&u,&v);
            addedge(u,v);	
        }
        dfs_size(1,-1);
        Max=n; dfs_center(1,1,-1,0);
    
        for(int i=1;i<=n-1;i++){
            scanf("%d %d",&u,&v);
            addedge(u+n,v+n);	
        }
        dfs_size(1+n,-1);
        Max=n; dfs_center(1+n,1+n,-1,1);
    }
    
    bool cmp(int u,int v){
        return subtree_tags[u]<subtree_tags[v];	
    }
    
    bool rootedTreeIsomorphism(int rt1,int rt2){
        for(int i=0;i<=2*n+1;i++)L[i].clear(),subtree_tags[i].clear();
        int h1=dfs_height(rt1,-1,0);
        int h2=dfs_height(rt2,-1,0);
        if(h1!=h2)return false;
        int h=h1-1;
        for(int j=0;j<(int)L[h].size();j++)tag[L[h][j]]=0;
        for(int i=h-1;i>=0;i--){
            for(int j=0;j<(int)L[i+1].size();j++){
                int v=L[i+1][j];
                subtree_tags[f[v]].push_back(tag[v]);
            }
    
            sort(L[i].begin(),L[i].end(),cmp);
    
            for(int j=0,cnt=0;j<(int)L[i].size();j++){
                if(j && subtree_tags[L[i][j]]!=subtree_tags[L[i][j-1]])++cnt;
                tag[L[i][j]]=cnt;	
            }
        }
        return subtree_tags[rt1]==subtree_tags[rt2];	
    }
    
    bool treeIsomorphism(){
        if(center[0].size()==center[1].size()){
            if(rootedTreeIsomorphism(center[0][0],center[1][0]))return true;
            if(center[0].size()>1)return rootedTreeIsomorphism(center[0][0],center[1][1]);
        }
        return false;
    }
    
    int main()
    {
        int T;
        scanf("%d",&T);
        while(T--){
            scanf("%d",&n);
            init(n);
            puts(treeIsomorphism()?"YES":"NO");	
        }
        return 0;
    }
    ```

## 参考资料

本文大部分内容译自[Paper]( http://wwwmayr.in.tum.de/konferenzen/Jass08/courses/1/smal/Smal_Paper.pdf )和[Slide]( https://logic.pdmi.ras.ru/~smal/files/smal_jass08_slides.pdf )。