#include <cstdio>
#include <cstring>

constexpr int LEN = 1004, p = 10000;
int a[LEN], b[LEN], c[LEN];

void clear(int a[]) {
  for (int i = 0; i < LEN; ++i) a[i] = 0;
}

void read(int a[]) {
  char s[4001];
  scanf("%4000s", s);
  clear(a);
  int len = std::strlen(s);
  for (int i = 0; i < len; ++i) {
    int digit = s[len - 1 - i] - '0';
    int power = 1;
    for (int j = 0; j < i % 4; ++j) power *= 10;
    a[i / 4] += digit * power;
  }
}

void print(int a[]) {
  int i = LEN - 1;
  while (i > 0 && a[i] == 0) --i;
  printf("%d", a[i--]);
  while (i >= 0) printf("%04d", a[i--]);
  putchar('\n');
}

// --8<-- [start:core]
// 这里的 a,b,c 数组均为 p 进制下的数
// 最终输出答案时需要将数字转为十进制
void add(int a[], int b[], int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    c[i] += a[i] + b[i];
    if (c[i] >= p) {  // 在普通高精度运算下，p=10
      c[i + 1] += 1;
      c[i] -= p;
    }
  }
}

// --8<-- [end:core]

int main() {
  read(a);
  read(b);
  add(a, b, c);
  print(c);
}
