#include <cstring>
#include <iostream>
#include <string>
using namespace std;
constexpr int sqn = 1000;

// --8<-- [start:example14]
struct node {
  node* nxt;
  int size;
  char d[(sqn << 1) + 5];

  node() { size = 0, nxt = NULL, memset(d, 0, sizeof(d)); }

  void pb(char c) { d[size++] = c; }
};

// --8<-- [end:example14]
int main() {
  string s;
  cin >> s;
  node a;
  for (char c : s) a.pb(c);
  cout.write(a.d, a.size);
  cout << "\n";
}
