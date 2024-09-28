#include <vector>

int n;
std::vector<int> a(1 << n);

std::vector<int> sos(int n, std::vector<int>& a) {
    // Copy.
    auto ps = a;
    // Loop over dimensions.
    for (int i = 0; i < n; ++i) {
        // Loop over i-th dimension.
        for (int st = 0; st < (1 << n); ++st) {
            // This condition implies that i-th dimension is 1.
            if ((st >> i) & 1) {
                // ps[... 1 ...] += ps[... 0 ...]. (i-th dimension)
                ps[st] += ps[st ^ (1 << i)];
            }
        }
    }
    return ps;
}
