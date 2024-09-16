#include <iostream>
#define MAXN 1000

extern void insertion_sort(int* a, int n);

int main() {
    int a[MAXN];
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    insertion_sort(a, n);
    for (int i = 1; i <= n; ++i) {
        std::cout << a[i] << " ";
    }
}
