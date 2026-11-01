#include <cstdio>
constexpr int prime[] = {2,  3,  4,  5,  7,  9,  11, 13, 17, 19,
                         23, 25, 29, 31, 37, 41, 43, 47, 49};
int cnt = 0;
char res[5];

int main() {
  for (int i : prime) {
    printf("%d\n", i);
    fflush(stdout);
    scanf("%s", res);
    if (res[0] == 'y' && ++cnt == 2) return printf("composite"), 0;
  }
  printf("prime");
  return 0;
}
