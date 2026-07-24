#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

const int N = 100, M = 400, mod = 998244353;

int n, m, a[N + 5], fact[M + 5], inv[M + 5];

inline int C(int x, int y) {
  return 1LL * fact[x] * inv[y] % mod * inv[x - y] % mod;
}

class HuAutomation {  // 胡牌自动机
 private:
  class Mat {
   private:
    int f[3][3];

   public:
    Mat() {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++) f[i][j] = -1;
    }

    int* operator[](const int& x) { return f[x]; }

    inline bool operator==(Mat x) const {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] != x[i][j]) return 0;
      return 1;
    }

    inline bool operator<(Mat x) const {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] != x[i][j]) return f[i][j] < x[i][j];
      return 0;
    }

    inline bool Check() {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] > 3) return 1;
      return 0;
    }

    inline void Upd(Mat x, int t) {
      // 将已有矩阵 x 的值更新到当前矩阵中，模拟加入 t 张当前牌后的状态
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (x[i][j] != -1)
            for (int k = 0; k < 3 && i + j + k <= t; k++)
              f[j][k] = max(f[j][k], min(i + x[i][j] + (t - i - j - k) / 3, 4));
      // i,j,k,(t-i-j-k)
      // 表示分别枚举用于拼面子、用于保留(i-1,i)、用于保留i和直接拼面子的牌数
      //  更新时限制最多 4 个对子
    }
  };

  struct node {
    int t, state[5];
    Mat F[2];

    node() {
      for (int i = 0; i <= 4; i++) state[i] = 0;
      t = 0;
      for (int i = 0; i <= 1; i++) F[i] = Mat();
    }

    inline bool Check() { return t == -1 || t >= 7 || F[1].Check(); }

    node Hu() {
      node x;
      x.t = -1;
      return x;
    }

    bool operator<(const node& x) const {
      if (t == x.t) {
        if (F[0] == x.F[0]) return F[1] < x.F[1];
        return F[0] < x.F[0];
      }
      return t < x.t;
    }

    node operator+(int x) {      // 加上 x 张新牌
      if (Check()) return Hu();  // 胡了直接返回
      node res;
      res.F[0].Upd(F[0], x), res.F[1].Upd(F[1], x);  // 更新
      res.t = t;
      if (x > 1) res.F[1].Upd(F[0], x - 2), ++res.t;
      if (res.Check()) res = Hu();  // 判断是否胡了
      return res;
    }
  } A[2100];

  map<node, int> mp;

  inline int Get(node x) {
    if (mp.count(x)) return mp[x];
    mp[x] = ++tot;
    A[tot] = x;
    return tot;
  }

  inline void Expand(int x) {
    // 构建状态转移图：
    // 对于当前状态 A[x]，尝试加入 0~4 张同种牌，得到 5 个新状态
    for (int i = 0; i <= 4; i++) A[x].state[i] = Get(A[x] + i);
  }

  inline node Hu() {
    node x;
    x.t = -1;
    return x;
  }

  inline node Emp() {
    node x;
    x.F[0][0][0] = 0;
    return x;
  }

 public:
  int tot, f[N + 5][M + 5][2100];

  inline void Build() {
    A[1] = Emp(), A[2] = Hu();  // 状态1是初始合法状态，2 是胡牌状态
    mp[A[1]] = 1, mp[A[2]] = 2;
    tot = 2;
    Expand(1);
    for (int i = 3; i <= tot; i++)
      Expand(i);  // 枚举所有可达状态，构建状态图（因为 2
                  // 是胡牌状态所以不需要拓展）
  }

  void DP() {
    f[0][0][1] = 1;
    for (int i = 1; i <= n; i++)
      for (int j = m; j >= 0; j--)
        for (int k = 1; k <= tot; k++)
          if (f[i - 1][j][k])
            for (int t = 0; t <= 4 - a[i]; t++)
              // 枚举这张牌能加多少个（不能超过4，总共已有a[i]个），做组合转移
              (f[i][j + t][A[k].state[a[i] + t]] +=
               1LL * f[i - 1][j][k] * C(4 - a[i], t) % mod) %= mod;
  }
} Hfu;

inline long long qpow(long long x, int y) {
  long long res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return res;
}

void init(int n) {
  fact[0] = 1;
  for (int i = 1; i <= n; i++) fact[i] = 1LL * fact[i - 1] * i % mod;
  inv[n] = qpow(fact[n], mod - 2);
  for (int i = n - 1; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int ans = 0;
  Hfu.Build();  // 状态图构建
  cin >> n;
  for (int i = 1; i <= 13; i++) {
    int x, y;
    cin >> x;
    cin >> y;
    ++a[x];
  }
  m = (n << 2) - 13;
  init(m);
  Hfu.DP();

  for (int i = 1; i <= m; i++) {
    (ans += 1LL * Hfu.f[n][i][1] * fact[i] % mod * fact[m - i] % mod) %= mod;
    for (int j = 3; j <= Hfu.tot; j++)  // 因为 2 节点是胡牌节点所以不统计
      (ans += 1LL * Hfu.f[n][i][j] * fact[i] % mod * fact[m - i] % mod) %= mod;
    // f[i][j][k]：表示处理到第 i 张牌，共摸了 j 张牌，走到了胡牌自动机上的 k
    // 号节点的方案数 每个方案乘以 i!(用于排列这 i 张) × (m - i)!
    // (剩下的牌排列)，求和后取模
  }

  cout << (1LL * ans * inv[m] + 1) % mod;
  // 最终答案乘上 inv[m] 是除以 m!，即去掉总排列数，最后 +1 是 dp 的定义是摸完 i
  // 张还没有胡
  return 0;
}
