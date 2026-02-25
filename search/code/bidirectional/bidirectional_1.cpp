#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;

struct State {
  int A[3][3];
  State() = default;

  State(string s) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        A[i][j] = s[i * 3 + j] - '0';
      }
    }
  }

  friend bool operator<(const State &a, const State &b) {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (a.A[i][j] != b.A[i][j]) {
          return a.A[i][j] < b.A[i][j];
        }
      }
    }
    return false;
  }
};

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void bfs(queue<State> &q, map<State, int> &m1, map<State, int> &m2) {
  auto u = q.front();
  q.pop();
  int xx, yy;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (u.A[i][j] == 0) {
        xx = i;
        yy = j;
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    int tx = dir[i][0] + xx, ty = dir[i][1] + yy;
    if (tx >= 0 && tx < 3 && ty >= 0 && ty < 3) {
      auto v = u;
      swap(v.A[xx][yy], v.A[tx][ty]);
      if (m2.count(v)) {
        cout << m1[u] + m2[v] << endl;
        exit(0);
      }
      if (!m1.count(v)) {
        m1[v] = m1[u] + 1;
        q.push(v);
      }
    }
  }
}

int main() {
  string I, O;
  cin >> I;
  O = "123804765";
  State in = I, ou = O;
  queue<State> q1, q2;
  map<State, int> mp1, mp2;
  q1.push(in);
  mp1[in] = 0;
  q2.push(ou);
  mp2[ou] = 1;
  if (I == O) {
    cout << 0;
    return 0;
  }
  while (1) {
    bfs(q1, mp1, mp2);
    bfs(q2, mp2, mp1);
  }
  return 0;
}
