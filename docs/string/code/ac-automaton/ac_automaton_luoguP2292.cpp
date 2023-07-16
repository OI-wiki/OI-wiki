// Code by rickyxrc | https://www.luogu.com.cn/record/115806238
#include <stdio.h>
#include <string.h>
#include <queue>

#define maxn 3000001
char T[maxn];
int n, cnt, vis[maxn], ans, m, dp[maxn];
struct trie_node
{
    int son[26];
    int fail, flag, depth;
    unsigned stat;
    void init();
} trie[maxn];

std::queue<int> q;

void init();
void insert(char *s, int num);

void getfail(void)
{
    for (int i = 0; i < 26; i++)
        trie[0].son[i] = 1;
    q.push(1);
    trie[1].fail = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        int Fail = trie[u].fail;
        trie[u].stat = trie[Fail].stat;
        if (trie[u].flag)
            trie[u].stat |= 1 << trie[u].depth;
        for (int i = 0; i < 26; i++)
        {
            int v = trie[u].son[i];
            if (!v)
                trie[u].son[i] = trie[Fail].son[i];
            else
            {
                trie[v].depth = trie[u].depth + 1;
                trie[v].fail = trie[Fail].son[i];
                q.push(v);
            }
        }
    }
}

int query(char *s)
{
    int u = 1, len = strlen(s), mx = 0;
    unsigned st = 1;
    for (int i = 0; i < len; i++)
    {
        int v = s[i] - 'a';
        u = trie[u].son[v];
        st <<= 1;
        if (trie[u].stat & st)
            st |= 1,
                mx = i + 1;
    }
    return mx;
}

int main()
{
    scanf("%d%d", &n, &m);
    init();
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", T);
        insert(T, i);
    }
    getfail();
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", T);
        printf("%d\n", query(T));
    }
}