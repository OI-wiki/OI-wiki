#include <iostream>
#include <cstdint>
#include <complex>
#include <cmath>

using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

const i32 MAXN = 1e7 + 10;

// 快速幂
template <class T>
constexpr T qpow(T a, u64 b) {
    T x{1};
    for (; b; a *= a, b >>= 1)
        if (b & 1) x *= a;
    return x;
}

// 模 p 整数环
namespace MODINT {
template <u32 P>
struct modint {
    static_assert(P >= 1);

  private:
    using self = modint<P>;
    u32 v_;

  public:
    constexpr static u32 mod() { return P; }

    constexpr modint(): v_(0) {}
    template <class T, std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value> * = nullptr>
    constexpr modint(T v): modint() {
        i64 x = (i64)(v % (i64)mod());
        v_ = (u32)(x + (x < 0 ? mod() : 0));
    }
    template <class T, std::enable_if_t<std::is_integral<T>::value && std::is_unsigned<T>::value> * = nullptr>
    constexpr modint(T v): v_((u32)(v % mod())) {}

    constexpr u32 val() const { return v_; }
    template <class T, std::enable_if_t<std::is_integral<T>::value> * = nullptr>
    constexpr u32 val(T x) { return v_ = x; }

    friend std::istream &operator>>(std::istream &is, self &x) {
        i64 xx;
        is >> xx;
        xx %= mod();
        x.v_ = (u32)(xx + (xx < 0 ? mod() : 0));
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const self &x) { return os << x.v_; }

    constexpr self &operator+=(const self &rhs) {
        v_ += rhs.v_;
        if (v_ >= mod()) v_ -= mod();
        return *this;
    }

    constexpr self &operator-=(const self &rhs) {
        v_ -= rhs.v_;
        if (v_ >= mod()) v_ += mod();
        return *this;
    }

    constexpr self &operator*=(const self &rhs) {
        v_ = (u32)((u64)v_ * rhs.v_ % mod());
        return *this;
    }

    constexpr friend self operator+(self lhs, const self &rhs) { return lhs += rhs; }
    constexpr friend self operator-(self lhs, const self &rhs) { return lhs -= rhs; }
    constexpr friend self operator*(self lhs, const self &rhs) { return lhs *= rhs; }
};
}  // namespace MODINT

namespace CNTT {
//! --- config ---

const u32 P = 999292927;
const std::complex<MODINT::modint<P>> OMEGA{1, 8};

//! --- config end ---

// 模 p 整数环
using Zp = MODINT::modint<P>;
// 模 p Gauss 整数环
using Zpi = std::complex<Zp>;

u32 r[MAXN];
u32 limit = 1, lb_limit = 0;

// @param type 1: DFT, -1: IDFT
template <i32 type>
void trans(Zpi *a) {
    static_assert(type == 1 || type == -1);

    for (u32 i = 0; i < limit; i++)
        if (i < r[i]) std::swap(a[i], a[r[i]]);

    for (u32 mid = 1; mid < limit; mid <<= 1) {
        // 单位根
        // Zpi Wn{cos(Pi / mid), type * sin(Pi / mid)};
        Zpi Wn = qpow(OMEGA, ((u64)P * P - 1) / mid / 2);
        if constexpr (type == -1) Wn = qpow(Wn, (u64)P * P - 2);

        for (u32 R = mid << 1, j = 0; j < limit; j += R) {
            Zpi w{1};
            for (u32 k = 0; k < mid; k++, w *= Wn) {
                Zpi x = a[j + k], y = w * a[j + mid + k];
                a[j + k] = x + y;
                a[j + mid + k] = x - y;
            }
        }
    }
}

void init(u32 len) {
    if (len + 1 > limit) {
        limit = (u32)1 << (lb_limit = (u32)ceil(log2(len + 1)));
        for (u32 i = 0; i < limit; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lb_limit - 1));
    }
}

void conv(Zpi *a, Zpi *b, Zpi *result) {
    // 在原序列中 i 与 i/2 的关系是：i 可以看做是 i/2 的二进制上的每一位左移一位得来
    // 那么在反转后的数组中就需要右移一位，同时特殊处理一下复数
    trans<1>(a);
    trans<1>(b);
    for (u32 i = 0; i <= limit; i++) result[i] = a[i] * b[i];
    trans<-1>(result);

    const Zp inv = qpow(Zp{limit}, P - 2);
    for (u32 i = 0; i <= limit; i++) result[i].real(result[i].real() * inv);
}
}  // namespace CNTT
using CNTT::Zpi, CNTT::init, CNTT::conv;

Zpi a[MAXN], b[MAXN];

using std::cin, std::cout;
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    u32 N, M;
    cin >> N >> M;
    for (u32 i = 0, _; i <= N; i++) {
        cin >> _;
        a[i].real(_);
    }
    for (u32 i = 0, _; i <= M; i++) {
        cin >> _;
        b[i].real(_);
    }

    init(N + M);
    conv(a, b, a);

    for (u32 i = 0; i <= N + M; i++) cout << a[i].real() << " \n"[i == N + M];
    return 0;
}
