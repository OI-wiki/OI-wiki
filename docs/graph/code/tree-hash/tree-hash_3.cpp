#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <chrono>

typedef unsigned long long ull;
typedef unsigned long long ll;

const int N=1e5+10, M=998244353;
const ull mask=std::chrono::steady_clock::now().time_since_epoch().count();

struct Tree {
	ull hash;
	ll deg, ans;
	std::map<ull, ll> son;
	
	Tree() {clear();}
	void add(Tree& o);
	void remove(Tree& o);
	void clear();
};

ll inv(ll x)
{
	ll y=M-2, z=1;
	while (y) {
		if (y & 1) {
			z = z * x % M;
		}
		x = x * x % M;
		y >>= 1;
	}
	return z;
}

ull shift(ull x)
{
	x ^= mask;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	x ^= mask;
	return x;
}

void Tree::add(Tree& o)
{
	ull temp = shift(o.hash);
	hash += temp;
	ans = ans * ++deg % M * inv(++son[temp]) % M * o.ans % M;
}
	
void Tree::remove(Tree& o)
{
	ull temp = shift(o.hash);
	hash -= temp;
	ans = ans * inv(deg--) % M * son[temp]-- % M * inv(o.ans) % M;
}

void Tree::clear()
{
	hash = mask ^ 1;
	deg = 0;
	ans = 1;
	son.clear();
}

std::vector<int> edge[N];
Tree sub[N], root[N];
std::map<ull, ll> trees;

void dfs(int x, int fa)
{
	for (int i : edge[x]) {
		if (i == fa) {
			continue;
		}
		dfs(i, x);
		sub[x].add(sub[i]);
	}
}

void dfs2(int x, int fa)
{
	for (int i : edge[x]) {
		if (i == fa) {
			continue;
		}
		root[x].remove(sub[i]);
		root[i] = sub[i];
		root[i].add(root[x]);
		root[x].add(sub[i]);
		dfs2(i, x);
	}
	trees[root[x].hash] = root[x].ans;
}

int main()
{
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i=1; i<n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		dfs(1, 0);
		root[1] = sub[1];
		dfs2(1, 0);
		ll tot = 0;
		for (auto p : trees) {
			tot = (tot + p.second) % M;
		}
		printf("%lld\n", tot);
		for (int i=1; i<=n; i++) {
			edge[i].clear();
			sub[i].clear();
			root[i].clear();
		}
		trees.clear();
	}
}
