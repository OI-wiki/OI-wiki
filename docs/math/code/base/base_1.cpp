// --8<-- [start:from_dec]
#include <algorithm>
#include <string>

// only non-negative
// 2 <= base && base <= 36
std::string from_dec(int x, int base) {
  if (x == 0) return "0";
  std::string res;
  while (x) {
    int r = x % base;
    x /= base;

    // 写法 1
    res.push_back(r < 10 ? '0' + r : 'A' + r - 10);
    // 写法 2
    // const static std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // res.push_back(digits[r]);
  }
  std::reverse(res.begin(), res.end());
  return res;
}

// --8<-- [end:from_dec]

// --8<-- [start:from_dec_bi]
#include <algorithm>
#include <string>

// only non-negative
// 1 <= base && base < 36
std::string from_dec_bi(int x, int base) {
  std::string res;
  while (x > 0) {
    int q = (x + base - 1) / base - 1, r = x - q * base;
    x = q;

    // 写法 1
    res.push_back(r < 10 ? '0' + r : 'A' + r - 10);
    // 写法 2
    // const static std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // res.push_back(digits[r]);
  }
  std::reverse(res.begin(), res.end());
  return res;
}

// --8<-- [end:from_dec_bi]

// --8<-- [start:from_dec_factorial]
#include <algorithm>
#include <string>

// only non-negative
std::string from_dec_factorial(int x) {
  if (x == 0) return "0";
  std::string res;
  int base = 1;
  while (x) {
    int r = x % base;
    x /= base++;

    // 写法 1
    res.push_back(r < 10 ? '0' + r : 'A' + r - 10);
    // 写法 2
    // const static std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // res.push_back(digits[r]);
  }
  std::reverse(res.begin(), res.end());
  return res;
}

// --8<-- [end:from_dec_factorial]

// --8<-- [start:to_dec]
#include <cctype>
#include <string>

// only non-negative
// 2 <= base && base <= 36
int to_dec(std::string const& s, int base) {
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

// --8<-- [start:to_dec_factorial]
#include <cctype>
#include <string>

// only non-negative
int to_dec_factorial(std::string const& s) {
  int res = 0, base = s.size();
  for (char c : s) {
    res *= base--;
    if (isdigit(c))
      res += c - '0';
    else if (isupper(c))
      res += c - 'A' + 10;
    else if (islower(c))
      res += c - 'a' + 10;
  }
  return res;
}

// --8<-- [end:to_dec_factorial]

#include <cassert>

void chk(std::string s, std::string t, int base) {
  const static std::string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (char c : s) {
    assert(digits.find(c) != std::string::npos);
    assert(digits.find(c) < base);
  }
  for (char c : t) {
    assert(digits.find(c) != std::string::npos);
    assert(0 < digits.find(c) && digits.find(c) <= base);
  }
  if (s.find('0') == std::string::npos) assert(s == t);
  assert(to_dec(s, base) == to_dec(t, base));
}

#include <iostream>

int main() {
  for (int x = 0; x < 1024; x++) assert(from_dec_bi(x, 1).size() == x);
  for (int b = 2; b < 36; b++) {
    for (int x = 0; x < 1024; x++) {
      std::string s = from_dec(x, b), t = from_dec_bi(x, b);
      chk(s, t, b);
      int y = to_dec(s, b);
      assert(x == y);
    }
  }

  int x, base;
  std::cin >> x >> base;
  std::string s = from_dec(x, base);
  std::cout << s << '\n';
  std::string t = from_dec_bi(x, base);
  std::cout << t << '\n';
  std::string u = from_dec_factorial(x);
  std::cout << u << '\n';
  chk(s, t, base);
  int y = to_dec(s, base);
  std::cout << y << '\n';
  int z = to_dec_factorial(u);
  std::cout << z << '\n';
  return 0;
}
