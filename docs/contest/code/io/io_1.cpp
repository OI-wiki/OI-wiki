#include <cstdio>

// --8<-- [start:core]
// #define DEBUG 1  // 调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}

  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  // 调试，可显示字符
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }

  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }

  void read(int &x) {
    bool sign = false;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') sign = true;
    for (; isdigit(ch); ch = gc())
      x = x * 10 + (sign ? ('0' - ch) : (ch - '0'));
  }

  void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc());
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }

  void read(char &c) { for (c = gc(); blank(c); c = gc()); }

  void push(const char &c) {
#if DEBUG  // 调试，可显示字符
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }

  void write(int x) {
    unsigned int t = static_cast<unsigned int>(x);
    if (x < 0) t = -t, push('-');
    static int sta[40];
    int top = 0;
    do {
      sta[top++] = t % 10, t /= 10;
    } while (t);
    while (top) push(sta[--top] + '0');
  }

  void write(int x, char lastChar) { write(x), push(lastChar); }
} io;

// --8<-- [end:core]
int n, x, sum;

int main() {
  io.read(n);
  while (n--) {
    io.read(x);
    sum += x;
  }
  io.write(sum);
  return 0;
}
