#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;

namespace gcd_impl1 {
template <typename T>
T abs(T x) {
  return x < 0 ? -x : x;
}

// --8<-- [start:not-recommended]
template <
    typename U, typename V,
    enable_if_t<is_integral<U>::value && is_integral<V>::value &&
                (is_unsigned<U>::value && is_unsigned<V>::value)>* = nullptr>
typename common_type<U, V>::type gcd(U x, V y) {
  return y == 0 ? x : gcd(y, x % y);
}

template <typename U, typename V,
          enable_if_t<is_integral<U>::value && is_integral<V>::value &&
                      (is_signed<U>::value || is_signed<V>::value)>* = nullptr>
auto gcd(U x, V y) {
  return gcd((typename make_unsigned<U>::type)(abs(x)),
             (typename make_unsigned<V>::type)(abs(y)));
}

template <typename U, typename V, typename... Args,
          enable_if_t<is_integral<U>::value && is_integral<V>::value &&
                      0 < sizeof...(Args)>* = nullptr>
auto gcd(U x, V y, Args... args) {
  return gcd(gcd(x, y), args...);
}

template <class T,
          decltype(declval<T>().begin(), declval<T>().end(), 0)* = nullptr>
auto gcd(const T& container) {
  auto ans = (typename make_unsigned<typename T::value_type>::type)(
      *container.begin());
  for (auto it = container.begin(); it != container.end(); ++it)
    ans = gcd(ans, *it);
  return ans;
}

// --8<-- [end:not-recommended]
}  // namespace gcd_impl1

namespace gcd_impl2 {
// --8<-- [start:recommended]
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }

// --8<-- [end:recommended]
}  // namespace gcd_impl2

int main() {
  vector<int> v;
  int x;
  while (cin >> x) v.push_back(x);
  cout << gcd_impl1::gcd((unsigned)v[0], (unsigned)v[1]) << '\n';
  cout << gcd_impl1::gcd(v[0], v[1]) << gcd_impl1::gcd((unsigned)v[0], v[1])
       << gcd_impl1::gcd(v[0], (unsigned)v[1]) << '\n';
  cout << gcd_impl1::gcd(v[0], v[1], v[2]) << '\n';
  cout << gcd_impl1::gcd(v) << '\n';
  cout << gcd_impl2::gcd(v[0], v[1]) << '\n';
}
