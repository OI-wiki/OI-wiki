#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
struct f {
  long long d;
  long long x;
} a[100005];
bool cmp(f A, f B) { return A.d < B.d; }
priority_queue<long long, vector<long long>, greater<long long> >
    q;  //小根堆维护最小值

int main() {
  long long n, i, j;
  cin >> n;
  for (i = 1; i <= n; i++) {
    cin >> a[i].d >> a[i].x;
  }
  sort(a + 1, a + n + 1, cmp);
  long long ans = 0;
  for (i = 1; i <= n; i++) {
    if (a[i].d <= q.size()) {  //符合条件
      if (q.top() < a[i].x) {  //比较
        ans += a[i].x - q.top();
        q.pop();
        q.push(a[i].x);
      }
    } else {  //后悔
      ans += a[i].x;
      q.push(a[i].x);
    }
  }
  cout << ans << endl;
  return 0;
}
