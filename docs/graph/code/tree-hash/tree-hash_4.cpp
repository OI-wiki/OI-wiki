#include <cstdio>
#include <cctype>
#include <vector>
#include <set>
#include <random>
#include <chrono>

typedef unsigned long long ull;

const ull mask=std::chrono::steady_clock::now().time_since_epoch().count();

ull shift(ull x)
{
    x ^= mask;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    x ^= mask;
    return x;
}

const int N=1e6+10;

int n;
ull hash[N];
std::vector<int> edge[N];
std::set<ull> trees;

void dfs(int x, int p)
{ 
    hash[x] = mask ^ 1;
    for (int i : edge[x]) {
        if (i == p) {
            continue;
        }
        dfs(i, x);
        hash[x] += shift(hash[i]);
    }
    trees.insert(hash[x]);
}

int main()
{
    scanf("%d", &n);
    for (int i=1; i<n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1, 0);
    printf("%lu", trees.size());
}
