#include <iostream>
using namespace std;

// --8<-- [start:mod]
int modPowerOfTwo(int x, int mod) { return x & (mod - 1); }

// --8<-- [end:mod]
// --8<-- [start:power]
bool isPowerOfTwo(int n) { return n > 0 && (n & (n - 1)) == 0; }

// --8<-- [end:power]
int main() {
  int x, m;
  cin >> x >> m;
  cout << modPowerOfTwo(x, m) << " " << isPowerOfTwo(m) << "\n";
}
