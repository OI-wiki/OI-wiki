#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <type_traits>

char *pc;

template <typename T>
typename std::enable_if<std::is_integral<T>::value && std::is_signed<T>::value>::type
rd(T &x) {
  bool neg = false;
  x = 0;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') neg = true;
    ch = *pc++;
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (neg ? ('0' - ch) : (ch - '0'));
    ch = *pc++;
  }
}

int main() {
  int fd = 0; // 从 stdin 读入
  // int fd = open("*.in", O_RDONLY); // 从文件读入
  struct stat state;
  fstat(fd, &state); // 获取文件大小
  pc = (char *)mmap(NULL, state.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
  int n, x, sum = 0;
  while (n--) {
    read(x);
    sum += x;
  }
  printf("%d\n", sum);
}
