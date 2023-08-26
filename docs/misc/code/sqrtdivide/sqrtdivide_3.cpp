#include <algorithm>
#include <forward_list>
#include <iostream>
#include <utility>
#include <vector>

typedef unsigned int u32;

const u32 lbB = 8;
const u32 B = 1 << lbB;
const u32 MAXN = 50176;

u32 N, M;
u32 arr[MAXN] = {};
u32 color_cnt[MAXN] = {};
u32 high_index[MAXN] = {};
u32 highcnt = 0;
u32 high_prefix[B][MAXN] = {};
std::forward_list<u32> low_index[MAXN] = {};

u32 t[MAXN] = {}, ts[MAXN >> lbB] = {};

inline u32 CId(u32 index) { return index >> lbB; }

inline u32 st(u32 cid) { return cid << lbB; }

inline u32 ed(u32 cid) { return (cid + 1 << lbB) - 1; }

inline void update(u32 index) {
  ++t[index];
  ++ts[CId(index)];
}

inline u32 range_sum(u32 L, u32 R) {
  u32 res = 0;
  u32 cl = CId(L), cr = CId(R);
  if (cl == cr) {
    for (u32 idx = L; idx <= R; ++idx) res += t[idx];
    return res;
  }
  for (u32 idx = L; idx <= ed(cl); ++idx) res += t[idx];
  for (u32 idx = st(cr); idx <= R; ++idx) res += t[idx];
  for (u32 cid = cl + 1; cid < cr; ++cid) res += ts[cid];
  return res;
}

inline u32 count(const u32 n) { return (n - 1) * n >> 1; }

struct Query {
  u32 L, R, time, res;

  Query(const u32 _L, const u32 _R, const u32 t)
      : L(_L), R(_R), time(t), res(0) {}
};

inline u32 gcd(u32 a, u32 b) {
  while (b) {
    u32 aa = a;
    a = b;
    b = aa % b;
  }
  return a;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cin >> N >> M;
  for (u32 idx = 1; idx <= N; ++idx) {
    std::cin >> arr[idx];
    ++color_cnt[arr[idx]];
  }

  for (u32 clr = 1; clr <= N; ++clr) {
    if (color_cnt[clr] >= B) {
      high_index[clr] = highcnt++;
    }
  }

  for (u32 idx = 1; idx <= N; ++idx) {
    for (u32 hclr = 0; hclr < highcnt; ++hclr) {
      high_prefix[hclr][idx] = high_prefix[hclr][idx - 1];
    }
    if (color_cnt[arr[idx]] >= B) {
      ++high_prefix[high_index[arr[idx]]][idx];
    }
  }

  std::vector<Query> querys;
  for (u32 m = 1; m <= M; ++m) {
    u32 l, r;
    std::cin >> l >> r;
    querys.push_back(Query(l, r, m));
  }

  // Part I: color_cnt >= B
  for (auto it = querys.begin(); it != querys.end(); ++it) {
    for (u32 hclr = 0; hclr < highcnt; ++hclr) {
      it->res += count(high_prefix[hclr][it->R] - high_prefix[hclr][it->L - 1]);
    }
  }

  // Part II: color_cnt < B
  std::sort(querys.begin(), querys.end(),
            [](const Query &lhs, const Query &rhs) { return lhs.R < rhs.R; });

  auto qit = querys.begin();
  for (u32 idx = 1; idx <= N; ++idx) {
    if (color_cnt[arr[idx]] < B) {
      for (auto lit = low_index[arr[idx]].begin();
           lit != low_index[arr[idx]].end(); ++lit) {
        update(*lit);
      }
      low_index[arr[idx]].push_front(idx);
    }
    while (qit != querys.end() && qit->R == idx) {
      qit->res += range_sum(qit->L, qit->R);
      ++qit;
    }
  }

  // perpare for output
  std::sort(
      querys.begin(), querys.end(),
      [](const Query &lhs, const Query &rhs) { return lhs.time < rhs.time; });

  for (auto it = querys.begin(); it != querys.end(); ++it) {
    if (it->L == it->R) {
      std::cout << "0/1" << std::endl;
      continue;
    }
    u32 dn = count(it->R + 1 - it->L);
    u32 up = it->res;
    u32 g = gcd(up, dn);
    std::cout << up / g << "/" << (up ? dn / g : 1) << std::endl;
  }

  return 0;
}