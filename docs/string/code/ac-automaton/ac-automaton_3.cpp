#include <deque>
#include <iostream>

void promote() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  return;
}

typedef char chr;
typedef std::deque<int> dic;

const int maxN = 2e5;
const int maxS = 2e5;
const int maxT = 2e6;

int n;
chr s[maxS + 10];
chr t[maxT + 10];
int cnt[maxN + 10];

struct AhoCorasickAutomaton {
  struct Node {
    int son[30];
    int val;
    int fail;
    int head;
    dic index;
  } node[maxS + 10];

  struct Edge {
    int head;
    int next;
  } edge[maxS + 10];

  int root;
  int ncnt;
  int ecnt;

  void Insert(chr *str, int i) {
    int u = root;
    for (int i = 1; str[i]; i++) {
      if (node[u].son[str[i] - 'a' + 1] == 0)
        node[u].son[str[i] - 'a' + 1] = ++ncnt;
      u = node[u].son[str[i] - 'a' + 1];
    }
    node[u].index.push_back(i);
    return;
  }

  void Build() {
    dic q;
    for (int i = 1; i <= 26; i++)
      if (node[root].son[i]) q.push_back(node[root].son[i]);
    while (!q.empty()) {
      int u = q.front();
      q.pop_front();
      for (int i = 1; i <= 26; i++) {
        if (node[u].son[i]) {
          node[node[u].son[i]].fail = node[node[u].fail].son[i];
          q.push_back(node[u].son[i]);
        } else {
          node[u].son[i] = node[node[u].fail].son[i];
        }
      }
    }
    return;
  }

  void Query(chr *str) {
    int u = root;
    for (int i = 1; str[i]; i++) {
      u = node[u].son[str[i] - 'a' + 1];
      node[u].val++;
    }
    return;
  }

  void addEdge(int tail, int head) {
    ecnt++;
    edge[ecnt].head = head;
    edge[ecnt].next = node[tail].head;
    node[tail].head = ecnt;
    return;
  }

  void DFS(int u) {
    for (int e = node[u].head; e; e = edge[e].next) {
      int v = edge[e].head;
      DFS(v);
      node[u].val += node[v].val;
    }
    for (auto i : node[u].index) cnt[i] += node[u].val;
    return;
  }

  void FailTree() {
    for (int u = 1; u <= ncnt; u++) addEdge(node[u].fail, u);
    DFS(root);
    return;
  }
} ACM;

int main() {
  std::cin >> n;
  for (int i = 1; i <= n; i++) {
    std::cin >> (s + 1);
    ACM.Insert(s, i);
  }
  ACM.Build();
  std::cin >> (t + 1);
  ACM.Query(t);
  ACM.FailTree();
  for (int i = 1; i <= n; i++) std::cout << cnt[i] << '\n';
  return 0;
}