#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;

const int N = 100, M = 400, mod = 998244353;

int n, m, a[N + 5], fact[M + 5], inv[M + 5];

// 组合数计算 C(x,y)
int C(int x, int y) {
  return 1LL * fact[x] * inv[y] % mod * inv[x - y] % mod;
}

// 胡牌自动机
class HuAutomation {
private:
  // 表示当前面子的矩阵状态（刻子数、副将数等信息）
  class Mat {
  private:
    int f[3][3];
  public:
    Mat() {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          f[i][j] = -1;
    }

    int* operator[](const int& x) { return f[x]; }

    // 判断两个矩阵是否相等
    bool operator==(Mat x) const {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] != x[i][j]) return false;
      return true;
    }

    // 用于排序，方便状态存储和查找
    bool operator<(Mat x) const {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] != x[i][j]) return f[i][j] < x[i][j];
      return false;
    }

    // 判断该状态是否合法（例如是否有超过3张同类牌）
    bool Check() {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] > 3) return true;
      return false;
    }

    // 从另一个状态 x 转移到当前状态，加 t 张某种牌
    void Upd(Mat x, int t) {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (x[i][j] != -1)
            for (int k = 0; k < 3 && i + j + k <= t; k++)
              f[j][k] = max(f[j][k], min(i + x[i][j] + (t - i - j - k) / 3, 4));
    }
  };

  // 自动机中的一个状态，封装了两个面子矩阵（含副将）与当前 t（副将出现次数）
  struct node {
    int t, state[5];   // state[i] 表示当前状态添加 i 张牌后转移到的状态编号
    Mat F[2];          // F[0] 为正常面子状态，F[1] 包含副将

    node() {
      for (int i = 0; i <= 4; i++) state[i] = 0;
      t = 0;
      for (int i = 0; i <= 1; i++) F[i] = Mat();
    }

    // 是否为非法状态：副将数过多或构型非法
    bool Check() {
      return t == -1 || t >= 7 || F[1].Check();
    }

    // 返回一个非法状态（用于剪枝），这里 t=-1 表示胡牌状态
    node Hu() {
      node x;
      x.t = -1;
      return x;
    }

    // 状态排序，方便map存储
    bool operator<(const node& x) const {
      if (t == x.t) {
        if (F[0] == x.F[0]) return F[1] < x.F[1];
        return F[0] < x.F[0];
      }
      return t < x.t;
    }

    // 对当前状态加 x 张同种牌，返回新状态
    node operator+(int x) {
      if (Check()) return Hu();  // 若当前已胡牌或非法，直接返回胡牌状态
      node res;
      res.F[0].Upd(F[0], x);
      res.F[1].Upd(F[1], x);
      res.t = t;
      if (x > 1) {
        res.F[1].Upd(F[0], x - 2);
        ++res.t;  // 副将计数增加
      }
      if (res.Check()) res = Hu(); // 若新状态非法则置为胡牌状态
      return res;
    }
  } A[2100];  // 状态表，A[i] 表示第 i 个合法状态

  map<node, int> mp;  // 状态去重，状态映射到唯一编号

  // 插入新状态或返回已存在状态编号
  int Get(node x) {
    if (mp.count(x)) return mp[x];
    mp[x] = ++tot;
    A[tot] = x;
    return tot;
  }

  // 扩展某状态的所有转移（加 0~4 张牌）
  void Expend(int x) {
    for (int i = 0; i <= 4; i++)
      A[x].state[i] = Get(A[x] + i);
  }

  // 构造胡牌状态节点
  node Hu() {
    node x;
    x.t = -1;
    return x;
  }

  // 构造空状态节点（初始状态）
  node Emp() {
    node x;
    x.F[0][0][0] = 0;  // 初始化状态：没有任何牌时是合法的起始状态
    return x;
  }

public:
  int tot;                    // 状态总数
  int f[N + 5][M + 5][2100]; // f[i][j][k]：考虑前 i 类牌，补了 j 张，状态为 k 的方案数

  // 构造自动机状态转移图
  void Build() {
    A[1] = Emp();
    A[2] = Hu();
    mp[A[1]] = 1;
    mp[A[2]] = 2;
    tot = 2;
    Expend(1);
    for (int i = 3; i <= tot; i++)
      Expend(i);
  }

  // 主体 DP
  void DP() {
    f[0][0][1] = 1;  // 初始状态方案数为1
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        for (int k = 1; k <= tot; k++) {
          if (f[i - 1][j][k] == 0) continue;
          for (int t = 0; t <= 4 - a[i]; t++) {
            // 状态转移，加 t 张牌到状态 k
            int nj = j + t;
            int ns = A[k].state[a[i] + t];
            f[i][nj][ns] = (f[i][nj][ns] + 1LL * f[i - 1][j][k] * C(4 - a[i], t)) % mod;
          }
        }
      }
    }
  }
};

// 快速幂计算逆元
long long qpow(long long x, int y) {
  long long res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return res;
}

// 初始化阶乘与逆元
void init(int n) {
  fact[0] = 1;
  for (int i = 1; i <= n; i++)
    fact[i] = 1LL * fact[i - 1] * i % mod;
  inv[n] = qpow(fact[n], mod - 2);
  for (int i = n - 1; i >= 0; i--)
    inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  HuAutomation Hfu;
  Hfu.Build();  // 构造胡牌自动机状态

  cin >> n;
  for (int i = 1; i <= 13; i++) {
    int x, y;
    cin >> x >> y;
    ++a[x];  // 读取已有的 13 张牌
  }
  m = (n << 2) - 13;  // 剩余牌数

  init(m);
  Hfu.DP();  // 状态 DP

  int ans = 0;
  for (int i = 1; i <= m; i++) {
    // 计算答案，状态1是空状态，状态3开始是胡牌状态
    ans = (ans + 1LL * Hfu.f[n][i][1] * fact[i] % mod * fact[m - i] % mod) % mod;
    for (int j = 3; j <= Hfu.tot; j++)
      ans = (ans + 1LL * Hfu.f[n][i][j] * fact[i] % mod * fact[m - i] % mod) % mod;
  }

  // 除以总排列数，+1 表示当前状态本身可胡
  cout << (1LL * ans * inv[m] % mod + 1) << "\n";

  return 0;
}
