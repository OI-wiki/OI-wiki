#include <iostream>

// --8<-- [start:core]
int a, mod, pow1[65536], pow2[65536];

void preproc() {
  pow1[0] = pow2[0] = 1;
  for (int i = 1; i < 65536; i++) pow1[i] = 1LL * pow1[i - 1] * a % mod;
  int pow65536 = 1LL * pow1[65535] * a % mod;
  for (int i = 1; i < 65536; i++) pow2[i] = 1LL * pow2[i - 1] * pow65536 % mod;
}

int query(int pows) {
  return 1LL * pow1[pows & 65535] * pow2[pows >> 16] % mod;
}

// --8<-- [end:core]
int pow(int a, int b, int mod) {
  int res = 1;
  for (; b; b >>= 1) {
    if (b & 1) res = 1LL * res * a % mod;
    a = 1LL * a * a % mod;
  }
  return res;
}

int main() {
  a = 3;
  mod = 1000000007;
  preproc();

  int tests[] = {0,     1,     2,      15,        65535,
                 65536, 65537, 100000, 123456789, (1LL << 31) - 1};

  bool succ = true;
  for (auto b : tests) {
    int fast = query(b);
    int slow = pow(a, b, mod);
    succ &= fast == slow;
  }
  std::cout << (succ ? "OK" : "Error") << std::endl;
}
