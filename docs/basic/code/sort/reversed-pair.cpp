#include <bits/stdc++.h>
using namespace std;
long long ans = 0;
int n;
int a[900009], t[900009];

void merge(int ll, int rr) {
  if (ll == rr) {
    return;
  }
  int mid = (ll + rr) / 2, i = ll, j = mid + 1, k = ll;
  merge(ll, mid);
  merge(mid + 1, rr);
  while (i <= mid && j <= rr) {
    if (a[i] <= a[j]) {
      t[k++] = a[i++];
    } else {
      /*
      若要获得本轮产生的所有逆序对, 请去除此条注释.
      cout << a[j] << ':';
      for (int s = i; s <= mid; ++s) {
        cout << a[s] << ' ';
      }
      cout << endl;*/
      t[k++] = a[j++];
      ans += mid - i + 1;
    }
  }
  while (i <= mid) {
    t[k++] = a[i++];
  }
  while (j <= rr) {
    t[k++] = a[j++];
  }
  for (int l = ll; l <= rr; l++) {
    a[l] = t[l];
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }

  merge(1, n);

  cout << ans << endl;
}