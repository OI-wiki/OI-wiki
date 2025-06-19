#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

// --8<-- [start:core]
template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value>::type
read(T &x) {
  bool neg = false;
  x = 0;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') neg = true;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (neg ? ('0' - ch) : (ch - '0'));
    ch = getchar();
  }
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value>::type
write(T x) {
  using UnsignedType = typename std::make_unsigned<T>::type;
  UnsignedType t = static_cast<UnsignedType>(x);
  if (x < 0) {
    t = -t;
    putchar('-');
  }
  static T sta[40];
  int top = 0;
  do {
    sta[top++] = t % 10;
    t /= 10;
  } while (t);
  while (top) putchar(sta[--top] + '0');
}

// --8<-- [end:core]
int n, x, sum;

int main() {
  read(n);
  while (n--) {
    read(x);
    sum += x;
  }
  write(sum);
  return 0;
}
