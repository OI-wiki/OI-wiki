#include <cctype>
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

  void read(int &x) {
    bool neg = false;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') neg = true;
    if (neg)
      for (; isdigit(ch); ch = gc()) x = x * 10 + ('0' - ch);
    else
      for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
  }

  void read(char *s) {
    char ch = gc();
    for (; isspace(ch); ch = gc());
    for (; !isspace(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }

  void read(char &c) { for (c = gc(); isspace(c); c = gc()); }

  void push(const char &c) {
#if DEBUG  // 调试，可显示字符
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }

  void write(int x) {
    bool neg = false;
    if (x < 0) {
      neg = true;
      push('-');
    }
    static int sta[40];
    int top = 0;
    do {
      sta[top++] = x % 10;
      x /= 10;
    } while (x);
    if (neg)
      while (top) push('0' - sta[--top]);
    else
      while (top) push('0' + sta[--top]);
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
