#include<iostream>

int main() {
    char *str1 = "Hello";
    char *str2 = "Hello";
    if (str1 == str2) {
        std::cout << "Same" << std::endl;
    } else {
        std::cout << "Different" << std::endl;
    }
    // The C++ standard does not specify two string literals share the same address.
}