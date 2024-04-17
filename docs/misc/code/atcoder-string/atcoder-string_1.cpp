#include <atcoder/string>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace atcoder;

int main() {
    static char buf[500'001];
    scanf("%s", buf);
    string s = buf;
    vector<int> sa = suffix_array(s);
    long long answer = 1LL * s.size() * (s.size() + 1) / 2;
    for (auto x : lcp_array(s, sa)) {
        answer -= x;
    }
    printf("%lld\n", answer);
    return 0;
}