#include <algorithm>
#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

// --8<-- [start:from_dec]
std::string from_dec(int x, int base) {
  assert(2 <= base && base <= 36);
  if (x == 0) return "0";
  std::string res;
  while (x) {
    int r = x % base;
    x /= base;
    if (r < 10)
      res.push_back('0' + r);
    else
      res.push_back('A' + r - 10);
  }
  std::reverse(res.begin(), res.end());
  return res;
}

// --8<-- [end:from_dec]

// --8<-- [start:to_dec]
int to_dec(std::string const& s, int base) {
  assert(2 <= base && base <= 36);
  int res = 0;
  for (char c : s) {
    res *= base;
    if (isdigit(c))
      res += c - '0';
    else if (isupper(c))
      res += c - 'A' + 10;
    else if (islower(c))
      res += c - 'a' + 10;
  }
  return res;
}

// --8<-- [end:to_dec]

int main() {
  int x, base;
  std::cin >> x >> base;
  std::string s = from_dec(x, base);
  std::cout << s << '\n';
  int y = to_dec(s, base);
  std::cout << y << '\n';
  return 0;
}