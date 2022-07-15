int ans = 0;
int a[100005], c[100005];
void merge(int b, int e) {
  if (b == e) {
    return ;
  }
  int mid = (b + e) / 2, i = b, j = mid + 1, k = b;
  merge(b, mid);
  merge(mid + 1, e);
  while (i <= mid && j <= e) {
    if (a[i] <= a[j]) {
      c[k++] = a[i++];
    } else {
      cout << a[j] << ':' ;
      for (int s = i; s <= mid; ++s) {
        cout << a[s] << ' ' ;
      }
      cout << endl;
      c[k++] = a[j++];
      ans += mid - i + 1;
    }
  }
  while (i <= mid) {
    c[k++] = a[i++];
  }
  while (j <= e) {
    c[k++] = a[j++];
  }
  for (int l = b; l <= e; l++) {
    a[l] = c[l];
  }
}
