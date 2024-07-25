#include <iostream>

extern int division(int n1, int n2);

int main() {
    int n1, n2;
    std::cin >> n1 >> n2;
    std::cout << division(n1, n2);
    return 0;
}