#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;
constexpr int N = 2010;
constexpr double eps = 1e-9;
int n, cnt, vis[N][N];
double ans;

double Rand() { return rand() / (double)RAND_MAX; }

double reps() { return (Rand() - 0.5) * eps; }

struct Node {
  double x, y, z;

  void shake() {
    x += reps();
    y += reps();
    z += reps();
  }

  double len() { return sqrt(x * x + y * y + z * z); }

  Node operator-(Node A) const { return {x - A.x, y - A.y, z - A.z}; }

  Node operator*(Node A) const {
    return {y * A.z - z * A.y, z * A.x - x * A.z, x * A.y - y * A.x};
  }

  double operator&(Node A) const { return x * A.x + y * A.y + z * A.z; }
} A[N];

struct Face {
  int v[3];

  Node Normal() { return (A[v[1]] - A[v[0]]) * (A[v[2]] - A[v[0]]); }

  double area() { return Normal().len() / 2.0; }
} f[N], C[N];

int see(Face a, Node b) { return ((b - A[a.v[0]]) & a.Normal()) > 0; }

void Convex_3D() {
  f[++cnt] = {1, 2, 3};
  f[++cnt] = {3, 2, 1};

  for (int i = 4, cc = 0; i <= n; i++) {
    for (int j = 1, v; j <= cnt; j++) {
      if (!(v = see(f[j], A[i]))) C[++cc] = f[j];

      for (int k = 0; k < 3; k++) vis[f[j].v[k]][f[j].v[(k + 1) % 3]] = v;
    }

    for (int j = 1; j <= cnt; j++)
      for (int k = 0; k < 3; k++) {
        int x = f[j].v[k], y = f[j].v[(k + 1) % 3];

        if (vis[x][y] && !vis[y][x]) C[++cc] = {x, y, i};
      }

    for (int j = 1; j <= cc; j++) f[j] = C[j];

    cnt = cc;
    cc = 0;
  }
}

int main() {
  cin >> n;

  for (int i = 1; i <= n; i++) cin >> A[i].x >> A[i].y >> A[i].z, A[i].shake();

  Convex_3D();

  for (int i = 1; i <= cnt; i++) ans += f[i].area();

  cout << fixed << setprecision(3) << ans << '\n';
  return 0;
}