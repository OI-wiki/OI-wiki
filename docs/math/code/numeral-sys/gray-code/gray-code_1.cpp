#include <cassert>
#include <iostream>
using namespace std;

// --8<-- [start:forward]
int g(int n) { return n ^ (n >> 1); }

// --8<-- [end:forward]
// --8<-- [start:inverse]
int rev_g(int g) {
  int n = 0;
  for (; g; g >>= 1) n ^= g;
  return n;
}

// --8<-- [end:inverse]
int main() {
  int bits;
  cin >> bits;
  assert(bits >= 0 && bits <= 20);
  for (int i = 0; i < (1 << bits); ++i) {
    int code = g(i);
    assert(rev_g(code) == i);
    for (int j = bits - 1; j >= 0; --j) cout << ((code >> j) & 1);
    cout << (i + 1 == (1 << bits) ? '\n' : ' ');
  }
}
