#include<iostream>

int main() {
    int a = 1;
    std::cout << (++a = a+++ ++a) << std::endl;
    std::cout << a << std::endl;
    return 0;
}