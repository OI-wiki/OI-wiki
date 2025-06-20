#include <cstdio>

// --8<-- [start:core]
void read(int &x) {
  bool neg = false;
  x = 0;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') neg = true;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (neg ? ('0' - ch) : (ch - '0'));
    ch = getchar();
  }
}

void write(int x) {
  unsigned int t = static_cast<unsigned int>(x);
  if (x < 0) {
    t = -t;
    putchar('-');
  }
  static int sta[40];
  int top = 0;
  do {
    sta[top++] = t % 10;
    t /= 10;
  } while (t);
  while (top) putchar(sta[--top] + '0');
}

// --8<-- [end:core]
int n, x, sum;

int main() {
  read(n);
  while (n--) {
    read(x);
    sum += x;
  }
  write(sum);
  return 0;
}
