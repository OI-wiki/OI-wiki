本文只是后缀树算法的一个简介，没有算法的具体描述，若想进一步了解，还请参考 [Algorithms on Strings, Trees, and Sequences](http://web.stanford.edu/~mjkay/gusfield.pdf) 。

给定一个长度为 $n$ 的字符串 $s$ ，该算法构建后缀树的时间复杂度为 $O(n\log(k))$ ，其中 $k$ 是字母的大小，而如果 $k$ 是一个固定的数，时间复杂度将会是线性的。

函数 `build_tree` 是用来构建后缀树的。后缀树存储在结构体数组 `node` 中。 `node[0]` 就是树根。

为了简化节点，该节点和其父节点的边长也存储在 `node` 中。另外还会 `node` 储存以下信息。

-  `(l, r)` - 子字符串的左右边界；
-  `par` - 父节点；
-  `link` - 后缀链；
-  `next` - 从这个节点出去的边的列表。

??? note "代码实现"

    ```cpp
    string s;
    int n;
    struct node {
    	int l, r, par, link;
    	map<char,int> next;
    	node (int l=0, int r=0, int par=-1)
    		: l(l), r(r), par(par), link(-1) {}
    	int len()  {  return r - l;  }
    	int &get (char c) {
    		if (!next.count(c))  next[c] = -1;
    		return next[c];
    	}
    };
    node t[MAXN];
    int sz;
    struct state {
    	int v, pos;
    	state (int v, int pos) : v(v), pos(pos)  {}
    };
    state ptr (0, 0); 
    state go (state st, int l, int r) {
    	while (l < r)
    		if (st.pos == t[st.v].len()) {
    			st = state (t[st.v].get( s[l] ), 0);
    			if (st.v == -1)  return st;
    		}
    		else {
    			if (s[ t[st.v].l + st.pos ] != s[l])
    				return state (-1, -1);
    			if (r-l < t[st.v].len() - st.pos)
    				return state (st.v, st.pos + r-l);
    			l += t[st.v].len() - st.pos;
    			st.pos = t[st.v].len();
    		}
    	return st;
    }
    int split (state st) {
    	if (st.pos == t[st.v].len())
    		return st.v;
    	if (st.pos == 0)
    		return t[st.v].par;
    	node v = t[st.v];
    	int id = sz++;
    	t[id] = node (v.l, v.l+st.pos, v.par);
    	t[v.par].get( s[v.l] ) = id;
    	t[id].get( s[v.l+st.pos] ) = st.v;
    	t[st.v].par = id;
    	t[st.v].l += st.pos;
    	return id;
    }
    int get_link (int v) {
    	if (t[v].link != -1)  return t[v].link;
    	if (t[v].par == -1)  return 0;
    	int to = get_link (t[v].par);
    	return t[v].link = split (go (state(to,t[to].len()), t[v].l + (t[v].par==0), t[v].r));
    }
    void tree_extend (int pos) {
    	for(;;) {
    		state nptr = go (ptr, pos, pos+1);
    		if (nptr.v != -1) {
    			ptr = nptr;
    			return;
    		}
    		int mid = split (ptr);
    		int leaf = sz++;
    		t[leaf] = node (pos, n, mid);
    		t[mid].get( s[pos] ) = leaf;
    		ptr.v = get_link (mid);
    		ptr.pos = t[ptr.v].len();
    		if (!mid)  break;
    	}
    }
    void build_tree() {
    	sz = 1;
    	for (int i=0; i<n; ++i)
    		tree_extend (i);
    }
    ```

## 压缩实现

该压缩方法来自 [freopen](http://codeforces.com/profile/freopen) 。

??? note "代码实现"

    ```cpp
    const int N=1000000,INF=1000000000;
    string a;
    int t[N][26],l[N],r[N],p[N],s[N],tv,tp,ts,la;
    void ukkadd (int c) {
    	suff:;
    	if (r[tv]<tp) {
    		if (t[tv][c]==-1) { t[tv][c]=ts;  l[ts]=la;
    			p[ts++]=tv;  tv=s[tv];  tp=r[tv]+1;  goto suff; }
    		tv=t[tv][c]; tp=l[tv];
    	}
    	if (tp==-1 || c==a[tp]-'a') tp++; else {
    		l[ts+1]=la;  p[ts+1]=ts;
    		l[ts]=l[tv];  r[ts]=tp-1;  p[ts]=p[tv];  t[ts][c]=ts+1;  t[ts][a[tp]-'a']=tv;
    		l[tv]=tp;  p[tv]=ts;  t[p[ts]][a[l[ts]]-'a']=ts;  ts+=2;
    		tv=s[p[ts-2]];  tp=l[ts-2];
    		while (tp<=r[ts-2]) {  tv=t[tv][a[tp]-'a'];  tp+=r[tv]-l[tv]+1;}
    		if (tp==r[ts-2]+1)  s[ts-2]=tv;  else s[ts-2]=ts; 
    		tp=r[tv]-(tp-r[ts-2])+2;  goto suff;
    	}
    }
    void build() {
    	ts=2;
    	tv=0;
    	tp=0;
    	fill(r,r+N,(int)a.size()-1);
    	s[0]=1;
    	l[0]=-1;
    	r[0]=-1;
    	l[1]=-1;
    	r[1]=-1;
    	memset (t, -1, sizeof t);
    	fill(t[1],t[1]+26,0);
    	for (la=0; la<(int)a.size(); ++la)
    		ukkadd (a[la]-'a');
    }
    ```

## 练习题

-  [UVA 10679 - I Love Strings!!!](http://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1620) 

 **本页面主要译自博文 [Суффиксное дерево. Алгоритм Укконена](http://e-maxx.ru/algo/ukkonen) 与其英文翻译版 [Suffix Tree. Ukkonen's Algorithm](https://cp-algorithms.com/string/suffix-tree-ukkonen.html) 。其中俄文版版权协议为 Public Domain + Leave a Link；英文版版权协议为 CC-BY-SA 4.0。** 
