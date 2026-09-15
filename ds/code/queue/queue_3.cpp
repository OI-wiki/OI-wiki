#include <iostream>
#include <stack>
#include <vector>
using namespace std;

const int M = 1000000 + 5;

struct Deque {
  // 将 stack 的底层容器从 deque 换为 vector 以减少空间常数
  stack<int, vector<int>> f, s;

  bool empty() { return f.empty() && s.empty(); }

  void push_back(int x) { f.push(x); }

  void push_front(int x) { s.push(x); }

  void balance() {
    // 平衡中需要辅助栈实现栈内元素倒置
    stack<int, vector<int>> t;
    if (s.empty()) {
      int n = f.size() / 2;
      for (; f.size() > n; f.pop()) t.push(f.top());
      for (; !t.empty(); t.pop()) s.push(t.top());
      for (; !f.empty(); f.pop()) t.push(f.top());
      f.swap(t);
      if (!f.empty()) s.swap(f);
    } else if (f.empty()) {
      int n = s.size() / 2;
      for (; s.size() > n; s.pop()) t.push(s.top());
      for (; !t.empty(); t.pop()) f.push(t.top());
      for (; !s.empty(); s.pop()) t.push(s.top());
      s.swap(t);
      if (!s.empty()) f.swap(s);
    }
  }

  void pop_front() {
    if (s.empty()) balance();
    s.pop();
  }

  void pop_back() {
    if (f.empty()) balance();
    f.pop();
  }

  int front() {
    if (s.empty()) balance();
    return s.top();
  }

  int back() {
    if (f.empty()) balance();
    return f.top();
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
