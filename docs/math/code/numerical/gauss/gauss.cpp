#include <bits/stdc++.h>
using namespace std;
const int maxN = 105;
const double eps = 1e-10;
double a[maxN][maxN];
int n;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n + 1; ++j) {
            scanf("%lf", &a[i][j]);
        }
    }
    for (int i = 1; i <= n; ++i) {
        int max = i;
        for (int j = i + 1; j <= n; ++j) {
            if (fabs(a[j][i]) > fabs(a[max][i])) {
                max = j;
            }
        }
        for (int j = 1; j <= n + 1; ++j) {
            swap(a[i][j], a[max][j]);
        }
        if (fabs(a[i][i]) < eps) {
            puts("No Solution\n");
            return 0;
        }
        for (int j = 1; j <= n; ++j) {
            if (j != i) {
                double temp = a[j][i] / a[i][i];
                for (int k = i + 1; k <= n + 1; ++k) {
                    a[j][k] -= a[i][k] * temp;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        printf("%.2lf\n", a[i][n + 1] / a[i][i]);
    }
    return 0;
}
