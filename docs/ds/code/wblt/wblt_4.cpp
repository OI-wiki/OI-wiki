#include<iostream>
#include<cstring>
using namespace std;
const int N = 1e5+100;
int n,m;
struct node
{
	int cnt,be;bool r=0;
	node *ll,*rr;
	node(){r=0;cnt=be=0;ll=rr=0;}
	node(node *x){memcpy(this,x,sizeof(node));}
	inline void d(){if(ll&&r){swap(ll,rr);ll?ll->r^=1:0;rr?rr->r^=1:0;r=0;}}
	inline void up(){cnt=(ll?ll->cnt:0)+(rr?rr->cnt:0);}
	#define mid ((l+r)>>1)
	inline void build(int l,int r)
	{
		if(l==r){cnt=1,be=l;return;}
		(ll=new node)->build(l,mid),(rr=new node)->build(mid+1,r);
		up();
	}
	inline void Rr()
	{
		node *n=new node,*t=ll;
		n->ll=t->rr,n->rr=rr,n->up(),rr=n;
		ll=t->ll;delete t;
	}
	inline void Lr()
	{
		node *n=new node,*t=rr;
		n->ll=ll,n->rr=t->ll,n->up(),ll=n;
		rr=t->rr;delete t;
	}
	inline void chk()
	{
		if(cnt<=3)return;
		d(),ll->d(),rr->d();
		if(ll->cnt-rr->cnt>=rr->cnt*1.5)Rr();
		if(rr->cnt-ll->cnt>=ll->cnt*1.5)Lr();
	}
	inline void addr(node *t)
	{
		d(),t->d();
		node *n=new node(this);
		(*this)=node();
		ll=n,rr=t,up(),chk();
	}
	inline void addl(node *t)
	{
		d(),t->d();
		node *n=new node(this);
		(*this)=node();
		ll=t,rr=n,up(),chk();
	}
	inline void split(node *&ls,int lim)
	{
		d();
		if(lim>=ll->cnt)
		{
			lim-=ll->cnt;
			if(ls)ls->addr(ll),ll=0;
			else {ls=new node(ll);delete ll;ll=0;}
			if(lim)
				rr->split(ls,lim);
			node *t=rr;
			(*this)=(*rr);
			delete t;
		}
		else if(lim)
			ll->split(ls,lim),up();
		if(ll&&rr)chk();
	}
	inline void out(){d();if((!ll)||(!rr)){if(be&&be<=n)cout<<be<<' ';}else ll->out(),rr->out();}
	#undef mid
}t;
inline void rev(int l,int r)
{
	node *ll=0;
	t.split(ll,l);
	node *mid=0;
	t.split(mid,r-l+1);
	mid->r^=1;
	t.addl(mid);
	t.addl(ll);
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int l,r;
	cin>>n>>m;
	t.build(0,n+1);
	for(int i=1;i<=m;i++)cin>>l>>r,rev(l,r);
	t.out();
}
