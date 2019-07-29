## 建立块状数组

块状数组，即把一个数组分为几个块，块内信息整体保存，若查询时遇到两边不完整的块直接暴力查询。一般情况下，块的长度为 $O(\sqrt{n})$ 。详细分析可以阅读 2017 年国家集训队论文中徐明宽的《非常规大小分块算法初探》。

下面直接给出一种建立块状数组的代码。

```cpp
num = sqrt(n);
for (int i = 1; i <= num; i++)
  st[i] = n / num * (i - 1) + 1, ed[i] = n / num * i;
ed[num] = n;
for (int i = 1; i <= num; i++) {
  for (int j = st[i]; j <= ed[i]; j++) {
    belong[j] = i;
  }
  size[i] = ed[i] - st[i] + 1;
}
```

其中 `st[i] ed[i]` 为块的起点和终点， `size[i]` 为块的大小。

## 保存与修改块内信息

### 例题 1：[教主的魔法](https://www.luogu.org/problemnew/show/P2801)

我们要询问一个块内大于等于一个数的数的个数，所以需要一个 `t` 数组对块内排序。对于整块的修改，使用类似于标记永久化的方式保存。时间复杂度 $O(n\sqrt{n}\times log_2{\sqrt{n}})$ 

```cpp
void Sort(int k) {
  for (int i = st[k]; i <= ed[k]; i++) t[i] = a[i];
  sort(t + st[k], t + ed[k] + 1);
}
void Modify(int l, int r, int c) {
  int x = belong[l], y = belong[r];
  if (x == y) {
    for (int i = l; i <= r; i++) a[i] += c;
    Sort(x);
    return;
  }
  for (int i = l; i <= ed[x]; i++) a[i] += c;
  for (int i = st[y]; i <= r; i++) a[i] += c;
  for (int i = x + 1; i < y; i++) dlt[i] += c;
  Sort(x);
  Sort(y);
}
int Answer(int l, int r, int c) {
  int ans = 0, x = belong[l], y = belong[r];
  if (x == y) {
    for (int i = l; i <= r; i++)
      if (a[i] + dlt[x] >= c) ans++;
    return ans;
  }
  for (int i = l; i <= ed[x]; i++)
    if (a[i] + dlt[x] >= c) ans++;
  for (int i = st[y]; i <= r; i++)
    if (a[i] + dlt[y] >= c) ans++;
  for (int i = x + 1; i <= y - 1; i++)
    ans += ed[i] - (lower_bound(t + st[i], t + ed[i] + 1, c - dlt[i]) - t) + 1;
  return ans;
}
```

### 例题 2：寒夜方舟

两种操作：

1.  区间 $[x,y]$ 每个数都变成 $z$ 
2. 查询区间 $[x,y]$ 内小于等于 $z$ 的数的个数

用 `dlt` 保存现在块内是否被整体赋值了。用一个值表示没有。对于边角块，查询前要 `pushdown` ，把块内存的信息下放到每一个数上。赋值之后记得重新 `sort` 一遍。其他方面同上题。

```cpp
void Sort(int k) {
  for (int i = st[k]; i <= ed[k]; i++) t[i] = a[i];
  sort(t + st[k], t + ed[k] + 1);
}
void PushDown(int x) {
  if (dlt[x] != 0x3f3f3f3f3f3f3f3fll)
    for (int i = st[x]; i <= ed[x]; i++) a[i] = t[i] = dlt[x];
  dlt[x] = 0x3f3f3f3f3f3f3f3fll;
}
void Modify(int l, int r, int c) {
  int x = belong[l], y = belong[r];
  PushDown(x);
  if (x == y) {
    for (int i = l; i <= r; i++) a[i] = c;
    Sort(x);
    return;
  }
  PushDown(y);
  for (int i = l; i <= ed[x]; i++) a[i] = c;
  for (int i = st[y]; i <= r; i++) a[i] = c;
  Sort(x);
  Sort(y);
  for (int i = x + 1; i < y; i++) dlt[i] = c;
}
int Binary_Search(int l, int r, int c) {
  int ans = l - 1, mid;
  while (l <= r) {
    mid = (l + r) / 2;
    if (t[mid] <= c)
      ans = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  return ans;
}
int Answer(int l, int r, int c) {
  int ans = 0, x = belong[l], y = belong[r];
  PushDown(x);
  if (x == y) {
    for (int i = l; i <= r; i++)
      if (a[i] <= c) ans++;
    return ans;
  }
  PushDown(y);
  for (int i = l; i <= ed[x]; i++)
    if (a[i] <= c) ans++;
  for (int i = st[y]; i <= r; i++)
    if (a[i] <= c) ans++;
  for (int i = x + 1; i <= y - 1; i++) {
    if (0x3f3f3f3f3f3f3f3fll == dlt[i])
      ans += Binary_Search(st[i], ed[i], c) - st[i] + 1;
    else if (dlt[i] <= c)
      ans += size[i];
  }
  return ans;
}
```

## 练习

1.  [单点修改，区间查询](https://loj.ac/problem/130)
2.  [区间修改，区间查询](https://loj.ac/problem/132)
3.  [【模板】线段树 2](https://www.luogu.org/problemnew/show/P3373)
4.  [\[Ynoi2019 模拟赛\]Yuno loves sqrt technology III](https://www.luogu.org/problemnew/show/P5048)
5.  [\[Violet\]蒲公英](https://www.luogu.org/problemnew/show/P4168)
6.  [作诗](https://www.luogu.org/problemnew/show/P4135)
