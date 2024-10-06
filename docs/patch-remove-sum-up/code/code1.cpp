#include<iostream>

int main() {
    int *ptr = NULL;
    *ptr = 10; // Produce RE
    std::cout << *ptr << std::endl;
    return 0;
}