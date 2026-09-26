#include <cstdio>
using namespace std;

const int SIZE = 10000 + 5;

struct Queue {
  int q[SIZE], ql, qr;

  Queue() : ql(1), qr(0) {}

  bool empty() { return ql > qr; }

  void push(int x) { q[++qr] = x; }

  void pop() { ++ql; }

  int front() { return q[ql]; }

  int back() { return q[qr]; }

  int size() { return qr - ql + 1; }

  int clear() {
    ql = 1;
    qr = 0;
  }
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
