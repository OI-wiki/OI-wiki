#include <iostream>
#include <vector>
using namespace std;

const int M = 1000000 + 5;

struct Deque {
  // 这里使用 vector 来模拟栈以减少空间常数
  vector<int> f, s;

  bool empty() { return f.empty() && s.empty(); }

  void push_back(int x) { f.push_back(x); }

  void push_front(int x) { s.push_back(x); }

  void balance() {
    vector<int> t;
    if (s.empty()) {
      int n = f.size() / 2;
      for (; f.size() > n; f.pop_back()) t.push_back(f.back());
      for (; !t.empty(); t.pop_back()) s.push_back(t.back());
      for (; !f.empty(); f.pop_back()) t.push_back(f.back());
      f.swap(t);
      if (!f.empty()) s.swap(f);
    } else if (f.empty()) {
      int n = s.size() / 2;
      for (; s.size() > n; s.pop_back()) t.push_back(s.back());
      for (; !t.empty(); t.pop_back()) f.push_back(t.back());
      for (; !s.empty(); s.pop_back()) t.push_back(s.back());
      s.swap(t);
      if (!s.empty()) f.swap(s);
    }
  }

  void pop_front() {
    if (s.empty()) balance();
    s.pop_back();
  }

  void pop_back() {
    if (f.empty()) balance();
    f.pop_back();
  }

  int front() {
    if (s.empty()) balance();
    return s.back();
  }

  int back() {
    if (f.empty()) balance();
    return f.back();
  }

  int size() { return f.size() + s.size(); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<Deque> q(M);
  int n;
  cin >> n;
  while (n--) {
    string opt;
    int a;
    cin >> opt >> a;
    if (opt == "push_back") {
      int x;
      cin >> x;
      q[a].push_back(x);
    } else if (opt == "pop_back") {
      if (!q[a].empty()) q[a].pop_back();
    } else if (opt == "push_front") {
      int x;
      cin >> x;
      q[a].push_front(x);
    } else if (opt == "pop_front") {
      if (!q[a].empty()) q[a].pop_front();
    } else if (opt == "size")
      cout << q[a].size() << "\n";
    else if (opt == "front") {
      if (!q[a].empty()) cout << q[a].front() << "\n";
    } else {
      if (!q[a].empty()) cout << q[a].back() << "\n";
    }
  }
  return 0;
}
