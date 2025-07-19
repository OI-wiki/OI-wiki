#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 100;

int T, a[MAXN + 1], h[MAXN + 1];
int g[MAXN + 1], m, n;
int nx[1 << 16][4];
int f[1001][1 << 16];
int an[MAXN + 1];

void add(int &x, int y) {
    x = (x + y) % MOD;
}

int ca(int mask, int x) {
    int res = 0;
    for (int i = 0; i < n; ++i)
        g[i + 1] = g[i] + ((mask >> i) & 1);

    for (int i = 1; i <= n; ++i) {
        if (a[i] == x)
            h[i] = g[i - 1] + 1;
        else
            h[i] = max(h[i - 1], g[i]);
    }

    for (int i = 1; i <= n; ++i)
        if (h[i] > h[i - 1])
            res |= (1 << (i - 1));

    return res;
}

int popcount(int x) {
    return __builtin_popcount(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        string S;
        cin >> S >> m;
        n = S.length();

        memset(f, 0, sizeof(f));
        memset(an, 0, sizeof(an));
        memset(a, 0, sizeof(a));

        for (int i = 0; i < n; ++i) {
            if (S[i] == 'A') a[i + 1] = 0;
            if (S[i] == 'C') a[i + 1] = 1;
            if (S[i] == 'G') a[i + 1] = 2;
            if (S[i] == 'T') a[i + 1] = 3;
        }

        int lim = (1 << n);
        for (int i = 0; i < lim; ++i)
            for (int j = 0; j < 4; ++j)
                nx[i][j] = ca(i, j);

        f[0][0] = 1;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < lim; ++j)
                if (f[i][j])
                    for (int k = 0; k < 4; ++k)
                        add(f[i + 1][nx[j][k]], f[i][j]);

        for (int i = 0; i < lim; ++i)
            add(an[popcount(i)], f[m][i]);

        for (int i = 0; i <= n; ++i)
            cout << an[i] << '\n';
    }

    return 0;
}