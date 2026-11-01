#include <cstring>
#include <iostream>
using namespace std;
constexpr int SZ = 100003;

// --8<-- [start:example68]
struct hash_map {  // 哈希表模板

  struct data {
    long long u;
    int v, nex;
  };  // 前向星结构

  data e[SZ << 1];  // SZ 是 const int 表示大小
  int h[SZ], cnt;

  int hash(long long u) { return (u % SZ + SZ) % SZ; }

  // 这里使用 (u % SZ + SZ) % SZ 而非 u % SZ 的原因是
  // C++ 中的 % 运算无法将负数转为正数

  int& operator[](long long u) {
    int hu = hash(u);  // 获取头指针
    for (int i = h[hu]; i; i = e[i].nex)
      if (e[i].u == u) return e[i].v;
    return e[++cnt] = data{u, -1, h[hu]}, h[hu] = cnt, e[cnt].v;
  }

  hash_map() {
    cnt = 0;
    memset(h, 0, sizeof(h));
  }
};

// --8<-- [end:example68]

hash_map table;

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
