#include <cstdio>
#include <stack>
using namespace std;

struct Queue {
  stack<int> f, s;

  bool empty() { return f.empty() && s.empty(); }

  void push(int x) { f.push(x); }

  void pop() {
    if (s.empty())
      for (; !f.empty(); f.pop()) s.push(f.top());
    s.pop();
  }

  int front() {
    if (s.empty())
      for (; !f.empty(); f.pop()) s.push(f.top());
    return s.top();
  }

  int size() { return f.size() + s.size(); }
};

int main() {
  Queue q;
  int n;
  scanf("%d", &n);
  while (n--) {
    int opt;
    scanf("%d", &opt);
    if (opt == 1) {
      int x;
      scanf("%d", &x);
      q.push(x);
    } else if (opt == 2) {
      if (q.empty())
        printf("ERR_CANNOT_POP\n");
      else
        q.pop();
    } else if (opt == 3) {
      if (q.empty())
        printf("ERR_CANNOT_QUERY\n");
      else
        printf("%d\n", q.front());
    } else
      printf("%d\n", q.size());
  }
  return 0;
}
