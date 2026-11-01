#include <cstdio>
#include <cstring>

constexpr int LEN = 1004;

int a[LEN], b[LEN], c[LEN];

void clear(int a[]) {
  for (int i = 0; i < LEN; ++i) a[i] = 0;
}

void read(int a[]) {
  static char s[LEN + 1];
  scanf("%s", s);

  clear(a);

  int len = strlen(s);
  for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
}

void print(int a[]) {
  int i;
  for (i = LEN - 1; i >= 1; --i)
    if (a[i] != 0) break;
  for (; i >= 0; --i) putchar(a[i] + '0');
  putchar('\n');
}

// --8<-- [start:core]
void mul_short(int a[], int b, int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // 直接把 a 的第 i 位数码乘以乘数，加入结果
    long long value = c[i] + 1LL * a[i] * b;
    c[i] = value % 10;
    c[i + 1] += value / 10;
  }
}

// --8<-- [end:core]

int main() {
  read(a);
  int multiplier;
  scanf("%d", &multiplier);
  mul_short(a, multiplier, c);
  print(c);
}
