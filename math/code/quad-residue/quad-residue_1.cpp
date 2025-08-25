#include <iostream>
#include <random>

long long p, v;  // 分别是模数和 r^2 - a 的值

struct Poly {
  long long a, b;

  Poly(long long _a = 0, long long _b = 0) : a(_a), b(_b) {}
};

Poly operator*(const Poly& x, const Poly& y) {
  // 重载乘法，可以参考上面有关运算性质的说明
  return Poly((x.a * y.a + v * (x.b * y.b % p)) % p,
              (x.a * y.b + x.b * y.a) % p);
}

// 多项式的快速幂，用于计算答案
Poly modpow(Poly a, long long b) {
  Poly res(1, 0);
  while (b) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}

// 普通的快速幂，用于判断二次非剩余
long long modpow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1) res = res * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return res;
}

// 用于生成随机数
std::mt19937 rng(std::random_device{}());

long long cipolla(long long a, long long _p) {
  p = _p;
  if (a == 0)
    return 0;  // 特判一下 0 的情况
  else if (modpow(a, (p - 1) / 2) == p - 1)
    return -1;  // 判断二次非剩余，此时无解
  else {
    // 随机 r，使得 r^2 - a 是一个二次非剩余
    long long r;
    for (r = rng() % p;; r = rng() % p) {
      if (modpow((r * r - a + p) % p, (p - 1) / 2) == p - 1) break;
    }
    v = (r * r - a + p) % p;
    return modpow(Poly(r, 1), (p + 1) / 2).a;  // 根据结论式计算结果
  }
}

int main() {
  int t, a, p;
  std::cin >> t;
  while (t--) {
    std::cin >> a >> p;
    int ans = cipolla(a, p);
    if (ans == -1)
      std::cout << "Hola!" << std::endl;
    else if (ans == 0)
      std::cout << 0 << std::endl;
    else {
      // 相反数是另一个解
      int ans2 = (p - ans) % p;
      if (ans2 < ans) std::swap(ans, ans2);
      std::cout << ans << " " << ans2 << std::endl;
    }
  }
  return 0;
}
