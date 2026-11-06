#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <set>

// --8<-- [start:core]
struct trie {
  int nex[100000][26], cnt;
  bool exist[100000];  // 该结点结尾的字符串是否存在

  void insert(char *s, int l) {  // 插入字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) nex[p][c] = ++cnt;  // 如果没有，就添加结点
      p = nex[p][c];
    }
    exist[p] = true;
  }

  bool find(char *s, int l) {  // 查找字符串
    int p = 0;
    for (int i = 0; i < l; i++) {
      int c = s[i] - 'a';
      if (!nex[p][c]) return 0;
      p = nex[p][c];
    }
    return exist[p];
  }
};

// --8<-- [end:core]

trie dictionary;

int main() {
  int n, m;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;
    dictionary.insert(&s[0], s.size());
  }
  cin >> m;
  set<string> called;
  while (m--) {
    string s;
    cin >> s;
    if (!dictionary.find(&s[0], s.size()))
      cout << "WRONG\n";
    else if (!called.insert(s).second)
      cout << "REPEAT\n";
    else
      cout << "OK\n";
  }
}
