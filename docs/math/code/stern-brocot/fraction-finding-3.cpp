#include <iostream>
#include <tuple>
#include <vector>

// Locate a given fraction in the Stern-Brocot tree.
auto find(int x, int y) {
    std::vector<std::pair<int, char>> res;
    bool right = true;
    while (y) {
        res.emplace_back(x / y, right ? 'R' : 'L');
        x %= y;
        std::swap(x, y);
        right ^= 1;
    }
    --res.back().first;
    return res;
}

int main() {
    int x, y;
    std::cin >> x >> y;
    for (auto [t, ch] : find(x, y)) {
        for (; t; --t) {
            std::cout << ch;
        }
    }
    return 0;
}
