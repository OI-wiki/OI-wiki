#include <cstdint>
#include <iostream>

using u32 = uint32_t;
using u32ptr = u32*;

constexpr int MAXN = 1000;

extern void MSD_radix_sort(u32ptr first, u32ptr last);

u32 a[MAXN];

using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  MSD_radix_sort(a, a + n);
  for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];
  return 0;
}
