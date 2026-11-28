// --8<-- [start:core]
// From <https://stackoverflow.com/a/776523/224132>
#include <climits>
#include <cstdint>

uint32_t rotl32(uint32_t value, unsigned int count) {
  const unsigned int mask = CHAR_BIT * sizeof(value) - 1;
  count &= mask;
  return (value << count) | (value >> (-count & mask));
}

uint32_t rotr32(uint32_t value, unsigned int count) {
  const unsigned int mask = CHAR_BIT * sizeof(value) - 1;
  count &= mask;
  return (value >> count) | (value << (-count & mask));
}

// --8<-- [end:core]

#include <iostream>

int main() {
  uint32_t a;
  unsigned b;
  std::cin >> a >> b;
  std::cout << rotl32(a, b) << '\n';
  std::cout << rotr32(a, b) << '\n';
}
