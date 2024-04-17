#include <atcoder/modint>
#include <cstdio>

using namespace std;
using namespace atcoder;

using mint = static_modint<11>;
int main() {
    mint a = 10;
    mint b(3);

    // 判断相等
    assert(a == 21);
    assert(a == -1);
    assert(-1 == a);

    // 取相反数
    assert(-b == 8);

    // 加
    assert(a + b == 2);  // (10 + 3) mod 11
    assert(1 + a == 0);

    // 减
    assert(a - b == 7);  // (10 - 3) mod 11
    assert(b - a == 4);

    // 乘
    assert(a * b == 8);  // (10 * 3) mod 11

    // 逆元
    assert(b.inv() == 4);  // (3 * 4) mod 11 == 1

    // 除
    assert(a / b == 7);  // (10 * 4) mod 11

    // +=, -=, *=, /=
    a += b;
    assert(a == 2 && b == 3);
    a -= b;
    assert(a == 10 && b == 3);
    a *= b;
    assert(a == 8 && b == 3);
    a /= b;
    assert(a == 10 && b == 3);

    // 幂
    assert(mint(2).pow(4) == 5);  // 16 mod 11

    // 获取值
    printf("%d\n", a.val());  // 10

    // 获取模数
    assert(mint::mod() == 11 && a.mod() == 11);

    // 使用 mint(3) 会发生一次取模操作，而 mint::raw(3) 更快，他赋值时不取模。
    // 必须保证赋值的 x 属于 [0, mod)。
    assert(mint::raw(3) == 3);
}