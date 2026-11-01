#include <cstring>
#include <iostream>
using namespace std;
constexpr int SZ = 100003;
// --8<-- [start:example69]
constexpr int N = 360007;  // N 是最大可以存储的元素数量

class Hash {
 private:
  int keys[N];
  int values[N];

 public:
  Hash() { memset(values, 0, sizeof(values)); }

  int& operator[](int n) {
    // 返回一个指向对应 Hash[Key] 的引用
    // 修改成不为 0 的值 0 时候视为空
    int idx = (n % N + N) % N, cnt = 1;
    while (keys[idx] != n && values[idx] != 0) {
      idx = (idx + 1LL * cnt * cnt) % N;
      cnt += 1;
    }
    keys[idx] = n;
    return values[idx];
  }
};

// --8<-- [end:example69]

Hash table;

int main() {
  int q;
  std::cin >> q;
  while (q--) {
    int op, key, value;
    std::cin >> op >> key;
    if (op == 1) {
      std::cin >> value;
      table[key] = value;
    } else
      std::cout << table[key] << "\n";
  }
}
