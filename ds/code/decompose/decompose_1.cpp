#include <cmath>
#include <iostream>
using namespace std;
int id[50005], len;
// id 表示块的编号, len=sqrt(n) , sqrt的时候时间复杂度最优
long long a[50005], b[50005], s[50005];

// a 数组表示数据数组, b 表示区间和, s 表示块长,因为块可能不是完整的所以要开数组
void add(int l, int r, long long x) {  // 区间加法
  int sid = id[l], eid = id[r];
  if (sid == eid) {  // 在一个块中
    for (int i = l; i <= r; i++) a[i] += x, s[sid] += x;
    return;
  }
  for (int i = l; id[i] == sid; i++) a[i] += x, s[sid] += x;
  for (int i = sid + 1; i < eid; i++)
    b[i] += x, s[i] += len * x;  // 更新区间和数组(完整的块)
  for (int i = r; id[i] == eid; i--) a[i] += x, s[eid] += x;
  // 以上两行不完整的块直接简单求和,就OK
}

long long query(int l, int r, long long p) {  // 区间查询
  int sid = id[l], eid = id[r];
  long long ans = 0;
  if (sid == eid) {  // 在一个块里直接暴力求和
    for (int i = l; i <= r; i++) ans = (ans + a[i] + b[sid]) % p;
    return ans;
  }
  for (int i = l; id[i] == sid; i++) ans = (ans + a[i] + b[sid]) % p;
  for (int i = sid + 1; i < eid; i++) ans = (ans + s[i]) % p;
  for (int i = r; id[i] == eid; i--) ans = (ans + a[i] + b[eid]) % p;
  // 和上面的区间修改是一个道理
  return ans;
}

int main() {
  int n;
  cin >> n;
  len = sqrt(n);  // 均值不等式可知复杂度最优为根号n
  for (int i = 1; i <= n; i++) {  // 题面要求
    cin >> a[i];
    id[i] = (i - 1) / len + 1;
    s[id[i]] += a[i];
  }
  for (int i = 1; i <= n; i++) {
    int op, l, r, c;
    cin >> op >> l >> r >> c;
    if (op == 0)
      add(l, r, c);
    else
      cout << query(l, r, c + 1) << endl;
  }
  return 0;
}

/*
https://loj.ac/s/1151495
 */